
using System;
using System.Net;

namespace UniverseLanWizard
{
    internal class SimpleFileDownloader
    {
        public static void DownloadFile(Uri url, string location)
        {
            using (var client = new WebClient())
            {
                client.Headers.Add("User-Agent", "Mozilla/5.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.0.3705;) UniverseLAN-Update-Checker");
                client.DownloadFile(url, location);
            }
        }

        public static void DownloadFile(string url, string location)
        {
            using (var client = new WebClient())
            {
                client.Headers.Add("User-Agent", "Mozilla/5.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.0.3705;) UniverseLAN-Update-Checker");
                client.DownloadFile(url, location);
            }
        }
    }
}
