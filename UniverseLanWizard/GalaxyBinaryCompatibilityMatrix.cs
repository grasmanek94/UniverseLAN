using System;
using System.Collections.Generic;
using System.Linq;

namespace UniverseLanWizard
{
    internal class GalaxyBinaryCompatibilityMatrix
    {
        private static string[][] VersionsMatrix = new string[][] {
            new string[] {"1.57"},
            new string[] {"1.59", "1.60"},
            new string[] {"1.61"},
            new string[] {"1.62", "1.63", "1.64"},
            new string[] {"1.65", "1.66"},
            new string[] {"1.67"},
            new string[] {"1.68"},
            new string[] {"1.69"},
            new string[] {"1.70"},
            new string[] {"1.71", "1.72"},
            new string[] {"1.73"},
            new string[] {"1.74"},
            new string[] {"1.75"},
            new string[] {"1.76"},
            new string[] {"1.77"},
            new string[] {"1.78", "1.79", "1.80"},
            new string[] {"1.82"},
            new string[] {"1.83"},
            new string[] {"1.84", "1.85", "1.86"},
            new string[] {"1.87"},
            new string[] {"1.88", "1.89", "1.90"},
            new string[] {"1.91", "1.92"},
            new string[] {"1.92.1", "1.93", "1.94", "1.95", "1.96", "1.97", "1.98"},
            new string[] {"1.99"},
            new string[] {"1.100", "1.100.2", "1.101", "1.101.2", "1.101.4"},
            new string[] {"1.102"},
            new string[] {"1.103", "1.103.1", "1.104", "1.104.1", "1.104.2"},
            new string[] {"1.104.3"},
            new string[] {"1.104.4", "1.104.5", "1.104.6", "1.105"},
            new string[] {"1.106", "1.107", "1.108"},
            new string[] {"1.109"},
            new string[] {"1.110", "1.110.1", "1.110.2", "1.110.3"},
            new string[] {"1.110.4", "1.111", "1.111.2", "1.112", "1.112.1", "1.112.2"},
            new string[] {"1.113"},
            new string[] {"1.113.2"},
            new string[] {"1.113.3"},
            new string[] {"1.114", "1.114.1", "1.114.2", "1.114.3", "1.114.4", "1.114.6", "1.114.7"},
            new string[] {"1.114.8", "1.114.9", "1.114.12"},
            new string[] {"1.120"},
            new string[] {"1.120.1", "1.121", "1.121.1", "1.121.2"},
            new string[] {"1.122", "1.122.1", "1.122.3", "1.122.4", "1.123", "1.123.1", "1.124"},
            new string[] {"1.125", "1.125.1", "1.125.2"},
            new string[] {"1.126", "1.126.1"},
            new string[] {"1.127"},
            new string[] {"1.128", "1.128.1", "1.128.2", "1.128.3"},
            new string[] {"1.129", "1.130", "1.130.1"},
            new string[] {"1.131", "1.131.1", "1.131.2", "1.131.3"},
            new string[] {"1.132", "1.132.1"},
            new string[] {"1.133"},
            new string[] {"1.133.1"},
            new string[] {"1.133.3", "1.133.4", "1.133.5", "1.133.6", "1.133.7", "1.133.9"},
            new string[] {"1.134", "1.134.1", "1.134.2", "1.134.3", "1.134.4", "1.134.5", "1.134.6", "1.134.7", "1.134.8"},
            new string[] {"1.134.9"},
            new string[] {"1.134.10"},
            new string[] {"1.135"},
            new string[] {"1.136", "1.136.4", "1.137", "1.137.1", "1.137.2", "1.137.3", "1.137.4", "1.137.5", "1.137.6", "1.138"},
            new string[] {"1.138.1", "1.139", "1.139.1", "1.139.2", "1.139.3", "1.139.4"},
            new string[] {"1.139.5"},
            new string[] {"1.139.6"},
            new string[] {"1.139.7", "1.139.8", "1.139.9"},
            new string[] {"1.140"},
            new string[] {"1.141", "1.142"},
            new string[] {"1.143", "1.143.1", "1.143.2", "1.143.3", "1.144", "1.144.1", "1.144.2", "1.145", "1.145.1", "1.145.2", "1.145.3", "1.145.4", "1.145.5"},
            new string[] {"1.146", "1.147"},
            new string[] {"1.147.1"},
            new string[] {"1.148", "1.148.1"},
            new string[] {"1.148.2"},
            new string[] {"1.148.3", "1.148.4"},
            new string[] {"1.148.5"},
            new string[] {"1.148.6"},
            new string[] {"1.148.7", "1.148.8", "1.148.9", "1.148.10"},
            new string[] {"1.148.11", "1.148.12"},
            new string[] {"1.148.14"},
            new string[] {"1.148.15"},
            new string[] {"1.148.16", "1.148.17", "1.148.18", "1.148.19", "1.148.20", "1.148.21", "1.148.22", "1.148.23", "1.148.25", "1.148.26", "1.149.0"},
            new string[] {"1.149.1"},
            new string[] {"1.149.2", "1.149.3", "1.149.4", "1.149.5", "1.149.6", "1.149.7", "1.149.8"},
            new string[] {"1.149.9"},
            new string[] {"1.149.10"},
            new string[] {"1.149.11"},
            new string[] {"1.149.12", "1.149.13", "1.149.14", "1.149.15", "1.149.16"},
            new string[] {"1.150"},
            new string[] {"1.151"},
            new string[] {"1.152.1"},
            new string[] {"1.152.2"},
            new string[] {"1.152.5", "1.152.6"}
        };

