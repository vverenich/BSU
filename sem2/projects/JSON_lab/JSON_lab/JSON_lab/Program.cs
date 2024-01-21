using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Schema;
using System;
using Newtonsoft.Json;
using System.IO;

namespace JSON_lab {
    class Program {
        static void Main(string[] args) {

            string fileString = File.ReadAllText("file.json");
            string schemaString = File.ReadAllText("schema.json");
            JObject obj = JObject.Parse(fileString);
            JSchema schema = JSchema.Parse(schemaString);

            if (obj.IsValid(schema)) {
                JsonTextReader reader = new JsonTextReader(new StringReader(fileString));
                while (reader.Read()) {
                    if (reader.TokenType == JsonToken.PropertyName) {
                        switch (reader.Value) {
                            case "subjectinfo": {
                                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                                    Console.WriteLine("**************************************************");
                                    Console.ForegroundColor = ConsoleColor.White;
                                    break;
                                }
                            case "_name": {
                                    reader.Read();
                                    Console.ForegroundColor = ConsoleColor.Green;
                                    Console.WriteLine(reader.Value);
                                    Console.ForegroundColor = ConsoleColor.White;
                                    break;
                                }
                            case "_type": {
                                    reader.Read();
                                    Console.WriteLine("Type: " + reader.Value);
                                    break;
                                }
                            case "_fullName": {
                                    reader.Read();
                                    Console.WriteLine("Teacher: " + reader.Value);
                                    break;
                                }
                            case "days": {
                                    Console.WriteLine("\nDays:");
                                    break;
                                }
                            case "_dayOfWeek": {
                                    reader.Read();
                                    Console.WriteLine("\tDay of week: " + reader.Value);
                                    break;
                                }
                            case "number": {
                                    reader.Read();
                                    Console.WriteLine("\tNumber of class: " + reader.Value);
                                    break;
                                }
                        }
                    }
                }
            }
        }
    }
}