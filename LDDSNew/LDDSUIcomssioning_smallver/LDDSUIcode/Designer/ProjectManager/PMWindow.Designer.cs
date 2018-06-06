namespace Designer.ProjectManager
{
    partial class PMWindow
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PMWindow));
            this.treeExplore = new System.Windows.Forms.TreeView();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.RightMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.RightMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // treeExplore
            // 
            this.treeExplore.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeExplore.Location = new System.Drawing.Point(0, 0);
            this.treeExplore.Name = "treeExplore";
            this.treeExplore.Size = new System.Drawing.Size(172, 338);
            this.treeExplore.TabIndex = 0;
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "closefolder.ico");
            this.imageList1.Images.SetKeyName(1, "openfolder.ico");
            this.imageList1.Images.SetKeyName(2, "form.ico");
            // 
            // RightMenuStrip
            // 
            this.RightMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem});
            this.RightMenuStrip.Name = "RightMenuStrip";
            this.RightMenuStrip.Size = new System.Drawing.Size(153, 48);
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.newToolStripMenuItem.Text = "New";
            // 
            // PMWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(172, 338);
            this.Controls.Add(this.treeExplore);
            this.Name = "FunctionList";
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockLeft;
            this.TabText = "FunctionList";
            this.Text = "FunctionList";
            this.TopMost = true;
            this.RightMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView treeExplore;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ContextMenuStrip RightMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
    }
}