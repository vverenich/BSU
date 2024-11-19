using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace The_game {
    class Game {
        int size;
        public int[,] cells;
        public int[,] beginningCells;
        public int space_x, space_y;
        public int clicks = 0;

        static Random rand = new Random();
        public Game(int size) {
            if (size < 2) {
                size = 2;
            }
            if (size > 5) {
                size = 5;
            }
            this.size = size;
            cells = new int[size, size];
            beginningCells = new int[size, size];
        }
        public void Start() {
            for (int x = 0; x < size; x++)
                for (int y = 0; y < size; y++)
                    cells[x, y] = CoordinatesToPosition(x, y) + 1;
            space_x = size - 1;
            space_y = size - 1;
            cells[space_x, space_y] = 0;
        }
        public void Swap(int position) {
            int x, y;
            PositionToCoordinates(position, out x, out y);
            if (Math.Abs(space_x - x) + Math.Abs(space_y - y) != 1) {
                return;
            }
            cells[space_x, space_y] = cells[x, y];
            cells[x, y] = 0;
            space_x = x;
            space_y = y;
            ++clicks;
        }
        public void RandomSwap() {

            int a = rand.Next(0, 4);
            int x = space_x;
            int y = space_y;
            switch (a) {
                case 0:
                    --x;
                    break;
                case 1:
                    ++x;
                    break;
                case 2:
                    --y;
                    break;
                case 3:
                    ++y;
                    break;
            }
            Swap(CoordinatesToPosition(x, y));
        }
        public int get_number(int position) {
            int x, y;
            PositionToCoordinates(position, out x, out y);
            if (x < 0 || x >= size)
                return 0;
            if (y < 0 || y >= size)
                return 0;
            return cells[x, y];
        }

        public int CoordinatesToPosition(int x, int y) {
            if (x < 0)
                x = 0;
            if (x > size - 1)
                x = size - 1;
            if (y < 0)
                y = 0;
            if (y > size - 1)
                y = size - 1;
            return y * size + x;
        }
        private void PositionToCoordinates(int position, out int x, out int y) {
            if (position < 0) {
                position = 0;
            }
            if (position > size * size - 1) {
                position = size * size - 1;
            }
            x = position % size;
            y = position / size;
        }
        public bool CheckNumbers() {
            if (!(space_x == size - 1 && space_y == size - 1)){
                return false;
            }
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if (!(i == size - 1 && j == size - 1)) {
                        if (cells[i, j] != CoordinatesToPosition(i, j) + 1) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
    }
}