using MS.WindowsAPICodePack.Internal;
using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;

namespace UniverseLanWizard
{
    internal class InstallWizardLogic
    {
        public List<InstallWizardAction> Actions { get; private set; }
        private GalaxyBinaryCompatibilityMatrix CompatibilityMatrix;
        public bool IsUnityGameDetected { get; private set; }
        public bool IsUnrealEngineGameDetected { get; private set; }
        public bool Has32Bit { get; private set; }
        public bool Has64Bit { get; private set; }
        private List<string> DownloadedFiles;
        private List<string> UniverseLANTargets;

        public InstallWizardLogic(GalaxyBinaryCompatibilityMatrix compatibility_matrix)
        {
            CompatibilityMatrix = compatibility_matrix;
        }

        public void ParseInfo(GalaxyGameScanner scanner)
        {
            Actions = new List<InstallWizardAction>();
            DownloadedFiles = new List<string>();
            UniverseLANTargets = new List<string>();
            IsUnityGameDetected = false;
            IsUnrealEngineGameDetected = false;
            Has32Bit = false;
            Has64Bit = false;

            ParseMetaInfo(scanner);
            ParseGalaxyDLLInfo(scanner);

            if(IsUnityGameDetected)
            {
                ParseUnityInfo(scanner);
            }
            else if(IsUnrealEngineGameDetected)
            {

            }
            else
            {

            }
        }

        private void UnpackZIPResults(string destination_path, IEnumerable<ZipArchiveEntry> entries)
        {
            foreach (ZipArchiveEntry entry in entries)
            {
                string path = Path.Combine(destination_path, entry.FullName);
                entry.ExtractToFile(path);
            }
        }

        private void UnpackUniverseLANFiles(ZipArchive archive, string destination_path)
        {
            UnpackZIPResults(destination_path, from curr in archive.Entries
                                               where Path.GetDirectoryName(curr.FullName) == "UniverseLANData"
                                               where !string.IsNullOrEmpty(curr.Name)
                                               select curr);

            UnpackZIPResults(destination_path, from curr in archive.Entries
                                               where Path.GetDirectoryName(curr.FullName) == "UniverseLANServerData"
                                               where !string.IsNullOrEmpty(curr.Name)
                                               select curr);

            UnpackZIPResults(destination_path, from curr in archive.Entries
                                               where curr.FullName == "UniverseLAN.ini"
                                               where !string.IsNullOrEmpty(curr.Name)
                                               select curr);

            if (Has32Bit)
            {
                UnpackZIPResults(destination_path, from curr in archive.Entries
                                                   where curr.FullName == "UniverseLANServer.exe"
                                                   where !string.IsNullOrEmpty(curr.Name)
                                                   select curr);
            }

            if(Has64Bit)
            {
                UnpackZIPResults(destination_path, from curr in archive.Entries
                                                   where curr.FullName == "UniverseLANServer64.exe"
                                                   where !string.IsNullOrEmpty(curr.Name)
                                                   select curr);
            }
        }

        private void RemoveUniverseLANFiles(string destination_path)
        {
            string UniverseLANData = Path.Combine(destination_path, "\\UniverseLANData\\");
            string UniverseLANServerData = Path.Combine(destination_path, "\\UniverseLANServerData\\");
            string UniverseLANIni = Path.Combine(destination_path, "\\UniverseLAN.ini");
            string UniverseLANServerx86 = Path.Combine(destination_path, "\\UniverseLANServer.exe");
            string UniverseLANServerx64 = Path.Combine(destination_path, "\\UniverseLANServer64.exe");

            Directory.Delete(UniverseLANData, true);
            Directory.Delete(UniverseLANServerData, true);
            File.Delete(UniverseLANIni);
            File.Delete(UniverseLANServerx86);
            File.Delete(UniverseLANServerx64);
        }

        private string GetServerExecutables()
        {
            string server_executables = "";

            if (Has32Bit)
            {
                server_executables = "UniverseLANServer.exe";
            }

            if (Has64Bit)
            {
                if (server_executables.Length > 0)
                {
                    server_executables += ",";
                }

                server_executables += "UniverseLANServer64.exe";
            }

            return server_executables;
        }

        private void ParseUnityInfo(GalaxyGameScanner scanner)
        {
            if(DownloadedFiles.Count < 1)
            {
                return;
            }

            var dlls = scanner.GetFoundDLLFiles();
            foreach (var dll in dlls)
            {
                string file_name = Path.GetFileName(dll).ToLower();
                if (file_name.Equals("Assembly-CSharp.dll", StringComparison.OrdinalIgnoreCase) && dll.Contains("_Data", StringComparison.OrdinalIgnoreCase))
                {
                    string dir = Path.GetDirectoryName(dll);
                    string game_root_path_relative = Path.Combine(dir, "..\\..\\");
                    string game_root_path = Path.GetFullPath(game_root_path_relative);

                    if (!UniverseLANTargets.Contains(game_root_path))
                    {
                        UniverseLANTargets.Add(game_root_path);
                        string temp_asset_file = DownloadedFiles.First();

                        // 3) extract UniverseLAN files
                        Actions.Add(new InstallWizardAction(
                            () =>
                            {
                                using (ZipArchive archive = ZipFile.OpenRead(temp_asset_file))
                                {
                                    UnpackUniverseLANFiles(archive, game_root_path);
                                }
                                return true;
                            },

                            () =>
                            {
                                RemoveUniverseLANFiles(game_root_path);

                                return true;
                            },

                            string.Format(
                                "Extract \"{0}\\[UniverseLANData,UniverseLANServerData,UniverseLAN.ini,{1}]\" to \"{2}\"",
                                temp_asset_file,
                                GetServerExecutables(),
                                game_root_path
                            )
                        ));
                    }
                }
            }
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
                        "Rename \"{0}\" ({2}-{3}) to \"{1}\"",
                        file_path,
                        file_path + ".uvlan.bak",
                        version_info.version,
                        version_info.bits.ToString()
                    )
                ));

                // 2) Get correct UVLan version
                Uri asset_url = CompatibilityMatrix.TryGetBinaryCompatibleAssetUrl(version_info.version, version_info.bits);
                if (asset_url == null)
                {
                    throw new UnsupportedGalaxyVersionException(string.Format("{0}-{1}", version_info.version, version_info.bits.ToString()));
                }

                Has32Bit |= (version_info.bits == Bitness.x86);
                Has64Bit |= (version_info.bits == Bitness.x64);

                string temp_asset_file = Path.Combine(Path.GetTempPath(), asset_url.Segments.Last());

                if (!DownloadedFiles.Contains(temp_asset_file))
                {
                    DownloadedFiles.Add(temp_asset_file);
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
                }

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
