using System;
using System.Collections.Generic
using System.Linq;

namespace ConsoleApp3 {
    class DomesticAnimals {
        public DomesticAnimals(string name_owner, string type, string name_animal, int? age = null) {
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
            set {
                if (String.IsNullOrEmpty(value.ToString())) {
                    throw new ArgumentException("You need to initialize type of animal");
                }
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
        public int AgeOfAnimalInYears {
            get {
                if(ageOfAnimalInYears == null) {
                    throw new NullReferenceException("You can't get value of age because it is null.")
                }
                return ageOfAnimalInYears;
            }
            set {
                if(value < 0) {
                    throw new ArgumentException("Age must be positive.");
                }
                ageOfAnimalInYears = value;
            }
        }

        //positive and negative values


    }
    class Program {
        public static void GetInformation(List<DomesticAnimals> list, string str) {
            var sortedList = from obj in list
                             orderby obj.NameOfOwner
                             select obj;
            var appropriateList = from obj in sortedList
                                  orderby Compare(obj.NameOfOwner, str) < 0
                                  select obj;
            Console.WriteLine("Information:");
            foreach(DomesticAnimals obj in appropriateList) {
                string age = new string();
                if(obj.AgeOfAnimalInYears!= null) {
                    age = Convert.ToString(obj.AgeOfAnimalInYears);
                }
                Console.WriteLine("\n\tName of owner:{0}\n\tType of animal:{1}\n\t" +
                    "Name of Animal:{2}\n\tAge of animal:{3}\n\n", obj.NameOfOwner,
                    obj.TypeOfAnimal, obj.NameOfAnimal,age);
            }
        }
        public static double AverageAgeOfAnimals(List<DomesticAnimals> list) {
            var listOfAnimalsWithDefinedAge = from obj in list
                                              where obj.AgeOfAnimalInYears != null
                                              select obj;
            int sum = 0;
            int number = listOfAnimalsWithDefinedAge.Count();
            foreach(DomesticAnimals obj in listOfAnimalsWithDefinedAge) {
                sum += obj.AgeOfAnimalInYears;
            }
            return (double)sum / number;//if it is nesessary

            

        }
        static void Main(string[] args) {
            List<DomesticAnimals> list= new 
        }
    }
}
