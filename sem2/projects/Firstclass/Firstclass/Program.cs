using System;

namespace FirstClass {
    class Program {
        static void Main(string[] args) {
            Fraction f1 = new Fraction(1000000002, 2000000000);
            Console.WriteLine(f1);
            Fraction f2 = new Fraction(999999999, 2000000000);
            Console.WriteLine(-f2);
            Fraction f3 = f1 / f2;
            Console.WriteLine(f3);
        }
    }
}