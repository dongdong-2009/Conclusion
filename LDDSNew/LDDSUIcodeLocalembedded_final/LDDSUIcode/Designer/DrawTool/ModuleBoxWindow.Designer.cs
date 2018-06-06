namespace Designer
{
    partial class ModuleBoxWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>


        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.toolBoxEvo = new Silver.UI.ToolBox();
            this.SuspendLayout();
            // 
            // toolBoxEvo
            // 
            this.toolBoxEvo.AllowDrop = true;
            this.toolBoxEvo.AllowSwappingByDragDrop = true;
            this.toolBoxEvo.DesignerHost = null;
            this.toolBoxEvo.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolBoxEvo.InitialScrollDelay = 500;
            this.toolBoxEvo.ItemBackgroundColor = System.Drawing.Color.Empty;
            this.toolBoxEvo.ItemBorderColor = System.Drawing.Color.Empty;
            this.toolBoxEvo.ItemHeight = 20;
            this.toolBoxEvo.ItemHoverColor = System.Drawing.SystemColors.Control;
            this.toolBoxEvo.ItemHoverTextColor = System.Drawing.SystemColors.ControlText;
            this.toolBoxEvo.ItemNormalColor = System.Drawing.SystemColors.Control;
            this.toolBoxEvo.ItemNormalTextColor = System.Drawing.SystemColors.ControlText;
            this.toolBoxEvo.ItemSelectedColor = System.Drawing.Color.White;
            this.toolBoxEvo.ItemSelectedTextColor = System.Drawing.SystemColors.ControlText;
            this.toolBoxEvo.ItemSpacing = 2;
            this.toolBoxEvo.LargeItemSize = new System.Drawing.Size(64, 64);
            this.toolBoxEvo.LayoutDelay = 10;
            this.toolBoxEvo.Location = new System.Drawing.Point(0, 0);
            this.toolBoxEvo.Name = "toolBoxEvo";
            this.toolBoxEvo.ScrollDelay = 60;
            this.toolBoxEvo.SelectAllTextWhileRenaming = true;
            this.toolBoxEvo.SelectedCategory = null;
            this.toolBoxEvo.SelectedTabIndex = -1;
            this.toolBoxEvo.ShowOnlyOneItemPerRow = false;
            this.toolBoxEvo.Size = new System.Drawing.Size(187, 276);
            this.toolBoxEvo.SmallItemSize = new System.Drawing.Size(32, 32);
            this.toolBoxEvo.TabHeight = 18;
            this.toolBoxEvo.TabHoverTextColor = System.Drawing.SystemColors.ControlText;
            this.toolBoxEvo.TabIndex = 0;
            this.toolBoxEvo.TabNormalTextColor = System.Drawing.SystemColors.ControlText;
            this.toolBoxEvo.TabSelectedTextColor = System.Drawing.SystemColors.ControlText;
            this.toolBoxEvo.TabSpacing = 1;
            this.toolBoxEvo.UseItemColorInRename = false;
            // 
            // ModuleBoxWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(187, 276);
            this.Controls.Add(this.toolBoxEvo);
            this.HideOnClose = true;
            this.Name = "ModuleBoxWindow";
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockLeft;
            this.TabText = "ModuleBox";
            this.Text = "ModuleBox";
            this.ResumeLayout(false);

        }

        #endregion

        private Silver.UI.ToolBox toolBoxEvo;
        private System.ComponentModel.IContainer components;
    }
}