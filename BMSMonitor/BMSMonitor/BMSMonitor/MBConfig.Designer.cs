namespace BMSMonitor
{
    partial class MBConfig
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MBConfig));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.MBCan = new System.Windows.Forms.Button();
            this.MBConOK = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.ScanTxt = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.NumTxt = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.AddrTxt = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.FuncTxt = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.IDTxt = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.MBCan);
            this.groupBox1.Controls.Add(this.MBConOK);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.ScanTxt);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.NumTxt);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.AddrTxt);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.FuncTxt);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.IDTxt);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(14, 14);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(5);
            this.groupBox1.Size = new System.Drawing.Size(325, 378);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "MBInfo";
            // 
            // MBCan
            // 
            this.MBCan.Location = new System.Drawing.Point(165, 316);
            this.MBCan.Name = "MBCan";
            this.MBCan.Size = new System.Drawing.Size(102, 48);
            this.MBCan.TabIndex = 12;
            this.MBCan.Text = "Cancel";
            this.MBCan.UseVisualStyleBackColor = true;
            this.MBCan.Click += new System.EventHandler(this.MBCan_Click);
            // 
            // MBConOK
            // 
            this.MBConOK.Location = new System.Drawing.Point(17, 316);
            this.MBConOK.Name = "MBConOK";
            this.MBConOK.Size = new System.Drawing.Size(102, 48);
            this.MBConOK.TabIndex = 11;
            this.MBConOK.Text = "OK";
            this.MBConOK.UseVisualStyleBackColor = true;
            this.MBConOK.Click += new System.EventHandler(this.MBConOK_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(255, 259);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(58, 24);
            this.label6.TabIndex = 10;
            this.label6.Text = "[ms]";
            // 
            // ScanTxt
            // 
            this.ScanTxt.Location = new System.Drawing.Point(141, 254);
            this.ScanTxt.Name = "ScanTxt";
            this.ScanTxt.Size = new System.Drawing.Size(108, 35);
            this.ScanTxt.TabIndex = 9;
            this.ScanTxt.Text = "1000";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(13, 259);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(118, 24);
            this.label5.TabIndex = 8;
            this.label5.Text = "Scan Rate";
            // 
            // NumTxt
            // 
            this.NumTxt.Location = new System.Drawing.Point(141, 201);
            this.NumTxt.Name = "NumTxt";
            this.NumTxt.Size = new System.Drawing.Size(108, 35);
            this.NumTxt.TabIndex = 7;
            this.NumTxt.Text = "10";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 206);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(94, 24);
            this.label4.TabIndex = 6;
            this.label4.Text = "Quanity";
            // 
            // AddrTxt
            // 
            this.AddrTxt.Location = new System.Drawing.Point(141, 148);
            this.AddrTxt.Name = "AddrTxt";
            this.AddrTxt.Size = new System.Drawing.Size(108, 35);
            this.AddrTxt.TabIndex = 5;
            this.AddrTxt.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 153);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(94, 24);
            this.label3.TabIndex = 4;
            this.label3.Text = "Address";
            // 
            // FuncTxt
            // 
            this.FuncTxt.Location = new System.Drawing.Point(141, 94);
            this.FuncTxt.Name = "FuncTxt";
            this.FuncTxt.Size = new System.Drawing.Size(108, 35);
            this.FuncTxt.TabIndex = 3;
            this.FuncTxt.Text = "03";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 99);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(106, 24);
            this.label2.TabIndex = 2;
            this.label2.Text = "Function";
            // 
            // IDTxt
            // 
            this.IDTxt.Location = new System.Drawing.Point(141, 41);
            this.IDTxt.Name = "IDTxt";
            this.IDTxt.Size = new System.Drawing.Size(108, 35);
            this.IDTxt.TabIndex = 1;
            this.IDTxt.Text = "1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(94, 24);
            this.label1.TabIndex = 0;
            this.label1.Text = "SlaveID";
            // 
            // MBConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(14F, 28F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(358, 413);
            this.Controls.Add(this.groupBox1);
            this.Font = new System.Drawing.Font("SimSun", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(5);
            this.Name = "MBConfig";
            this.Text = "MBConfig";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox IDTxt;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox FuncTxt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox AddrTxt;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox NumTxt;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox ScanTxt;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button MBCan;
        private System.Windows.Forms.Button MBConOK;
    }
}