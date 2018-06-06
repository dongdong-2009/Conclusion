namespace Designer
{
    partial class ToolBoxWindow
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
            this.toolbox1 = new ToolboxLibrary.Toolbox();
            this.SuspendLayout();
            // 
            // toolbox1
            // 
            this.toolbox1.DesignerHost = null;
            this.toolbox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolbox1.FilePath = null;
            this.toolbox1.Location = new System.Drawing.Point(0, 0);
            this.toolbox1.Name = "toolbox1";
            this.toolbox1.SelectedCategory = null;
            this.toolbox1.Size = new System.Drawing.Size(171, 338);
            this.toolbox1.TabIndex = 0;
            // 
            // ToolBoxWindow
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.ClientSize = new System.Drawing.Size(171, 338);
            this.Controls.Add(this.toolbox1);
            this.HideOnClose = true;
            this.Name = "ToolBoxWindow";
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockLeft;
            this.TabText = "工具箱";
            this.Tag = "工具箱";
            this.Text = "工具箱";
            this.ResumeLayout(false);

        }

        #endregion

        private ToolboxLibrary.Toolbox toolbox1;
    }
}