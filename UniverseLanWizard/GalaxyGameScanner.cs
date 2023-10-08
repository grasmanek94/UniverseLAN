using System.IO;
using System.Linq;
using System;
using System.Collections.Generic;

namespace UniverseLanWizard
{
    internal class GalaxyGameScanner
    {
        public delegate void OnScanEvent(GalaxyGameScanner sender);
        public delegate void OnScanEventUpdate(GalaxyGameScanner sender, int files_processed);
        public delegate void OnScanEventDLLFound(GalaxyGameScanner sender, string file, DLLHashEntry version_info);

        public event OnScanEvent OnScanStarted;
        public event OnScanEvent OnScanFinished;
        public event OnScanEventUpdate OnScanUpdate;
        public event OnScanEventDLLFound OnScanDLLFound;

        public string CurrentScanDirectory { get; private set; }
        public int CurrentFilesProcessedCount { get; private set; }

        private DLLHashDatabase HashDatabase;
        private Dictionary<string, DLLHashEntry> DLLHashEntries;
        private Dictionary<string, List<string>> OtherEntries;

        private string[] DLLFileNameFilter = new string[]
        {
            "Galaxy.dll",
            "Galaxy64.dll",
            "REDGalaxy.dll",
            "REDGalaxy64.dll"
        };

        private string[] OtherExtensionFilters = new string[]
        {
            ".info",
            ".exe",
            ".dll"
        };

        public GalaxyGameScanner(DLLHashDatabase database)
        {
            if (database == null)
            {
                throw new ArgumentNullException(nameof(database));
            }

            HashDatabase = database;
        }

        public void Scan(string directory, bool force_scan_all_files = false)
        {
            CurrentScanDirectory = directory;
            DLLHashEntries = new Dictionary<string, DLLHashEntry>();
            OtherEntries = new Dictionary<string, List<string>>();
            foreach(string extension in OtherExtensionFilters)
            {
                OtherEntries[extension] = new List<string>();
            }

            CurrentFilesProcessedCount = 0;

            OnScanStarted(this);

            try
            {
                var all_files = Directory.EnumerateFiles(directory, "*", new EnumerationOptions
                { 
                    IgnoreInaccessible = true,
                    RecurseSubdirectories = true
                });

                foreach (string current_file in all_files)
                {
                    bool is_galaxy_dll = DLLFileNameFilter.Contains(Path.GetFileName(current_file), StringComparer.OrdinalIgnoreCase);
                    if (force_scan_all_files || is_galaxy_dll)
                    {
                        try
                        {
                            DLLHashEntry entry = HashDatabase.GetFileVersion(current_file);
                            DLLHashEntries.Add(current_file, entry);
                            OnScanDLLFound(this, current_file, entry);
                        }
                        catch (Exception ex)
                        when (ex is CannotDetermineGalaxyVersionException || ex is UnknownBitnessException)
                        {
                            // ignore
                        }
                    }
                    
                    if (!is_galaxy_dll && OtherEntries.ContainsKey(Path.GetExtension(current_file).ToLower()))
                    {
                        OtherEntries[Path.GetExtension(current_file).ToLower()].Add(current_file);
                    }

                    OnScanUpdate(this, ++CurrentFilesProcessedCount);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            finally { OnScanFinished(this); }
        }

        public Dictionary<string, DLLHashEntry> GetFoundGalaxyDLLs()
        {
            // Shallow clone
            return DLLHashEntries.ToDictionary(entry => entry.Key,
                                               entry => entry.Value);
        }

        public List<string> GetFoundExecutables()
        {
            // Shallow clone
            return OtherEntries[".exe"].ToList();
        }

        public List<string> GetFoundInfoFiles()
        {
            // Shallow clone
            return OtherEntries[".info"].ToList();
        }

        public List<string> GetFoundDLLFiles()
        {
            // Shallow clone
            return OtherEntries[".dll"].ToList();
        }

        public int GetFoundGalaxyDLLsCount()
        {
            return DLLHashEntries?.Count ?? 0;
        }
    }
}
