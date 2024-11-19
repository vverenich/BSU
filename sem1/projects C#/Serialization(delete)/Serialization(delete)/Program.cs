using System;
using System.IO;
using System.Xml.Serialization;
using System.Text.RegularExpressions;
using System.Collections.Generic;

namespace Serialization {
    // класс и его члены объявлены как public
    [Serializable]
    public class Person {
        public string Name { get; set; }
        public int Age { get; set; }

        // стандартный конструктор без параметров
        public Person() { }

        public Person(string name, int age) {
            Name = name;
            Age = age;
        }
    }
    class Program {
        static void Main(string[] args) {
            // объект для сериализации
            Person person = new Person("Tom", 29);
            Person person1 = new Person("Vlad", 30);
            Person person2 = new Person("Anna", 12);

            // передаем в конструктор тип класса
            XmlSerializer formatterForList = new XmlSerializer(typeof(List<Person>));

            

            // получаем поток, куда будем записывать сериализованный объект
            List<Person> list = new List<Person> { }; 
            using (StreamReader sr = new StreamReader("persons.xml")) {
                if(!sr.EndOfStream)
                list = (List<Person>)formatterForList.Deserialize(sr);
            }
            using (StreamWriter fs = new StreamWriter("persons.xml")) {
                list.Add(person);
                formatterForList.Serialize(fs, list);
            }


            using (StreamReader sr = new StreamReader("persons.xml")) {
                list = (List<Person>)formatterForList.Deserialize(sr);
            }
            using (StreamWriter fs = new StreamWriter("persons.xml")) {
                list.Add(person1);
                formatterForList.Serialize(fs, list);
            }

            using (StreamReader sr = new StreamReader("persons.xml")) {
                list = (List<Person>)formatterForList.Deserialize(sr);
            }
            using (StreamWriter fs = new StreamWriter("persons.xml")) {
                list.Add(person2);
                formatterForList.Serialize(fs, list);
            }

            
            using (StreamReader sr= new StreamReader("persons.xml")) {
                 /*List<Person> people = new List<Person> { };
                 while (!fs.EndOfStream) {
                     people.Add((Person)formatterForList.Deserialize(fs));
                 }
                 foreach (Person p in people) {
                     Console.WriteLine($"Имя: {p.Name} --- Возраст: {p.Age}");
                 }*/
                list = (List<Person>)formatterForList.Deserialize(sr);
                foreach (Person p in list) {
                    Console.WriteLine(p.Name + "   " + p.Age);
                }
            }

           

        }
    }
}
