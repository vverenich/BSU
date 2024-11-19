using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IntroductionInIT2 {
    class Program {
        static void Main(string[] args) {
            string[] komp = { "Газеты", "Журналы", "Соцсети", "Радио","Телевидение",
                "Покупатели" };
            string[] V = { "отличное", "среднее", "плохое" };
            string[] U = { "наблюдать", "выяснить причину", "сообщить о мерах по улучшению" };
            double[] X = { 0.21, 0.36, 0.90, 0.17, 0.10, 0.53 };
            Console.WriteLine("*************************************************************" +
                "***********");
            Console.WriteLine("\t\t\tОЦЕНКА ПРОИЗВОДИМОЙ ОБУВИ");
            Console.WriteLine("*************************************************************" +
                "***********");
            Console.WriteLine($"{"Источник",-15}{"Параметр X",-15}{"Мнение",-15}{"Управляющее решение",-15}");
            Console.WriteLine("*************************************************************" +
               "***********");
            for (int i = 0; i < komp.Length; ++i) {
                if (X[i] >= 0.00 && X[i] <= 0.33) 
                    Console.WriteLine($"{komp[i], -15}{ X[i],-15}{ V[0], -15}{ U[0], -15}");
                if (X[i] >= 0.34 && X[i] <= 0.66)
                    Console.WriteLine($"{komp[i],-15}{ X[i],-15}{ V[1],-15}{ U[1],-15}");
                if (X[i] >= 0.67 && X[i] <= 1.00)
                    Console.WriteLine($"{komp[i],-15}{ X[i],-15}{ V[2],-15}{ U[2],-15}");
                Console.WriteLine();
            }
            Console.WriteLine("*************************************************************" +
               "***********");
            Console.ReadKey();
        }
    }
}
