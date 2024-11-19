using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Game_Fool {
    public partial class Game_Fool : Form {
        private string password = "FPMI";
        private bool CodeEntered = false;
        private int i = 0;
        public Game_Fool() {
            InitializeComponent();
            bttnNo.TabStop = false;
            bttnNo.BringToFront();
            
        }

        private void MovingButton() {
            if(!CodeEntered) {
                if (distBetweenCenterAndMouseX() <= 65 && distBetweenCenterAndMouseX() >= 0 &&
                    Math.Abs(distBetweenCenterAndMouseY()) <= 40) {
                    bttnNo.Left += 20;
                }
                if (distBetweenCenterAndMouseX() <= 65 && distBetweenCenterAndMouseX() > 40 && 
                    distBetweenCenterAndMouseY() <= 60 && distBetweenCenterAndMouseY() > 40) {
                    bttnNo.Left += 15;
                    bttnNo.Top += 15;
                }
                if (distBetweenCenterAndMouseX() <= 65 && distBetweenCenterAndMouseX() > 40 &&
                    distBetweenCenterAndMouseY() >= -90 && distBetweenCenterAndMouseY() <= -60) {
                    bttnNo.Left += 15;
                    bttnNo.Top -= 15;
                }
                if (distBetweenCenterAndMouseX() >= -65 && distBetweenCenterAndMouseX() <= 0 &&
                    Math.Abs(distBetweenCenterAndMouseY()) <= 40) {
                    bttnNo.Left -= 20;
                }
                if (distBetweenCenterAndMouseX() >= -65 && distBetweenCenterAndMouseX() <= -40 &&
                    distBetweenCenterAndMouseY() <= 60 && distBetweenCenterAndMouseY() >= 40) {
                    bttnNo.Left -= 15;
                    bttnNo.Top += 15;
                }
                if (distBetweenCenterAndMouseX() >= -65 && distBetweenCenterAndMouseX() <= -40 && 
                    distBetweenCenterAndMouseY() >= -90 && distBetweenCenterAndMouseY() <= -60) {
                    bttnNo.Left -= 15;
                    bttnNo.Top -= 15;
                }
                if (distBetweenCenterAndMouseY() <= 65 && distBetweenCenterAndMouseY() >= 0 && 
                    Math.Abs(distBetweenCenterAndMouseX()) <= 40) {
                    bttnNo.Top += 20;
                }
                if (distBetweenCenterAndMouseY() >= -90 && distBetweenCenterAndMouseY() <= 0 && 
                    Math.Abs(distBetweenCenterAndMouseX()) <= 60) {
                    bttnNo.Top -= 20;
                }
                if (bttnNo.Location.Y + 100 >= this.Size.Height || bttnNo.Location.Y -10 <= 0) {
                    bttnNo.Location = new Point(1034, 421);
                }
                if (bttnNo.Location.X + 40 >= this.Size.Width || bttnNo.Location.X + 40 <= 0) {
                    bttnNo.Location = new Point(1034, 421);
                }
            }
        }
        private int distBetweenCenterAndMouseX() {
            return bttnNo.Location.X + bttnNo.Size.Width / 2 - (MousePosition.X - Location.X);
        }
        private int distBetweenCenterAndMouseY() {
            return bttnNo.Location.Y + bttnNo.Size.Height / 2 - (MousePosition.Y - Location.Y);
        }
        private void Form1_MouseMove(object sender, MouseEventArgs e) {
            MovingButton();
        }

        private void bttnY_Click(object sender, EventArgs e) {
            MessageBox.Show("So sorry to hear that from you:(");
        }

        private void bttnNo_Click(object sender, EventArgs e) {
            MessageBox.Show("How did you do it?");
        }

        private void LabelQuestion_MouseMove(object sender, MouseEventArgs e) {
            MovingButton();
        }

        private void bttnY_MouseMove(object sender, MouseEventArgs e) {
            MovingButton();
        }
        protected override void OnKeyDown(KeyEventArgs e) {
            if(e.KeyCode == (Keys)password[i]) {
                e.Handled = true;
                ++i;
                if(i == password.Length) {
                    CodeEntered = true;
                    MessageBox.Show("You have entered password!");
                    i = 0;
                }
            } else {
                i = 0;
            }
        }

        private void bttnNo_Enter(object sender, EventArgs e) {
            bttnY.Focus();
        }

        private void bttnNo_MouseMove(object sender, MouseEventArgs e) {
            if (!CodeEntered) {
                bttnNo.Location = new Point(1034, 421);
            }
        }
    }
}