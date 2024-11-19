using System;
using System.Drawing;
using System.Windows.Forms;

namespace czFlag {
    public partial class Flags : Form {
        bool choice = true;
        public Flags() {
            InitializeComponent();
        }
        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            if (choice) {
                DrawFlagOfTanzania(ClientRectangle, e.Graphics);
            } else {
                DrawFlagOfSolomonIslands(ClientRectangle, e.Graphics);
            }
        }
        private void Form1_Load(object sender, EventArgs e) { }
        private void DrawFlagOfSolomonIslands(Rectangle r, Graphics g) {
            const int PROPX = 1, PROPY = 2;
            g.Clear(Color.Gray);

            int h = r.Height, w = r.Width;
            Point O = new Point(0, 0);
            if (PROPX * r.Width > PROPY * r.Height) {
                w = h * PROPY / PROPX;
                O.X = (r.Width - w) / 2;
            } else if (PROPX * r.Width < PROPY * r.Height) {
                h = w * PROPX / PROPY;
                O.Y = (r.Height - h) / 2;
            }

            Point A = new Point(O.X + w * 1827 / 1920, O.Y);
            Point B = new Point(O.X + w, O.Y + h * 73 / 960);
            Point C = new Point(O.X, O.Y + h * 925 / 960);
            Point D = new Point(O.X + w * 125 / 1920, O.Y + h);
            Point E = new Point(O.X + w, O.Y);
            Point F = new Point(O.X, O.Y + h);
            Point G = new Point(O.X + w, O.Y + h);
            Point H = new Point(O.X + w * 145 / 1920, O.Y + h * 145 / 960);
            Point I = new Point(O.X + w * 530 / 1920, O.Y + h * 145 / 960);
            Point K = new Point(O.X + w * 147 / 1920, O.Y + h * 470 / 960);
            Point L = new Point(O.X + w * 530 / 1920, O.Y + h * 470 / 960);
            Point J = new Point(O.X + w * 335 / 1920, O.Y + h * 300 / 960);

            Point[] blue_part = new Point[3];
            blue_part[0] = O;
            blue_part[1] = A;
            blue_part[2] = C;
            Point[] yellow_part = new Point[6];
            yellow_part[0] = A;
            yellow_part[1] = E;
            yellow_part[2] = B;
            yellow_part[3] = D;
            yellow_part[4] = F;
            yellow_part[5] = C;
            Point[] green_part = new Point[3];
            green_part[0] = B;
            green_part[1] = G;
            green_part[2] = D;

            SolidBrush brush = new SolidBrush(Color.FromArgb(40, 97, 212));
            g.FillPolygon(brush, blue_part);
            brush.Color = Color.FromArgb(25, 90, 20);
            g.FillPolygon(brush, green_part);
            brush.Color = Color.FromArgb(225, 223, 20);
            g.FillPolygon(brush, yellow_part);
            brush.Color = Color.White;
            DrawStar(g, H, brush, (double)17 / 5, w, 5);
            DrawStar(g, I, brush, (double)17 / 5, w, 5);
            DrawStar(g, J, brush, (double)17 / 5, w, 5);
            DrawStar(g, K, brush, (double)17 / 5, w, 5);
            DrawStar(g, L, brush, (double)17 / 5, w, 5);
            brush.Dispose();
        }
        private void DrawStar(Graphics g, Point centralPoint, SolidBrush brush, double bigDtoSmallD, int realWidth, int rays) {
            double alpha = Math.PI / rays;
            Point[] points = new Point[rays * 2];
            double beta = Math.PI / 2;
            for (int i = 0; i < rays * 2; ++i, beta += alpha) {
                int d;
                if (i % 2 == 0)
                    d = realWidth / 60;
                else
                    d = realWidth * (int)bigDtoSmallD / 60;
                Point point = new Point((int)(centralPoint.X + d * Math.Cos(beta)), (int)(centralPoint.Y + d * Math.Sin(beta)));
                points[i] = point;
            }
            g.FillPolygon(brush, points);
        }
        private void DrawFlagOfTanzania(Rectangle r, Graphics g) {
            const int PROPX = 2, PROPY = 3;
            g.Clear(Color.Gray);

            int h = r.Height, w = r.Width;
            Point O = new Point(0, 0);
            if (PROPX * r.Width > PROPY * r.Height) {
                w = h * PROPY / PROPX;
                O.X = (r.Width - w) / 2;
            } else if (PROPX * r.Width < PROPY * r.Height) {
                h = w * PROPX / PROPY;
                O.Y = (r.Height - h) / 2;
            }
            Point A = new Point(O.X + w * 980 / 1280, O.Y);
            Point B = new Point(O.X + w * 1080 / 1280, O.Y);
            Point C = new Point(O.X, O.Y + h * 660 / 850);
            Point D = new Point(O.X, O.Y + h * 730 / 850);

            Point E = new Point(O.X + w, O.Y + h * 160 / 850);
            Point F = new Point(O.X + w * 220 / 1280, O.Y + h);
            Point G = new Point(O.X + w, O.Y + h * 230 / 850);
            Point H = new Point(O.X + w * 315 / 1280, O.Y + h);

            Point I = new Point(O.X, O.Y + h);
            Point J = new Point(O.X + w, O.Y);
            Point K = new Point(O.X + w, O.Y + h);


            Point[] green_part = new Point[3];
            green_part[0] = O;
            green_part[1] = A;
            green_part[2] = C;
            Point[] blue_part = new Point[3];
            blue_part[0] = H;
            blue_part[1] = G;
            blue_part[2] = K;
            Point[] black_part = new Point[6];
            black_part[0] = B;
            black_part[1] = J;
            black_part[2] = E;
            black_part[3] = F;
            black_part[4] = I;
            black_part[5] = D;
            Point[] yellow_part1 = new Point[4];
            yellow_part1[0] = A;
            yellow_part1[1] = B;
            yellow_part1[2] = D;
            yellow_part1[3] = C;
            Point[] yellow_part2 = new Point[4];
            yellow_part2[0] = E;
            yellow_part2[1] = G;
            yellow_part2[2] = H;
            yellow_part2[3] = F;

            SolidBrush brush = new SolidBrush(Color.White);
            Pen pen = new Pen(brush);
            pen.Color = Color.Blue;
            g.DrawLine(pen, G, H);
            pen.Color = Color.Yellow;
            g.DrawLine(pen, B, D);
            g.DrawLine(pen, E, F);
            pen.Color = Color.Green;
            g.DrawLine(pen, A, C);
            brush.Color = Color.FromArgb(14, 178, 79);
            g.FillPolygon(brush, green_part);
            brush.Color = Color.FromArgb(36, 148, 182);
            g.FillPolygon(brush, blue_part);
            brush.Color = Color.Black;
            g.FillPolygon(brush, black_part);
            brush.Color = Color.FromArgb(210, 210, 0);
            g.FillPolygon(brush, yellow_part2);
            brush.Color = Color.FromArgb(210, 210, 0);
            g.FillPolygon(brush, yellow_part1);
            brush.Dispose();
            pen.Dispose();
        }
        private void Form1_Resize_1(object sender, EventArgs e) {
            Invalidate();
        }
        private void Form1_MouseClick(object sender, MouseEventArgs e) {
            choice = !choice;
            Refresh();
        }
    }
}