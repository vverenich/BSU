using System;

namespace ConsoleApp3 {
    public enum Species {
        NorthIsland,
        Southern,
        Okarito,
        LittleSpotted,
        GreatSpotted
    }
    public class Kiwi : Bird, ISwimmable {
        public Species Type { get; set; }
        private uint years;
        private double weight;
        private uint wingspanInCm;
        public Kiwi(string n, Species aType, uint aYears, double aWeight, uint aWingspan, Gender aSex) {
            Name = n;
            Type = aType;
            Years = aYears;
            Weight = aWeight;
            WingspanInCm = aWingspan;
            Sex = aSex;
        }
        public Kiwi GiveBirth(string aName) {
            if (Sex != Gender.female) {
                throw new ArgumentException("Only females can give birth.");
            }
            Random rnd = new Random();
            int gen = rnd.Next(0, 1);
            return new Kiwi(aName, Type, 0, 0.01, 0, (Gender)gen);
        }
        public override uint WingspanInCm {
            set {
                if (value > 6) {
                    throw new ArgumentException("Wingspan of a kiwi can not to be more than 6 cm.");
                }
                wingspanInCm = value;
            }
            get {
                return wingspanInCm;
            }
        }
        public override uint Years {
            set {
                if (value > 100) {
                    throw new ArgumentException("Kiwies can't live more trhan 100 years!");
                }
                years = value;
            }
            get {
                return years;
            }
        }
        public override double Weight {
            set {
                if (value < 0 || value > 5) {
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
            Console.WriteLine($"Kiwi {Name} is swimming.");
        }
    }
}
