namespace PortOperationWin
{
    partial class statusWin
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.btn_cancel = new System.Windows.Forms.Button();
            this.btn_ok = new System.Windows.Forms.Button();
            this.sw_port = new System.Windows.Forms.ComboBox();
            this.deviceAdd = new System.Windows.Forms.TextBox();
            this.reset = new System.Windows.Forms.Button();
            this.sw_baudrate = new System.Windows.Forms.TextBox();
            this.sw_parity = new System.Windows.Forms.TextBox();
            this.sw_databits = new System.Windows.Forms.TextBox();
            this.sw_stopbits = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(162, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "Status Port Config:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(13, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Port:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(13, 103);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "BaudRate:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(13, 139);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(43, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Parity:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(13, 176);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "DataBits:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(13, 213);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(58, 13);
            this.label6.TabIndex = 3;
            this.label6.Text = "StopBits:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(13, 247);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(100, 13);
            this.label7.TabIndex = 4;
            this.label7.Text = "Device Address:";
            // 
            // btn_cancel
            // 
            this.btn_cancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_cancel.Location = new System.Drawing.Point(12, 322);
            this.btn_cancel.Name = "btn_cancel";
            this.btn_cancel.Size = new System.Drawing.Size(75, 24);
            this.btn_cancel.TabIndex = 5;
            this.btn_cancel.Text = "Cancel";
            this.btn_cancel.UseVisualStyleBackColor = true;
            this.btn_cancel.Click += new System.EventHandler(this.btn_cancel_Click);
            // 
            // btn_ok
            // 
            this.btn_ok.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_ok.Location = new System.Drawing.Point(186, 322);
            this.btn_ok.Name = "btn_ok";
            this.btn_ok.Size = new System.Drawing.Size(75, 24);
            this.btn_ok.TabIndex = 5;
            this.btn_ok.Text = "OK";
            this.btn_ok.UseVisualStyleBackColor = true;
            this.btn_ok.Click += new System.EventHandler(this.btn_ok_Click);
            // 
            // sw_port
            // 
            this.sw_port.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.sw_port.FormattingEnabled = true;
            this.sw_port.Location = new System.Drawing.Point(183, 66);
            this.sw_port.Name = "sw_port";
            this.sw_port.Size = new System.Drawing.Size(82, 21);
            this.sw_port.TabIndex = 6;
            // 
            // deviceAdd
            // 
            this.deviceAdd.Location = new System.Drawing.Point(183, 247);
            this.deviceAdd.Name = "deviceAdd";
            this.deviceAdd.Size = new System.Drawing.Size(82, 20);
            this.deviceAdd.TabIndex = 12;
            // 
            // reset
            // 
            this.reset.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.reset.Location = new System.Drawing.Point(100, 322);
            this.reset.Name = "reset";
            this.reset.Size = new System.Drawing.Size(75, 24);
            this.reset.TabIndex = 5;
            this.reset.Text = "Reset";
            this.reset.UseVisualStyleBackColor = true;
            this.reset.Click += new System.EventHandler(this.btn_ok_Click);
            // 
            // sw_baudrate
            // 
            this.sw_baudrate.Location = new System.Drawing.Point(183, 100);
            this.sw_baudrate.Name = "sw_baudrate";
            this.sw_baudrate.Size = new System.Drawing.Size(82, 20);
            this.sw_baudrate.TabIndex = 13;
            // 
            // sw_parity
            // 
            this.sw_parity.Location = new System.Drawing.Point(183, 136);
            this.sw_parity.Name = "sw_parity";
            this.sw_parity.Size = new System.Drawing.Size(82, 20);
            this.sw_parity.TabIndex = 13;
            // 
            // sw_databits
            // 
            this.sw_databits.Location = new System.Drawing.Point(183, 173);
            this.sw_databits.Name = "sw_databits";
            this.sw_databits.Size = new System.Drawing.Size(82, 20);
            this.sw_databits.TabIndex = 14;
            // 
            // sw_stopbits
            // 
            this.sw_stopbits.Location = new System.Drawing.Point(183, 210);
            this.sw_stopbits.Name = "sw_stopbits";
            this.sw_stopbits.Size = new System.Drawing.Size(82, 20);
            this.sw_stopbits.TabIndex = 14;
            // 
            // statusWin
            // 
            this.ClientSize = new System.Drawing.Size(287, 373);
            this.Controls.Add(this.sw_stopbits);
            this.Controls.Add(this.sw_databits);
            this.Controls.Add(this.sw_parity);
            this.Controls.Add(this.sw_baudrate);
            this.Controls.Add(this.deviceAdd);
            this.Controls.Add(this.sw_port);
            this.Controls.Add(this.reset);
            this.Controls.Add(this.btn_ok);
            this.Controls.Add(this.btn_cancel);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "statusWin";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.Form_SerialSetting_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button btn_cancel;
        private System.Windows.Forms.Button btn_ok;
        private System.Windows.Forms.ComboBox sw_port;
        private System.Windows.Forms.TextBox deviceAdd;
        private System.Windows.Forms.Button reset;
        private System.Windows.Forms.TextBox sw_baudrate;
        private System.Windows.Forms.TextBox sw_parity;
        private System.Windows.Forms.TextBox sw_databits;
        private System.Windows.Forms.TextBox sw_stopbits;
    }
}
