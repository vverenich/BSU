using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FirstClass {
    class Program {
        static void Main(string[] args) {
            Fraction f1 = new Fraction(-4, 9);
            Console.WriteLine(f1);
            Fraction f2 = new Fraction(17, 9);
            Console.WriteLine(f2);
            Fraction f3 = f1 / f2;
            Console.WriteLine(f3);

            if (!(f1 == f2)) {
                Fraction f4 = f1 / f2;
                Console.WriteLine(f4);
            }
            Console.WriteLine(f1);
            Console.WriteLine(f2);
           
        }
    }
}

