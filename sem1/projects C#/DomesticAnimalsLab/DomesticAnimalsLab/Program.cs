using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace AnimalsLab {
    class Animal {
        public Animal(string name_owner, string type, string name_animal, int? age = null) {
            NameOfOwner = name_owner;
            TypeOfAnimal = type;
            NameOfAnimal = name_animal;
            AgeOfAnimalInYears = age;
        }
        string nameOfOwner;
        public string NameOfOwner {
            get => nameOfOwner;
            set {
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
                typeOfAnimal = value;
            }
        }
        string nameOfAnimal;
        public string NameOfAnimal {
            get => nameOfAnimal;
            set {
                nameOfAnimal = value;
            }
        }
        int? ageOfAnimalInYears;
        public int? AgeOfAnimalInYears {
            get {
                /*if (ageOfAnimalInYears == null) {
                    throw new NullReferenceException("You can't get value of age because it is null.");
                }*/
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
        public static void GetInformation(List<Animal> list, string str) {
            var listOfAppropriateObjects = from obj in list
                                           orderby obj.NameOfOwner
                                           where String.Compare(obj.NameOfOwner, str) == -1
                                           select obj;
            Console.WriteLine("\nInformation about the owners' pets:\n");
            foreach (Animal obj in listOfAppropriateObjects) {
                string age = String.Empty;
                if (obj.AgeOfAnimalInYears != null) {
                    age = Convert.ToString(obj.AgeOfAnimalInYears);
                }
                Console.WriteLine("\tName of owner:{0}\n\tType of animal:{1}\n\t" +
                    "Name of Animal:{2}\n\tAge of animal:{3}\n", obj.NameOfOwner,
                    obj.TypeOfAnimal, obj.NameOfAnimal, age);
            }
        }
        public static double AverageAgeOfAnimals(List<Animal> list) {
            var objectsWithDefinedAge = from obj in list
                                        where obj.AgeOfAnimalInYears != null
                                        select obj;
            int sum = 0;
            int number = objectsWithDefinedAge.Count();
            foreach (Animal obj in objectsWithDefinedAge) {
                sum += (int)obj.AgeOfAnimalInYears;
            }
            return (double)sum / number;//if it is nesessary
        }
        public static void PrintNamesOfOwners(List<Animal> list) {
            var groupedObjects = from obj in list
                                 group obj by obj.TypeOfAnimal;
            var listOfAppropriateObjects = from group_ in groupedObjects
                                           orderby group_.Count()
                                           where group_.Count() == groupedObjects.LastOrDefault().Count()
                                           from obj in group_
                                           where !String.IsNullOrEmpty(obj.NameOfOwner)
                                           select obj;
            if (listOfAppropriateObjects.Count() == 0) {
                Console.WriteLine("\nNo one animal in the most numerous type of animals has owner.");
            } else {
                Console.WriteLine("\nOwners' names of the most numerous type of animals:");
                foreach (Animal t in listOfAppropriateObjects) {
                    Console.WriteLine("\t{0}", t.NameOfOwner);
                }
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

            GetInformation(listOfObjects, "v");
            Console.WriteLine(AverageAgeOfAnimals(listOfObjects));
            PrintNamesOfOwners(listOfObjects);
            //Third method, menu, output parameter
        }
    }
}

