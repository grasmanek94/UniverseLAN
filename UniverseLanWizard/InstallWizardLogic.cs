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

        public InstallWizardLogic(GalaxyBinaryCompatibilityMatrix compatibility_matrix)
        {
            CompatibilityMatrix = compatibility_matrix;
        }

        public void ParseInfo(GalaxyGameScanner scanner)
        {
            Actions = new List<InstallWizardAction>();
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
    }
}
