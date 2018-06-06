namespace Designer.DAQ
{
    partial class DAQ
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
            this.treeExplore = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // treeExplore
            // 
            this.treeExplore.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeExplore.Location = new System.Drawing.Point(0, 0);
            this.treeExplore.Name = "treeExplore";
            this.treeExplore.Size = new System.Drawing.Size(239, 329);
            this.treeExplore.TabIndex = 1;
            // 
            // DAQ
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(239, 329);
            this.Controls.Add(this.treeExplore);
            this.HideOnClose = true;
            this.Name = "DAQ";
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockLeft;
            this.TabText = "DAQ & COM";
            this.Text = "DAQ & COM";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView treeExplore;
    }
}