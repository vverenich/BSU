using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Game_ {
    public partial class Form1 : Form {
        Button[,] cells;
        Image[,] BeginningCells;
        int size = 4;
        int emptyCell_i;
        int emptyCell_j;
        DateTime time = new DateTime(0, 0);
        int clicks = 0;

        private void FillCells() {
            for (int i = 0; i < size * size - 1; ++i) {
                button(i).Image = Image.FromFile(@"D:\\ImagesForLab\image_part_0" + i + ".jpg");
            }
        }
        public void Start() {
            cells = new Button[size, size];
            BeginningCells = new Image[size, size];
            emptyCell_i = size - 1;
            emptyCell_j = size - 1;
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cells[i, j] = button(CoordinatesToPosition(i, j));
                }
            }
            emptyCell_i = size - 1;
            emptyCell_j = size - 1;
        }
        public Form1() {
            InitializeComponent();
        }

        private void button_Click(object sender, EventArgs e) {
            int position = Convert.ToInt32(((Button)sender).Tag);
            Swap(position);
            if (CheckNumbers()) {
                timer1.Stop();
                MessageBox.Show("You won!");
            }
        }
        private Button button(int pos) {
            switch (pos) {
                case 0:
                    return button0;
                case 1:
                    return button1;
                case 2:
                    return button2;
                case 3:
                    return button3;
                case 4:
                    return button4;
                case 5:
                    return button5;
                case 6:
                    return button6;
                case 7:
                    return button7;
                case 8:
                    return button8;
                case 9:
                    return button9;
                case 10:
                    return button10;
                case 11:
                    return button11;
                case 12:
                    return button12;
                case 13:
                    return button13;
                case 14:
                    return button14;
                case 15:
                    return button15;
                default:
                    return null;
            }
        }

        private void newGameToolStripMenuItem_Click(object sender, EventArgs e) {
            start_game();
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    BeginningCells[i, j]= cells[i, j].Image;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e) {
            start_game();
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    BeginningCells[i, j] = cells[i, j].Image;
                }
            }
        }
        private void start_game() {
            Start();
            tableLayoutPanel1.Enabled = true;
            FillCells();
            for (int i = 0; i < 20; ++i) {
                RandomSwap();
            }
            clicks = 0;
            toolStripStatusLabel4.Text = clicks.ToString();
            RestartTime();
        }
        private void PositionToCoordinates(int pos, out int i, out int j) {
            i = pos % size;
            j = pos / size;
        }
        private int CoordinatesToPosition(int i, int j) {
            return j * size + i;
        }
        private void Swap(int pos) {
            int i, j;
            PositionToCoordinates(pos, out i, out j);
            if (Math.Abs(emptyCell_i - i) + Math.Abs(emptyCell_j - j) == 1) {
                cells[emptyCell_i, emptyCell_j].Image = cells[i, j].Image;
                cells[i, j].Image = null;
                emptyCell_i = i;
                emptyCell_j = j;
            }
            ++clicks;
            toolStripStatusLabel4.Text = clicks.ToString();

        }
        private void RandomSwap() {
            static Random rand = new Random();
            int a = rand.Next(0, 4);
            int i = emptyCell_i;
            int j = emptyCell_j;
            bool CanBeShifted = false;
            while (!CanBeShifted) {
                if (i - 1 >= 0 && a == 0) {
                    --i;
                    CanBeShifted = true;
                }
                if (i + 1 < size && a == 1) {
                    ++i;
                    CanBeShifted = true;
                }
                if (j - 1 >= 0 && a == 2) {
                    --j;
                    CanBeShifted = true;
                }
                if (j + 1 < size && a == 3) {
                    ++j;
                    CanBeShifted = true;
                }
                if (!CanBeShifted) {
                    if (a < 3) {
                        ++a;
                    } else {
                        a = 0;
                    }
                }
            }
            Swap(CoordinatesToPosition(i, j));
        }
        private bool CheckNumbers() {
            if (emptyCell_i == size - 1 && emptyCell_j == size - 1) {
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < size; ++j) {
                        if (!(i == size - 1 && j == size - 1)) {
                            if (Convert.ToInt32(cells[i, j].Tag) != CoordinatesToPosition(i, j)) {
                                return false;
                            }
                        }
                    }
                }
                tableLayoutPanel1.Enabled = false;
                return true;
            } else {
                return false;
            }
        }

        private void timer1_Tick(object sender, EventArgs e) {
            time = time.AddSeconds(1);
            toolStripStatusLabel2.Text = time.ToString("mm:ss");
        }
        private void RestartTime() {
            toolStripStatusLabel2.Text = "00:00";
            time = new DateTime(0, 0);
            timer1.Start();
        }

        private void repeatGameToolStripMenuItem_Click(object sender, EventArgs e) {
            start_game();
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cells[i, j].Image = BeginningCells[i, j].Image;
                }
            }
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e) {

        }
    }
}






