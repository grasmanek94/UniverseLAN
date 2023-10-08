using System;
using System.IO;
using System.Net.Http;

namespace UniverseLanWizard
{
    internal class SimpleFileDownloader
    {
        public static void DownloadFile(Uri url, string location)
        {
            using (var client = new HttpClient())
            {
                client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.0.3705;) UniverseLAN-Update-Checker");

                var response = client.GetAsync(url);
                response.Wait();

                using (var fs = new FileStream(location, FileMode.CreateNew))
                {
                    var task = response.Result.Content.CopyToAsync(fs);
                    task.Wait();
                }
            }
        }

        public static void DownloadFile(string url, string location)
        {
            using (var client = new HttpClient())
            {
                client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.0.3705;) UniverseLAN-Update-Checker");

                var response = client.GetAsync(url);
                response.Wait();

                using (var fs = new FileStream(location, FileMode.CreateNew))
                {
                    var task = response.Result.Content.CopyToAsync(fs);
                    task.Wait();
                }
            }
        }
    }
}
