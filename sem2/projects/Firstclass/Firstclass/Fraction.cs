using System;

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
            long d = (long)f1.denominator * f2.denominator;
            long n = (long)f1.numerator * f2.denominator + (long)f1.denominator * f2.numerator;
            long gcd = GetGCD(d, n);
            d = d / gcd;
            n = n / gcd;
            return new Fraction((int)n, (int)d);
        }
        public static Fraction operator -(Fraction f) {
            Fraction f1 = new Fraction(f.numerator, f.denominator);
            f1.numerator = f1.numerator * -1;
            return f1;
        }
        public static Fraction operator -(Fraction f1, Fraction f2) {
            Fraction f = new Fraction(f2.numerator, f2.denominator);
            f = -f;
            return f1 + f;
        }
        public static Fraction operator /(Fraction f1, Fraction f2) {
            long n = (long)f1.numerator * f2.denominator;
            long d = (long)f1.denominator * f2.numerator;
            if (d == 0) {
                throw new ArgumentException("Denominator can not be zero");
            }
            long gcd = GetGCD(d, n);
            d = d / gcd;
            n = n / gcd;
            return new Fraction((int)n, (int)d);
        }
        public static Fraction operator *(Fraction f1, Fraction f2) {
            long n = (long)f1.numerator * f2.numerator;
            long d = (long)f1.denominator * f2.denominator;
            long gcd = GetGCD(d, n);
            d = d / gcd;
            n = n / gcd;
            return new Fraction((int)n, (int)d);
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
            if (!(f1 == f2)) {
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
            if ((f1 > f2) || (f1 == f2)) {
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
        public static Fraction operator +(Fraction f1, int a) {
            Fraction f2 = new Fraction(a, 1);
            return f1 + f2;
        }
        public static Fraction operator +(int a, Fraction f1) {
            Fraction f2 = new Fraction(a, 1);
            return f1 + f2;
        }
        public static Fraction operator -(Fraction f1, int a) {
            Fraction f2 = new Fraction(a, 1);
            return f1 - f2;
        }
        public static Fraction operator -(int a, Fraction f1) {
            Fraction f2 = new Fraction(a, 1);
            return f2 - f1;
        }
        public static Fraction operator *(Fraction f1, int a) {
            Fraction f2 = new Fraction(a, 1);
            return f1 * f2;
        }
        public static Fraction operator *(int a, Fraction f1) {
            Fraction f2 = new Fraction(a, 1);
            return f2 * f1;
        }
        public static Fraction operator /(Fraction f1, int a) {
            Fraction f2 = new Fraction(a, 1);
            return f1 / f2;
        }
        public static Fraction operator /(int a, Fraction f1) {
            Fraction f2 = new Fraction(a, 1);
            return f2 / f1;
        }
        public static bool operator >(Fraction f1, int a) {
            Fraction f2 = new Fraction(a, 1);
            return f1 > f2;
        }
        public static bool operator <(Fraction f1, int a) {
            Fraction f2 = new Fraction(a, 1);
            return f1 < f2;
        }
        public static bool operator ==(Fraction f1, int a) {
            Fraction f2 = new Fraction(a, 1);
            return f1 == f2;
        }
        public static bool operator >=(Fraction f1, int a) => !(f1 < a);
        public static bool operator <=(Fraction f1, int a) => !(f1 > a);
        public static bool operator !=(Fraction f1, int a) => !(f1 == a);
        public static bool operator >(int a, Fraction f1) {
            Fraction f2 = new Fraction(a, 1);
            return f2 > f1;
        }
        public static bool operator <(int a, Fraction f1) {
            Fraction f2 = new Fraction(a, 1);
            return f2 < f1;
        }
        public static bool operator ==(int a, Fraction f1) {
            Fraction f2 = new Fraction(a, 1);
            return f1 == f2;
        }
        public static bool operator >=(int a, Fraction f1) => !(a < f1);

        public static bool operator <=(int a, Fraction f1) => !(a > f1);
        public static bool operator !=(int a, Fraction f1) => !(f1 == a);
        public static explicit operator double(Fraction f) => (double)f.numerator / (double)f.denominator;
        public override bool Equals(object obj) {
            if (obj == null) {
                throw new NullReferenceException();
            }
            if (!(obj is Fraction)) {
                throw new ArgumentException("Argument should be Fraction type");
            }
            return (numerator * (obj as Fraction).denominator == (obj as Fraction).numerator * denominator);
        }
        public override int GetHashCode() => checked(numerator - denominator);
        public override string ToString() => String.Format($"{ numerator}/{ denominator}");
    }
}
