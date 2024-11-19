using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Calculator {
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();
        }

    

        private void button_Click(object sender, RoutedEventArgs e) {
            try {
                double a = Double.Parse(textBox1.Text) + Double.Parse(textBox3.Text);
                textBox2.Text = a.ToString();
            } catch (Exception) {
                MessageBox.Show("Invalid parameter.");
            }
        }

        private void button_Copy_Click(object sender, RoutedEventArgs e) {
            try {
                double a = Double.Parse(textBox1.Text) - Double.Parse(textBox3.Text);
                textBox2.Text = a.ToString();
            } catch (Exception) {
                MessageBox.Show("Invalid parameter.");
            }
        }

        private void textBox3_TextChanged(object sender, TextChangedEventArgs e) {

        }

        private void textBox1_TextChanged(object sender, TextChangedEventArgs e) {

        }

        private void textBox2_TextChanged(object sender, TextChangedEventArgs e) {

        }

        private void button_Copy1_Click(object sender, RoutedEventArgs e) {
            try {
                double a = Double.Parse(textBox1.Text) * Double.Parse(textBox3.Text);
                textBox2.Text = a.ToString();
            } catch (Exception) {
                MessageBox.Show("Invalid parameter.");
            }
        }

        private void button_Copy2_Click(object sender, RoutedEventArgs e) {
            try {
                double a = Double.Parse(textBox1.Text) / Double.Parse(textBox3.Text);
                double b = Double.Parse(textBox3.Text);
                if (b != 0) {
                    textBox2.Text = Math.Round(Double.Parse(textBox1.Text) / Double.Parse(textBox3.Text), 13).ToString();
                } else {
                    textBox2.Text = "You can't devide by zero.";
                }
            } catch (Exception) {
                MessageBox.Show("Invalid parameter.");
            }
        }

        private void textBox3_LostFocus(object sender, RoutedEventArgs e) {

        }
    }
}

