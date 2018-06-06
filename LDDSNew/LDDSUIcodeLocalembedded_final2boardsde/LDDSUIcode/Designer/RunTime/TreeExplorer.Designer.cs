namespace Designer.RunTime
{
    partial class TreeExplorer
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
            this.treeExploreView = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // treeExploreView
            // 
            this.treeExploreView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeExploreView.Location = new System.Drawing.Point(0, 0);
            this.treeExploreView.Name = "treeExploreView";
            this.treeExploreView.Size = new System.Drawing.Size(221, 465);
            this.treeExploreView.TabIndex = 2;
            // 
            // TreeExplorer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(221, 465);
            this.Controls.Add(this.treeExploreView);
            this.Name = "TreeExplorer";
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockLeft;
            this.TabText = "TreeExplorer";
            this.Text = "TreeExplorer";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView treeExploreView;
    }
}