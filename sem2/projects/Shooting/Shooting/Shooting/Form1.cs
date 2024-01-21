using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;

namespace Shooting {

    public partial class Form1 : Form {
        bool start = false;
        bool finish = false;
        bool hit = false;
        Target target;


        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {

            SwitchAvailabilityOfControls(false);
        }

        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            DrawPanel(ClientRectangle, e.Graphics);
            DrawField(e.Graphics);
            if (start) {
                DrawTarget(target.Radius, e.Graphics);
                foreach (Point p in target.points) {
                    DrawPoint(p, e.Graphics);
                }

                if (hit) {
                    DrawPoint(ShotPoint(), e.Graphics);
                    hit = false;
                }
                if (target.ShotsLeft() == 0 || finish) {
                    DrawField(e.Graphics);
                    FinishGame();
                }
            }
        }
        public void SwitchAvailabilityOfControls(bool choice) {
            labelEnterNumberOfShots.Enabled = !choice;
            labelEnterRadius.Enabled = !choice;
            textBoxRadius.Enabled = !choice;
            textBoxNumberOfShots.Enabled = !choice;
            ButtonStart.Enabled = !choice;

            labelEnterX.Enabled = choice;
            labelEnterY.Enabled = choice;
            textBoxX.Enabled = choice;
            textBoxY.Enabled = choice;
            buttonShoot.Enabled = choice;
            labelHits.Enabled = choice;
            labelMisses.Enabled = choice;
            labelHitsCounter.Enabled = choice;
            labelMissesCounter.Enabled = choice;
            labelShotsLeft.Enabled = choice;
            labelShotsLeftConter.Enabled = choice;
            buttonFinish.Enabled = choice;
        }
        private void DrawField(Graphics g) {
            Point TopOfVerticalLine = new Point(300, 0);
            Point BottomOfVerticalLine = new Point(300, 600);
            Point LeftHorizontalLine = new Point(0, 300);
            Point RightHorizontalLine = new Point(600, 300);

            Point[] FieldPoints = new Point[4];
            FieldPoints[0] = new Point(0, 0);
            FieldPoints[1] = new Point(600, 0);
            FieldPoints[2] = new Point(600, 600);
            FieldPoints[3] = new Point(0, 600);

            SolidBrush brush = new SolidBrush(Color.Aqua);
            g.FillPolygon(brush, FieldPoints);

            brush.Color = Color.Black;
            Pen pen = new Pen(brush);
            g.DrawLine(pen, BottomOfVerticalLine, TopOfVerticalLine);
            g.DrawLine(pen, LeftHorizontalLine, RightHorizontalLine);
            brush.Dispose();
            pen.Dispose();
        }
        public void DrawPanel(Rectangle r, Graphics g) {
            Point[] PanelPoints = new Point[4];
            PanelPoints[0] = new Point(600, 0);
            PanelPoints[1] = new Point(1000, 0);
            PanelPoints[2] = new Point(1000, 600);
            PanelPoints[3] = new Point(600, 600);

            SolidBrush brush = new SolidBrush(Color.DodgerBlue);
            g.FillPolygon(brush, PanelPoints);
            brush.Dispose();
        }
        public void DrawTarget(int r, Graphics g) {

            Point center = new Point(300, 300);

            Point[] pointsOfTriangle = new Point[3];
            pointsOfTriangle[0] = center;
            pointsOfTriangle[1] = new Point(center.X, center.Y + r);
            pointsOfTriangle[2] = new Point(center.X - r, center.Y + r);

            Rectangle rect = new Rectangle(center.X - r, center.Y - r, 2 * r, 2 * r);

            SolidBrush brush = new SolidBrush(Color.FromArgb(0, 0, 204));
            g.FillPie(brush, rect, 180.0F, 180.0F);
            g.FillPolygon(brush, pointsOfTriangle);
            brush.Dispose();
        }

        private void DrawPoint(Point p, Graphics g) {
            SolidBrush brush = new SolidBrush(Color.Red);
            g.FillEllipse(brush, p.X - 2, p.Y - 2, 4, 4);
            brush.Dispose();
        }

        public void StartGame() {
            int shots = Convert.ToInt32(textBoxNumberOfShots.Text);
            int radius = Convert.ToInt32(textBoxRadius.Text);

            target = new Target(shots, radius);
            start = true;
            Invalidate();
            SwitchAvailabilityOfControls(true);
            UpdateCounters();
        }

        public void UpdateCounters() {
            labelHitsCounter.Text = target.NumberOfHits.ToString();
            labelHitsCounter.Update();
            labelMissesCounter.Text = target.NumberOfMisses.ToString();
            labelMissesCounter.Update();
            labelShotsLeftConter.Text = (target.ShotsLeft()).ToString();
            labelShotsLeftConter.Update();
        }
        public Point ShotPoint() {
            int X = Convert.ToInt32(textBoxX.Text);
            int Y = Convert.ToInt32(textBoxY.Text);

            return new Point(X, Y);
        }
        public void FinishGame() {
            start = false;
            finish = false;

            MessageBox.Show("Game over!\nYour hits: " + target.NumberOfHits.ToString() + "\nYour misses: " + target.NumberOfMisses.ToString());
            SwitchAvailabilityOfControls(false);
            ResetValues();
            Invalidate();
            textBoxRadius.Focus();
        }

