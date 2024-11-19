using System;

namespace ConsoleApp3 {
    public enum Kinds {
        African,
        NorthernRockhopper,
        King,
        Adelie,
        Fairy,
        YellowEyed,
        SouthernRockhopper,
        Magellanic,
        Chinstrap,
        Macaroni,
        AustralianLittle,
        Emperor,
        Snares,
        Galapagos,
        ErectCrested,
        Royal,
        Humboldt,
        EasternRockhopper,
        Fiordland
    }
    public class Penguin : Bird, ISwimmable {
        public Kinds Type { get; set; }
        private uint years;
        private double weight;
        private uint wingspanInCm;
        public Penguin(string n, Kinds aType, uint aYears, double aWeight, uint aWingspan, Gender aSex) {
            Name = n;
            Type = aType;
            Years = aYears;
            Weight = aWeight;
            WingspanInCm = aWingspan;
            Sex = aSex;
        }
        public Penguin GiveBirth(string aName) {
            if (Sex != Gender.female) {
                throw new ArgumentException("Only females can give birth.");
            }
            Random rnd = new Random();
            int gen = rnd.Next(0, 1);
            return new Penguin(aName, Type, 0, 0.01, 7, (Gender)gen);
        }
        public override uint WingspanInCm {
            set {
                if (value > 76) {
                    throw new ArgumentException("Wingspan of a penguin can not to be more than 76 cm.");
                }
                wingspanInCm = value;
            }
            get {
                return wingspanInCm;
            }
        }
        public override uint Years {
            set {
                if (value > 20) {
                    throw new ArgumentException("Penguins can't live more trhan 20 years!");
                }
                years = value;
            }
            get {
                return years;
            }
        }
        public override double Weight {
            set {
                if (value < 0 || value > 50) {
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
            return 35;
        }
        void ISwimmable.Swim() {
            Console.WriteLine($"Penguin {Name} is swimming.");
        }
    }
}
