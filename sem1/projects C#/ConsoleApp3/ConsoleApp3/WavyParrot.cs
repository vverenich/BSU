using System;

namespace ConsoleApp3 {
    public enum Varieties {
        Budgerigar
    }
    public class WavyParrot : Bird, IFlyable {
        public Varieties Type { get; set; }
        private uint years;
        private double weight;
        private uint wingspanInCm;
        public WavyParrot(string n, Varieties aType, uint aYears, double aWeight, uint aWingspan, Gender aSex) {
            Name = n;
            Type = aType;
            Years = aYears;
            Weight = aWeight;
            WingspanInCm = aWingspan;
            Sex = aSex;
        }
        public WavyParrot GiveBirth(string aName) {
            if (Sex != Gender.female) {
                throw new ArgumentException("Only females can give birth.");
            }
            Random rnd = new Random();
            int gen = rnd.Next(0, 1);
            return new WavyParrot(aName, Type, 0, 0.01, 4, (Gender)gen);
        }
        public override uint WingspanInCm {
            set {
                if (value > 30) {
                    throw new ArgumentException("Wingspan of a budgerigar can not to be more than 30 cm.");
                }
                wingspanInCm = value;
            }
            get {
                return wingspanInCm;
            }
        }
        public override uint Years {
            set {
                if (value > 25) {
                    throw new ArgumentException("Wavy parrots can't live more trhan 25 years!");
                }
                years = value;
            }
            get {
                return years;
            }
        }
        public override double Weight {
            set {
                if (value < 0 || value > 0.04) {
                    throw new ArgumentException("Invalid parameter");
                }
                weight = value;
            }
            get {
                return weight;
            }
        }
        int IFlyable.GetMinSpeedOfFlying() {
            return 0;
        }
        int IFlyable.GetMaxSpeedOfFlying() {
            return 36;
        }
        void IFlyable.Fly() {
            Console.WriteLine($"Wavy parrot {Name} is flying.");
        }
    }
}
