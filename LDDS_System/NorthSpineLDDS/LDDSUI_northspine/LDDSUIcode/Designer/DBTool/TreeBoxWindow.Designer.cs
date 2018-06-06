namespace Designer.DBTool
{
    partial class TreeBoxWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TreeBoxWindow));
            this.treeBox = new Silver.UI.ToolBox();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.SuspendLayout();
            // 
            // treeBox
            // 
            this.treeBox.AllowDrop = true;
            this.treeBox.AllowSwappingByDragDrop = true;
            this.treeBox.DesignerHost = null;
            this.treeBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeBox.InitialScrollDelay = 500;
            this.treeBox.ItemBackgroundColor = System.Drawing.Color.Empty;
            this.treeBox.ItemBorderColor = System.Drawing.Color.Empty;
            this.treeBox.ItemHeight = 20;
            this.treeBox.ItemHoverColor = System.Drawing.SystemColors.Control;
            this.treeBox.ItemHoverTextColor = System.Drawing.SystemColors.ControlText;
            this.treeBox.ItemNormalColor = System.Drawing.SystemColors.Control;
            this.treeBox.ItemNormalTextColor = System.Drawing.SystemColors.ControlText;
            this.treeBox.ItemSelectedColor = System.Drawing.Color.White;
            this.treeBox.ItemSelectedTextColor = System.Drawing.SystemColors.ControlText;
            this.treeBox.ItemSpacing = 2;
            this.treeBox.LargeItemSize = new System.Drawing.Size(64, 64);
            this.treeBox.LayoutDelay = 10;
            this.treeBox.Location = new System.Drawing.Point(0, 0);
            this.treeBox.Name = "treeBox";
            this.treeBox.ScrollDelay = 60;
            this.treeBox.SelectAllTextWhileRenaming = true;
            this.treeBox.SelectedCategory = null;
            this.treeBox.SelectedTabIndex = -1;
            this.treeBox.ShowOnlyOneItemPerRow = false;
            this.treeBox.Size = new System.Drawing.Size(188, 324);
            this.treeBox.SmallItemSize = new System.Drawing.Size(32, 32);
            this.treeBox.TabHeight = 18;
            this.treeBox.TabHoverTextColor = System.Drawing.SystemColors.ControlText;
            this.treeBox.TabIndex = 0;
            this.treeBox.TabNormalTextColor = System.Drawing.SystemColors.ControlText;
            this.treeBox.TabSelectedTextColor = System.Drawing.SystemColors.ControlText;
            this.treeBox.TabSpacing = 1;
            this.treeBox.UseItemColorInRename = false;
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "bluedot.png");
            this.imageList1.Images.SetKeyName(1, "yellowdot.png");
            // 
            // TreeBoxWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(188, 324);
            this.Controls.Add(this.treeBox);
            this.Name = "TreeBoxWindow";
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockLeft;
            this.TabText = "DBManager";
            this.Text = "DBManager";
            this.ResumeLayout(false);

        }

        #endregion

        private Silver.UI.ToolBox treeBox;
        private System.Windows.Forms.ImageList imageList1;
    }
}