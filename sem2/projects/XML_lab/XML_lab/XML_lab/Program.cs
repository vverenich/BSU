using System;
using System.Xml;
using System.Xml.Schema;

namespace XML_lab {
    class Program {
        static void Main(string[] args) {
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.DtdProcessing = DtdProcessing.Parse;
            settings.ValidationType = ValidationType.DTD;
            using (XmlReader reader = XmlReader.Create("schedule.xml", settings)) {
                try {
                    while (reader.Read()) {
                        if (reader.NodeType == XmlNodeType.Element) {
                            switch (reader.Name) {
                                case "subject": {
                                        Console.ForegroundColor = ConsoleColor.DarkYellow;
                                        Console.WriteLine("**************************************************");
                                        Console.ForegroundColor = ConsoleColor.White;
                                        break;
                                    }
                                case "subjectinfo": {
                                        Console.ForegroundColor = ConsoleColor.Green;
                                        Console.WriteLine(reader.GetAttribute("name"));
                                        Console.ForegroundColor = ConsoleColor.White;
                                        Console.WriteLine("Type: " + reader.GetAttribute("type"));
                                        Console.WriteLine("Teacher: " + reader.GetAttribute("fullName"));
                                        break;
                                    }
                                case "days": {
                                        Console.WriteLine("\nDays:");
                                        break;
                                    }
                                case "dayinfo": {
                                        Console.WriteLine("\tDay of week: " + reader.GetAttribute("dayOfWeek") + "\tNumber of class: " + reader.GetAttribute("number"));
                                        break;
                                    }
                            }
                            reader.MoveToElement();
                        }
                    }
                } catch (XmlSchemaException ex) {
                    Console.WriteLine(ex.Message);
                    return;
                }
            }
        }
    }
}
