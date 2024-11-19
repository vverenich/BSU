using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Timer {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }
        int i = 1;
        private void timer1_Tick(object sender, EventArgs e) {
            textBox1.Text = i.ToString();
            ++i;
        }

        private void Form1_Load(object sender, EventArgs e) {

        }

        private void label1_Click(object sender, EventArgs e) {

        }

        private void textBox1_TextChanged(object sender, EventArgs e) {

        }

        private void button1_Click(object sender, EventArgs e) {
            Timer.Start();
        }

        private void button2_Click(object sender, EventArgs e) {
            Timer.Stop();
        }
    }
}
