namespace BMSMonitor
{
    partial class SerialPortCfg
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SerialPortCfg));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SPCmbName = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.SPBtnOpen = new System.Windows.Forms.Button();
            this.SPStatus = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.SPCmbStopB = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.SPCmbDataP = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.SPCmbDataB = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.SPCmbBaud = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SPCmbCom = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.ASCIIrdo = new System.Windows.Forms.RadioButton();
            this.RTUrdo = new System.Windows.Forms.RadioButton();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.Restxt = new System.Windows.Forms.TextBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.Delaytxt = new System.Windows.Forms.TextBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.CanBtn = new System.Windows.Forms.Button();
            this.ComBtn = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.SPCmbName);
            this.groupBox1.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(307, 79);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "ConnectionSetup";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(16, 44);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 24);
            this.label1.TabIndex = 1;
            this.label1.Text = "Mode";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SPCmbName
            // 
            this.SPCmbName.FormattingEnabled = true;
            this.SPCmbName.Items.AddRange(new object[] {
            "Serial Port",
            "Modbus TCP/IP"});
            this.SPCmbName.Location = new System.Drawing.Point(80, 40);
            this.SPCmbName.Name = "SPCmbName";
            this.SPCmbName.Size = new System.Drawing.Size(216, 32);
            this.SPCmbName.TabIndex = 0;
            this.SPCmbName.Text = "Serial Port";
            this.SPCmbName.SelectedIndexChanged += new System.EventHandler(this.SPCmbName_SelectedIndexChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.SPBtnOpen);
            this.groupBox2.Controls.Add(this.SPStatus);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.SPCmbStopB);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.SPCmbDataP);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.SPCmbDataB);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.SPCmbBaud);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.SPCmbCom);
            this.groupBox2.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.Location = new System.Drawing.Point(13, 111);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(307, 333);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "SerialPortSetting";
            // 
            // SPBtnOpen
            // 
            this.SPBtnOpen.Location = new System.Drawing.Point(20, 282);
            this.SPBtnOpen.Name = "SPBtnOpen";
            this.SPBtnOpen.Size = new System.Drawing.Size(87, 41);
            this.SPBtnOpen.TabIndex = 14;
            this.SPBtnOpen.Text = "Open";
            this.SPBtnOpen.UseVisualStyleBackColor = true;
            this.SPBtnOpen.Click += new System.EventHandler(this.SPBtnOpen_Click);
            // 
            // SPStatus
            // 
            this.SPStatus.BackColor = System.Drawing.Color.Gray;
            this.SPStatus.ForeColor = System.Drawing.SystemColors.ScrollBar;
            this.SPStatus.Location = new System.Drawing.Point(209, 282);
            this.SPStatus.Name = "SPStatus";
            this.SPStatus.Size = new System.Drawing.Size(72, 41);
            this.SPStatus.TabIndex = 13;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 241);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(70, 24);
            this.label6.TabIndex = 11;
            this.label6.Text = "StopB";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SPCmbStopB
            // 
            this.SPCmbStopB.FormattingEnabled = true;
            this.SPCmbStopB.Items.AddRange(new object[] {
            "1 bit",
            "1.5 bit",
            "2 bit"});
            this.SPCmbStopB.Location = new System.Drawing.Point(80, 237);
            this.SPCmbStopB.Name = "SPCmbStopB";
            this.SPCmbStopB.Size = new System.Drawing.Size(216, 32);
            this.SPCmbStopB.TabIndex = 10;
            this.SPCmbStopB.Text = "1 bit";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 188);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(70, 24);
            this.label5.TabIndex = 9;
            this.label5.Text = "DataP";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SPCmbDataP
            // 
            this.SPCmbDataP.FormattingEnabled = true;
            this.SPCmbDataP.Items.AddRange(new object[] {
            "NONE",
            "ODD",
            "EVEN"});
            this.SPCmbDataP.Location = new System.Drawing.Point(80, 184);
            this.SPCmbDataP.Name = "SPCmbDataP";
            this.SPCmbDataP.Size = new System.Drawing.Size(216, 32);
            this.SPCmbDataP.TabIndex = 8;
            this.SPCmbDataP.Text = "NONE";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 138);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 24);
            this.label4.TabIndex = 7;
            this.label4.Text = "DataB";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SPCmbDataB
            // 
            this.SPCmbDataB.FormattingEnabled = true;
            this.SPCmbDataB.Items.AddRange(new object[] {
            "8 bit",
            "9 bit"});
            this.SPCmbDataB.Location = new System.Drawing.Point(80, 134);
            this.SPCmbDataB.Name = "SPCmbDataB";
            this.SPCmbDataB.Size = new System.Drawing.Size(216, 32);
            this.SPCmbDataB.TabIndex = 6;
            this.SPCmbDataB.Text = "8 bit";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 88);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 24);
            this.label3.TabIndex = 5;
            this.label3.Text = "Baud";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SPCmbBaud
            // 
            this.SPCmbBaud.FormattingEnabled = true;
            this.SPCmbBaud.Items.AddRange(new object[] {
            "110",
            "300",
            "600",
            "1200",
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "38400",
            "56000",
            "57600",
            "119200"});
            this.SPCmbBaud.Location = new System.Drawing.Point(80, 84);
            this.SPCmbBaud.Name = "SPCmbBaud";
            this.SPCmbBaud.Size = new System.Drawing.Size(216, 32);
            this.SPCmbBaud.TabIndex = 4;
            this.SPCmbBaud.Text = "9600";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(46, 24);
            this.label2.TabIndex = 3;
            this.label2.Text = "Com";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SPCmbCom
            // 
            this.SPCmbCom.FormattingEnabled = true;
            this.SPCmbCom.Location = new System.Drawing.Point(80, 34);
            this.SPCmbCom.Name = "SPCmbCom";
            this.SPCmbCom.Size = new System.Drawing.Size(216, 32);
            this.SPCmbCom.TabIndex = 2;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.ASCIIrdo);
            this.groupBox3.Controls.Add(this.RTUrdo);
            this.groupBox3.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox3.Location = new System.Drawing.Point(326, 13);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(247, 93);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Mode";
            // 
            // ASCIIrdo
            // 
            this.ASCIIrdo.AutoSize = true;
            this.ASCIIrdo.Location = new System.Drawing.Point(128, 45);
            this.ASCIIrdo.Name = "ASCIIrdo";
            this.ASCIIrdo.Size = new System.Drawing.Size(95, 28);
            this.ASCIIrdo.TabIndex = 1;
            this.ASCIIrdo.TabStop = true;
            this.ASCIIrdo.Text = "ASCII";
            this.ASCIIrdo.UseVisualStyleBackColor = true;
            this.ASCIIrdo.CheckedChanged += new System.EventHandler(this.ASCIIrdo_CheckedChanged);
            this.ASCIIrdo.Click += new System.EventHandler(this.ASCIIrdo_Click);
            // 
            // RTUrdo
            // 
            this.RTUrdo.AutoSize = true;
            this.RTUrdo.Location = new System.Drawing.Point(25, 45);
            this.RTUrdo.Name = "RTUrdo";
            this.RTUrdo.Size = new System.Drawing.Size(71, 28);
            this.RTUrdo.TabIndex = 0;
            this.RTUrdo.TabStop = true;
            this.RTUrdo.Text = "RTU";
            this.RTUrdo.UseVisualStyleBackColor = true;
            this.RTUrdo.CheckedChanged += new System.EventHandler(this.RTUrdo_CheckedChanged);
            this.RTUrdo.Click += new System.EventHandler(this.RTUrdo_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Controls.Add(this.Restxt);
            this.groupBox4.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox4.Location = new System.Drawing.Point(326, 112);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(247, 100);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Response TimeOut";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("SimSun", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.Location = new System.Drawing.Point(162, 57);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 21);
            this.label9.TabIndex = 2;
            this.label9.Text = "[ms]";
            // 
            // Restxt
            // 
            this.Restxt.Location = new System.Drawing.Point(50, 51);
            this.Restxt.Name = "Restxt";
            this.Restxt.Size = new System.Drawing.Size(106, 35);
            this.Restxt.TabIndex = 1;
            this.Restxt.Text = "1000";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.label7);
            this.groupBox5.Controls.Add(this.Delaytxt);
            this.groupBox5.Font = new System.Drawing.Font("SimSun", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox5.Location = new System.Drawing.Point(326, 227);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(247, 96);
            this.groupBox5.TabIndex = 4;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Delay Between Polls";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("SimSun", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(162, 45);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(54, 21);
            this.label7.TabIndex = 4;
            this.label7.Text = "[ms]";
            // 
            // Delaytxt
            // 
            this.Delaytxt.Location = new System.Drawing.Point(50, 39);
            this.Delaytxt.Name = "Delaytxt";
            this.Delaytxt.Size = new System.Drawing.Size(106, 31);
            this.Delaytxt.TabIndex = 3;
            this.Delaytxt.Text = "250";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.CanBtn);
            this.groupBox6.Controls.Add(this.ComBtn);
            this.groupBox6.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox6.Location = new System.Drawing.Point(326, 339);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(247, 105);
            this.groupBox6.TabIndex = 5;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Comfirm";
            // 
            // CanBtn
            // 
            this.CanBtn.Location = new System.Drawing.Point(128, 46);
            this.CanBtn.Name = "CanBtn";
            this.CanBtn.Size = new System.Drawing.Size(113, 41);
            this.CanBtn.TabIndex = 16;
            this.CanBtn.Text = "Cancel";
            this.CanBtn.UseVisualStyleBackColor = true;
            this.CanBtn.Click += new System.EventHandler(this.CanBtn_Click);
            // 
            // ComBtn
            // 
            this.ComBtn.Location = new System.Drawing.Point(6, 46);
            this.ComBtn.Name = "ComBtn";
            this.ComBtn.Size = new System.Drawing.Size(106, 41);
            this.ComBtn.TabIndex = 15;
            this.ComBtn.Text = "OK";
            this.ComBtn.UseVisualStyleBackColor = true;
            this.ComBtn.Click += new System.EventHandler(this.ComBtn_Click);
            // 
            // SerialPortCfg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(585, 456);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "SerialPortCfg";
            this.Text = "SerialPort";
            this.Load += new System.EventHandler(this.SerialPort_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox SPCmbName;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox SPCmbCom;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox SPCmbBaud;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox SPCmbDataB;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox SPCmbDataP;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox SPCmbStopB;
        private System.Windows.Forms.Label SPStatus;
        private System.Windows.Forms.Button SPBtnOpen;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton ASCIIrdo;
        private System.Windows.Forms.RadioButton RTUrdo;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox Restxt;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox Delaytxt;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Button CanBtn;
        private System.Windows.Forms.Button ComBtn;
    }
}