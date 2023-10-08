using System.IO;
using System.Linq;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;
using System;
using System.Diagnostics;

namespace UniverseLanWizard
{
    internal class DLLHashDatabase
    {
        private List<DLLHashEntry> DLLHashEntries = new List<DLLHashEntry>();
        private Dictionary<long, Dictionary<string, DLLHashEntry>> DLLSizeToEntries = new Dictionary<long, Dictionary<string, DLLHashEntry>>();
        private SHA1Managed SHA1 = new SHA1Managed();

        public DLLHashDatabase(){}

        public void LoadFile(string hash_db_filename) {
            LoadString(File.ReadAllText(hash_db_filename));
        }

        public void LoadString(string str)
        {
            // Read the file in format 'hash=version_other_stuff_etc|filesize
            List<string> lines = str.Split('\n').ToList();

            // Split the above format into 'DLLHashEntry'-s
            var delimeters = new char[] { '=', '|', '_' };
            foreach (string line in lines)
            {
                var data = line.Split(delimeters);
                var entry = new DLLHashEntry();

                entry.hash = data[0];
                entry.version = data[1];
                entry.size = long.Parse(data.Last());
                switch(data[4])
                {
                    case "32bit":
                        entry.bits = Bitness.x86;
                        break;

                    case "64bit":
                        entry.bits = Bitness.x64;
                        break;

                    default:
                        throw new UnknownBitnessException(data[4]);
                }

                DLLHashEntries.Add(entry);
            }

            foreach (var entry in DLLHashEntries)
            {
                Dictionary<string, DLLHashEntry> local_entries;
                if (!DLLSizeToEntries.TryGetValue(entry.size, out local_entries))
                {
                    local_entries = new Dictionary<string, DLLHashEntry>();
                    DLLSizeToEntries.Add(entry.size, local_entries);
                }

                local_entries.Add(entry.hash.Trim().ToLower(), entry);
            }
        }

        private string GetHash(string filename)
        {
            byte[] hash = SHA1.ComputeHash(File.ReadAllBytes(filename));
            StringBuilder formatted = new StringBuilder(2 * hash.Length);
            foreach (byte b in hash)
            {
                formatted.AppendFormat("{0:x2}", b);
            }

            return formatted.ToString().Trim().ToLower();
        }

        private enum MachineType
        {
            Native = 0, I386 = 0x014c, Itanium = 0x0200, x64 = 0x8664
        }

        private static MachineType GetMachineType(string filename)
        {
            const int PE_POINTER_OFFSET = 60;
            const int MACHINE_OFFSET = 4;
            byte[] data = new byte[4096];
            using (Stream s = new FileStream(filename, FileMode.Open, FileAccess.Read))
            {
                s.Read(data, 0, 4096);
            }
            // dos header is 64 bytes, last element, long (4 bytes) is the address of the PE header
            int PE_HEADER_ADDR = BitConverter.ToInt32(data, PE_POINTER_OFFSET);
            int machineUint = BitConverter.ToUInt16(data, PE_HEADER_ADDR + MACHINE_OFFSET);
            return (MachineType)machineUint;
        }

        // fallback
        private DLLHashEntry GetFileVersionUnknownEntry(string filename)
        {
            FileVersionInfo version_info = FileVersionInfo.GetVersionInfo(filename);

            string version = String.Format("{0}.{1}.{2}",
                version_info.ProductMajorPart,
                version_info.ProductMinorPart,
                version_info.ProductBuildPart
            );

            if (!version_info.ProductName.Contains("GOG") ||
                !version_info.ProductName.Contains("Galaxy") ||
                !version_info.OriginalFilename.Contains("Galaxy") ||
                !version_info.FileDescription.Contains("GOG") ||
                !version_info.FileDescription.Contains("Galaxy") ||
                !version_info.FileDescription.Contains("Library") ||
                version.Equals("0.0.0"))
            {
                throw new CannotDetermineGalaxyVersionException();
            }

            DLLHashEntry entry = new DLLHashEntry();
            entry.hash = GetHash(filename);
            entry.version = version;
            entry.size = new FileInfo(filename).Length;

            var type = GetMachineType(filename);
            switch (type)
            {
                case MachineType.I386:
                    entry.bits = Bitness.x86;
                    break;

                case MachineType.x64:
                    entry.bits = Bitness.x64;
                    break;

                default:
                    throw new UnknownBitnessException(type.ToString());
            }   

            return entry;
        }

        public DLLHashEntry GetFileVersion(string filename)
        {
            FileInfo fi = new FileInfo(filename);

            if (!fi.Exists)
            {
                throw new FileNotFoundException();
            }

            Dictionary<string, DLLHashEntry> local_entries;
            if (!DLLSizeToEntries.TryGetValue(fi.Length, out local_entries))
            {
                return GetFileVersionUnknownEntry(filename);
            }

            DLLHashEntry data;
            if(local_entries.TryGetValue(GetHash(filename), out data))
            {
                return data;
            }

            return GetFileVersionUnknownEntry(filename);
        }
    }
}
