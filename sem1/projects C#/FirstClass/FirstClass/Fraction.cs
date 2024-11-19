using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstClass {
    class Fraction {
        private int numerator;
        private int denominator;
        private void Reduction() {
            if (numerator == 0) {
                denominator = 1;
            } else {
                int gcd = (int)GetGCD(denominator, numerator);
                numerator = numerator / gcd;
                denominator = denominator / gcd;
                if (denominator < 0) {
                    denominator = denominator * -1;
                    numerator = numerator * -1;
                }
            }
        }
        public static long GetGCD(long a, long b) {
            a = Math.Abs(a);
            b = Math.Abs(b);
            while (a != 0 && b != 0) {
                if (a > b) {
                    a = a % b;
                } else {
                    b = b % a;
                }
            }
            return a + b;
        }
        public Fraction(int num, int den) {
            if (den == 0) {
                throw new ArgumentException("Denominator can not be zero");
            }
            denominator = den;
            numerator = num;
            Reduction();
        }
        public int Denominator {
            get {
                return denominator;
            }
            set {
                if (value == 0) {
                    throw new ArgumentException("Denominator can not be zero");
                }
                denominator = value;
                Reduction();
            }
        }
        public int Numerator {
            get {
                return numerator;
            }
            set {
                numerator = value;
                Reduction();
            }
        }
        public static Fraction operator +(Fraction f1, Fraction f2) {
            long d = f1.denominator * f2.denominator;
            long n = f1.numerator * f2.denominator + f1.denominator * f2.numerator;
            long gcd = GetGCD(d, n);
            d = d / gcd;
            n = n / gcd;
            return new Fraction((int)n, (int)d);
        }
        public static Fraction operator -(Fraction f) {
            Fraction f1 = f;
            f1.numerator = f1.numerator * -1;
            return f1;
        }
        public static Fraction operator -(Fraction f1, Fraction f2) {
            Fraction f = -f2;
            return f1 + f;
        }
        public static Fraction operator /(Fraction f1, Fraction f2) {
            long n = f1.numerator * f2.denominator;
            long d = f1.denominator * f2.numerator;
            if (d == 0) {
                throw new ArgumentException("Denominator can not be zero");
            }
            long gcd = GetGCD(d, n);
            d = d / gcd;
            n = n / gcd;
            return new Fraction((int)n, (int)d);
        }
        public static Fraction operator *(Fraction f1, Fraction f2) {
            int d = f2.numerator;
            int n = f2.denominator;
            Fraction f = new Fraction(n, d);
            return f1 / f;
        }

        public static bool operator >(Fraction f1, Fraction f2) {
            Fraction f = f1 - f2;
            if (f.numerator > 0) {
                return true;
            } else {
                return false;
            }
        }
        public static bool operator ==(Fraction f1, Fraction f2) {
            Fraction f = f1 - f2;
            if (f.numerator == 0) {
                return true;
            } else {
                return false;
            }
        }
        public static bool operator !=(Fraction f1, Fraction f2) {
            if (!(f1 == f2)){
                return true;
            } else {
                return false;
            }
        }
        public static bool operator <=(Fraction f1, Fraction f2) {
            if (!(f1 > f2)) {
                return true;
            } else {
                return false;
            }
        }
        public static bool operator >=(Fraction f1, Fraction f2) {
            if (!(f1 > f2) || (f1==f2)) {
                return true;
            } else {
                return false;
            }
        }
        public static bool operator <(Fraction f1, Fraction f2) {
            if (!(f1 >= f2)) {
                return true;
            } else {
                return false;
            }
        }
        public override bool Equals(object obj) {
            if(obj == null) {
                throw new NullReferenceException();
            }
            if(!(obj is Fraction)) {
                throw new ArgumentException("Argument should be Fraction type");
            }
            return (numerator * (obj as Fraction).denominator == (obj as Fraction).numerator * denominator);
        }
        public override int GetHashCode() => checked(Numerator - Denominator);
             
        public override string ToString() {
            return String.Format($"Fraction with numerator equal to { numerator}" + 
                 $" and denominator equal to { denominator}") ;
        }
    }
}
