using System;
using System.Collections.Generic;
using System.Text;

namespace Fridge {
    partial class fridge {
        public bool[,] table { get; private set; }
        public int size { get; private set; }

        public fridge(int aSize) {
            size = aSize;
            table = new bool[aSize, aSize];
        }
        void newGame() {
            Random rnd = new Random();
            for(int i =0; i< size; ++i) {
                for(int j =0; j<size; ++j) {
                    table[i, j] = rnd.Next(2) == 0;
                }
            }
        }
        public bool isFinished() {
            for(int i =0; i<size; ++i) {
                for(int j =0; j < size; ++j) {
                    if (!table[i, j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        public void touch(int r, int c) {
            for(int i =0; i<size; ++i) {
                table[i, c] = !table[i, c];
            }
            for(int i = 0; i < size; ++i) {
                table[r, i] = !table[r, i];
            }
            table[r, c] = !table[r, c];
        }
    }
}