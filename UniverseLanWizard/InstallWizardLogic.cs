using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Runtime.InteropServices;

namespace UniverseLanWizard
{
    internal class InstallWizardLogic
    {
        public List<InstallWizardAction> Actions { get; private set; }
        private GalaxyBinaryCompatibilityMatrix CompatibilityMatrix;
        public bool IsUnityGameDetected { get; private set; }
        public bool IsUnrealEngineGameDetected { get; private set; }

        public InstallWizardLogic(GalaxyBinaryCompatibilityMatrix compatibility_matrix)
        {
            CompatibilityMatrix = compatibility_matrix;
        }

        public void ParseInfo(GalaxyGameScanner scanner)
        {
            Actions = new List<InstallWizardAction>();
            IsUnityGameDetected = false;
            IsUnrealEngineGameDetected = false;

            ParseMetaInfo(scanner);
            ParseGalaxyDLLInfo(scanner);
        }

        private void ParseGalaxyDLLInfo(GalaxyGameScanner scanner)
        {
            var galaxy_dll_files = scanner.GetFoundGalaxyDLLs(); // for each DLL file add steps:
            foreach (var galaxy_dll_entry in galaxy_dll_files)
            {
                string file_path = galaxy_dll_entry.Key;
                string galaxy_dll_file_name = Path.GetFileName(file_path); // which DLL file exactly

                DLLHashEntry version_info = galaxy_dll_entry.Value;

                // 1) Rename DLL file to <name>.uvlan.bak
                Actions.Add(new InstallWizardAction(
                    () =>
                    {
                        File.Move(file_path, file_path + ".uvlan.bak");
                        return true;
                    },

                    () =>
                    {
                        File.Move(file_path + ".uvlan.bak", file_path);
                        return true;
                    },

                    string.Format(
                        "Rename \"{0}\" to \"{1}\"",
                        file_path,
                        file_path + ".uvlan.bak"
                    )
                ));

                // 2) Get correct UVLan version
                Uri asset_url = CompatibilityMatrix.TryGetBinaryCompatibleAssetUrl(version_info.version, version_info.bits);
                if (asset_url == null)
                {
                    throw new UnsupportedGalaxyVersionException(string.Format("{0}-{1}", version_info.version, version_info.bits.ToString()));
                }
                string temp_asset_file = Path.Combine(Path.GetTempPath(), asset_url.Segments.Last());

                Actions.Add(new InstallWizardAction(
                    () =>
                    {
                        SimpleFileDownloader.DownloadFile(asset_url, temp_asset_file);
                        return true;
                    },

                    () =>
                    {
                        File.Delete(temp_asset_file);
                        return true;
                    },

                    string.Format(
                        "Download \"{0}\" to \"{1}\"",
                        asset_url.ToString(),
                        temp_asset_file
                    ),

                    // cleanup
                    () =>
                    {
                        File.Delete(temp_asset_file);
                        return true;
                    }
                ));

                // 3) extract correct DLL to the old DLL location
                Actions.Add(new InstallWizardAction(
                    () =>
                    {
                        using (ZipArchive archive = ZipFile.OpenRead(temp_asset_file))
                        {
                            foreach (ZipArchiveEntry entry in archive.Entries)
                            {
                                if (entry.FullName.Equals(galaxy_dll_file_name, StringComparison.OrdinalIgnoreCase))
                                {
                                    entry.ExtractToFile(file_path);
                                }
                            }
                        }
                        return true;
                    },

                    () =>
                    {
                        File.Delete(file_path);
                        return true;
                    },

                    string.Format(
                        "Extract \"{0}\\{1}\" to \"{2}\"",
                        temp_asset_file,
                        galaxy_dll_file_name,
                        file_path
                    )
                ));
            }
        }

        // only finds simple ascii matches
        private bool FindInFile(string file_path, string match)
        {
            if(match.Length < 1)
            {
                return true;
            }

            int current_match = 0;

            using (StreamReader sr = new StreamReader(file_path, System.Text.Encoding.ASCII))
            {
                while (!sr.EndOfStream)
                {
                    char c = (char)sr.Read();
                    
                    // ToLower
                    if (c >= 'A' && c <= 'Z')
                    {
                        c += (char)32;
                    }

                    if (match[current_match] == c)
                    {
                        if (++current_match == match.Length)
                        {
                            return true;
                        }
                    }
                    else if(current_match != 0)
                    {
                        current_match = 0;
                        if (match[current_match] == c)
                        {
                            ++current_match;
                        }
                    }
                }
            }

            return false;
        }

        private void ParseMetaInfo(GalaxyGameScanner scanner)
        {
            var dlls = scanner.GetFoundDLLFiles();

            // Unity
            bool unity_found_unity_engine_dll = false;
            bool unity_found_assembly_csharp_dll = false;

            // unreal engine
            bool unreal_engine_str_found = false;

            foreach (var dll in dlls)
            {
                string file_name = Path.GetFileName(dll).ToLower();
                switch(file_name)
                {
                    case "unityengine.dll":
                        unity_found_unity_engine_dll = true;
                        break;

                    case "assembly-csharp.dll":
                        unity_found_assembly_csharp_dll = true;
                        break;
                }


            }

            var exes = scanner.GetFoundExecutables();
            foreach (var exe in exes)
            {
                string file_name = Path.GetFileName(exe).ToLower();

                if (!unreal_engine_str_found && file_name.EndsWith("-shipping.exe"))
                {
                    unreal_engine_str_found = FindInFile(exe, "unrealtype.h");
                }
            }

            IsUnityGameDetected = unity_found_unity_engine_dll && unity_found_assembly_csharp_dll;
            IsUnrealEngineGameDetected = unreal_engine_str_found;

            if(IsUnityGameDetected)
            {
                Actions.Add(new InstallWizardAction(() => { return true; }, () => { return true; }, "Detected Unity game"));
            }

            if (IsUnrealEngineGameDetected)
            {
                Actions.Add(new InstallWizardAction(() => { return true; }, () => { return true; }, "Detected Unreal Engine game"));
            }
        }
    }
}
