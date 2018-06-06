namespace Designer.DrawTool
{
    partial class DBConnect
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
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.DeviceNameComboBox = new System.Windows.Forms.ComboBox();
            this.DeviceTypeComboBox = new System.Windows.Forms.ComboBox();
            this.FunctionUnitComboBox = new System.Windows.Forms.ComboBox();
            this.ModuleNameComboBox = new System.Windows.Forms.ComboBox();
            this.ModuleTypeComboBox = new System.Windows.Forms.ComboBox();
            this.ProjectComboBox = new System.Windows.Forms.ComboBox();
            this.Load = new System.Windows.Forms.Button();
            this.Update = new System.Windows.Forms.Button();
            this.New = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
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
            this.splitContainer1.Panel2.Controls.Add(this.Load);
            this.splitContainer1.Panel2.Controls.Add(this.Update);
            this.splitContainer1.Panel2.Controls.Add(this.New);
            this.splitContainer1.Size = new System.Drawing.Size(216, 161);
            this.splitContainer1.SplitterDistance = 132;
            this.splitContainer1.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.groupBox1.Controls.Add(this.splitContainer2);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(216, 132);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Context";
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(3, 17);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.splitContainer2.Panel1.Controls.Add(this.label6);
            this.splitContainer2.Panel1.Controls.Add(this.label5);
            this.splitContainer2.Panel1.Controls.Add(this.label4);
            this.splitContainer2.Panel1.Controls.Add(this.label3);
            this.splitContainer2.Panel1.Controls.Add(this.label2);
            this.splitContainer2.Panel1.Controls.Add(this.label1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.splitContainer2.Panel2.Controls.Add(this.DeviceNameComboBox);
            this.splitContainer2.Panel2.Controls.Add(this.DeviceTypeComboBox);
            this.splitContainer2.Panel2.Controls.Add(this.FunctionUnitComboBox);
            this.splitContainer2.Panel2.Controls.Add(this.ModuleNameComboBox);
            this.splitContainer2.Panel2.Controls.Add(this.ModuleTypeComboBox);
            this.splitContainer2.Panel2.Controls.Add(this.ProjectComboBox);
            this.splitContainer2.Size = new System.Drawing.Size(210, 112);
            this.splitContainer2.SplitterDistance = 79;
            this.splitContainer2.TabIndex = 0;
            // 
            // label6
            // 
            this.label6.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.label6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label6.Dock = System.Windows.Forms.DockStyle.Top;
            this.label6.Location = new System.Drawing.Point(0, 100);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(79, 20);
            this.label6.TabIndex = 5;
            this.label6.Text = "DeviceName";
            // 
            // label5
            // 
            this.label5.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.label5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label5.Dock = System.Windows.Forms.DockStyle.Top;
            this.label5.Location = new System.Drawing.Point(0, 80);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(79, 20);
            this.label5.TabIndex = 4;
            this.label5.Text = "DeviceType";
            // 
            // label4
            // 
            this.label4.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.label4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label4.Dock = System.Windows.Forms.DockStyle.Top;
            this.label4.Location = new System.Drawing.Point(0, 60);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 20);
            this.label4.TabIndex = 3;
            this.label4.Text = "FunctionUnit";
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label3.Dock = System.Windows.Forms.DockStyle.Top;
            this.label3.Location = new System.Drawing.Point(0, 40);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 20);
            this.label3.TabIndex = 2;
            this.label3.Text = "ModuleName";
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label2.Dock = System.Windows.Forms.DockStyle.Top;
            this.label2.Location = new System.Drawing.Point(0, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(79, 20);
            this.label2.TabIndex = 1;
            this.label2.Text = "ModuleType";
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label1.Dock = System.Windows.Forms.DockStyle.Top;
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "Project";
            // 
            // DeviceNameComboBox
            // 
            this.DeviceNameComboBox.BackColor = System.Drawing.Color.Gainsboro;
            this.DeviceNameComboBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.DeviceNameComboBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.DeviceNameComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.DeviceNameComboBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.DeviceNameComboBox.ForeColor = System.Drawing.SystemColors.InfoText;
            this.DeviceNameComboBox.FormattingEnabled = true;
            this.DeviceNameComboBox.Location = new System.Drawing.Point(0, 100);
            this.DeviceNameComboBox.Name = "DeviceNameComboBox";
            this.DeviceNameComboBox.Size = new System.Drawing.Size(127, 20);
            this.DeviceNameComboBox.TabIndex = 5;
            // 
            // DeviceTypeComboBox
            // 
            this.DeviceTypeComboBox.BackColor = System.Drawing.Color.Gainsboro;
            this.DeviceTypeComboBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.DeviceTypeComboBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.DeviceTypeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.DeviceTypeComboBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.DeviceTypeComboBox.ForeColor = System.Drawing.SystemColors.InfoText;
            this.DeviceTypeComboBox.FormattingEnabled = true;
            this.DeviceTypeComboBox.Location = new System.Drawing.Point(0, 80);
            this.DeviceTypeComboBox.Name = "DeviceTypeComboBox";
            this.DeviceTypeComboBox.Size = new System.Drawing.Size(127, 20);
            this.DeviceTypeComboBox.TabIndex = 4;
            // 
            // FunctionUnitComboBox
            // 
            this.FunctionUnitComboBox.BackColor = System.Drawing.Color.Gainsboro;
            this.FunctionUnitComboBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.FunctionUnitComboBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.FunctionUnitComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FunctionUnitComboBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.FunctionUnitComboBox.ForeColor = System.Drawing.SystemColors.InfoText;
            this.FunctionUnitComboBox.FormattingEnabled = true;
            this.FunctionUnitComboBox.Location = new System.Drawing.Point(0, 60);
            this.FunctionUnitComboBox.Name = "FunctionUnitComboBox";
            this.FunctionUnitComboBox.Size = new System.Drawing.Size(127, 20);
            this.FunctionUnitComboBox.TabIndex = 3;
            // 
            // ModuleNameComboBox
            // 
            this.ModuleNameComboBox.BackColor = System.Drawing.Color.Gainsboro;
            this.ModuleNameComboBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.ModuleNameComboBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.ModuleNameComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ModuleNameComboBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.ModuleNameComboBox.ForeColor = System.Drawing.SystemColors.InfoText;
            this.ModuleNameComboBox.FormattingEnabled = true;
            this.ModuleNameComboBox.Location = new System.Drawing.Point(0, 40);
            this.ModuleNameComboBox.Name = "ModuleNameComboBox";
            this.ModuleNameComboBox.Size = new System.Drawing.Size(127, 20);
            this.ModuleNameComboBox.TabIndex = 2;
            // 
            // ModuleTypeComboBox
            // 
            this.ModuleTypeComboBox.BackColor = System.Drawing.Color.Gainsboro;
            this.ModuleTypeComboBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.ModuleTypeComboBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.ModuleTypeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ModuleTypeComboBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.ModuleTypeComboBox.ForeColor = System.Drawing.SystemColors.InfoText;
            this.ModuleTypeComboBox.FormattingEnabled = true;
            this.ModuleTypeComboBox.Location = new System.Drawing.Point(0, 20);
            this.ModuleTypeComboBox.Name = "ModuleTypeComboBox";
            this.ModuleTypeComboBox.Size = new System.Drawing.Size(127, 20);
            this.ModuleTypeComboBox.TabIndex = 1;
            // 
            // ProjectComboBox
            // 
            this.ProjectComboBox.BackColor = System.Drawing.Color.Gainsboro;
            this.ProjectComboBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.ProjectComboBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.ProjectComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ProjectComboBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.ProjectComboBox.ForeColor = System.Drawing.SystemColors.InfoText;
            this.ProjectComboBox.FormattingEnabled = true;
            this.ProjectComboBox.Location = new System.Drawing.Point(0, 0);
            this.ProjectComboBox.Margin = new System.Windows.Forms.Padding(8, 7, 8, 7);
            this.ProjectComboBox.Name = "ProjectComboBox";
            this.ProjectComboBox.Size = new System.Drawing.Size(127, 20);
            this.ProjectComboBox.TabIndex = 0;
            // 
            // Load
            // 
            this.Load.Dock = System.Windows.Forms.DockStyle.Left;
            this.Load.Location = new System.Drawing.Point(43, 0);
            this.Load.Name = "Load";
            this.Load.Size = new System.Drawing.Size(46, 25);
            this.Load.TabIndex = 2;
            this.Load.Text = "Load";
            this.Load.UseVisualStyleBackColor = true;
            this.Load.Click += new System.EventHandler(this.Load_Click);
            // 
            // Update
            // 
            this.Update.Location = new System.Drawing.Point(146, 0);
            this.Update.Name = "Update";
            this.Update.Size = new System.Drawing.Size(70, 25);
            this.Update.TabIndex = 1;
            this.Update.Text = "Update";
            this.Update.UseVisualStyleBackColor = true;
            this.Update.Click += new System.EventHandler(this.Update_Click);
            // 
            // New
            // 
            this.New.Dock = System.Windows.Forms.DockStyle.Left;
            this.New.Location = new System.Drawing.Point(0, 0);
            this.New.Margin = new System.Windows.Forms.Padding(6);
            this.New.Name = "New";
            this.New.Size = new System.Drawing.Size(43, 25);
            this.New.TabIndex = 0;
            this.New.Text = "New";
            this.New.UseVisualStyleBackColor = true;
            // 
            // DBConnect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(216, 161);
            this.Controls.Add(this.splitContainer1);
            this.Name     = "DBConnect";
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Float;
            this.TabText = "DBConnect";
            this.Text    = "DBConnect";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.ComboBox ProjectComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox DeviceTypeComboBox;
        private System.Windows.Forms.ComboBox FunctionUnitComboBox;
        private System.Windows.Forms.ComboBox ModuleNameComboBox;
        private System.Windows.Forms.ComboBox ModuleTypeComboBox;
        private System.Windows.Forms.Button Update;
        private System.Windows.Forms.Button New;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox DeviceNameComboBox;
        private System.Windows.Forms.Button Load;
    }
}