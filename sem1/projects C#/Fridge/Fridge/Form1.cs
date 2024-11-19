using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Fridge {
    public partial class fridge : Form {
        public fridge() {
            InitializeComponent();
        }
        const int SIZE = 4;
        fridge fr = new fridge(SIZE);


        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e) {
            
        }

        private void fridge_Load(object sender, EventArgs e) {
            dgv.RowCount = SIZE;
            dgv.ColumnCount = SIZE;
            for(int i =0; i<SIZE; ++i) {
                dgv.Columns[i].Width = 50;
            }
            for(int i =0; i < SIZE; ++i) {
                dgv.Rows[i].Height = 50;
            }
        }

        void showPosition() {
            for(int i =0; i<SIZE; ++i) {
                for(int j =0; j < SIZE; ++j) {
                    if (fr.table[i, j]) {
                        dgv.Rows[i].Cells[j].Value = "Opened";
                        dgv.Rows[i].Cells[j].Style.BackColor = Color.Azure;
                        dgv.Rows[i].Cells[j].Style.ForeColor = Color.Black;
                    } else {
                        dgv.Rows[i].Cells[j].Value = "Closed";
                        dgv.Rows[i].Cells[j].Style.BackColor = Color.Red;
                        dgv.Rows[i].Cells[j].Style.ForeColor = Color.White;
                    }
                }
            }
        }

        private void dgv_CellClick(object sender, DataGridViewCellEventArgs e) {
            fr.touch(e.RowIndex, e.ColumnIndex);
            showPosition();
            if (fr.isFinished()) {
                MessageBox.Show("Холодильник открыт, кот выпущен");
            }
        }
    }
}
