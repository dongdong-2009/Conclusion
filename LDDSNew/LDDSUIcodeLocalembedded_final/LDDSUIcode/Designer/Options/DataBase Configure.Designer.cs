namespace Designer.Options
{
    partial class DataBase_Configure
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.DB = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.PWD = new System.Windows.Forms.TextBox();
            this.UID = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.IP = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Test = new System.Windows.Forms.Button();
            this.Update = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.Port = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.groupBox1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.Test);
            this.splitContainer1.Panel2.Controls.Add(this.Update);
            this.splitContainer1.Panel2.Controls.Add(this.Cancel);
            this.splitContainer1.Size = new System.Drawing.Size(183, 223);
            this.splitContainer1.SplitterDistance = 185;
            this.splitContainer1.TabIndex = 3;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Port);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.DB);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.PWD);
            this.groupBox1.Controls.Add(this.UID);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.IP);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(183, 185);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "DataBase Configure";
            // 
            // DB
            // 
            this.DB.Location = new System.Drawing.Point(74, 119);
            this.DB.Name = "DB";
            this.DB.Size = new System.Drawing.Size(100, 21);
            this.DB.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 119);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "DataBase";
            // 
            // PWD
            // 
            this.PWD.Location = new System.Drawing.Point(74, 89);
            this.PWD.Name = "PWD";
            this.PWD.Size = new System.Drawing.Size(100, 21);
            this.PWD.TabIndex = 5;
            // 
            // UID
            // 
            this.UID.Location = new System.Drawing.Point(74, 58);
            this.UID.Name = "UID";
            this.UID.Size = new System.Drawing.Size(100, 21);
            this.UID.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "PWD";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(23, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "UID";
            // 
            // IP
            // 
            this.IP.Location = new System.Drawing.Point(74, 28);
            this.IP.Name = "IP";
            this.IP.Size = new System.Drawing.Size(100, 21);
            this.IP.TabIndex = 1;
            this.IP.Leave += new System.EventHandler(this.IP_Leave);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Serve IP";
            // 
            // Test
            // 
            this.Test.Dock = System.Windows.Forms.DockStyle.Right;
            this.Test.Location = new System.Drawing.Point(30, 0);
            this.Test.Name = "Test";
            this.Test.Size = new System.Drawing.Size(51, 34);
            this.Test.TabIndex = 2;
            this.Test.Text = "Test";
            this.Test.UseVisualStyleBackColor = true;
            this.Test.Click += new System.EventHandler(this.Test_Click);
            // 
            // Update
            // 
            this.Update.Dock = System.Windows.Forms.DockStyle.Right;
            this.Update.Location = new System.Drawing.Point(81, 0);
            this.Update.Name = "Update";
            this.Update.Size = new System.Drawing.Size(51, 34);
            this.Update.TabIndex = 1;
            this.Update.Text = "Update";
            this.Update.UseVisualStyleBackColor = true;
            this.Update.Click += new System.EventHandler(this.Update_Click);
            // 
            // Cancel
            // 
            this.Cancel.Dock = System.Windows.Forms.DockStyle.Right;
            this.Cancel.Location = new System.Drawing.Point(132, 0);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(51, 34);
            this.Cancel.TabIndex = 0;
            this.Cancel.Text = "Cancel";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // Port
            // 
            this.Port.Location = new System.Drawing.Point(74, 150);
            this.Port.Name = "Port";
            this.Port.Size = new System.Drawing.Size(100, 21);
            this.Port.TabIndex = 9;
            this.Port.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Port_KeyPress);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 150);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "Port";
            // 
            // DataBase_Configure
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(183, 223);
            this.Controls.Add(this.splitContainer1);
            this.MaximizeBox = false;
            this.Name = "DataBase_Configure";
            this.Text = "DataBase_Configure";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox PWD;
        private System.Windows.Forms.TextBox UID;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox IP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox DB;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button Update;
        private System.Windows.Forms.Button Cancel;
        private System.Windows.Forms.Button Test;
        private System.Windows.Forms.TextBox Port;
        private System.Windows.Forms.Label label5;
    }
}