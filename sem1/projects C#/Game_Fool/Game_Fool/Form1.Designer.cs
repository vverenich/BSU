
namespace Game_Fool {
    partial class Game_Fool {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.bttnNo = new System.Windows.Forms.Button();
            this.LabelQuestion = new System.Windows.Forms.Label();
            this.bttnY = new System.Windows.Forms.Button();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.SuspendLayout();
            // 
            // bttnNo
            // 
            this.bttnNo.Font = new System.Drawing.Font("Segoe Print", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.bttnNo.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.bttnNo.Location = new System.Drawing.Point(1034, 421);
            this.bttnNo.Name = "bttnNo";
            this.bttnNo.Size = new System.Drawing.Size(80, 80);
            this.bttnNo.TabIndex = 0;
            this.bttnNo.TabStop = false;
            this.bttnNo.Text = "Нет";
            this.bttnNo.UseVisualStyleBackColor = true;
            this.bttnNo.Click += new System.EventHandler(this.bttnNo_Click);
            this.bttnNo.Enter += new System.EventHandler(this.bttnNo_Enter);
            this.bttnNo.MouseMove += new System.Windows.Forms.MouseEventHandler(this.bttnNo_MouseMove);
            // 
            // LabelQuestion
            // 
            this.LabelQuestion.AutoSize = true;
            this.LabelQuestion.Font = new System.Drawing.Font("Segoe Print", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.LabelQuestion.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.LabelQuestion.Location = new System.Drawing.Point(754, 269);
            this.LabelQuestion.Name = "LabelQuestion";
            this.LabelQuestion.Size = new System.Drawing.Size(360, 105);
            this.LabelQuestion.TabIndex = 1;
            this.LabelQuestion.Text = "Ты дурак?";
            this.LabelQuestion.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.LabelQuestion.MouseMove += new System.Windows.Forms.MouseEventHandler(this.LabelQuestion_MouseMove);
            // 
            // bttnY
            // 
            this.bttnY.Font = new System.Drawing.Font("Segoe Print", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.bttnY.Location = new System.Drawing.Point(754, 421);
            this.bttnY.MaximumSize = new System.Drawing.Size(80, 80);
            this.bttnY.MinimumSize = new System.Drawing.Size(80, 80);
            this.bttnY.Name = "bttnY";
            this.bttnY.Size = new System.Drawing.Size(80, 80);
            this.bttnY.TabIndex = 2;
            this.bttnY.TabStop = false;
            this.bttnY.Text = "Да";
            this.bttnY.UseVisualStyleBackColor = true;
            this.bttnY.Click += new System.EventHandler(this.bttnY_Click);
            this.bttnY.MouseMove += new System.Windows.Forms.MouseEventHandler(this.bttnY_MouseMove);
            // 
            // Game_Fool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1765, 895);
            this.Controls.Add(this.bttnY);
            this.Controls.Add(this.LabelQuestion);
            this.Controls.Add(this.bttnNo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.KeyPreview = true;
            this.Name = "Game_Fool";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Game_Fool";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseMove);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bttnNo;
        private System.Windows.Forms.Label LabelQuestion;
        private System.Windows.Forms.Button bttnY;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}

