namespace Shooting {
    partial class Form1 {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.textBoxRadius = new System.Windows.Forms.TextBox();
            this.labelEnterRadius = new System.Windows.Forms.Label();
            this.textBoxNumberOfShots = new System.Windows.Forms.TextBox();
            this.labelEnterNumberOfShots = new System.Windows.Forms.Label();
            this.buttonShoot = new System.Windows.Forms.Button();
            this.textBoxY = new System.Windows.Forms.TextBox();
            this.textBoxX = new System.Windows.Forms.TextBox();
            this.labelEnterX = new System.Windows.Forms.Label();
            this.labelEnterY = new System.Windows.Forms.Label();
            this.ButtonStart = new System.Windows.Forms.Button();
            this.labelMisses = new System.Windows.Forms.Label();
            this.labelHits = new System.Windows.Forms.Label();
            this.labelShotsLeft = new System.Windows.Forms.Label();
            this.labelHitsCounter = new System.Windows.Forms.Label();
            this.labelMissesCounter = new System.Windows.Forms.Label();
            this.labelShotsLeftConter = new System.Windows.Forms.Label();
            this.buttonFinish = new System.Windows.Forms.Button();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.O = new System.Windows.Forms.Label();
            this.A = new System.Windows.Forms.Label();
            this.B = new System.Windows.Forms.Label();
            this.C = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // textBoxRadius
            // 
            this.textBoxRadius.BackColor = System.Drawing.SystemColors.Control;
            this.textBoxRadius.Location = new System.Drawing.Point(809, 15);
            this.textBoxRadius.Name = "textBoxRadius";
            this.textBoxRadius.Size = new System.Drawing.Size(126, 20);
            this.textBoxRadius.TabIndex = 0;
            this.textBoxRadius.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxRadius_Validating);
            // 
            // labelEnterRadius
            // 
            this.labelEnterRadius.AutoSize = true;
            this.labelEnterRadius.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelEnterRadius.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelEnterRadius.Location = new System.Drawing.Point(616, 16);
            this.labelEnterRadius.Name = "labelEnterRadius";
            this.labelEnterRadius.Size = new System.Drawing.Size(120, 16);
            this.labelEnterRadius.TabIndex = 1;
            this.labelEnterRadius.Text = "Enter the radius:";
            // 
            // textBoxNumberOfShots
            // 
            this.textBoxNumberOfShots.BackColor = System.Drawing.SystemColors.Control;
            this.textBoxNumberOfShots.Location = new System.Drawing.Point(809, 39);
            this.textBoxNumberOfShots.Name = "textBoxNumberOfShots";
            this.textBoxNumberOfShots.Size = new System.Drawing.Size(126, 20);
            this.textBoxNumberOfShots.TabIndex = 2;
            this.textBoxNumberOfShots.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxNumberOfShots_Validating);
            // 
            // labelEnterNumberOfShots
            // 
            this.labelEnterNumberOfShots.AutoSize = true;
            this.labelEnterNumberOfShots.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelEnterNumberOfShots.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelEnterNumberOfShots.Location = new System.Drawing.Point(617, 39);
            this.labelEnterNumberOfShots.Name = "labelEnterNumberOfShots";
            this.labelEnterNumberOfShots.Size = new System.Drawing.Size(186, 16);
            this.labelEnterNumberOfShots.TabIndex = 3;
            this.labelEnterNumberOfShots.Text = "Enter the number of shots:";
            // 
            // buttonShoot
            // 
            this.buttonShoot.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonShoot.Location = new System.Drawing.Point(838, 240);
            this.buttonShoot.Margin = new System.Windows.Forms.Padding(2);
            this.buttonShoot.Name = "buttonShoot";
            this.buttonShoot.Size = new System.Drawing.Size(96, 48);
            this.buttonShoot.TabIndex = 5;
            this.buttonShoot.Text = "Shoot";
            this.buttonShoot.UseVisualStyleBackColor = true;
            this.buttonShoot.Click += new System.EventHandler(this.buttonShoot_Click);
            // 
            // textBoxY
            // 
            this.textBoxY.BackColor = System.Drawing.SystemColors.Control;
            this.textBoxY.Location = new System.Drawing.Point(734, 270);
            this.textBoxY.Name = "textBoxY";
            this.textBoxY.Size = new System.Drawing.Size(76, 20);
            this.textBoxY.TabIndex = 7;
            // 
            // textBoxX
            // 
            this.textBoxX.BackColor = System.Drawing.SystemColors.Control;
            this.textBoxX.Location = new System.Drawing.Point(734, 240);
            this.textBoxX.Name = "textBoxX";
            this.textBoxX.Size = new System.Drawing.Size(76, 20);
            this.textBoxX.TabIndex = 6;
            // 
            // labelEnterX
            // 
            this.labelEnterX.AutoSize = true;
            this.labelEnterX.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelEnterX.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelEnterX.Location = new System.Drawing.Point(615, 240);
            this.labelEnterX.Name = "labelEnterX";
            this.labelEnterX.Size = new System.Drawing.Size(111, 16);
            this.labelEnterX.TabIndex = 8;
            this.labelEnterX.Text = "Enter X(0; 600):";
            // 
            // labelEnterY
            // 
            this.labelEnterY.AutoSize = true;
            this.labelEnterY.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelEnterY.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelEnterY.Location = new System.Drawing.Point(616, 270);
            this.labelEnterY.Name = "labelEnterY";
            this.labelEnterY.Size = new System.Drawing.Size(112, 16);
            this.labelEnterY.TabIndex = 9;
            this.labelEnterY.Text = "Enter Y(0; 600):";
            // 
            // ButtonStart
            // 
            this.ButtonStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ButtonStart.Location = new System.Drawing.Point(618, 72);
            this.ButtonStart.Margin = new System.Windows.Forms.Padding(2);
            this.ButtonStart.Name = "ButtonStart";
            this.ButtonStart.Size = new System.Drawing.Size(316, 44);
            this.ButtonStart.TabIndex = 10;
            this.ButtonStart.Text = "Start";
            this.ButtonStart.UseVisualStyleBackColor = true;
            this.ButtonStart.Click += new System.EventHandler(this.ButtonStart_Click);
            // 
            // labelMisses
            // 
            this.labelMisses.AutoSize = true;
            this.labelMisses.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelMisses.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelMisses.Location = new System.Drawing.Point(615, 384);
            this.labelMisses.Name = "labelMisses";
            this.labelMisses.Size = new System.Drawing.Size(61, 16);
            this.labelMisses.TabIndex = 14;
            this.labelMisses.Text = "Misses:";
            // 
            // labelHits
            // 
            this.labelHits.AutoSize = true;
            this.labelHits.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelHits.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelHits.Location = new System.Drawing.Point(616, 358);
            this.labelHits.Name = "labelHits";
            this.labelHits.Size = new System.Drawing.Size(39, 16);
            this.labelHits.TabIndex = 13;
            this.labelHits.Text = "Hits:";
            // 
            // labelShotsLeft
            // 
            this.labelShotsLeft.AutoSize = true;
            this.labelShotsLeft.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelShotsLeft.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelShotsLeft.Location = new System.Drawing.Point(615, 410);
            this.labelShotsLeft.Name = "labelShotsLeft";
            this.labelShotsLeft.Size = new System.Drawing.Size(76, 16);
            this.labelShotsLeft.TabIndex = 16;
            this.labelShotsLeft.Text = "Shots left:";
            // 
            // labelHitsCounter
            // 
            this.labelHitsCounter.AutoSize = true;
            this.labelHitsCounter.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelHitsCounter.Location = new System.Drawing.Point(711, 361);
            this.labelHitsCounter.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelHitsCounter.Name = "labelHitsCounter";
            this.labelHitsCounter.Size = new System.Drawing.Size(10, 13);
            this.labelHitsCounter.TabIndex = 17;
            this.labelHitsCounter.Text = "-";
            // 
            // labelMissesCounter
            // 
            this.labelMissesCounter.AutoSize = true;
            this.labelMissesCounter.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelMissesCounter.Location = new System.Drawing.Point(711, 387);
            this.labelMissesCounter.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelMissesCounter.Name = "labelMissesCounter";
            this.labelMissesCounter.Size = new System.Drawing.Size(10, 13);
            this.labelMissesCounter.TabIndex = 18;
            this.labelMissesCounter.Text = "-";
            // 
            // labelShotsLeftConter
            // 
            this.labelShotsLeftConter.AutoSize = true;
            this.labelShotsLeftConter.BackColor = System.Drawing.Color.DodgerBlue;
            this.labelShotsLeftConter.Location = new System.Drawing.Point(711, 413);
            this.labelShotsLeftConter.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelShotsLeftConter.Name = "labelShotsLeftConter";
            this.labelShotsLeftConter.Size = new System.Drawing.Size(10, 13);
            this.labelShotsLeftConter.TabIndex = 19;
            this.labelShotsLeftConter.Text = "-";
            // 
            // buttonFinish
            // 
            this.buttonFinish.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonFinish.Location = new System.Drawing.Point(619, 476);
            this.buttonFinish.Margin = new System.Windows.Forms.Padding(2);
            this.buttonFinish.Name = "buttonFinish";
            this.buttonFinish.Size = new System.Drawing.Size(315, 50);
            this.buttonFinish.TabIndex = 20;
            this.buttonFinish.Text = "Finish";
            this.buttonFinish.UseVisualStyleBackColor = true;
            this.buttonFinish.Click += new System.EventHandler(this.buttonFinish_Click);
            // 
            // errorProvider
            // 
            this.errorProvider.ContainerControl = this;
            // 
            // O
            // 
            this.O.AutoSize = true;
            this.O.BackColor = System.Drawing.Color.Aqua;
            this.O.Location = new System.Drawing.Point(-4, -1);
            this.O.Name = "O";
            this.O.Size = new System.Drawing.Size(28, 13);
            this.O.TabIndex = 21;
            this.O.Text = "(0,0)";
            // 
            // A
            // 
            this.A.AutoSize = true;
            this.A.BackColor = System.Drawing.Color.Aqua;
            this.A.Location = new System.Drawing.Point(560, -1);
            this.A.Name = "A";
            this.A.Size = new System.Drawing.Size(40, 13);
            this.A.TabIndex = 22;
            this.A.Text = "(600,0)";
            // 
            // B
            // 
            this.B.AutoSize = true;
            this.B.BackColor = System.Drawing.Color.Aqua;
            this.B.Location = new System.Drawing.Point(-4, 588);
            this.B.Name = "B";
            this.B.Size = new System.Drawing.Size(40, 13);
            this.B.TabIndex = 23;
            this.B.Text = "(0,600)";
            // 
            // C
            // 
            this.C.AutoSize = true;
            this.C.BackColor = System.Drawing.Color.Aqua;
            this.C.Location = new System.Drawing.Point(548, 588);
            this.C.Name = "C";
            this.C.Size = new System.Drawing.Size(52, 13);
            this.C.TabIndex = 24;
            this.C.Text = "(600,600)";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(984, 600);
            this.Controls.Add(this.C);
            this.Controls.Add(this.B);
            this.Controls.Add(this.A);
            this.Controls.Add(this.O);
            this.Controls.Add(this.buttonFinish);
            this.Controls.Add(this.labelShotsLeftConter);
            this.Controls.Add(this.labelMissesCounter);
            this.Controls.Add(this.labelHitsCounter);
            this.Controls.Add(this.labelShotsLeft);
            this.Controls.Add(this.labelMisses);
            this.Controls.Add(this.labelHits);
            this.Controls.Add(this.ButtonStart);
            this.Controls.Add(this.labelEnterY);
            this.Controls.Add(this.labelEnterX);
            this.Controls.Add(this.textBoxY);
            this.Controls.Add(this.textBoxX);
            this.Controls.Add(this.buttonShoot);
            this.Controls.Add(this.labelEnterNumberOfShots);
            this.Controls.Add(this.textBoxNumberOfShots);
            this.Controls.Add(this.labelEnterRadius);
            this.Controls.Add(this.textBoxRadius);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(1000, 634);
            this.MinimumSize = new System.Drawing.Size(1000, 634);
            this.Name = "Form1";
            this.Text = "GameShooting";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseClick);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxRadius;
        private System.Windows.Forms.Label labelEnterRadius;
        private System.Windows.Forms.TextBox textBoxNumberOfShots;
        private System.Windows.Forms.Label labelEnterNumberOfShots;
        private System.Windows.Forms.Button buttonShoot;
        private System.Windows.Forms.TextBox textBoxY;
        private System.Windows.Forms.TextBox textBoxX;
        private System.Windows.Forms.Label labelEnterX;
        private System.Windows.Forms.Label labelEnterY;
        private System.Windows.Forms.Button ButtonStart;
        private System.Windows.Forms.Label labelMisses;
        private System.Windows.Forms.Label labelHits;
        private System.Windows.Forms.Label labelShotsLeft;
        private System.Windows.Forms.Label labelHitsCounter;
        private System.Windows.Forms.Label labelMissesCounter;
        private System.Windows.Forms.Label labelShotsLeftConter;
        private System.Windows.Forms.Button buttonFinish;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Label O;
        private System.Windows.Forms.Label A;
        private System.Windows.Forms.Label C;
        private System.Windows.Forms.Label B;
    }
}

