using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AnimalsLab {
    class Animal {
        public Animal(string name_owner, string type, string name_animal, int? age = null) {
            NameOfOwner = name_owner;
            TypeOfAnimal = type;
            NameOfAnimal = name_animal;
            AgeOfAnimalInYears = age;
        }
        void CheckStringForSpaces(string str) {
            if (str.Length > 0) {
                if (str[0] == ' ') {
                    throw new ArgumentException("Spaces can't be at the beginning of string.");
                }
                if (str[str.Length - 1] == ' ') {
                    throw new ArgumentException("Spaces can't be at the end of string.");
                }
            }
        }
        string nameOfOwner;
        public string NameOfOwner {
            get => nameOfOwner;
            set {
                CheckStringForSpaces(value);
                nameOfOwner = value;
            }
        }
        string typeOfAnimal;
        public string TypeOfAnimal {
            get => typeOfAnimal;
            private set {
                if (String.IsNullOrEmpty(value.ToString())) {
                    throw new ArgumentException("You need to initialize type of animal");
                }
                CheckStringForSpaces(value);
                typeOfAnimal = value;
            }
        }
        string nameOfAnimal;
        public string NameOfAnimal {
            get => nameOfAnimal;
            set {
                CheckStringForSpaces(value);
                nameOfAnimal = value;
            }
        }
        int? ageOfAnimalInYears;
        public int? AgeOfAnimalInYears {
            get {
                return ageOfAnimalInYears;
            }
            set {
                if (value < 0) {
                    throw new ArgumentException("Age must be positive.");
                }
                ageOfAnimalInYears = value;
            }
        }
    }
    class Program {
        public enum Output {
            File,
            Console,
        }

        public static void GetInformation(List<Animal> list, string str, Output output) {
            var listOfAppropriateObjects = from obj in list
                                           orderby obj.NameOfOwner
                                           where String.Compare(obj.NameOfOwner, str) == -1
                                           select obj;
            if (output == Output.Console) {
                Console.WriteLine("Information about the owners' pets:\n");
                foreach (Animal obj in listOfAppropriateObjects) {
                    string age = String.Empty;
                    if (obj.AgeOfAnimalInYears != null) {
                        age = Convert.ToString(obj.AgeOfAnimalInYears);
                    }
                    Console.WriteLine("\tName of owner:{0}\n\tType of animal:{1}\n\t" +
                        "Name of Animal:{2}\n\tAge of animal:{3}\n", obj.NameOfOwner,
                        obj.TypeOfAnimal, obj.NameOfAnimal, age);
                }
            } else {
                var fout = new StreamWriter("out.txt");
                fout.WriteLine("Information about the owners' pets:\n");
                foreach (Animal obj in listOfAppropriateObjects) {
                    string age = String.Empty;
                    if (obj.AgeOfAnimalInYears != null) {
                        age = Convert.ToString(obj.AgeOfAnimalInYears);
                    }
                    fout.WriteLine("\tName of owner: " + obj.NameOfOwner);
                    fout.WriteLine("\tType of animal: " + obj.TypeOfAnimal);
                    fout.WriteLine("\tName of Animal: " + obj.NameOfAnimal);
                    fout.WriteLine("\tAge of animal: " + age);
                    fout.WriteLine();
                }
                fout.Close();
            }
        }
        public static void AverageAgeOfAnimals(List<Animal> list, Output output) {
            var objectsWithDefinedAge = from obj in list
                                        where obj.AgeOfAnimalInYears != null
                                        select obj;
            int sum = 0;
            int number = objectsWithDefinedAge.Count();
            foreach (Animal obj in objectsWithDefinedAge) {
                sum += (int)obj.AgeOfAnimalInYears;
            }
            double result = (double)sum / number;
            if (output == Output.Console) {
                Console.WriteLine("Average age of animals: " + result + "\n");
            } else {
                var fout = new StreamWriter("out.txt");
                fout.WriteLine("Average age of animals: " + result + "\n");
                fout.Close();
            }
        }
        public static void PrintNamesOfOwners(List<Animal> list, Output output) {
            var groupedObjects = from obj in list
                                 group obj by obj.TypeOfAnimal into groups
                                 select new {
                                     Count = groups.Count(),
                                     Objects = from g in groups
                                               where !String.IsNullOrEmpty(g.NameOfOwner)
                                               select g
                                 };

            int maxNumber = groupedObjects.Max(t => t.Count);

            var appropriateObjects = from gr in groupedObjects
                                     where gr.Count == maxNumber
                                     from g in gr.Objects
                                     select g;
            if (output == Output.Console) {
                if (appropriateObjects.Count() == 0) {
                    Console.WriteLine("No one animal in the most numerous type of animals" +
                        " has owner.");
                } else {
                    Console.WriteLine("Owners' names of the most numerous type of animals:");
                    foreach (Animal t in appropriateObjects) {
                        Console.WriteLine("\t{0}", t.NameOfOwner);
                    }
                }
            } else {
                var fout = new StreamWriter("out.txt");
                if (appropriateObjects.Count() == 0) {
                    fout.WriteLine("No one animal in the most numerous type of animals " +
                        "has owner.");
                } else {
                    fout.WriteLine("Owners' names of the most numerous type of animals:");
                    foreach (Animal t in appropriateObjects) {
                        fout.WriteLine("\t{0}", t.NameOfOwner);
                    }
                }
                fout.Close();
            }
        }
        static void Main(string[] args) {

            List<Animal> listOfObjects = new List<Animal>();
            string[] lines = File.ReadAllLines("in.txt");
            try {
                foreach (string line in lines) {
                    char[] separator = new char[] { ',' };
                    string[] parameters = line.Split(separator, 4);
                    int age;
                    if (int.TryParse(parameters[3], out age)) {
                        listOfObjects.Add(new Animal(parameters[0], parameters[1],
                            parameters[2], age));
                    } else {
                        listOfObjects.Add(new Animal(parameters[0], parameters[1],
                            parameters[2]));
                    }
                }
            } catch (ArgumentException e) {
                Console.WriteLine(e.Message);
            }

            bool finish = false;
            while (!finish) {
                Output output = new Output();
                int number = 0;
                while (number != 2 && number != 1) {
                    Console.WriteLine("Where do you want to see the result in the Console(enter 1) or in the File(enter 2)?\t");
                    Int32.TryParse(Console.ReadLine(), out number);
                    switch (number) {
                        case 1:
                            output = Output.Console;
                            break;
                        case 2:
                            output = Output.File;
                            break;
                        default:
                            Console.Write("\nYou made an illegal choice.\n\n");
                            break;
                    }
                }
                number = 0;
                while (number != 1 && number != 2 && number != 3 && !finish) {
                    Console.WriteLine("\nWhat do you prefer to get?");
                    Console.WriteLine("\tEnter '1' to get information about owners whose names are in a " +
                        "sorted list are up to the specified position." +
                        "\n\tEnter '2' to get the average age of each owner's pets." +
                        "\n\tEnter '3' to get the names of the owners of the largest number of animals." +
                        "\n\tEnter '4' to exit.");

                    Int32.TryParse(Console.ReadLine(), out number);
                    switch (number) {
                        case 1:
                            string pos;
                            Console.WriteLine("\nEnter letter position:");
                            pos = Console.ReadLine();
                            GetInformation(listOfObjects, pos, output);
                            break;
                        case 2:
                            AverageAgeOfAnimals(listOfObjects, output);
                            break;
                        case 3:
                            PrintNamesOfOwners(listOfObjects, output);
                            break;
                        case 4:
                            finish = true;
                            break;
                        default:
                            Console.WriteLine("You made an illegal choice.");
                            break;
                    }

                }
            }
        }
    }
}
