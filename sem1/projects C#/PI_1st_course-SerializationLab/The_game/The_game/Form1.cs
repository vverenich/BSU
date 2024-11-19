using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.VisualBasic;
using System.Xml.Serialization;
using System.IO;

namespace The_game {

    public partial class Form1 : Form {
        Game game;
        DateTime time;
        string playerName;
        DateTime startTime;
        public Form1() {
            InitializeComponent();
            game = new Game(4);
        }
        private void button_Click(object sender, EventArgs e) {
            int position = Convert.ToInt16(((Button)sender).Tag);
            game.Swap(position);
            refresh();
            if (game.CheckNumbers()) {
                timer1.Stop();
                MessageBox.Show("You won!");
                GameResult result = new GameResult(playerName, startTime, time, game.clicks);
                WriteResultToXML(result);
                tableLayoutPanel1.Enabled = false;
            }
            toolStripStatusLabel4.Text = Convert.ToString(game.clicks);
        }
        private Button button(int position) {
            switch (position) {
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
        private void menu_start_Click(object sender, EventArgs e) {
            StartGame();
        }
        private void StartGame() {
            game.Start();
            playerName = Interaction.InputBox("Enter your name:", "Input name", "Anonymouse", 500, 300);
            startTime = DateTime.Now;

            tableLayoutPanel1.Enabled = true;
            for (int j = 0; j < 100; j++)
                game.RandomSwap();
            game.clicks = 0;
            refresh();
            toolStripStatusLabel4.Text = Convert.ToString(game.clicks);
            RestartTime();
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    game.beginningCells[i, j] = game.cells[i, j];
                }
            }
        }

        private void RestartTime() {
            toolStripStatusLabel2.Text = "00:00";
            time = new DateTime(0, 0);
            timer1.Start();
        }
        private void refresh() {
            for (int position = 0; position < 16; ++position) {
                int nr = game.get_number(position);
                button(position).Text = nr.ToString();
                button(position).Visible = (nr > 0);
            }
        }
        private void Form1_Load(object sender, EventArgs e) {
            StartGame();
        }

        private void timer1_Tick_1(object sender, EventArgs e) {
            time = time.AddSeconds(1);
            toolStripStatusLabel2.Text = time.ToString("mm:ss");
        }

        private void newGameToolStripMenuItem_Click(object sender, EventArgs e) {
            StartGame();
        }

        private void repeatGameToolStripMenuItem_Click(object sender, EventArgs e) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    game.cells[i, j] = game.beginningCells[i, j];
                    if (game.beginningCells[i, j] == 0) {
                        game.space_x = i;
                        game.space_y = j;
                    }
                }
            }
            refresh();
            game.clicks = 0;
            toolStripStatusLabel4.Text = Convert.ToString(game.clicks);
            RestartTime();
        }
        private static void WriteResultToXML(GameResult result) {
            XmlSerializer formatter = new XmlSerializer(typeof(List<GameResult>));
            List<GameResult> results = new List<GameResult> { };

            using (StreamReader sr = new StreamReader("results.xml")) {
                if (!sr.EndOfStream) {
                    results = (List<GameResult>)formatter.Deserialize(sr);
                }
            }

            using (StreamWriter sw = new StreamWriter("results.xml")) {
                results.Add(result);
                formatter.Serialize(sw, results);
            }
        }

        private void getBestResults_Click(object sender, EventArgs e) {
            XmlSerializer formatter = new XmlSerializer(typeof(List<GameResult>));
            List<GameResult> results = new List<GameResult> { };

            using (StreamReader sr = new StreamReader("results.xml")) {
                if (!sr.EndOfStream) {
                    results = (List<GameResult>)formatter.Deserialize(sr);
                }
            }

            string resultsString = "";
            results.Sort((res1, res2) => res1.Time.CompareTo(res2.Time));
            for (int i = 0; i < results.Count && i < 10; ++i) {
                resultsString += "\n" + (i + 1).ToString() + ". " + results[i].ToString();
            }
            MessageBox.Show(resultsString);
        }

        private void getBestResultsByMoves_Click(object sender, EventArgs e) {
            XmlSerializer formatter = new XmlSerializer(typeof(List<GameResult>));
            List<GameResult> results = new List<GameResult> { };

            using (StreamReader sr = new StreamReader("results.xml")) {
                if (!sr.EndOfStream) {
                    results = (List<GameResult>)formatter.Deserialize(sr);
                }
            }

            string resultsString = "";
            results.Sort((res1, res2) => res1.Clicks.CompareTo(res2.Clicks));
            for (int i = 0; i < results.Count && i < 10; ++i) {
                resultsString += "\n" + (i + 1).ToString() + ". " + results[i].ToString();
            }
            MessageBox.Show(resultsString);
        }

        private void getLastResults_Click(object sender, EventArgs e) {
            XmlSerializer formatter = new XmlSerializer(typeof(List<GameResult>));
            List<GameResult> results = new List<GameResult> { };

            using (StreamReader sr = new StreamReader("results.xml")) {
                if (!sr.EndOfStream) {
                    results = (List<GameResult>)formatter.Deserialize(sr);
                }
            }

            string resultsString = "";
            for (int i = 0; i < results.Count && i < 10; ++i) {
                resultsString += "\n" + (i + 1).ToString() + ". " + results[i].ToString();
            }
            MessageBox.Show(resultsString);
        }

        private void deleteResultsFromDate_Click(object sender, EventArgs e) {
            XmlSerializer formatter = new XmlSerializer(typeof(List<GameResult>));
            List<GameResult> results = new List<GameResult> { };

            using (StreamReader sr = new StreamReader("results.xml")) {
                if (!sr.EndOfStream) {
                    results = (List<GameResult>)formatter.Deserialize(sr);
                }
            }

            DateTime date = new DateTime();

            string str = Interaction.InputBox("Enter date(example 05/10/2002):");
            if (DateTime.TryParse(str, out date)) {
                results.RemoveAll(res => res.StartTime>date);
            } else {
                MessageBox.Show("Wrong input.");
            }

            using(StreamWriter sw = new StreamWriter("results.xml")) {
                formatter.Serialize(sw, results);
            }
        }
    }
}
