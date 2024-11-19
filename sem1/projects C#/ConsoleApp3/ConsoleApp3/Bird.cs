using System;

namespace ConsoleApp3 {
    public enum Gender {
        male,
        female
    };
    public abstract class Bird {
        private string name;
        public Gender Sex { get; set; }
        public void Eat() {
            Console.WriteLine("Bird is eating.");
        }
        public void Drink() {
            Console.WriteLine("Bird is drinking.");
        }
        public abstract uint Years { get; set; }
        public abstract double Weight { get; set; }
        public abstract uint WingspanInCm { get; set; }
        public string Name {
            set {
                if (String.IsNullOrEmpty(value)) {
                    throw new ArgumentException("The name can not be null or empty.");
                }
                name = value;
            }
            get {
                return name;
            }
        }
    }

}
