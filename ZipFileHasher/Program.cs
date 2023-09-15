using SharpCompress.Readers;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
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

            string[] all_entries = Directory.GetFileSystemEntries(path, "*.tar.gz", SearchOption.AllDirectories);
            int proc_count = (int)(Environment.ProcessorCount * 0.95);

            List<Task<string[]>> tasks = new List<Task<string[]>>();

            for(int i = 0; i < proc_count; ++i)
            {
                tasks.Add(Task<string[]>.Factory.StartNew(() => ProcessEntries(all_entries, i, proc_count)));
            }

            Task.WaitAll(tasks.ToArray());

            foreach(var task in tasks)
            {
                File.AppendAllText("sha1_hashes.txt", task.Result[0]);
                File.AppendAllText("md5_hashes.txt", task.Result[1]);
            }

            Console.WriteLine("All threads complete");
        }

        static string[] ProcessEntries(string[] entries, int id, int proc_count)
        {
            string md5_hashes = "";
            string sha1_hashes = "";

            for(int e = id; e < entries.Length; e += proc_count)
            {
                string entry = entries[e];
                using (Stream stream = File.OpenRead(entry))
                {
                    var reader = ReaderFactory.Open(stream);
                    while (reader.MoveToNextEntry())
                    {
                        if (!reader.Entry.IsDirectory)
                        {
                            if (reader.Entry.Key.EndsWith("/Galaxy.dll") || reader.Entry.Key.EndsWith("/Galaxy64.dll"))
                            {
                                string dll_name = reader.Entry.Key.Split('/').Last();
                                string dll_version = Path.GetFileName(entry).Replace("DevelopmentKit_", "").Replace(".tar.gz", "");

                                using (MemoryStream memory_stream = new MemoryStream())
                                {
                                    reader.WriteEntryTo(memory_stream);
                                    using (SHA1Managed sha1 = new SHA1Managed())
                                    {
                                        byte[] hash = sha1.ComputeHash(memory_stream.ToArray());
                                        StringBuilder formatted = new StringBuilder(2 * hash.Length);
                                        foreach (byte b in hash)
                                        {
                                            formatted.AppendFormat("{0:x2}", b);
                                        }
                                        string output = string.Format("{0}={1}", formatted.ToString(), dll_version);
                                        Console.WriteLine(output);
                                        sha1_hashes += output + "\n";
                                    }

                                    using (MD5 md5 = MD5.Create())
                                    {
                                        byte[] hash = md5.ComputeHash(memory_stream.ToArray());
                                        StringBuilder formatted = new StringBuilder(2 * hash.Length);
                                        foreach (byte b in hash)
                                        {
                                            formatted.AppendFormat("{0:x2}", b);
                                        }
                                        string output = string.Format("{0}={1}", formatted.ToString(), dll_version);
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
