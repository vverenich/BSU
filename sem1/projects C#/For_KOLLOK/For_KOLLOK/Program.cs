using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace For_KOLLOK {
    class Program {
        static void Main(string[] args) {
            double x = 14.48;
            string s = "Результат вычислений:";
            Console.WriteLine("{0, -25} [{1, 10:E3}]", s, x);
        }
    }
}
