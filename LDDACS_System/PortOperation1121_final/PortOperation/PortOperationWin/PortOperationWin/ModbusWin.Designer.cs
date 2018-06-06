namespace PortOperationWin
{
    partial class ModbusWin
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
            this.w_port = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.exit = new System.Windows.Forms.Button();
            this.w_devadd = new System.Windows.Forms.TextBox();
            this.w_stopbits = new System.Windows.Forms.TextBox();
            this.w_databits = new System.Windows.Forms.TextBox();
            this.w_parity = new System.Windows.Forms.TextBox();
            this.w_baudrate = new System.Windows.Forms.TextBox();
            this.open = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.writecommand = new System.Windows.Forms.Button();
            this.writevalue = new System.Windows.Forms.TextBox();
            this.writeadd = new System.Windows.Forms.TextBox();
            this.recevalue = new System.Windows.Forms.RichTextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.readcommand = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // w_port
            // 
            this.w_port.FormattingEnabled = true;
            this.w_port.Location = new System.Drawing.Point(153, 64);
            this.w_port.Name = "w_port";
            this.w_port.Size = new System.Drawing.Size(82, 21);
            this.w_port.TabIndex = 21;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(35, 248);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(100, 13);
            this.label7.TabIndex = 18;
            this.label7.Text = "Device Address:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(35, 211);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(58, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "StopBits:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(35, 174);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 13);
            this.label5.TabIndex = 14;
            this.label5.Text = "DataBits:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(35, 137);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(43, 13);
            this.label4.TabIndex = 15;
            this.label4.Text = "Parity:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(35, 101);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 13);
            this.label3.TabIndex = 16;
            this.label3.Text = "BaudRate:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(35, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "Port:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(177, 20);
            this.label1.TabIndex = 12;
            this.label1.Text = "User Modbus Config:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(11, 8);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(92, 13);
            this.label8.TabIndex = 27;
            this.label8.Text = "Write Register:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(13, 33);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(56, 13);
            this.label9.TabIndex = 28;
            this.label9.Text = "Address:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(13, 58);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(43, 13);
            this.label10.TabIndex = 29;
            this.label10.Text = "Value:";
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Controls.Add(this.exit);
            this.panel1.Controls.Add(this.w_devadd);
            this.panel1.Controls.Add(this.w_stopbits);
            this.panel1.Controls.Add(this.w_databits);
            this.panel1.Controls.Add(this.w_parity);
            this.panel1.Controls.Add(this.w_baudrate);
            this.panel1.Controls.Add(this.open);
            this.panel1.Location = new System.Drawing.Point(12, 44);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(258, 307);
            this.panel1.TabIndex = 30;
            // 
            // exit
            // 
            this.exit.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.exit.Location = new System.Drawing.Point(170, 247);
            this.exit.Name = "exit";
            this.exit.Size = new System.Drawing.Size(51, 39);
            this.exit.TabIndex = 39;
            this.exit.Text = "Exit";
            this.exit.UseVisualStyleBackColor = true;
            this.exit.Click += new System.EventHandler(this.btn_exit_Click);
            // 
            // w_devadd
            // 
            this.w_devadd.Location = new System.Drawing.Point(139, 202);
            this.w_devadd.Name = "w_devadd";
            this.w_devadd.Size = new System.Drawing.Size(86, 20);
            this.w_devadd.TabIndex = 38;
            // 
            // w_stopbits
            // 
            this.w_stopbits.Location = new System.Drawing.Point(139, 166);
            this.w_stopbits.Name = "w_stopbits";
            this.w_stopbits.Size = new System.Drawing.Size(86, 20);
            this.w_stopbits.TabIndex = 37;
            // 
            // w_databits
            // 
            this.w_databits.Location = new System.Drawing.Point(139, 128);
            this.w_databits.Name = "w_databits";
            this.w_databits.Size = new System.Drawing.Size(86, 20);
            this.w_databits.TabIndex = 36;
            // 
            // w_parity
            // 
            this.w_parity.Location = new System.Drawing.Point(139, 91);
            this.w_parity.Name = "w_parity";
            this.w_parity.Size = new System.Drawing.Size(86, 20);
            this.w_parity.TabIndex = 35;
            // 
            // w_baudrate
            // 
            this.w_baudrate.Location = new System.Drawing.Point(139, 55);
            this.w_baudrate.Name = "w_baudrate";
            this.w_baudrate.Size = new System.Drawing.Size(86, 20);
            this.w_baudrate.TabIndex = 34;
            // 
            // open
            // 
            this.open.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.open.Location = new System.Drawing.Point(24, 247);
            this.open.Name = "open";
            this.open.Size = new System.Drawing.Size(52, 39);
            this.open.TabIndex = 33;
            this.open.Text = "Open";
            this.open.UseVisualStyleBackColor = true;
            this.open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel2.Controls.Add(this.writecommand);
            this.panel2.Controls.Add(this.writevalue);
            this.panel2.Controls.Add(this.writeadd);
            this.panel2.Controls.Add(this.label10);
            this.panel2.Controls.Add(this.label8);
            this.panel2.Controls.Add(this.label9);
            this.panel2.Location = new System.Drawing.Point(296, 12);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(299, 109);
            this.panel2.TabIndex = 31;
            // 
            // writecommand
            // 
            this.writecommand.Location = new System.Drawing.Point(208, 27);
            this.writecommand.Name = "writecommand";
            this.writecommand.Size = new System.Drawing.Size(59, 47);
            this.writecommand.TabIndex = 32;
            this.writecommand.Text = "Write";
            this.writecommand.UseVisualStyleBackColor = true;
            this.writecommand.Click += new System.EventHandler(this.write_btn_click);
            // 
            // writevalue
            // 
            this.writevalue.Location = new System.Drawing.Point(98, 54);
            this.writevalue.Name = "writevalue";
            this.writevalue.Size = new System.Drawing.Size(86, 20);
            this.writevalue.TabIndex = 31;
            // 
            // writeadd
            // 
            this.writeadd.Location = new System.Drawing.Point(97, 29);
            this.writeadd.Name = "writeadd";
            this.writeadd.Size = new System.Drawing.Size(86, 20);
            this.writeadd.TabIndex = 30;
            // 
            // recevalue
            // 
            this.recevalue.Location = new System.Drawing.Point(13, 51);
            this.recevalue.Name = "recevalue";
            this.recevalue.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedVertical;
            this.recevalue.Size = new System.Drawing.Size(189, 156);
            this.recevalue.TabIndex = 36;
            this.recevalue.Text = "";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(12, 35);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(41, 13);
            this.label12.TabIndex = 35;
            this.label12.Text = "Recv:";
            // 
            // panel3
            // 
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel3.Controls.Add(this.recevalue);
            this.panel3.Controls.Add(this.readcommand);
            this.panel3.Controls.Add(this.label12);
            this.panel3.Controls.Add(this.label13);
            this.panel3.Location = new System.Drawing.Point(297, 137);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(299, 214);
            this.panel3.TabIndex = 31;
            // 
            // readcommand
            // 
            this.readcommand.Location = new System.Drawing.Point(208, 31);
            this.readcommand.Name = "readcommand";
            this.readcommand.Size = new System.Drawing.Size(59, 47);
            this.readcommand.TabIndex = 32;
            this.readcommand.Text = "Read";
            this.readcommand.UseVisualStyleBackColor = true;
            this.readcommand.Click += new System.EventHandler(this.read_btn_click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(11, 12);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(92, 13);
            this.label13.TabIndex = 27;
            this.label13.Text = "Read Register:";
            // 
            // ModbusWin
            // 
            this.ClientSize = new System.Drawing.Size(608, 373);
            this.Controls.Add(this.w_port);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel2);
            this.Name = "ModbusWin";
            this.Load += new System.EventHandler(this.Form_SerialSetting_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox w_port;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox writevalue;
        private System.Windows.Forms.TextBox writeadd;
        private System.Windows.Forms.Button open;
        private System.Windows.Forms.RichTextBox recevalue;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button writecommand;
        private System.Windows.Forms.TextBox w_baudrate;
        private System.Windows.Forms.TextBox w_devadd;
        private System.Windows.Forms.TextBox w_stopbits;
        private System.Windows.Forms.TextBox w_databits;
        private System.Windows.Forms.TextBox w_parity;
        private System.Windows.Forms.Button exit;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Button readcommand;
        private System.Windows.Forms.Label label13;
    }
}
