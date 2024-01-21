using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Threads {
    class SayClass {
        public static int numberOfPrintedMessages = 7;
        static object locker = new object();
        string word;
        int numberOfRepeats;
        int delay;


        public SayClass(string str, int repeats, int del) {
            Word = str;
            NumberOfRepeats = repeats;
            Delay = del;
        }
        public string Word {
            get {
                return word;
            }
            set {
                word = value;
            }
        }
        public int NumberOfRepeats {
            get {
                return numberOfRepeats;
            }
            set {
                if (value < 0) {
                    throw new ArgumentException("Number of repeats can't be negative number.");
                }
                numberOfRepeats = value;
            }
        }
        public int Delay {
            get {
                return delay;
            }
            set {
                if (value < 0) {
                    throw new ArgumentException("Delay value can't be negative number.");
                }
                delay = value;
            }
        }
        public void PrintWord() {
            for (int i = 0; i < NumberOfRepeats && numberOfPrintedMessages != 0; ++i) {
                lock (locker) {
                    --numberOfPrintedMessages;
                }
                    Console.Write(Word + " ");
                    Thread.Sleep(Delay);
            }
        }
    }
    class Program {
        static void Main(string[] args) {
            SayClass SayPapa = new SayClass("papa", 4, 1000);
            SayClass SayMama = new SayClass("mama", 4, 1000);
            SayClass SaySon = new SayClass("son", 4, 1000);

            Thread t1 = new Thread(SayMama.PrintWord);
            Thread t2 = new Thread(SayPapa.PrintWord);
            Thread t3 = new Thread(SaySon.PrintWord);

            t1.Start();
            t2.Start();
            t3.Start();

            t1.Join();
            t2.Join();
            t3.Join();
        }
    }
}
