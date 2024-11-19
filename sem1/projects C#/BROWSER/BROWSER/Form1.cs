using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BROWSER {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e) {
            webBrowser1.GoBack();
        }

        private void forward_Click(object sender, EventArgs e) {
            webBrowser1.GoForward();
        }

        private void Update_Click(object sender, EventArgs e) {
            webBrowser1.Refresh();
        }

        private void textBox1_TextChanged(object sender, EventArgs e) {

        }

        private void Search_Click(object sender, EventArgs e) {
            webBrowser1.Navigate("http://" + textBox1.Text);
        }

        private void Form1_Load(object sender, EventArgs e) {

        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e) {

        }
    }
}
