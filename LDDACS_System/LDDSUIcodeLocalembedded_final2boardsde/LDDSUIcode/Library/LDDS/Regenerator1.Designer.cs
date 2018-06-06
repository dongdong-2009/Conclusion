using System.Windows.Forms;
using System.Drawing;

namespace Library.LDDS
{
    partial class Regenerator1
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
            this.components = new System.ComponentModel.Container();
            this.label2 = new Library.Lable();
            this.label3 = new Library.Lable();
            this.label4 = new Library.Lable();
            this.label5 = new Library.Lable();
            this.label6 = new Library.Lable();
            this.label7 = new Library.Lable();
            this.label8 = new Library.Lable();
            this.label10 = new Library.Lable();
            this.label11 = new Library.Lable();
            this.label12 = new Library.Lable();
            this.label13 = new Library.Lable();
            this.label17 = new Library.Lable();
            this.label18 = new Library.Lable();
            this.label19 = new Library.Lable();
            this.label20 = new Library.Lable();
            this.label21 = new Library.Lable();
            this.label22 = new Library.Lable();
            this.label27 = new Library.Lable();
            this.label28 = new Library.Lable();
            this.AirTempIn = new Library.TextBox();
            this.AirHumIn = new Library.TextBox();
            this.AirTempOut = new Library.TextBox();
            this.AirHumOut = new Library.TextBox();
            this.PumpFb = new Library.TextBox();
            this.FanFb = new Library.TextBox();
            this.VavFb = new Library.TextBox();
            this.SolTempIn = new Library.TextBox();
            this.SolTempOut = new Library.TextBox();
            this.WaterTempIn = new Library.TextBox();
            this.WaterTempOut = new Library.TextBox();
            this.PanelControl = new Library.statusIndicator();
            this.Runstatus = new Library.statusIndicator();
            this.PumpSet = new Library.SendButton();
            this.FanSet = new Library.SendButton();
            this.SetVavSet = new Library.SendButton();
            this.SolLevelRe = new Library.Common.levelmeter();
            this.DeviceRun = new Library.Common.ButtonCheck();
            this.Startblock = new Library.Common.ButtonCheck();
            this.Wkvalve = new Library.Common.ButtonCheck();
            this.ButtonFan = new Library.Button();
            this.ButtonPump = new Library.Button();
            this.ButtonVav = new Library.Button();
            this.lable12 = new Library.Lable();
            this.Concentration = new Library.SendButton();
            this.lable13 = new Library.Lable();
            this.AutoControl = new Library.Common.ButtonCheck();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.BackColor = System.Drawing.Color.White;
            this.label2.bHaveAction = false;
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label2.ClickEvent = null;
            this.label2.DoubleEvent = null;
            this.label2.FillColorName = null;
            this.label2.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label2.Format = "{0:F2}单位";
            this.label2.heightName = null;
            this.label2.isVisible = true;
            this.label2.Location = new System.Drawing.Point(678, 199);
            this.label2.Name = "label2";
            this.label2.newFillColor = System.Drawing.Color.Red;
            this.label2.oldFillColor = System.Drawing.Color.DarkGray;
            this.label2.Size = new System.Drawing.Size(30, 15);
            this.label2.TabIndex = 2;
            this.label2.Text = "FB:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label2.textName = null;
            this.label2.Visible = false;
            this.label2.visibleName = null;
            this.label2.widthName = null;
            this.label2.xName = null;
            this.label2.yName = null;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.BackColor = System.Drawing.Color.White;
            this.label3.bHaveAction = false;
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label3.ClickEvent = null;
            this.label3.DoubleEvent = null;
            this.label3.FillColorName = null;
            this.label3.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label3.Format = "{0:F2}单位";
            this.label3.heightName = null;
            this.label3.isVisible = true;
            this.label3.Location = new System.Drawing.Point(678, 214);
            this.label3.Name = "label3";
            this.label3.newFillColor = System.Drawing.Color.Red;
            this.label3.oldFillColor = System.Drawing.Color.DarkGray;
            this.label3.Size = new System.Drawing.Size(30, 20);
            this.label3.TabIndex = 4;
            this.label3.Text = "SV:";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label3.textName = null;
            this.label3.Visible = false;
            this.label3.visibleName = null;
            this.label3.widthName = null;
            this.label3.xName = null;
            this.label3.yName = null;
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.BackColor = System.Drawing.Color.White;
            this.label4.bHaveAction = false;
            this.label4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label4.ClickEvent = null;
            this.label4.DoubleEvent = null;
            this.label4.FillColorName = null;
            this.label4.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label4.Format = "{0:F2}单位";
            this.label4.heightName = null;
            this.label4.isVisible = true;
            this.label4.Location = new System.Drawing.Point(674, 488);
            this.label4.Name = "label4";
            this.label4.newFillColor = System.Drawing.Color.Red;
            this.label4.oldFillColor = System.Drawing.Color.DarkGray;
            this.label4.Size = new System.Drawing.Size(30, 20);
            this.label4.TabIndex = 9;
            this.label4.Text = "SV:";
            this.label4.textName = null;
            this.label4.Visible = false;
            this.label4.visibleName = null;
            this.label4.widthName = null;
            this.label4.xName = null;
            this.label4.yName = null;
            // 
            // label5
            // 
            this.label5.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label5.BackColor = System.Drawing.Color.White;
            this.label5.bHaveAction = false;
            this.label5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label5.ClickEvent = null;
            this.label5.DoubleEvent = null;
            this.label5.FillColorName = null;
            this.label5.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label5.Format = "{0:F2}单位";
            this.label5.heightName = null;
            this.label5.isVisible = true;
            this.label5.Location = new System.Drawing.Point(385, 488);
            this.label5.Name = "label5";
            this.label5.newFillColor = System.Drawing.Color.Red;
            this.label5.oldFillColor = System.Drawing.Color.DarkGray;
            this.label5.Size = new System.Drawing.Size(60, 15);
            this.label5.TabIndex = 9;
            this.label5.Text = "IST:";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label5.textName = null;
            this.label5.visibleName = null;
            this.label5.widthName = null;
            this.label5.xName = null;
            this.label5.yName = null;
            // 
            // label6
            // 
            this.label6.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label6.BackColor = System.Drawing.Color.White;
            this.label6.bHaveAction = false;
            this.label6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label6.ClickEvent = null;
            this.label6.DoubleEvent = null;
            this.label6.FillColorName = null;
            this.label6.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label6.Format = "{0:F2}单位";
            this.label6.heightName = null;
            this.label6.isVisible = true;
            this.label6.Location = new System.Drawing.Point(445, 488);
            this.label6.Name = "label6";
            this.label6.newFillColor = System.Drawing.Color.Red;
            this.label6.oldFillColor = System.Drawing.Color.DarkGray;
            this.label6.Size = new System.Drawing.Size(60, 15);
            this.label6.TabIndex = 4;
            this.label6.Text = "OST:";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label6.textName = null;
            this.label6.visibleName = null;
            this.label6.widthName = null;
            this.label6.xName = null;
            this.label6.yName = null;
            // 
            // label7
            // 
            this.label7.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label7.BackColor = System.Drawing.Color.White;
            this.label7.bHaveAction = false;
            this.label7.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label7.ClickEvent = null;
            this.label7.DoubleEvent = null;
            this.label7.FillColorName = null;
            this.label7.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label7.Format = "{0:F2}单位";
            this.label7.heightName = null;
            this.label7.isVisible = true;
            this.label7.Location = new System.Drawing.Point(385, 518);
            this.label7.Name = "label7";
            this.label7.newFillColor = System.Drawing.Color.Red;
            this.label7.oldFillColor = System.Drawing.Color.DarkGray;
            this.label7.Size = new System.Drawing.Size(60, 15);
            this.label7.TabIndex = 9;
            this.label7.Text = "IWT:";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label7.textName = null;
            this.label7.visibleName = null;
            this.label7.widthName = null;
            this.label7.xName = null;
            this.label7.yName = null;
            // 
            // label8
            // 
            this.label8.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label8.BackColor = System.Drawing.Color.White;
            this.label8.bHaveAction = false;
            this.label8.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label8.ClickEvent = null;
            this.label8.DoubleEvent = null;
            this.label8.FillColorName = null;
            this.label8.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label8.Format = "{0:F2}单位";
            this.label8.heightName = null;
            this.label8.isVisible = true;
            this.label8.Location = new System.Drawing.Point(445, 518);
            this.label8.Name = "label8";
            this.label8.newFillColor = System.Drawing.Color.Red;
            this.label8.oldFillColor = System.Drawing.Color.DarkGray;
            this.label8.Size = new System.Drawing.Size(60, 15);
            this.label8.TabIndex = 4;
            this.label8.Text = "OWT:";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label8.textName = null;
            this.label8.visibleName = null;
            this.label8.widthName = null;
            this.label8.xName = null;
            this.label8.yName = null;
            // 
            // label10
            // 
            this.label10.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label10.BackColor = System.Drawing.Color.White;
            this.label10.bHaveAction = false;
            this.label10.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label10.ClickEvent = null;
            this.label10.DoubleEvent = null;
            this.label10.FillColorName = null;
            this.label10.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label10.Format = "{0:F2}单位";
            this.label10.heightName = null;
            this.label10.isVisible = true;
            this.label10.Location = new System.Drawing.Point(454, 87);
            this.label10.Name = "label10";
            this.label10.newFillColor = System.Drawing.Color.Red;
            this.label10.oldFillColor = System.Drawing.Color.DarkGray;
            this.label10.Size = new System.Drawing.Size(60, 15);
            this.label10.TabIndex = 9;
            this.label10.Text = "OAT:";
            this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label10.textName = null;
            this.label10.visibleName = null;
            this.label10.widthName = null;
            this.label10.xName = null;
            this.label10.yName = null;
            // 
            // label11
            // 
            this.label11.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label11.BackColor = System.Drawing.Color.White;
            this.label11.bHaveAction = false;
            this.label11.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label11.ClickEvent = null;
            this.label11.DoubleEvent = null;
            this.label11.FillColorName = null;
            this.label11.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label11.Format = "{0:F2}单位";
            this.label11.heightName = null;
            this.label11.isVisible = true;
            this.label11.Location = new System.Drawing.Point(514, 87);
            this.label11.Name = "label11";
            this.label11.newFillColor = System.Drawing.Color.Red;
            this.label11.oldFillColor = System.Drawing.Color.DarkGray;
            this.label11.Size = new System.Drawing.Size(60, 15);
            this.label11.TabIndex = 9;
            this.label11.Text = "OAH:";
            this.label11.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label11.textName = null;
            this.label11.visibleName = null;
            this.label11.widthName = null;
            this.label11.xName = null;
            this.label11.yName = null;
            // 
            // label12
            // 
            this.label12.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label12.AutoSize = true;
            this.label12.bHaveAction = false;
            this.label12.ClickEvent = null;
            this.label12.DoubleEvent = null;
            this.label12.FillColorName = null;
            this.label12.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label12.Format = "{0:F2}单位";
            this.label12.heightName = null;
            this.label12.isVisible = true;
            this.label12.Location = new System.Drawing.Point(40, 610);
            this.label12.Name = "label12";
            this.label12.newFillColor = System.Drawing.Color.Red;
            this.label12.oldFillColor = System.Drawing.Color.DarkGray;
            this.label12.Size = new System.Drawing.Size(51, 13);
            this.label12.TabIndex = 4;
            this.label12.Text = "StartRe:";
            this.label12.textName = null;
            this.label12.visibleName = null;
            this.label12.widthName = null;
            this.label12.xName = null;
            this.label12.yName = null;
            // 
            // label13
            // 
            this.label13.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label13.BackColor = System.Drawing.Color.White;
            this.label13.bHaveAction = false;
            this.label13.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label13.ClickEvent = null;
            this.label13.DoubleEvent = null;
            this.label13.FillColorName = null;
            this.label13.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label13.Format = "{0:F2}单位";
            this.label13.heightName = null;
            this.label13.isVisible = true;
            this.label13.Location = new System.Drawing.Point(674, 470);
            this.label13.Name = "label13";
            this.label13.newFillColor = System.Drawing.Color.Red;
            this.label13.oldFillColor = System.Drawing.Color.DarkGray;
            this.label13.Size = new System.Drawing.Size(30, 15);
            this.label13.TabIndex = 4;
            this.label13.Text = "FB:";
            this.label13.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label13.textName = null;
            this.label13.Visible = false;
            this.label13.visibleName = null;
            this.label13.widthName = null;
            this.label13.xName = null;
            this.label13.yName = null;
            // 
            // label17
            // 
            this.label17.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label17.AutoSize = true;
            this.label17.bHaveAction = false;
            this.label17.ClickEvent = null;
            this.label17.DoubleEvent = null;
            this.label17.FillColorName = null;
            this.label17.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label17.Format = "{0:F2}单位";
            this.label17.heightName = null;
            this.label17.isVisible = true;
            this.label17.Location = new System.Drawing.Point(40, 640);
            this.label17.Name = "label17";
            this.label17.newFillColor = System.Drawing.Color.Red;
            this.label17.oldFillColor = System.Drawing.Color.DarkGray;
            this.label17.Size = new System.Drawing.Size(67, 13);
            this.label17.TabIndex = 9;
            this.label17.Text = "StartBlock:";
            this.label17.textName = null;
            this.label17.visibleName = null;
            this.label17.widthName = null;
            this.label17.xName = null;
            this.label17.yName = null;
            // 
            // label18
            // 
            this.label18.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label18.BackColor = System.Drawing.Color.White;
            this.label18.bHaveAction = false;
            this.label18.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label18.ClickEvent = null;
            this.label18.DoubleEvent = null;
            this.label18.FillColorName = null;
            this.label18.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label18.Format = "{0:F2}单位";
            this.label18.heightName = null;
            this.label18.isVisible = true;
            this.label18.Location = new System.Drawing.Point(614, 87);
            this.label18.Name = "label18";
            this.label18.newFillColor = System.Drawing.Color.Red;
            this.label18.oldFillColor = System.Drawing.Color.DarkGray;
            this.label18.Size = new System.Drawing.Size(60, 15);
            this.label18.TabIndex = 4;
            this.label18.Text = "IAT:";
            this.label18.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label18.textName = null;
            this.label18.visibleName = null;
            this.label18.widthName = null;
            this.label18.xName = null;
            this.label18.yName = null;
            // 
            // label19
            // 
            this.label19.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label19.BackColor = System.Drawing.Color.White;
            this.label19.bHaveAction = false;
            this.label19.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label19.ClickEvent = null;
            this.label19.DoubleEvent = null;
            this.label19.FillColorName = null;
            this.label19.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label19.Format = "{0:F2}单位";
            this.label19.heightName = null;
            this.label19.isVisible = true;
            this.label19.Location = new System.Drawing.Point(674, 87);
            this.label19.Name = "label19";
            this.label19.newFillColor = System.Drawing.Color.Red;
            this.label19.oldFillColor = System.Drawing.Color.DarkGray;
            this.label19.Size = new System.Drawing.Size(60, 15);
            this.label19.TabIndex = 4;
            this.label19.Text = "IAH:";
            this.label19.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label19.textName = null;
            this.label19.visibleName = null;
            this.label19.widthName = null;
            this.label19.xName = null;
            this.label19.yName = null;
            // 
            // label20
            // 
            this.label20.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label20.bHaveAction = false;
            this.label20.ClickEvent = null;
            this.label20.DoubleEvent = null;
            this.label20.FillColorName = null;
            this.label20.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label20.Format = "{0:F2}单位";
            this.label20.heightName = null;
            this.label20.isVisible = true;
            this.label20.Location = new System.Drawing.Point(109, 525);
            this.label20.Name = "label20";
            this.label20.newFillColor = System.Drawing.Color.Red;
            this.label20.oldFillColor = System.Drawing.Color.DarkGray;
            this.label20.Size = new System.Drawing.Size(60, 15);
            this.label20.TabIndex = 9;
            this.label20.Text = "WSV:";
            this.label20.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label20.textName = null;
            this.label20.visibleName = null;
            this.label20.widthName = null;
            this.label20.xName = null;
            this.label20.yName = null;
            // 
            // label21
            // 
            this.label21.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label21.BackColor = System.Drawing.Color.White;
            this.label21.bHaveAction = false;
            this.label21.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label21.ClickEvent = null;
            this.label21.DoubleEvent = null;
            this.label21.FillColorName = null;
            this.label21.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label21.Format = "{0:F2}单位";
            this.label21.heightName = null;
            this.label21.isVisible = true;
            this.label21.Location = new System.Drawing.Point(295, 337);
            this.label21.Name = "label21";
            this.label21.newFillColor = System.Drawing.Color.Red;
            this.label21.oldFillColor = System.Drawing.Color.DarkGray;
            this.label21.Size = new System.Drawing.Size(30, 15);
            this.label21.TabIndex = 9;
            this.label21.Text = "FB:";
            this.label21.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label21.textName = null;
            this.label21.Visible = false;
            this.label21.visibleName = null;
            this.label21.widthName = null;
            this.label21.xName = null;
            this.label21.yName = null;
            // 
            // label22
            // 
            this.label22.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label22.BackColor = System.Drawing.Color.White;
            this.label22.bHaveAction = false;
            this.label22.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label22.ClickEvent = null;
            this.label22.DoubleEvent = null;
            this.label22.FillColorName = null;
            this.label22.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label22.Format = "{0:F2}单位";
            this.label22.heightName = null;
            this.label22.isVisible = true;
            this.label22.Location = new System.Drawing.Point(295, 355);
            this.label22.Name = "label22";
            this.label22.newFillColor = System.Drawing.Color.Red;
            this.label22.oldFillColor = System.Drawing.Color.DarkGray;
            this.label22.Size = new System.Drawing.Size(30, 20);
            this.label22.TabIndex = 9;
            this.label22.Text = "SV:";
            this.label22.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label22.textName = null;
            this.label22.Visible = false;
            this.label22.visibleName = null;
            this.label22.widthName = null;
            this.label22.xName = null;
            this.label22.yName = null;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.bHaveAction = false;
            this.label27.ClickEvent = null;
            this.label27.DoubleEvent = null;
            this.label27.FillColorName = null;
            this.label27.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label27.Format = "{0:F2}单位";
            this.label27.heightName = null;
            this.label27.isVisible = true;
            this.label27.Location = new System.Drawing.Point(29, 24);
            this.label27.Name = "label27";
            this.label27.newFillColor = System.Drawing.Color.Red;
            this.label27.oldFillColor = System.Drawing.Color.DarkGray;
            this.label27.Size = new System.Drawing.Size(53, 13);
            this.label27.TabIndex = 2;
            this.label27.Text = "PanCtrl:";
            this.label27.textName = null;
            this.label27.visibleName = null;
            this.label27.widthName = null;
            this.label27.xName = null;
            this.label27.yName = null;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.bHaveAction = false;
            this.label28.ClickEvent = null;
            this.label28.DoubleEvent = null;
            this.label28.FillColorName = null;
            this.label28.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label28.Format = "{0:F2}单位";
            this.label28.heightName = null;
            this.label28.isVisible = true;
            this.label28.Location = new System.Drawing.Point(79, 24);
            this.label28.Name = "label28";
            this.label28.newFillColor = System.Drawing.Color.Red;
            this.label28.oldFillColor = System.Drawing.Color.DarkGray;
            this.label28.Size = new System.Drawing.Size(47, 13);
            this.label28.TabIndex = 4;
            this.label28.Text = "Runsts:";
            this.label28.textName = null;
            this.label28.visibleName = null;
            this.label28.widthName = null;
            this.label28.xName = null;
            this.label28.yName = null;
            // 
            // AirTempIn
            // 
            this.AirTempIn.BoardNumber = null;
            this.AirTempIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirTempIn.DeviceName = "";
            this.AirTempIn.ID = "";
            this.AirTempIn.isVisible = true;
            this.AirTempIn.Location = new System.Drawing.Point(614, 102);
            this.AirTempIn.Name = "AirTempIn";
            this.AirTempIn.RelatedDeviceType = "";
            this.AirTempIn.RelatedPort = null;
            this.AirTempIn.Size = new System.Drawing.Size(60, 20);
            this.AirTempIn.TabIndex = 13;
            this.AirTempIn.Text = "Re_AirTempIn";
            this.AirTempIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirHumIn
            // 
            this.AirHumIn.BoardNumber = null;
            this.AirHumIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirHumIn.DeviceName = "";
            this.AirHumIn.ID = "";
            this.AirHumIn.isVisible = true;
            this.AirHumIn.Location = new System.Drawing.Point(674, 102);
            this.AirHumIn.Name = "AirHumIn";
            this.AirHumIn.RelatedDeviceType = "";
            this.AirHumIn.RelatedPort = null;
            this.AirHumIn.Size = new System.Drawing.Size(60, 20);
            this.AirHumIn.TabIndex = 14;
            this.AirHumIn.Text = "Re_AirHumIn";
            this.AirHumIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirTempOut
            // 
            this.AirTempOut.BoardNumber = null;
            this.AirTempOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirTempOut.DeviceName = "";
            this.AirTempOut.ID = "";
            this.AirTempOut.isVisible = true;
            this.AirTempOut.Location = new System.Drawing.Point(454, 102);
            this.AirTempOut.Name = "AirTempOut";
            this.AirTempOut.RelatedDeviceType = "";
            this.AirTempOut.RelatedPort = null;
            this.AirTempOut.Size = new System.Drawing.Size(60, 20);
            this.AirTempOut.TabIndex = 15;
            this.AirTempOut.Text = "Re_AirTempOut";
            this.AirTempOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirHumOut
            // 
            this.AirHumOut.BoardNumber = null;
            this.AirHumOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirHumOut.DeviceName = "";
            this.AirHumOut.ID = "";
            this.AirHumOut.isVisible = true;
            this.AirHumOut.Location = new System.Drawing.Point(514, 102);
            this.AirHumOut.Name = "AirHumOut";
            this.AirHumOut.RelatedDeviceType = "";
            this.AirHumOut.RelatedPort = null;
            this.AirHumOut.Size = new System.Drawing.Size(60, 20);
            this.AirHumOut.TabIndex = 16;
            this.AirHumOut.Text = "Re_AirHumOut";
            this.AirHumOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // PumpFb
            // 
            this.PumpFb.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PumpFb.BoardNumber = null;
            this.PumpFb.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.PumpFb.DeviceName = "";
            this.PumpFb.ID = "";
            this.PumpFb.isVisible = true;
            this.PumpFb.Location = new System.Drawing.Point(704, 468);
            this.PumpFb.Name = "PumpFb";
            this.PumpFb.RelatedDeviceType = "";
            this.PumpFb.RelatedPort = null;
            this.PumpFb.Size = new System.Drawing.Size(60, 20);
            this.PumpFb.TabIndex = 17;
            this.PumpFb.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.PumpFb.Visible = false;
            // 
            // FanFb
            // 
            this.FanFb.BoardNumber = null;
            this.FanFb.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FanFb.DeviceName = "";
            this.FanFb.ID = "";
            this.FanFb.isVisible = true;
            this.FanFb.Location = new System.Drawing.Point(708, 199);
            this.FanFb.Name = "FanFb";
            this.FanFb.RelatedDeviceType = "";
            this.FanFb.RelatedPort = null;
            this.FanFb.Size = new System.Drawing.Size(60, 20);
            this.FanFb.TabIndex = 18;
            this.FanFb.Text = "Re_FanFb";
            this.FanFb.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.FanFb.Visible = false;
            // 
            // VavFb
            // 
            this.VavFb.BoardNumber = null;
            this.VavFb.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.VavFb.DeviceName = "";
            this.VavFb.ID = "";
            this.VavFb.isVisible = true;
            this.VavFb.Location = new System.Drawing.Point(326, 336);
            this.VavFb.Name = "VavFb";
            this.VavFb.RelatedDeviceType = "";
            this.VavFb.RelatedPort = null;
            this.VavFb.Size = new System.Drawing.Size(60, 20);
            this.VavFb.TabIndex = 19;
            this.VavFb.Text = "Re_VavFb";
            this.VavFb.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VavFb.Visible = false;
            // 
            // SolTempIn
            // 
            this.SolTempIn.BoardNumber = null;
            this.SolTempIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SolTempIn.DeviceName = "";
            this.SolTempIn.ID = "";
            this.SolTempIn.isVisible = true;
            this.SolTempIn.Location = new System.Drawing.Point(385, 503);
            this.SolTempIn.Name = "SolTempIn";
            this.SolTempIn.RelatedDeviceType = "";
            this.SolTempIn.RelatedPort = null;
            this.SolTempIn.Size = new System.Drawing.Size(60, 20);
            this.SolTempIn.TabIndex = 20;
            this.SolTempIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // SolTempOut
            // 
            this.SolTempOut.BoardNumber = null;
            this.SolTempOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SolTempOut.DeviceName = "";
            this.SolTempOut.ID = "";
            this.SolTempOut.isVisible = true;
            this.SolTempOut.Location = new System.Drawing.Point(445, 503);
            this.SolTempOut.Name = "SolTempOut";
            this.SolTempOut.RelatedDeviceType = "";
            this.SolTempOut.RelatedPort = null;
            this.SolTempOut.Size = new System.Drawing.Size(60, 20);
            this.SolTempOut.TabIndex = 21;
            this.SolTempOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // WaterTempIn
            // 
            this.WaterTempIn.BoardNumber = null;
            this.WaterTempIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.WaterTempIn.DeviceName = "";
            this.WaterTempIn.ID = "";
            this.WaterTempIn.isVisible = true;
            this.WaterTempIn.Location = new System.Drawing.Point(385, 533);
            this.WaterTempIn.Name = "WaterTempIn";
            this.WaterTempIn.RelatedDeviceType = "";
            this.WaterTempIn.RelatedPort = null;
            this.WaterTempIn.Size = new System.Drawing.Size(60, 20);
            this.WaterTempIn.TabIndex = 22;
            this.WaterTempIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // WaterTempOut
            // 
            this.WaterTempOut.BoardNumber = null;
            this.WaterTempOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.WaterTempOut.DeviceName = "";
            this.WaterTempOut.ID = "";
            this.WaterTempOut.isVisible = true;
            this.WaterTempOut.Location = new System.Drawing.Point(445, 533);
            this.WaterTempOut.Name = "WaterTempOut";
            this.WaterTempOut.RelatedDeviceType = "";
            this.WaterTempOut.RelatedPort = null;
            this.WaterTempOut.Size = new System.Drawing.Size(60, 20);
            this.WaterTempOut.TabIndex = 23;
            this.WaterTempOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // PanelControl
            // 
            this.PanelControl.BackColor = System.Drawing.Color.Transparent;
            this.PanelControl.BoardNumber = null;
            this.PanelControl.DeviceName = "";
            this.PanelControl.ID = "";
            this.PanelControl.isVisible = true;
            this.PanelControl.Location = new System.Drawing.Point(34, 44);
            this.PanelControl.Name = "PanelControl";
            this.PanelControl.RelatedDeviceType = "";
            this.PanelControl.RelatedPort = null;
            this.PanelControl.Size = new System.Drawing.Size(20, 20);
            this.PanelControl.TabIndex = 2;
            this.PanelControl.Text = "PanelControl:";
            // 
            // Runstatus
            // 
            this.Runstatus.BackColor = System.Drawing.Color.Transparent;
            this.Runstatus.BoardNumber = null;
            this.Runstatus.DeviceName = "";
            this.Runstatus.ID = "";
            this.Runstatus.isVisible = true;
            this.Runstatus.Location = new System.Drawing.Point(84, 44);
            this.Runstatus.Name = "Runstatus";
            this.Runstatus.RelatedDeviceType = "";
            this.Runstatus.RelatedPort = null;
            this.Runstatus.Size = new System.Drawing.Size(20, 20);
            this.Runstatus.TabIndex = 4;
            this.Runstatus.Text = "Runstatus:";
            // 
            // PumpSet
            // 
            this.PumpSet.BoardNumber = null;
            this.PumpSet.DeviceName = "";
            this.PumpSet.ID = "";
            this.PumpSet.Location = new System.Drawing.Point(704, 488);
            this.PumpSet.Name = "PumpSet";
            this.PumpSet.PortBind = null;
            this.PumpSet.PortData = null;
            this.PumpSet.RelatedDeviceType = "";
            this.PumpSet.RelatedPort = null;
            this.PumpSet.Size = new System.Drawing.Size(60, 20);
            this.PumpSet.TabIndex = 27;
            this.PumpSet.Visible = false;
            this.PumpSet.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // FanSet
            // 
            this.FanSet.BoardNumber = null;
            this.FanSet.DeviceName = "";
            this.FanSet.ID = "";
            this.FanSet.Location = new System.Drawing.Point(708, 214);
            this.FanSet.Name = "FanSet";
            this.FanSet.PortBind = null;
            this.FanSet.PortData = null;
            this.FanSet.RelatedDeviceType = "";
            this.FanSet.RelatedPort = null;
            this.FanSet.Size = new System.Drawing.Size(60, 20);
            this.FanSet.TabIndex = 28;
            this.FanSet.Visible = false;
            this.FanSet.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // SetVavSet
            // 
            this.SetVavSet.BoardNumber = null;
            this.SetVavSet.DeviceName = "";
            this.SetVavSet.ID = "";
            this.SetVavSet.Location = new System.Drawing.Point(326, 356);
            this.SetVavSet.Name = "SetVavSet";
            this.SetVavSet.PortBind = null;
            this.SetVavSet.PortData = null;
            this.SetVavSet.RelatedDeviceType = "";
            this.SetVavSet.RelatedPort = null;
            this.SetVavSet.Size = new System.Drawing.Size(60, 20);
            this.SetVavSet.TabIndex = 26;
            this.SetVavSet.Visible = false;
            this.SetVavSet.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // SolLevelRe
            // 
            this.SolLevelRe.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SolLevelRe.BoardNumber = null;
            this.SolLevelRe.DeviceName = "";
            this.SolLevelRe.ID = "";
            this.SolLevelRe.LevelRange = "";
            this.SolLevelRe.Location = new System.Drawing.Point(546, 530);
            this.SolLevelRe.Name = "SolLevelRe";
            this.SolLevelRe.RelatedDeviceType = "";
            this.SolLevelRe.RelatedPort = null;
            this.SolLevelRe.Size = new System.Drawing.Size(12, 100);
            this.SolLevelRe.TabIndex = 24;
            this.SolLevelRe.Text = "Re_SolLevelRe";
            // 
            // DeviceRun
            // 
            this.DeviceRun.BackColor = System.Drawing.Color.Transparent;
            this.DeviceRun.BoardNumber = null;
            this.DeviceRun.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.DeviceRun.Cursor = System.Windows.Forms.Cursors.Hand;
            this.DeviceRun.DeviceName = "";
            this.DeviceRun.Location = new System.Drawing.Point(110, 610);
            this.DeviceRun.Name = "DeviceRun";
            this.DeviceRun.PortBind = "Reg3_Handle";
            this.DeviceRun.PortData = null;
            this.DeviceRun.RelatedDeviceType = "";
            this.DeviceRun.RelatedPort = "Reg3";
            this.DeviceRun.Size = new System.Drawing.Size(57, 23);
            this.DeviceRun.TabIndex = 5;
            this.DeviceRun.Click += new System.EventHandler(this.LDDSonoff_Click);
            // 
            // Startblock
            // 
            this.Startblock.BackColor = System.Drawing.Color.Transparent;
            this.Startblock.BoardNumber = null;
            this.Startblock.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style2;
            this.Startblock.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Startblock.DeviceName = "";
            this.Startblock.Location = new System.Drawing.Point(110, 640);
            this.Startblock.Name = "Startblock";
            this.Startblock.PortBind = null;
            this.Startblock.PortData = null;
            this.Startblock.RelatedDeviceType = "";
            this.Startblock.RelatedPort = null;
            this.Startblock.Size = new System.Drawing.Size(57, 23);
            this.Startblock.TabIndex = 5;
            this.Startblock.Click += new System.EventHandler(this.Startblock_Click);
            // 
            // Wkvalve
            // 
            this.Wkvalve.BackColor = System.Drawing.Color.Transparent;
            this.Wkvalve.BoardNumber = null;
            this.Wkvalve.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.Wkvalve.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Wkvalve.DeviceName = "";
            this.Wkvalve.Location = new System.Drawing.Point(109, 540);
            this.Wkvalve.Name = "Wkvalve";
            this.Wkvalve.PortBind = "DO4_Handle";
            this.Wkvalve.PortData = null;
            this.Wkvalve.RelatedDeviceType = "";
            this.Wkvalve.RelatedPort = "DO4";
            this.Wkvalve.Size = new System.Drawing.Size(60, 20);
            this.Wkvalve.TabIndex = 5;
            // 
            // ButtonFan
            // 
            this.ButtonFan.AutoSize = true;
            this.ButtonFan.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.ButtonFan.isVisible = true;
            this.ButtonFan.Location = new System.Drawing.Point(678, 174);
            this.ButtonFan.Name = "ButtonFan";
            this.ButtonFan.Size = new System.Drawing.Size(40, 23);
            this.ButtonFan.TabIndex = 30;
            this.ButtonFan.Text = "FAN";
            this.ButtonFan.Click += new System.EventHandler(this.ButtonFanClick);
            // 
            // ButtonPump
            // 
            this.ButtonPump.AutoSize = true;
            this.ButtonPump.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.ButtonPump.isVisible = true;
            this.ButtonPump.Location = new System.Drawing.Point(673, 445);
            this.ButtonPump.Name = "ButtonPump";
            this.ButtonPump.Size = new System.Drawing.Size(49, 23);
            this.ButtonPump.TabIndex = 31;
            this.ButtonPump.Text = "PUMP";
            this.ButtonPump.Click += new System.EventHandler(this.ButtonPumpClick);
            // 
            // ButtonVav
            // 
            this.ButtonVav.AutoSize = true;
            this.ButtonVav.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.ButtonVav.isVisible = true;
            this.ButtonVav.Location = new System.Drawing.Point(294, 314);
            this.ButtonVav.Name = "ButtonVav";
            this.ButtonVav.Size = new System.Drawing.Size(46, 23);
            this.ButtonVav.TabIndex = 32;
            this.ButtonVav.Text = "HWV";
            this.ButtonVav.Click += new System.EventHandler(this.ButtonVavClick);
            // 
            // lable12
            // 
            this.lable12.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable12.AutoSize = true;
            this.lable12.bHaveAction = false;
            this.lable12.ClickEvent = null;
            this.lable12.DoubleEvent = null;
            this.lable12.FillColorName = null;
            this.lable12.Font = new System.Drawing.Font("Times New Roman", 10F, System.Drawing.FontStyle.Bold);
            this.lable12.Format = "{0:F2}单位";
            this.lable12.heightName = null;
            this.lable12.isVisible = true;
            this.lable12.Location = new System.Drawing.Point(22, 110);
            this.lable12.Name = "lable12";
            this.lable12.newFillColor = System.Drawing.Color.Red;
            this.lable12.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable12.Size = new System.Drawing.Size(124, 17);
            this.lable12.TabIndex = 36;
            this.lable12.Text = "Concentration SP :";
            this.lable12.textName = null;
            this.lable12.visibleName = null;
            this.lable12.widthName = null;
            this.lable12.xName = null;
            this.lable12.yName = null;
            // 
            // Concentration
            // 
            this.Concentration.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Concentration.BoardNumber = null;
            this.Concentration.DeviceName = "";
            this.Concentration.ID = "";
            this.Concentration.Location = new System.Drawing.Point(60, 133);
            this.Concentration.Name = "Concentration";
            this.Concentration.PortBind = null;
            this.Concentration.PortData = null;
            this.Concentration.RelatedDeviceType = "";
            this.Concentration.RelatedPort = null;
            this.Concentration.Size = new System.Drawing.Size(60, 20);
            this.Concentration.TabIndex = 55;
            this.Concentration.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // lable13
            // 
            this.lable13.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable13.AutoSize = true;
            this.lable13.bHaveAction = false;
            this.lable13.ClickEvent = null;
            this.lable13.DoubleEvent = null;
            this.lable13.FillColorName = null;
            this.lable13.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable13.Format = "{0:F2}单位";
            this.lable13.heightName = null;
            this.lable13.isVisible = true;
            this.lable13.Location = new System.Drawing.Point(22, 583);
            this.lable13.Name = "lable13";
            this.lable13.newFillColor = System.Drawing.Color.Red;
            this.lable13.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable13.Size = new System.Drawing.Size(77, 13);
            this.lable13.TabIndex = 61;
            this.lable13.Text = "AutoControl:";
            this.lable13.textName = null;
            this.lable13.visibleName = null;
            this.lable13.widthName = null;
            this.lable13.xName = null;
            this.lable13.yName = null;
            // 
            // AutoControl
            // 
            this.AutoControl.BackColor = System.Drawing.Color.Transparent;
            this.AutoControl.BoardNumber = null;
            this.AutoControl.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.AutoControl.Cursor = System.Windows.Forms.Cursors.Hand;
            this.AutoControl.DeviceName = "";
            this.AutoControl.Location = new System.Drawing.Point(110, 581);
            this.AutoControl.Name = "AutoControl";
            this.AutoControl.PortBind = "Reg3_Handle";
            this.AutoControl.PortData = null;
            this.AutoControl.RelatedDeviceType = "";
            this.AutoControl.RelatedPort = "Reg3";
            this.AutoControl.Size = new System.Drawing.Size(57, 23);
            this.AutoControl.TabIndex = 60;
            // 
            // Regenerator1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.BackgroundImage = global::Library.Properties.Resources.reg940730;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Controls.Add(this.lable13);
            this.Controls.Add(this.AutoControl);
            this.Controls.Add(this.lable12);
            this.Controls.Add(this.Concentration);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label27);
            this.Controls.Add(this.label28);
            this.Controls.Add(this.AirTempIn);
            this.Controls.Add(this.AirHumIn);
            this.Controls.Add(this.AirTempOut);
            this.Controls.Add(this.AirHumOut);
            this.Controls.Add(this.PumpFb);
            this.Controls.Add(this.FanFb);
            this.Controls.Add(this.VavFb);
            this.Controls.Add(this.SolTempIn);
            this.Controls.Add(this.SolTempOut);
            this.Controls.Add(this.WaterTempIn);
            this.Controls.Add(this.WaterTempOut);
            this.Controls.Add(this.Runstatus);
            this.Controls.Add(this.PanelControl);
            this.Controls.Add(this.SolLevelRe);
            this.Controls.Add(this.SetVavSet);
            this.Controls.Add(this.PumpSet);
            this.Controls.Add(this.FanSet);
            this.Controls.Add(this.ButtonFan);
            this.Controls.Add(this.ButtonPump);
            this.Controls.Add(this.ButtonVav);
            this.Controls.Add(this.DeviceRun);
            this.Controls.Add(this.Startblock);
            this.Controls.Add(this.Wkvalve);
            this.DoubleBuffered = true;
            this.Name = "Regenerator1";
            this.Size = new System.Drawing.Size(900, 724);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        //  private Library.Lable label1;
        private Library.Lable label2;
        private Library.Lable label3;
        private Library.Lable label4;
        private Library.Lable label5;
        private Library.Lable label6;
        private Library.Lable label7;
        private Library.Lable label8;
        //private Library.Lable label9;
        private Library.Lable label10;
        private Library.Lable label11;
        private Library.Lable label12;
        private Library.Lable label13;
        //  private Library.Lable label16;
        private Library.Lable label17;
        private Library.Lable label18;
        private Library.Lable label19;
        private Library.Lable label20;
        private Library.Lable label21;
        private Library.Lable label22;
        private Library.Lable label27;
        private Library.Lable label28;

        public Library.TextBox AirTempIn;
        public Library.TextBox AirHumIn;
        public Library.TextBox AirTempOut;
        public Library.TextBox AirHumOut;
        //  public Library.TextBox Re_SolFlow;
        public Library.TextBox PumpFb;
        public Library.TextBox FanFb;
        public Library.TextBox VavFb;
        // public Library.TextBox Re_SolLevelRe;
        // public Library.TextBox Re_SolLevelST;
        public Library.TextBox SolTempIn;
        public Library.TextBox SolTempOut;
        public Library.TextBox WaterTempIn;
        public Library.TextBox WaterTempOut;
        //   public Library.TextBox Re_HumidityRatio;

        public Library.statusIndicator Runstatus;
        public Library.statusIndicator PanelControl;
        private Library.SendButton SetVavSet;
        private Library.SendButton PumpSet;
        private Library.SendButton FanSet;

        private Library.Common.levelmeter SolLevelRe;

        private Library.Button ButtonFan;
        private Library.Button ButtonPump;
        private Library.Button ButtonVav;

        private Library.Common.ButtonCheck DeviceRun;
        private Library.Common.ButtonCheck Startblock;
        private Library.Common.ButtonCheck Wkvalve;
        private Lable lable12;
        private SendButton Concentration;
        private Lable lable13;
        private Common.ButtonCheck AutoControl;
    }
}
