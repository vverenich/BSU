using System;
using System.IO;
using System.Text.RegularExpressions;

namespace RegexLab {
    class Program {



        static void Main(string[] args) {
            while (true) {
                Console.WriteLine("Enter file name:");
                string path = Console.ReadLine();
                if (!File.Exists(path)) {
                    Console.WriteLine("File doesn't exist");
                    continue;
                }

                StreamReader fin = File.OpenText(path);
                string text = fin.ReadToEnd();
                Regex regex = new Regex(@"[1-28]\.FEB\.[0-9]{2}");//djjdfjdfj
                MatchCollection matches = regex.Matches(text);


            }
        }
    }
}