        public bool CheckShot(Point center, Point p, int r) {
            int distX = Math.Abs(p.X - center.X);
            int distY = Math.Abs(p.Y - center.Y);
            if (Math.Pow(distX, 2) + Math.Pow(distY, 2) <= Math.Pow(r, 2) && p.Y <= center.Y) {
                return true;
            }
            int C = -600;
            int A = 1;
            int B = 1;
            double sigma = -(A * p.X + B * p.Y + C);
            if (sigma <= 0 && p.X <= center.X && p.Y <= center.Y + r) {
                return true;
            }
            return false;
        }

        private void textBoxRadius_Validating(object sender, CancelEventArgs e) {
            int n;
            string str = textBoxRadius.Text;
            if (!int.TryParse(str, out n)) {
                errorProvider.SetError(textBoxRadius, "Incorrect value!");
                e.Cancel = true;
            } else if (Convert.ToInt32(str) <= 0 || Convert.ToInt32(str) > 300) {
                MessageBox.Show("Enter positive number less or equal to 300.");
                e.Cancel = true;
            } else {
                errorProvider.Clear();
            }
        }

        private void ButtonStart_Click(object sender, EventArgs e) {
            if (!(String.IsNullOrEmpty(textBoxRadius.Text) || String.IsNullOrEmpty(textBoxNumberOfShots.Text))) {
                StartGame();
            }
        }

        private void buttonShoot_Click(object sender, EventArgs e) {
            MakeShot();
            UpdateCounters();
            Invalidate();
        }

        public void MakeShot() {
            Point p = ShotPoint();
            Point center = new Point(300, 300);
            if (0 <= p.X && p.X <= 600 && 0 <= p.Y && p.Y <= 600) {
                if (CheckShot(center, p, target.Radius)) {
                    ++target.NumberOfHits;
                    hit = true;
                    target.points.Add(p);
                } else {
                    ++target.NumberOfMisses;
                }
            } else {
                MessageBox.Show("This Point doesn't belong to field.");
            }
        }

        private void buttonFinish_Click(object sender, EventArgs e) {
            finish = true;
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e) {
            int X = Cursor.Position.X - Location.X - 5;
            int Y = Cursor.Position.Y - Location.Y - 30;
            if (start&&X<=600) {
                textBoxX.Text = X.ToString();
                textBoxY.Text = Y.ToString();
                MakeShot();
                UpdateCounters();
                Invalidate();
            }
        }

        private void textBoxNumberOfShots_Validating(object sender, CancelEventArgs e) {
            int n;
            string str = textBoxNumberOfShots.Text;
            if (!int.TryParse(str, out n)) {
                errorProvider.SetError(textBoxNumberOfShots, "Incorrect value!");
                e.Cancel = true;
            } else if (Convert.ToInt32(str) <= 0) {
                MessageBox.Show("Enter positive number.");
                e.Cancel = true;
            } else {
                errorProvider.Clear();
            }
        }
        public void ResetValues() {
            textBoxNumberOfShots.Text = null;
            textBoxRadius.Text = null;
            labelHitsCounter.Text = "-";
            labelMissesCounter.Text = "-";
            labelShotsLeftConter.Text = "-";

            textBoxNumberOfShots.Update();
            textBoxRadius.Update();
            labelHitsCounter.Update();
            labelMissesCounter.Update();
            labelShotsLeftConter.Update();
        }

        private void button1_Click(object sender, EventArgs e) {
            textBoxRadius.Enabled = false;
            Application.Exit();
        }

    }
    class Target {
        int numberOfShots;
        int radius;
        int numberOfHits = 0;
        int numberOfMisses = 0;
        public List<Point> points = new List<Point>();

        public Target(int shots, int rad) {
            NumberOfShots = shots;
            Radius = rad;
        }
        public int NumberOfShots {
            get {
                return numberOfShots;
            }
            set {
                if (value < 0) {
                    throw new ArgumentException("Number of shots must be non-negative.");
                }
                numberOfShots = value;
            }
        }
        public int Radius {
            get {
                return radius;
            }
            set {
                if (value <= 0) {
                    throw new ArgumentException("Radius must be positive.");
                }
                radius = value;
            }
        }
        public int NumberOfHits {
            get {
                return numberOfHits;
            }
            set {
                if (value < 0) {
                    throw new ArgumentException("Number of hits must be non-negative.");
                }
                numberOfHits = value;
            }
        }
        public int NumberOfMisses {
            get {
                return numberOfMisses;
            }
            set {
                if (value < 0) {
                    throw new ArgumentException("Number of misses must be non-negative.");
                }
                numberOfMisses = value;
            }
        }
        public int ShotsLeft() {
            return NumberOfShots - NumberOfMisses - NumberOfHits;
        }

    }
}


