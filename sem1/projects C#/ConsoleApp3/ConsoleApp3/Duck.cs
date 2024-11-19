using System;

namespace ConsoleApp3 {
    public enum Types {
        Dabbling,
        Diving,
        Eider,
        Goldeneye,
        Merganser,
        Perching,
        Scoter,
        Sea,
        Stifftail,
        Teal,
        Whistling
    }
    public class Duck : Bird, ISwimmable, IFlyable {
        public Types Type { get; set; }
        private uint years;
        private double weight;
        private uint wingspanInCm;
        public Duck(string n, Types aType, uint aYears, double aWeight, uint aWingspan, Gender aSex) {
            Name = n;
            Type = aType;
            Years = aYears;
            Weight = aWeight;
            WingspanInCm = aWingspan;
            Sex = aSex;
        }
        public Duck GiveBirth(string aName) {
            if (Sex != Gender.female) {
                throw new ArgumentException("Only females can give birth.");
            }
            Random rnd = new Random();
            int gen = rnd.Next(0, 1);
            return new Duck(aName, Type, 0, 0.01, 7, (Gender)gen);
        }
        public override uint WingspanInCm {
            set {
                if (value > 100) {
                    throw new ArgumentException("Wingspan of a duck can not to be more than 100 cm.");
                }
                wingspanInCm = value;
            }
            get {
                return wingspanInCm;
            }
        }
        public override uint Years {
            set {
                if (value > 10) {
                    throw new ArgumentException("Ducks can't live more trhan 10 years!");
                }
                years = value;
            }
            get {
                return years;
            }
        }
        public override double Weight {
            set {
                if (value < 0 || value > 22) {
                    throw new ArgumentException("Invalid parameter");
                }
                weight = value;
            }
            get {
                return weight;
            }
        }
        int ISwimmable.GetMinSpeedOfSwimming() {
            return 0;
        }
        int ISwimmable.GetMaxSpeedOfSwimming() {
            return 5;
        }
        void ISwimmable.Swim() {
            Console.WriteLine($"Duck {Name} is swimming.");
        }
        int IFlyable.GetMinSpeedOfFlying() {
            return 0;
        }
        int IFlyable.GetMaxSpeedOfFlying() {
            return 90;
        }
        void IFlyable.Fly() {
            Console.WriteLine($"Duck {Name} is flying.");
        }
    }
}

