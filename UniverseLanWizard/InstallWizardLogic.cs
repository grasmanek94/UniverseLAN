
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace UniverseLanWizard
{
    internal class InstallWizardLogic
    {
        private List<InstallWizardAction> Actions;
        private GalaxyBinaryCompatibilityMatrix CompatibilityMatrix;

        public InstallWizardLogic(GalaxyBinaryCompatibilityMatrix compatibility_matrix)
        {
            CompatibilityMatrix = compatibility_matrix;
        }

        private void ParseGalaxyDLLInfo(GalaxyGameScanner scanner)
        {
            var galaxy_dll_files = scanner.GetFoundGalaxyDLLs(); // for each DLL file add steps:
            foreach (var galaxy_dll_entry in galaxy_dll_files)
            {
                string file_path = galaxy_dll_entry.Key;
                string bare_file_name = Path.GetFileName(file_path); // which DLL file exactly

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

                // 2) Get correct UVLan version and place it at the location
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
            }
        }

        public void ParseInfo(GalaxyGameScanner scanner)
        {
            Actions = new List<InstallWizardAction>();
            ParseGalaxyDLLInfo(scanner);

        }
    }
}
