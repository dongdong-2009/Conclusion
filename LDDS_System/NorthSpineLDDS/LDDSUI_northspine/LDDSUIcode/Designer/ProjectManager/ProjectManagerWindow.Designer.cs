namespace Designer.ProjectManager
{
    partial class ProjectManagerWindow
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
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.NewButton = new System.Windows.Forms.ToolStripButton();
            this.OpenButton = new System.Windows.Forms.ToolStripButton();
            this.DeletepButton = new System.Windows.Forms.ToolStripButton();
            this.AddButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.RunButton = new System.Windows.Forms.ToolStripButton();
            this.RunOPButton = new System.Windows.Forms.ToolStripButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CreationTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Projectdescription = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.toolStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NewButton,
            this.OpenButton,
            this.DeletepButton,
            this.AddButton,
            this.toolStripSeparator1,
            this.RunButton,
            this.RunOPButton});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(579, 55);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // NewButton
            // 
            this.NewButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.NewButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.NewButton.Image = global::Designer.Properties.Resources.folder_new_51;
            this.NewButton.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.NewButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.NewButton.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.NewButton.Name = "NewButton";
            this.NewButton.Size = new System.Drawing.Size(52, 53);
            this.NewButton.Text = "NewProject";
            // 
            // OpenButton
            // 
            this.OpenButton.AutoSize = false;
            this.OpenButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.OpenButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.OpenButton.Image = global::Designer.Properties.Resources.folder_open_31;
            this.OpenButton.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.OpenButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.OpenButton.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.OpenButton.Name = "OpenButton";
            this.OpenButton.Size = new System.Drawing.Size(53, 53);
            this.OpenButton.Text = "OpenProject";
            // 
            // DeletepButton
            // 
            this.DeletepButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.DeletepButton.Image = global::Designer.Properties.Resources.edit_delete_3;
            this.DeletepButton.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.DeletepButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.DeletepButton.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.DeletepButton.Name = "DeletepButton";
            this.DeletepButton.Size = new System.Drawing.Size(52, 53);
            this.DeletepButton.Text = "DeleteProject";
            // 
            // AddButton
            // 
            this.AddButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.AddButton.Image = global::Designer.Properties.Resources.folder_new_72;
            this.AddButton.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.AddButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.AddButton.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.AddButton.Name = "AddButton";
            this.AddButton.Size = new System.Drawing.Size(52, 53);
            this.AddButton.Text = "AddProject";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 53);
            // 
            // RunButton
            // 
            this.RunButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.RunButton.Image = global::Designer.Properties.Resources.system_run1;
            this.RunButton.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.RunButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.RunButton.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.RunButton.Name = "RunButton";
            this.RunButton.Size = new System.Drawing.Size(52, 53);
            this.RunButton.Text = "RunProject";
            // 
            // RunOPButton
            // 
            this.RunOPButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.RunOPButton.Image = global::Designer.Properties.Resources.system_run_5;
            this.RunOPButton.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.RunOPButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.RunOPButton.Margin = new System.Windows.Forms.Padding(5, 1, 5, 1);
            this.RunOPButton.Name = "RunOPButton";
            this.RunOPButton.Size = new System.Drawing.Size(52, 53);
            this.RunOPButton.Text = "RunOP";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.statusStrip1);
            this.panel1.Controls.Add(this.dataGridView1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 55);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(579, 153);
            this.panel1.TabIndex = 1;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 131);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(579, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "ProjectManager";
            // 
            // dataGridView1
            // 
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridView1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.dataGridView1.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.Sunken;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.CreationTime,
            this.Column2,
            this.Projectdescription});
            this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView1.Location = new System.Drawing.Point(0, 0);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(579, 153);
            this.dataGridView1.TabIndex = 0;
            // 
            // Column1
            // 
            this.Column1.HeaderText = "ProjectName";
            this.Column1.Name = "Column1";
            // 
            // CreationTime
            // 
            this.CreationTime.HeaderText = "CreationTime";
            this.CreationTime.Name = "CreationTime";
            // 
            // Column2
            // 
            this.Column2.HeaderText = "ProjectPath";
            this.Column2.Name = "Column2";
            this.Column2.ReadOnly = true;
            // 
            // Projectdescription
            // 
            this.Projectdescription.HeaderText = "Projectdescription";
            this.Projectdescription.Name = "Projectdescription";
            // 
            // ProjectManagerWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(579, 208);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.toolStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.HideOnClose = true;
            this.Name = "ProjectManagerWindow";
            this.TabText = "Manager";
            this.Text = "Manager";
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton NewButton;
        private System.Windows.Forms.ToolStripButton OpenButton;
        private System.Windows.Forms.ToolStripButton DeletepButton;
        private System.Windows.Forms.ToolStripButton AddButton;
        private System.Windows.Forms.ToolStripButton RunButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton RunOPButton;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn CreationTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Projectdescription;
        private System.Windows.Forms.StatusStrip statusStrip1;
    }
}