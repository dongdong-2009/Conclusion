namespace Library
{
    partial class SendButton
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.sendData = new System.Windows.Forms.TextBox();
            this.button = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // sendData
            // 
            this.sendData.Dock = System.Windows.Forms.DockStyle.Top;
            this.sendData.Location = new System.Drawing.Point(0, 0);
            this.sendData.Name = "sendData";
            this.sendData.Text = "Waiting";
            this.sendData.Size = new System.Drawing.Size(40, 20);
            this.sendData.TabIndex = 1;
            this.sendData.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.sendData_KeyPress);
            // 
            // button
            // 
            // this.button.BackgroundImage = global::Library.Properties.Resources.SDbutton;
            this.button.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Tile;
            this.button.Dock = System.Windows.Forms.DockStyle.None;
            this.button.Location = new System.Drawing.Point(40, 0);
            this.button.Name = "button";
            this.button.Size = new System.Drawing.Size(20, 20);
            this.button.TabIndex = 0;
            this.button.Text = "";
            this.button.UseVisualStyleBackColor = true;
            this.button.Click += new System.EventHandler(this.button_Click);
            // 
            // SendButton
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.button);
            this.Controls.Add(this.sendData);
            this.Name = "SendButton";
            this.Size = new System.Drawing.Size(60, 20);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button;
        public System.Windows.Forms.TextBox sendData;
    }
}
