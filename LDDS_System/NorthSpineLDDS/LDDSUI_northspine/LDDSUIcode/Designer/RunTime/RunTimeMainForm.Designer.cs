namespace Designer.RunTime
{
    partial class RunTimeMainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RunTimeMainForm));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.ToolStripControls = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton5 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton4 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.ControlsDockPanel = new WeifenLuo.WinFormsUI.Docking.DockPanel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.toolStrip1.BackColor = System.Drawing.Color.DarkSeaGreen;
            this.toolStrip1.Dock = System.Windows.Forms.DockStyle.None;
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripControls,
            this.toolStripButton5,
            this.toolStripButton4,
            this.toolStripButton2,
            this.toolStripButton1});
            this.toolStrip1.Location = new System.Drawing.Point(546, 75);
            this.toolStrip1.Margin = new System.Windows.Forms.Padding(1);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(338, 25);
            this.toolStrip1.TabIndex = 4;
            this.toolStrip1.Text = "CC";
            // 
            // ToolStripControls
            // 
            this.ToolStripControls.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ToolStripControls.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.ToolStripControls.Font = new System.Drawing.Font("Microsoft YaHei", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ToolStripControls.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ToolStripControls.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.ToolStripControls.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.ToolStripControls.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ToolStripControls.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.ToolStripControls.Name = "ToolStripControls";
            this.ToolStripControls.Size = new System.Drawing.Size(64, 23);
            this.ToolStripControls.Tag = "Controls";
            this.ToolStripControls.Text = "Controls";
            this.ToolStripControls.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.ToolStripControls.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.ToolStripControls.Click += new System.EventHandler(this.ToolStripControls_Click);
            // 
            // toolStripButton5
            // 
            this.toolStripButton5.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.toolStripButton5.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton5.Font = new System.Drawing.Font("Microsoft YaHei", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.toolStripButton5.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.toolStripButton5.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton5.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton5.ImageTransparentColor = System.Drawing.SystemColors.Control;
            this.toolStripButton5.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.toolStripButton5.Name = "toolStripButton5";
            this.toolStripButton5.Size = new System.Drawing.Size(55, 23);
            this.toolStripButton5.Tag = "Alarms";
            this.toolStripButton5.Text = "Alarms";
            this.toolStripButton5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton5.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.toolStripButton5.Click += new System.EventHandler(this.ToolStripAlarms_Click);
            // 
            // toolStripButton4
            // 
            this.toolStripButton4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.toolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton4.Font = new System.Drawing.Font("Microsoft YaHei", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.toolStripButton4.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.toolStripButton4.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton4.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton4.ImageTransparentColor = System.Drawing.SystemColors.Control;
            this.toolStripButton4.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.toolStripButton4.Name = "toolStripButton4";
            this.toolStripButton4.Size = new System.Drawing.Size(51, 23);
            this.toolStripButton4.Tag = "Charts";
            this.toolStripButton4.Text = "Charts";
            this.toolStripButton4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton4.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton2.Font = new System.Drawing.Font("Microsoft YaHei", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.toolStripButton2.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.toolStripButton2.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton2.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton2.ImageTransparentColor = System.Drawing.SystemColors.Control;
            this.toolStripButton2.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(59, 23);
            this.toolStripButton2.Tag = "Reports";
            this.toolStripButton2.Text = "Reports";
            this.toolStripButton2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton2.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton1.Font = new System.Drawing.Font("Microsoft YaHei", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.toolStripButton1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.toolStripButton1.ImageAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton1.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripButton1.ImageTransparentColor = System.Drawing.SystemColors.Control;
            this.toolStripButton1.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(56, 23);
            this.toolStripButton1.Tag = "System";
            this.toolStripButton1.Text = "System";
            this.toolStripButton1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.toolStripButton1.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            // 
            // ControlsDockPanel
            // 
            this.ControlsDockPanel.ActiveAutoHideContent = null;
            this.ControlsDockPanel.BackColor = System.Drawing.SystemColors.Control;
            this.ControlsDockPanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ControlsDockPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ControlsDockPanel.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.World);
            this.ControlsDockPanel.Location = new System.Drawing.Point(0, 0);
            this.ControlsDockPanel.Name = "ControlsDockPanel";
            this.ControlsDockPanel.Size = new System.Drawing.Size(941, 718);
            this.ControlsDockPanel.TabIndex = 6;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Transparent;
            this.pictureBox1.BackgroundImage = global::Designer.Properties.Resources.longlogo2;
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(941, 100);
            this.pictureBox1.TabIndex = 10;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.statusStrip1.Location = new System.Drawing.Point(0, 696);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(941, 22);
            this.statusStrip1.TabIndex = 13;
            this.statusStrip1.Tag = "NTU";
            this.statusStrip1.Text = "NTU";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.ImageAlign = System.Drawing.ContentAlignment.BottomRight;
            this.toolStripStatusLabel1.Margin = new System.Windows.Forms.Padding(0, 2, 0, 2);
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(31, 18);
            this.toolStripStatusLabel1.Text = "NTU";
            this.toolStripStatusLabel1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // RunTimeMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(941, 718);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.ControlsDockPanel);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.Name = "RunTimeMainForm";
            this.TabText = "BSTAR";
            this.Text = "BSTAR";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.RunTimeMainForm_FormClosing);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public WeifenLuo.WinFormsUI.Docking.DockPanel ControlsDockPanel;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton ToolStripControls;
        private System.Windows.Forms.ToolStripButton toolStripButton5;
        private System.Windows.Forms.ToolStripButton toolStripButton4;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;

    }
}