        private Dictionary<string, string[]> VersionsMatrixDict;
        private Dictionary<Bitness, Dictionary<string, Uri>> BitnessVersionAssets;

        public GalaxyBinaryCompatibilityMatrix()
        {
            VersionsMatrixDict = new Dictionary<string, string[]>();

            BitnessVersionAssets = new Dictionary<Bitness, Dictionary<string, Uri>>
            {
                { Bitness.x64, new Dictionary<string, Uri>() },
                { Bitness.x86, new Dictionary<string, Uri>() }
            };

            foreach (string[] arr in VersionsMatrix)
            {
                foreach(string version in arr)
                {
                    VersionsMatrixDict.Add(version, arr);
                    var split = version.Split('.');
                    int dots = split.Length - 1;
                    if (dots == 1)
                    {
                        arr.Append(version + ".0");
                        VersionsMatrixDict.Add(version + ".0", arr);
                    }
                    else if(dots == 2 && split.Last() == "0")
                    {
                        string short_version = string.Format("{0}.{1}", split[0], split[1]);
                        arr.Append(short_version);
                        VersionsMatrixDict.Add(short_version, arr);
                    }
                }
            }
        }

        public List<string> GetCompatibleVersions(string version)
        {
            if(VersionsMatrixDict.ContainsKey(version))
            {
                return VersionsMatrixDict[version].ToList();
            }

            return null;
        }

        private void AddVersionAssetBitness(Bitness bitness, string version, string browser_download_url)
        {
            var uri = new Uri(browser_download_url);
            BitnessVersionAssets[bitness].Add(version, uri);

            // if the version is 1.100.0 also add 1.100
            // if the version is 1.100 also add 1.100.0
            var split = version.Split('.');
            int dots = split.Length - 1;
            if (dots == 1)
            {
                BitnessVersionAssets[bitness].Add(version + ".0", uri);
            }
            else if (dots == 2 && split.Last() == "0")
            {
                BitnessVersionAssets[bitness].Add(string.Format("{0}.{1}", split[0], split[1]), uri);
            }
        }

        public void AddVersionAsset(string name, string browser_download_url)
        {
            // Expects format name:
            // UniverseLAN-<version>-Build-<build number>-<supported platforms separated by _>.zip
            string[] info = name.Split('-');
            string[] bitness_and_extension = info.Last().Split(new char[] { '.', '_' });

            string version = info[1];

            foreach(var bitness in bitness_and_extension)
            {
                switch(bitness)
                {
                    case "x64":
                        AddVersionAssetBitness(Bitness.x64, version, browser_download_url);
                        break;

                    case "x86":
                        AddVersionAssetBitness(Bitness.x86, version, browser_download_url);
                        break;
                }
            }
        }

        public Uri TryGetBinaryCompatibleAssetUrl(string version, Bitness bitness)
        {
            if (!BitnessVersionAssets[bitness].TryGetValue(version, out var url))
            {
                if (VersionsMatrixDict.TryGetValue(version, out var alt_versions))
                {
                    foreach (var alt_version in alt_versions)
                    {
                        if(BitnessVersionAssets[bitness].TryGetValue(alt_version, out url))
                        {
                            return url;
                        }
                    }
                }
            }
            return url;
        }
    }
}
