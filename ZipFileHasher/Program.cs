using SharpCompress.Readers;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace ZipFileHasher
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string path = ".";
            if (args.Length != 0 && args[0].Length != 0)
            {
                path = args[0];
            }

            List<string> all_entries = new List<string>(Directory.GetFileSystemEntries(path, "*.tar.gz", SearchOption.AllDirectories));
            if (File.Exists("md5_hashes.txt"))
            {
                string[] current_present_hashes = File.ReadAllLines("md5_hashes.txt");

                foreach (var item in current_present_hashes)
                {
                    string endswith = "DevelopmentKit_" + item.Split(new char[]{'=', '|'})[1] + ".tar.gz";
                    all_entries = all_entries.Where(x => { return !x.EndsWith(endswith); }).ToList();
                }
            }

            int proc_count = (int)(Environment.ProcessorCount * 0.95);

            List<Task<string[]>> tasks = new List<Task<string[]>>();

            for(int i = 0; i < proc_count; ++i)
            {
                int id = i;
                tasks.Add(Task<string[]>.Factory.StartNew(() => ProcessEntries(all_entries, id, proc_count)));
            }

            Task.WaitAll(tasks.ToArray());

            foreach(var task in tasks)
            {
                File.AppendAllText("sha1_hashes.txt", task.Result[0]);
                File.AppendAllText("md5_hashes.txt", task.Result[1]);
            }

            Console.WriteLine("All threads complete");
        }

        static string[] ProcessEntries(List<string> entries, int id, int proc_count)
        {
            string md5_hashes = "";
            string sha1_hashes = "";

            for(int e = id; e < entries.Count; e += proc_count)
            {
                string entry = entries[e];
                using (Stream stream = File.OpenRead(entry))
                {
                    var reader = ReaderFactory.Open(stream);
                    while (reader.MoveToNextEntry())
                    {
                        if (!reader.Entry.IsDirectory)
                        {
                            if (reader.Entry.Key.EndsWith("/Galaxy.dll") || reader.Entry.Key.EndsWith("/Galaxy64.dll") ||
                                reader.Entry.Key.EndsWith("/REDGalaxy.dll") || reader.Entry.Key.EndsWith("/REDGalaxy64.dll")
                                )
                            {
                                string dll_name = reader.Entry.Key.Split('/').Last();
                                string dll_version = Path.GetFileName(entry).Replace("DevelopmentKit_", "").Replace(".tar.gz", "");

                                using (MemoryStream memory_stream = new MemoryStream())
                                {
                                    reader.WriteEntryTo(memory_stream);
                                    byte[] arr = memory_stream.ToArray();

                                    using (SHA1Managed sha1 = new SHA1Managed())
                                    {
                                        byte[] hash = sha1.ComputeHash(arr);
                                        StringBuilder formatted = new StringBuilder(2 * hash.Length);
                                        foreach (byte b in hash)
                                        {
                                            formatted.AppendFormat("{0:x2}", b);
                                        }
                                        string output = string.Format("{0}={1}|{2}", formatted.ToString(), dll_version, arr.Length);
                                        Console.WriteLine(output);
                                        sha1_hashes += output + "\n";
                                    }

                                    using (MD5 md5 = MD5.Create())
                                    {
                                        byte[] hash = md5.ComputeHash(arr);
                                        StringBuilder formatted = new StringBuilder(2 * hash.Length);
                                        foreach (byte b in hash)
                                        {
                                            formatted.AppendFormat("{0:x2}", b);
                                        }
                                        string output = string.Format("{0}={1}|{2}", formatted.ToString(), dll_version, arr.Length);
                                        Console.WriteLine(output);
                                        md5_hashes += output + "\n";
                                    }
                                }
                            }
                        }
                    }
                }
            } 

            return new string[] { sha1_hashes, md5_hashes };
        }
    }
}
