using SharpCompress.Readers;
using System;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

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

            string[] entries = Directory.GetFileSystemEntries(path, "*.tar.gz", SearchOption.AllDirectories);

            foreach (string entry in entries)
            {
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

                                using(MemoryStream memory_stream = new MemoryStream())
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
                                        File.AppendAllText("hashes.txt", output + "\n");
                                    }      
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
