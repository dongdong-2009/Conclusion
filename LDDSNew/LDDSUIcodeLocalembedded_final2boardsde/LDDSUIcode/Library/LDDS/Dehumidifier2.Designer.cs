using System.Windows.Forms;
using System.Drawing;

namespace Library.LDDS
{
    partial class Dehumidifier2
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
            this.label1 = new Library.Lable();
            this.label2 = new Library.Lable();
            this.label3 = new Library.Lable();
            this.label4 = new Library.Lable();
            this.label5 = new Library.Lable();
            this.label6 = new Library.Lable();
            this.label8 = new Library.Lable();
            this.label10 = new Library.Lable();
            this.label11 = new Library.Lable();
            this.label13 = new Library.Lable();
            this.label15 = new Library.Lable();
            this.label18 = new Library.Lable();
            this.label19 = new Library.Lable();
            this.label20 = new Library.Lable();
            this.label21 = new Library.Lable();
            this.label22 = new Library.Lable();
            this.label24 = new Library.Lable();
            this.label27 = new Library.Lable();
            this.label28 = new Library.Lable();
            this.label30 = new Library.Lable();
            this.StongSolLevel = new Library.Button();
            this.ButtonPump = new Library.Button();
            this.ButtonVav = new Library.Button();
            this.AirTempIn = new Library.TextBox();
            this.AirHumIn = new Library.TextBox();
            this.AirTempOut = new Library.TextBox();
            this.AirHumOut = new Library.TextBox();
            this.SolFlow = new Library.TextBox();
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
            this.HumidityRatio = new Library.SendButton();
            this.DeviceRun = new Library.Common.ButtonCheck();
            this.Startblock = new Library.Common.ButtonCheckFun();
            this.StrSolVav = new Library.Common.ButtonCheck();
            this.SolLevelDe = new Library.Common.levelmeter();
            this.SolLevelST = new Library.Common.levelmeter();
            this.outletair = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lable2 = new Library.Lable();
            this.lable1 = new Library.Lable();
            this.lable3 = new Library.Lable();
            this.ButtonFan = new Library.Button();
            this.CtrlParaP = new Library.SendButton();
            this.CtrlParaI = new Library.SendButton();
            this.CtrlParaD = new Library.SendButton();
            this.DeSLevelHigh = new Library.SendButton();
            this.DeSLevelTrasf = new Library.SendButton();
            this.DeSLevelOpt = new Library.SendButton();
            this.lable4 = new Library.Lable();
            this.StrSLevelHigh = new Library.SendButton();
            this.StrSLevelLow = new Library.SendButton();
            this.DeSLevelLow = new Library.SendButton();
            this.lable6 = new Library.Lable();
            this.lable7 = new Library.Lable();
            this.lable10 = new Library.Lable();
            this.lable8 = new Library.Lable();
            this.lable9 = new Library.Lable();
            this.lable12 = new Library.Lable();
            this.TsfPump = new Library.Common.ButtonCheck();
            this.lable15 = new Library.Lable();
            this.DeSolLevel = new Library.Button();
            this.CtrlParaPID = new Library.Button();
            this.AutoControl = new Library.Common.ButtonCheck();
            this.lable5 = new Library.Lable();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.BackColor = System.Drawing.Color.White;
            this.label1.bHaveAction = false;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label1.ClickEvent = null;
            this.label1.DoubleEvent = null;
            this.label1.FillColorName = null;
            this.label1.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label1.Format = "{0:F2}单位";
            this.label1.heightName = null;
            this.label1.isVisible = true;
            this.label1.Location = new System.Drawing.Point(649, 398);
            this.label1.Name = "label1";
            this.label1.newFillColor = System.Drawing.Color.Red;
            this.label1.oldFillColor = System.Drawing.Color.DarkGray;
            this.label1.Size = new System.Drawing.Size(60, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "IWT:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label1.textName = null;
            this.label1.visibleName = null;
            this.label1.widthName = null;
            this.label1.xName = null;
            this.label1.yName = null;
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
            this.label2.Location = new System.Drawing.Point(269, 511);
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
            this.label3.Location = new System.Drawing.Point(269, 526);
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
            this.label4.Location = new System.Drawing.Point(453, 568);
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
            this.label5.Location = new System.Drawing.Point(649, 368);
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
            this.label6.Location = new System.Drawing.Point(709, 368);
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
            this.label8.Location = new System.Drawing.Point(709, 398);
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
            this.label10.Location = new System.Drawing.Point(632, 52);
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
            this.label11.Location = new System.Drawing.Point(692, 52);
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
            this.label13.Location = new System.Drawing.Point(453, 553);
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
            // label15
            // 
            this.label15.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label15.BackColor = System.Drawing.Color.White;
            this.label15.bHaveAction = false;
            this.label15.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label15.ClickEvent = null;
            this.label15.DoubleEvent = null;
            this.label15.FillColorName = null;
            this.label15.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label15.Format = "{0:F2}单位";
            this.label15.heightName = null;
            this.label15.isVisible = true;
            this.label15.Location = new System.Drawing.Point(618, 196);
            this.label15.Name = "label15";
            this.label15.newFillColor = System.Drawing.Color.Red;
            this.label15.oldFillColor = System.Drawing.Color.DarkGray;
            this.label15.Size = new System.Drawing.Size(60, 15);
            this.label15.TabIndex = 9;
            this.label15.Text = "SFR:";
            this.label15.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label15.textName = null;
            this.label15.visibleName = null;
            this.label15.widthName = null;
            this.label15.xName = null;
            this.label15.yName = null;
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
            this.label18.Location = new System.Drawing.Point(219, 340);
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
            this.label19.Location = new System.Drawing.Point(279, 340);
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
            this.label20.BackColor = System.Drawing.Color.White;
            this.label20.bHaveAction = false;
            this.label20.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label20.ClickEvent = null;
            this.label20.DoubleEvent = null;
            this.label20.FillColorName = null;
            this.label20.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label20.Format = "{0:F2}单位";
            this.label20.heightName = null;
            this.label20.isVisible = true;
            this.label20.Location = new System.Drawing.Point(523, 412);
            this.label20.Name = "label20";
            this.label20.newFillColor = System.Drawing.Color.Red;
            this.label20.oldFillColor = System.Drawing.Color.DarkGray;
            this.label20.Size = new System.Drawing.Size(60, 15);
            this.label20.TabIndex = 9;
            this.label20.Text = "SSV:";
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
            this.label21.Location = new System.Drawing.Point(509, 299);
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
            this.label22.Location = new System.Drawing.Point(509, 314);
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
            // label24
            // 
            this.label24.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label24.AutoSize = true;
            this.label24.bHaveAction = false;
            this.label24.ClickEvent = null;
            this.label24.DoubleEvent = null;
            this.label24.FillColorName = null;
            this.label24.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label24.Format = "{0:F2}单位";
            this.label24.heightName = null;
            this.label24.isVisible = true;
            this.label24.Location = new System.Drawing.Point(732, 637);
            this.label24.Name = "label24";
            this.label24.newFillColor = System.Drawing.Color.Red;
            this.label24.oldFillColor = System.Drawing.Color.DarkGray;
            this.label24.Size = new System.Drawing.Size(67, 13);
            this.label24.TabIndex = 4;
            this.label24.Text = "StartBlock:";
            this.label24.textName = null;
            this.label24.visibleName = null;
            this.label24.widthName = null;
            this.label24.xName = null;
            this.label24.yName = null;
            // 
            // label27
            // 
            this.label27.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label27.AutoSize = true;
            this.label27.bHaveAction = false;
            this.label27.ClickEvent = null;
            this.label27.DoubleEvent = null;
            this.label27.FillColorName = null;
            this.label27.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label27.Format = "{0:F2}单位";
            this.label27.heightName = null;
            this.label27.isVisible = true;
            this.label27.Location = new System.Drawing.Point(25, 27);
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
            this.label28.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label28.AutoSize = true;
            this.label28.bHaveAction = false;
            this.label28.ClickEvent = null;
            this.label28.DoubleEvent = null;
            this.label28.FillColorName = null;
            this.label28.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label28.Format = "{0:F2}单位";
            this.label28.heightName = null;
            this.label28.isVisible = true;
            this.label28.Location = new System.Drawing.Point(85, 27);
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
            // label30
            // 
            this.label30.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label30.AutoSize = true;
            this.label30.bHaveAction = false;
            this.label30.ClickEvent = null;
            this.label30.DoubleEvent = null;
            this.label30.FillColorName = null;
            this.label30.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.label30.Format = "{0:F2}单位";
            this.label30.heightName = null;
            this.label30.isVisible = true;
            this.label30.Location = new System.Drawing.Point(732, 607);
            this.label30.Name = "label30";
            this.label30.newFillColor = System.Drawing.Color.Red;
            this.label30.oldFillColor = System.Drawing.Color.DarkGray;
            this.label30.Size = new System.Drawing.Size(51, 13);
            this.label30.TabIndex = 4;
            this.label30.Text = "StartDe:";
            this.label30.textName = null;
            this.label30.visibleName = null;
            this.label30.widthName = null;
            this.label30.xName = null;
            this.label30.yName = null;
            // 
            // StongSolLevel
            // 
            this.StongSolLevel.AutoSize = true;
            this.StongSolLevel.Font = new System.Drawing.Font("Times New Roman", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StongSolLevel.isVisible = true;
            this.StongSolLevel.Location = new System.Drawing.Point(28, 418);
            this.StongSolLevel.Name = "StongSolLevel";
            this.StongSolLevel.Size = new System.Drawing.Size(168, 27);
            this.StongSolLevel.TabIndex = 29;
            this.StongSolLevel.Text = "Strong Solution Level";
            this.StongSolLevel.Click += new System.EventHandler(this.ButtonStongSolLevelClick);
            // 
            // ButtonPump
            // 
            this.ButtonPump.AutoSize = true;
            this.ButtonPump.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.ButtonPump.isVisible = true;
            this.ButtonPump.Location = new System.Drawing.Point(481, 528);
            this.ButtonPump.Name = "ButtonPump";
            this.ButtonPump.Size = new System.Drawing.Size(49, 23);
            this.ButtonPump.TabIndex = 30;
            this.ButtonPump.Text = "PUMP";
            this.ButtonPump.Click += new System.EventHandler(this.ButtonPumpClick);
            // 
            // ButtonVav
            // 
            this.ButtonVav.AutoSize = true;
            this.ButtonVav.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.ButtonVav.isVisible = true;
            this.ButtonVav.Location = new System.Drawing.Point(536, 274);
            this.ButtonVav.Name = "ButtonVav";
            this.ButtonVav.Size = new System.Drawing.Size(46, 23);
            this.ButtonVav.TabIndex = 31;
            this.ButtonVav.Text = "CWV";
            this.ButtonVav.Click += new System.EventHandler(this.ButtonVavClick);
            // 
            // AirTempIn
            // 
            this.AirTempIn.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.AirTempIn.BoardNumber = null;
            this.AirTempIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirTempIn.DeviceName = "";
            this.AirTempIn.ID = "";
            this.AirTempIn.isVisible = true;
            this.AirTempIn.Location = new System.Drawing.Point(219, 355);
            this.AirTempIn.Name = "AirTempIn";
            this.AirTempIn.RelatedDeviceType = "";
            this.AirTempIn.RelatedPort = null;
            this.AirTempIn.Size = new System.Drawing.Size(60, 20);
            this.AirTempIn.TabIndex = 11;
            this.AirTempIn.Text = "AirTempIn";
            this.AirTempIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirHumIn
            // 
            this.AirHumIn.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.AirHumIn.BoardNumber = null;
            this.AirHumIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirHumIn.DeviceName = "";
            this.AirHumIn.ID = "";
            this.AirHumIn.isVisible = true;
            this.AirHumIn.Location = new System.Drawing.Point(279, 355);
            this.AirHumIn.Name = "AirHumIn";
            this.AirHumIn.RelatedDeviceType = "";
            this.AirHumIn.RelatedPort = null;
            this.AirHumIn.Size = new System.Drawing.Size(60, 20);
            this.AirHumIn.TabIndex = 12;
            this.AirHumIn.Text = "AirHumIn";
            this.AirHumIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirTempOut
            // 
            this.AirTempOut.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.AirTempOut.BoardNumber = null;
            this.AirTempOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirTempOut.DeviceName = "";
            this.AirTempOut.ID = "";
            this.AirTempOut.isVisible = true;
            this.AirTempOut.Location = new System.Drawing.Point(632, 67);
            this.AirTempOut.Name = "AirTempOut";
            this.AirTempOut.RelatedDeviceType = "";
            this.AirTempOut.RelatedPort = null;
            this.AirTempOut.Size = new System.Drawing.Size(60, 20);
            this.AirTempOut.TabIndex = 13;
            this.AirTempOut.Text = "AirTempOut";
            this.AirTempOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirHumOut
            // 
            this.AirHumOut.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.AirHumOut.BoardNumber = null;
            this.AirHumOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirHumOut.DeviceName = "";
            this.AirHumOut.ID = "";
            this.AirHumOut.isVisible = true;
            this.AirHumOut.Location = new System.Drawing.Point(692, 67);
            this.AirHumOut.Name = "AirHumOut";
            this.AirHumOut.RelatedDeviceType = "";
            this.AirHumOut.RelatedPort = null;
            this.AirHumOut.Size = new System.Drawing.Size(60, 20);
            this.AirHumOut.TabIndex = 14;
            this.AirHumOut.Text = "AirHumOut";
            this.AirHumOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // SolFlow
            // 
            this.SolFlow.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SolFlow.BoardNumber = null;
            this.SolFlow.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SolFlow.DeviceName = "";
            this.SolFlow.ID = "";
            this.SolFlow.isVisible = true;
            this.SolFlow.Location = new System.Drawing.Point(618, 211);
            this.SolFlow.Name = "SolFlow";
            this.SolFlow.RelatedDeviceType = "";
            this.SolFlow.RelatedPort = null;
            this.SolFlow.Size = new System.Drawing.Size(60, 20);
            this.SolFlow.TabIndex = 15;
            this.SolFlow.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
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
            this.PumpFb.Location = new System.Drawing.Point(483, 553);
            this.PumpFb.Name = "PumpFb";
            this.PumpFb.RelatedDeviceType = "";
            this.PumpFb.RelatedPort = null;
            this.PumpFb.Size = new System.Drawing.Size(60, 20);
            this.PumpFb.TabIndex = 16;
            this.PumpFb.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.PumpFb.Visible = false;
            // 
            // FanFb
            // 
            this.FanFb.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FanFb.BoardNumber = null;
            this.FanFb.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FanFb.DeviceName = "";
            this.FanFb.ID = "";
            this.FanFb.isVisible = true;
            this.FanFb.Location = new System.Drawing.Point(299, 511);
            this.FanFb.Name = "FanFb";
            this.FanFb.RelatedDeviceType = "";
            this.FanFb.RelatedPort = null;
            this.FanFb.Size = new System.Drawing.Size(60, 20);
            this.FanFb.TabIndex = 17;
            this.FanFb.Text = "FanFb";
            this.FanFb.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.FanFb.Visible = false;
            // 
            // VavFb
            // 
            this.VavFb.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.VavFb.BoardNumber = null;
            this.VavFb.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.VavFb.DeviceName = "";
            this.VavFb.ID = "";
            this.VavFb.isVisible = true;
            this.VavFb.Location = new System.Drawing.Point(539, 299);
            this.VavFb.Name = "VavFb";
            this.VavFb.RelatedDeviceType = "";
            this.VavFb.RelatedPort = null;
            this.VavFb.Size = new System.Drawing.Size(60, 20);
            this.VavFb.TabIndex = 18;
            this.VavFb.Text = "VavFb";
            this.VavFb.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.VavFb.Visible = false;
            // 
            // SolTempIn
            // 
            this.SolTempIn.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SolTempIn.BoardNumber = null;
            this.SolTempIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SolTempIn.DeviceName = "";
            this.SolTempIn.ID = "";
            this.SolTempIn.isVisible = true;
            this.SolTempIn.Location = new System.Drawing.Point(649, 383);
            this.SolTempIn.Name = "SolTempIn";
            this.SolTempIn.RelatedDeviceType = "";
            this.SolTempIn.RelatedPort = null;
            this.SolTempIn.Size = new System.Drawing.Size(60, 20);
            this.SolTempIn.TabIndex = 19;
            this.SolTempIn.Text = "SolTempIn";
            this.SolTempIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // SolTempOut
            // 
            this.SolTempOut.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SolTempOut.BoardNumber = null;
            this.SolTempOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SolTempOut.DeviceName = "";
            this.SolTempOut.ID = "";
            this.SolTempOut.isVisible = true;
            this.SolTempOut.Location = new System.Drawing.Point(709, 383);
            this.SolTempOut.Name = "SolTempOut";
            this.SolTempOut.RelatedDeviceType = "";
            this.SolTempOut.RelatedPort = null;
            this.SolTempOut.Size = new System.Drawing.Size(60, 20);
            this.SolTempOut.TabIndex = 20;
            this.SolTempOut.Text = "SolTempOut";
            this.SolTempOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // WaterTempIn
            // 
            this.WaterTempIn.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.WaterTempIn.BoardNumber = null;
            this.WaterTempIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.WaterTempIn.DeviceName = "";
            this.WaterTempIn.ID = "";
            this.WaterTempIn.isVisible = true;
            this.WaterTempIn.Location = new System.Drawing.Point(649, 413);
            this.WaterTempIn.Name = "WaterTempIn";
            this.WaterTempIn.RelatedDeviceType = "";
            this.WaterTempIn.RelatedPort = null;
            this.WaterTempIn.Size = new System.Drawing.Size(60, 20);
            this.WaterTempIn.TabIndex = 21;
            this.WaterTempIn.Text = "WaterTempIn";
            this.WaterTempIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // WaterTempOut
            // 
            this.WaterTempOut.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.WaterTempOut.BoardNumber = null;
            this.WaterTempOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.WaterTempOut.DeviceName = "";
            this.WaterTempOut.ID = "";
            this.WaterTempOut.isVisible = true;
            this.WaterTempOut.Location = new System.Drawing.Point(709, 413);
            this.WaterTempOut.Name = "WaterTempOut";
            this.WaterTempOut.RelatedDeviceType = "";
            this.WaterTempOut.RelatedPort = null;
            this.WaterTempOut.Size = new System.Drawing.Size(60, 20);
            this.WaterTempOut.TabIndex = 22;
            this.WaterTempOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // PanelControl
            // 
            this.PanelControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PanelControl.BackColor = System.Drawing.Color.Transparent;
            this.PanelControl.BoardNumber = null;
            this.PanelControl.DeviceName = "";
            this.PanelControl.ID = "";
            this.PanelControl.isVisible = true;
            this.PanelControl.Location = new System.Drawing.Point(25, 47);
            this.PanelControl.Name = "PanelControl";
            this.PanelControl.RelatedDeviceType = "";
            this.PanelControl.RelatedPort = null;
            this.PanelControl.Size = new System.Drawing.Size(20, 20);
            this.PanelControl.TabIndex = 2;
            this.PanelControl.Text = "De_AutoManual:";
            // 
            // Runstatus
            // 
            this.Runstatus.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Runstatus.BackColor = System.Drawing.Color.Transparent;
            this.Runstatus.BoardNumber = null;
            this.Runstatus.DeviceName = "";
            this.Runstatus.ID = "";
            this.Runstatus.isVisible = true;
            this.Runstatus.Location = new System.Drawing.Point(85, 47);
            this.Runstatus.Name = "Runstatus";
            this.Runstatus.RelatedDeviceType = "";
            this.Runstatus.RelatedPort = null;
            this.Runstatus.Size = new System.Drawing.Size(20, 20);
            this.Runstatus.TabIndex = 4;
            this.Runstatus.Text = "Runstatus:";
            // 
            // PumpSet
            // 
            this.PumpSet.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PumpSet.BoardNumber = null;
            this.PumpSet.DeviceName = "";
            this.PumpSet.ID = "";
            this.PumpSet.Location = new System.Drawing.Point(483, 568);
            this.PumpSet.Name = "PumpSet";
            this.PumpSet.PortBind = null;
            this.PumpSet.PortData = null;
            this.PumpSet.RelatedDeviceType = "";
            this.PumpSet.RelatedPort = null;
            this.PumpSet.Size = new System.Drawing.Size(60, 20);
            this.PumpSet.TabIndex = 24;
            this.PumpSet.Visible = false;
            //this.PumpSet.Click += new System.EventHandler(this.sendButtonClick);
            this.PumpSet.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // FanSet
            // 
            this.FanSet.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FanSet.BoardNumber = null;
            this.FanSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FanSet.DeviceName = "";
            this.FanSet.ID = "";
            this.FanSet.Location = new System.Drawing.Point(299, 526);
            this.FanSet.Name = "FanSet";
            this.FanSet.PortBind = null;
            this.FanSet.PortData = null;
            this.FanSet.RelatedDeviceType = "";
            this.FanSet.RelatedPort = null;
            this.FanSet.Size = new System.Drawing.Size(60, 20);
            this.FanSet.TabIndex = 25;
            this.FanSet.Visible = false;
            //this.FanSet.Click += new System.EventHandler(this.sendButtonClick);
            this.FanSet.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // SetVavSet
            // 
            this.SetVavSet.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SetVavSet.BoardNumber = null;
            this.SetVavSet.DeviceName = "";
            this.SetVavSet.ID = "";
            this.SetVavSet.Location = new System.Drawing.Point(539, 314);
            this.SetVavSet.Name = "SetVavSet";
            this.SetVavSet.PortBind = null;
            this.SetVavSet.PortData = null;
            this.SetVavSet.RelatedDeviceType = "";
            this.SetVavSet.RelatedPort = null;
            this.SetVavSet.Size = new System.Drawing.Size(60, 20);
            this.SetVavSet.TabIndex = 23;
            this.SetVavSet.Visible = false;
           // this.SetVavSet.Click += new System.EventHandler(this.sendButtonClick);
            this.SetVavSet.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // HumidityRatio
            // 
            this.HumidityRatio.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.HumidityRatio.BoardNumber = null;
            this.HumidityRatio.DeviceName = "";
            this.HumidityRatio.ID = "";
            this.HumidityRatio.Location = new System.Drawing.Point(80, 131);
            this.HumidityRatio.Name = "HumidityRatio";
            this.HumidityRatio.PortBind = null;
            this.HumidityRatio.PortData = null;
            this.HumidityRatio.RelatedDeviceType = "";
            this.HumidityRatio.RelatedPort = null;
            this.HumidityRatio.Size = new System.Drawing.Size(60, 20);
            this.HumidityRatio.TabIndex = 26;
           // this.HumidityRatio.Click += new System.EventHandler(this.sendButtonClick);
            this.HumidityRatio.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // DeviceRun
            // 
            this.DeviceRun.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DeviceRun.BackColor = System.Drawing.Color.Transparent;
            this.DeviceRun.BoardNumber = null;
            this.DeviceRun.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.DeviceRun.Cursor = System.Windows.Forms.Cursors.Hand;
            this.DeviceRun.DeviceName = "";
            this.DeviceRun.Location = new System.Drawing.Point(798, 600);
            this.DeviceRun.Name = "DeviceRun";
            this.DeviceRun.PortBind = null;
            this.DeviceRun.PortData = null;
            this.DeviceRun.RelatedDeviceType = "";
            this.DeviceRun.RelatedPort = null;
            this.DeviceRun.Size = new System.Drawing.Size(57, 23);
            this.DeviceRun.TabIndex = 5;
            this.DeviceRun.Click += new System.EventHandler(this.LDDSonoff_Click);
            // 
            // Startblock
            // 
            this.Startblock.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Startblock.BackColor = System.Drawing.Color.Transparent;
            this.Startblock.BoardNumber = null;
            this.Startblock.CheckStyleX = Library.Common.ButtonCheckFun.CheckStyle.style2;
            this.Startblock.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Startblock.DeviceName = "";
            this.Startblock.Location = new System.Drawing.Point(798, 632);
            this.Startblock.Name = "Startblock";
            this.Startblock.PortBind = null;
            this.Startblock.PortData = null;
            this.Startblock.RelatedDeviceType = "";
            this.Startblock.RelatedPort = null;
            this.Startblock.Size = new System.Drawing.Size(57, 23);
            this.Startblock.TabIndex = 5;
            this.Startblock.Click += new System.EventHandler(this.Startblock_Click);
            // 
            // StrSolVav
            // 
            this.StrSolVav.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.StrSolVav.BackColor = System.Drawing.Color.Transparent;
            this.StrSolVav.BoardNumber = null;
            this.StrSolVav.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.StrSolVav.Cursor = System.Windows.Forms.Cursors.Hand;
            this.StrSolVav.DeviceName = "";
            this.StrSolVav.Location = new System.Drawing.Point(523, 427);
            this.StrSolVav.Name = "StrSolVav";
            this.StrSolVav.PortBind = null;
            this.StrSolVav.PortData = null;
            this.StrSolVav.RelatedDeviceType = "";
            this.StrSolVav.RelatedPort = null;
            this.StrSolVav.Size = new System.Drawing.Size(60, 20);
            this.StrSolVav.TabIndex = 5;
            this.StrSolVav.Click += new System.EventHandler(this.LDDSonoff_Click);
            // 
            // SolLevelDe
            // 
            this.SolLevelDe.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SolLevelDe.BoardNumber = null;
            this.SolLevelDe.DeviceName = "";
            this.SolLevelDe.ID = "";
            this.SolLevelDe.LevelRange = "";
            this.SolLevelDe.Location = new System.Drawing.Point(644, 486);
            this.SolLevelDe.Name = "SolLevelDe";
            this.SolLevelDe.RelatedDeviceType = "";
            this.SolLevelDe.RelatedPort = null;
            this.SolLevelDe.Size = new System.Drawing.Size(12, 100);
            this.SolLevelDe.TabIndex = 27;
            this.SolLevelDe.Text = "De_SolLevelDe";
            // 
            // SolLevelST
            // 
            this.SolLevelST.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SolLevelST.BoardNumber = null;
            this.SolLevelST.DeviceName = "";
            this.SolLevelST.ID = "";
            this.SolLevelST.LevelRange = "";
            this.SolLevelST.Location = new System.Drawing.Point(351, 94);
            this.SolLevelST.Name = "SolLevelST";
            this.SolLevelST.RelatedDeviceType = "";
            this.SolLevelST.RelatedPort = null;
            this.SolLevelST.Size = new System.Drawing.Size(12, 300);
            this.SolLevelST.TabIndex = 28;
            this.SolLevelST.Text = "De_SolLevelST";
            // 
            // outletair
            // 
            this.outletair.Name = "outletair";
            // 
            // lable2
            // 
            this.lable2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable2.BackColor = System.Drawing.Color.White;
            this.lable2.bHaveAction = false;
            this.lable2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable2.ClickEvent = null;
            this.lable2.DoubleEvent = null;
            this.lable2.FillColorName = null;
            this.lable2.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable2.Format = "{0:F2}单位";
            this.lable2.heightName = null;
            this.lable2.isVisible = true;
            this.lable2.Location = new System.Drawing.Point(57, 214);
            this.lable2.Name = "lable2";
            this.lable2.newFillColor = System.Drawing.Color.Red;
            this.lable2.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable2.Size = new System.Drawing.Size(24, 24);
            this.lable2.TabIndex = 4;
            this.lable2.Text = "P:";
            this.lable2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable2.textName = null;
            this.lable2.Visible = false;
            this.lable2.visibleName = null;
            this.lable2.widthName = null;
            this.lable2.xName = null;
            this.lable2.yName = null;
            // 
            // lable1
            // 
            this.lable1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable1.BackColor = System.Drawing.Color.White;
            this.lable1.bHaveAction = false;
            this.lable1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable1.ClickEvent = null;
            this.lable1.DoubleEvent = null;
            this.lable1.FillColorName = null;
            this.lable1.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable1.Format = "{0:F2}单位";
            this.lable1.heightName = null;
            this.lable1.isVisible = true;
            this.lable1.Location = new System.Drawing.Point(57, 236);
            this.lable1.Name = "lable1";
            this.lable1.newFillColor = System.Drawing.Color.Red;
            this.lable1.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable1.Size = new System.Drawing.Size(24, 24);
            this.lable1.TabIndex = 4;
            this.lable1.Text = "I:";
            this.lable1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable1.textName = null;
            this.lable1.Visible = false;
            this.lable1.visibleName = null;
            this.lable1.widthName = null;
            this.lable1.xName = null;
            this.lable1.yName = null;
            // 
            // lable3
            // 
            this.lable3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable3.BackColor = System.Drawing.Color.White;
            this.lable3.bHaveAction = false;
            this.lable3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable3.ClickEvent = null;
            this.lable3.DoubleEvent = null;
            this.lable3.FillColorName = null;
            this.lable3.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable3.Format = "{0:F2}单位";
            this.lable3.heightName = null;
            this.lable3.isVisible = true;
            this.lable3.Location = new System.Drawing.Point(57, 258);
            this.lable3.Name = "lable3";
            this.lable3.newFillColor = System.Drawing.Color.Red;
            this.lable3.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable3.Size = new System.Drawing.Size(24, 26);
            this.lable3.TabIndex = 4;
            this.lable3.Text = "D:";
            this.lable3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable3.textName = null;
            this.lable3.Visible = false;
            this.lable3.visibleName = null;
            this.lable3.widthName = null;
            this.lable3.xName = null;
            this.lable3.yName = null;
            // 
            // ButtonFan
            // 
            this.ButtonFan.AutoSize = true;
            this.ButtonFan.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.ButtonFan.isVisible = true;
            this.ButtonFan.Location = new System.Drawing.Point(310, 482);
            this.ButtonFan.Name = "ButtonFan";
            this.ButtonFan.Size = new System.Drawing.Size(49, 23);
            this.ButtonFan.TabIndex = 30;
            this.ButtonFan.Text = "FAN";
            this.ButtonFan.Click += new System.EventHandler(this.ButtonFanClick);
            // 
            // CtrlParaP
            // 
            this.CtrlParaP.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.CtrlParaP.BoardNumber = null;
            this.CtrlParaP.DeviceName = "";
            this.CtrlParaP.ID = "";
            this.CtrlParaP.Location = new System.Drawing.Point(83, 215);
            this.CtrlParaP.Name = "CtrlParaP";
            this.CtrlParaP.PortBind = null;
            this.CtrlParaP.PortData = null;
            this.CtrlParaP.RelatedDeviceType = "";
            this.CtrlParaP.RelatedPort = null;
            this.CtrlParaP.Size = new System.Drawing.Size(60, 20);
            this.CtrlParaP.TabIndex = 26;
            this.CtrlParaP.Visible = false;
           // this.CtrlParaP.Click += new System.EventHandler(this.sendButtonClick);
            this.CtrlParaP.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);
            // 
            // CtrlParaI
            // 
            this.CtrlParaI.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.CtrlParaI.BoardNumber = null;
            this.CtrlParaI.DeviceName = "";
            this.CtrlParaI.ID = "";
            this.CtrlParaI.Location = new System.Drawing.Point(83, 238);
            this.CtrlParaI.Name = "CtrlParaI";
            this.CtrlParaI.PortBind = null;
            this.CtrlParaI.PortData = null;
            this.CtrlParaI.RelatedDeviceType = "";
            this.CtrlParaI.RelatedPort = null;
            this.CtrlParaI.Size = new System.Drawing.Size(60, 20);
            this.CtrlParaI.TabIndex = 26;
            this.CtrlParaI.Visible = false;
           // this.CtrlParaI.Click += new System.EventHandler(this.sendButtonClick);
            this.CtrlParaI.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // CtrlParaD
            // 
            this.CtrlParaD.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.CtrlParaD.BoardNumber = null;
            this.CtrlParaD.DeviceName = "";
            this.CtrlParaD.ID = "";
            this.CtrlParaD.Location = new System.Drawing.Point(83, 261);
            this.CtrlParaD.Name = "CtrlParaD";
            this.CtrlParaD.PortBind = null;
            this.CtrlParaD.PortData = null;
            this.CtrlParaD.RelatedDeviceType = "";
            this.CtrlParaD.RelatedPort = null;
            this.CtrlParaD.Size = new System.Drawing.Size(60, 20);
            this.CtrlParaD.TabIndex = 26;
            this.CtrlParaD.Visible = false;
            // this.CtrlParaD.Click += new System.EventHandler(this.sendButtonClick);
            this.CtrlParaD.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // DeSLevelHigh
            // 
            this.DeSLevelHigh.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DeSLevelHigh.BoardNumber = null;
            this.DeSLevelHigh.DeviceName = "";
            this.DeSLevelHigh.ID = "";
            this.DeSLevelHigh.Location = new System.Drawing.Point(138, 570);
            this.DeSLevelHigh.Name = "DeSLevelHigh";
            this.DeSLevelHigh.PortBind = null;
            this.DeSLevelHigh.PortData = null;
            this.DeSLevelHigh.RelatedDeviceType = "";
            this.DeSLevelHigh.RelatedPort = null;
            this.DeSLevelHigh.Size = new System.Drawing.Size(60, 20);
            this.DeSLevelHigh.TabIndex = 26;
            this.DeSLevelHigh.Visible = false;
          //  this.DeSLevelHigh.Click += new System.EventHandler(this.sendButtonClick);
            this.DeSLevelHigh.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // DeSLevelTrasf
            // 
            this.DeSLevelTrasf.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DeSLevelTrasf.BoardNumber = null;
            this.DeSLevelTrasf.DeviceName = "";
            this.DeSLevelTrasf.ID = "";
            this.DeSLevelTrasf.Location = new System.Drawing.Point(138, 593);
            this.DeSLevelTrasf.Name = "DeSLevelTrasf";
            this.DeSLevelTrasf.PortBind = null;
            this.DeSLevelTrasf.PortData = null;
            this.DeSLevelTrasf.RelatedDeviceType = "";
            this.DeSLevelTrasf.RelatedPort = null;
            this.DeSLevelTrasf.Size = new System.Drawing.Size(60, 20);
            this.DeSLevelTrasf.TabIndex = 26;
            this.DeSLevelTrasf.Visible = false;
            //this.DeSLevelTrasf.Click += new System.EventHandler(this.sendButtonClick);
            this.DeSLevelTrasf.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // DeSLevelOpt
            // 
            this.DeSLevelOpt.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DeSLevelOpt.BoardNumber = null;
            this.DeSLevelOpt.DeviceName = "";
            this.DeSLevelOpt.ID = "";
            this.DeSLevelOpt.Location = new System.Drawing.Point(138, 616);
            this.DeSLevelOpt.Name = "DeSLevelOpt";
            this.DeSLevelOpt.PortBind = null;
            this.DeSLevelOpt.PortData = null;
            this.DeSLevelOpt.RelatedDeviceType = "";
            this.DeSLevelOpt.RelatedPort = null;
            this.DeSLevelOpt.Size = new System.Drawing.Size(60, 20);
            this.DeSLevelOpt.TabIndex = 26;
            this.DeSLevelOpt.Visible = false;
           // this.DeSLevelOpt.Click += new System.EventHandler(this.sendButtonClick);
            this.DeSLevelOpt.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // lable4
            // 
            this.lable4.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable4.BackColor = System.Drawing.Color.White;
            this.lable4.bHaveAction = false;
            this.lable4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable4.ClickEvent = null;
            this.lable4.DoubleEvent = null;
            this.lable4.FillColorName = null;
            this.lable4.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable4.Format = "{0:F2}单位";
            this.lable4.heightName = null;
            this.lable4.isVisible = false;
            this.lable4.Location = new System.Drawing.Point(29, 570);
            this.lable4.Name = "lable4";
            this.lable4.newFillColor = System.Drawing.Color.Red;
            this.lable4.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable4.Size = new System.Drawing.Size(107, 20);
            this.lable4.TabIndex = 4;
            this.lable4.Text = "HighLevel Alarm:";
            this.lable4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable4.textName = null;
            this.lable4.Visible = false;
            this.lable4.visibleName = null;
            this.lable4.widthName = null;
            this.lable4.xName = null;
            this.lable4.yName = null;
            // 
            // StrSLevelHigh
            // 
            this.StrSLevelHigh.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.StrSLevelHigh.BoardNumber = null;
            this.StrSLevelHigh.DeviceName = "";
            this.StrSLevelHigh.ID = "";
            this.StrSLevelHigh.Location = new System.Drawing.Point(136, 451);
            this.StrSLevelHigh.Name = "StrSLevelHigh";
            this.StrSLevelHigh.PortBind = null;
            this.StrSLevelHigh.PortData = null;
            this.StrSLevelHigh.RelatedDeviceType = "";
            this.StrSLevelHigh.RelatedPort = null;
            this.StrSLevelHigh.Size = new System.Drawing.Size(60, 20);
            this.StrSLevelHigh.TabIndex = 26;
            this.StrSLevelHigh.Visible = false;
           // this.StrSLevelHigh.Click += new System.EventHandler(this.sendButtonClick);
            this.StrSLevelHigh.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);


            // 
            // StrSLevelLow
            // 
            this.StrSLevelLow.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.StrSLevelLow.BoardNumber = null;
            this.StrSLevelLow.DeviceName = "";
            this.StrSLevelLow.ID = "";
            this.StrSLevelLow.Location = new System.Drawing.Point(136, 474);
            this.StrSLevelLow.Name = "StrSLevelLow";
            this.StrSLevelLow.PortBind = null;
            this.StrSLevelLow.PortData = null;
            this.StrSLevelLow.RelatedDeviceType = "";
            this.StrSLevelLow.RelatedPort = null;
            this.StrSLevelLow.Size = new System.Drawing.Size(60, 20);
            this.StrSLevelLow.TabIndex = 26;
            this.StrSLevelLow.Visible = false;
           // this.StrSLevelLow.Click += new System.EventHandler(this.sendButtonClick);
            this.StrSLevelLow.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // DeSLevelLow
            // 
            this.DeSLevelLow.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DeSLevelLow.BoardNumber = null;
            this.DeSLevelLow.DeviceName = "";
            this.DeSLevelLow.ID = "";
            this.DeSLevelLow.Location = new System.Drawing.Point(138, 637);
            this.DeSLevelLow.Name = "DeSLevelLow";
            this.DeSLevelLow.PortBind = null;
            this.DeSLevelLow.PortData = null;
            this.DeSLevelLow.RelatedDeviceType = "";
            this.DeSLevelLow.RelatedPort = null;
            this.DeSLevelLow.Size = new System.Drawing.Size(60, 20);
            this.DeSLevelLow.TabIndex = 26;
            this.DeSLevelLow.Visible = false;
            //this.DeSLevelLow.Click += new System.EventHandler(this.sendButtonClick);
            this.DeSLevelLow.UserControlBtnClicked += new SendButton.BtnclickHandle(this.sendButtonClick);

            // 
            // lable6
            // 
            this.lable6.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable6.BackColor = System.Drawing.Color.White;
            this.lable6.bHaveAction = false;
            this.lable6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable6.ClickEvent = null;
            this.lable6.DoubleEvent = null;
            this.lable6.FillColorName = null;
            this.lable6.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable6.Format = "{0:F2}单位";
            this.lable6.heightName = null;
            this.lable6.isVisible = false;
            this.lable6.Location = new System.Drawing.Point(29, 637);
            this.lable6.Name = "lable6";
            this.lable6.newFillColor = System.Drawing.Color.Red;
            this.lable6.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable6.Size = new System.Drawing.Size(107, 20);
            this.lable6.TabIndex = 4;
            this.lable6.Text = "LowLevel Alarm:";
            this.lable6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable6.textName = null;
            this.lable6.Visible = false;
            this.lable6.visibleName = null;
            this.lable6.widthName = null;
            this.lable6.xName = null;
            this.lable6.yName = null;
            // 
            // lable7
            // 
            this.lable7.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable7.BackColor = System.Drawing.Color.White;
            this.lable7.bHaveAction = false;
            this.lable7.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable7.ClickEvent = null;
            this.lable7.DoubleEvent = null;
            this.lable7.FillColorName = null;
            this.lable7.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable7.Format = "{0:F2}单位";
            this.lable7.heightName = null;
            this.lable7.isVisible = false;
            this.lable7.Location = new System.Drawing.Point(29, 616);
            this.lable7.Name = "lable7";
            this.lable7.newFillColor = System.Drawing.Color.Red;
            this.lable7.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable7.Size = new System.Drawing.Size(107, 20);
            this.lable7.TabIndex = 4;
            this.lable7.Text = "OptimalLevel:";
            this.lable7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable7.textName = null;
            this.lable7.Visible = false;
            this.lable7.visibleName = null;
            this.lable7.widthName = null;
            this.lable7.xName = null;
            this.lable7.yName = null;
            // 
            // lable10
            // 
            this.lable10.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable10.BackColor = System.Drawing.Color.White;
            this.lable10.bHaveAction = false;
            this.lable10.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable10.ClickEvent = null;
            this.lable10.DoubleEvent = null;
            this.lable10.FillColorName = null;
            this.lable10.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable10.Format = "{0:F2}单位";
            this.lable10.heightName = null;
            this.lable10.isVisible = false;
            this.lable10.Location = new System.Drawing.Point(29, 593);
            this.lable10.Name = "lable10";
            this.lable10.newFillColor = System.Drawing.Color.Red;
            this.lable10.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable10.Size = new System.Drawing.Size(107, 20);
            this.lable10.TabIndex = 4;
            this.lable10.Text = "TransferLevel:";
            this.lable10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable10.textName = null;
            this.lable10.Visible = false;
            this.lable10.visibleName = null;
            this.lable10.widthName = null;
            this.lable10.xName = null;
            this.lable10.yName = null;
            // 
            // lable8
            // 
            this.lable8.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable8.BackColor = System.Drawing.Color.White;
            this.lable8.bHaveAction = false;
            this.lable8.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable8.ClickEvent = null;
            this.lable8.DoubleEvent = null;
            this.lable8.FillColorName = null;
            this.lable8.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable8.Format = "{0:F2}单位";
            this.lable8.heightName = null;
            this.lable8.isVisible = false;
            this.lable8.Location = new System.Drawing.Point(28, 451);
            this.lable8.Name = "lable8";
            this.lable8.newFillColor = System.Drawing.Color.Red;
            this.lable8.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable8.Size = new System.Drawing.Size(107, 20);
            this.lable8.TabIndex = 4;
            this.lable8.Text = "HighLevel Alarm:";
            this.lable8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable8.textName = null;
            this.lable8.Visible = false;
            this.lable8.visibleName = null;
            this.lable8.widthName = null;
            this.lable8.xName = null;
            this.lable8.yName = null;
            // 
            // lable9
            // 
            this.lable9.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable9.BackColor = System.Drawing.Color.White;
            this.lable9.bHaveAction = false;
            this.lable9.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable9.ClickEvent = null;
            this.lable9.DoubleEvent = null;
            this.lable9.FillColorName = null;
            this.lable9.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable9.Format = "{0:F2}单位";
            this.lable9.heightName = null;
            this.lable9.isVisible = false;
            this.lable9.Location = new System.Drawing.Point(28, 474);
            this.lable9.Name = "lable9";
            this.lable9.newFillColor = System.Drawing.Color.Red;
            this.lable9.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable9.Size = new System.Drawing.Size(107, 20);
            this.lable9.TabIndex = 4;
            this.lable9.Text = "LowLevel Alarm:";
            this.lable9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable9.textName = null;
            this.lable9.Visible = false;
            this.lable9.visibleName = null;
            this.lable9.widthName = null;
            this.lable9.xName = null;
            this.lable9.yName = null;
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
            this.lable12.Location = new System.Drawing.Point(42, 108);
            this.lable12.Name = "lable12";
            this.lable12.newFillColor = System.Drawing.Color.Red;
            this.lable12.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable12.Size = new System.Drawing.Size(130, 17);
            this.lable12.TabIndex = 4;
            this.lable12.Text = "Humidity Ratio SP :";
            this.lable12.textName = null;
            this.lable12.visibleName = null;
            this.lable12.widthName = null;
            this.lable12.xName = null;
            this.lable12.yName = null;
            // 
            // TsfPump
            // 
            this.TsfPump.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TsfPump.BackColor = System.Drawing.Color.Transparent;
            this.TsfPump.BoardNumber = null;
            this.TsfPump.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.TsfPump.Cursor = System.Windows.Forms.Cursors.Hand;
            this.TsfPump.DeviceName = "";
            this.TsfPump.Location = new System.Drawing.Point(383, 456);
            this.TsfPump.Name = "TsfPump";
            this.TsfPump.PortBind = null;
            this.TsfPump.PortData = null;
            this.TsfPump.RelatedDeviceType = "";
            this.TsfPump.RelatedPort = null;
            this.TsfPump.Size = new System.Drawing.Size(60, 20);
            this.TsfPump.TabIndex = 5;
            this.TsfPump.Click += new System.EventHandler(this.LDDSonoff_Click);
            // 
            // lable15
            // 
            this.lable15.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable15.BackColor = System.Drawing.Color.White;
            this.lable15.bHaveAction = false;
            this.lable15.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable15.ClickEvent = null;
            this.lable15.DoubleEvent = null;
            this.lable15.FillColorName = null;
            this.lable15.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable15.Format = "{0:F2}单位";
            this.lable15.heightName = null;
            this.lable15.isVisible = true;
            this.lable15.Location = new System.Drawing.Point(383, 441);
            this.lable15.Name = "lable15";
            this.lable15.newFillColor = System.Drawing.Color.Red;
            this.lable15.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable15.Size = new System.Drawing.Size(60, 15);
            this.lable15.TabIndex = 9;
            this.lable15.Text = "T_PUMP:";
            this.lable15.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable15.textName = null;
            this.lable15.visibleName = null;
            this.lable15.widthName = null;
            this.lable15.xName = null;
            this.lable15.yName = null;
            // 
            // DeSolLevel
            // 
            this.DeSolLevel.AutoSize = true;
            this.DeSolLevel.Font = new System.Drawing.Font("Times New Roman", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DeSolLevel.isVisible = true;
            this.DeSolLevel.Location = new System.Drawing.Point(28, 537);
            this.DeSolLevel.Name = "DeSolLevel";
            this.DeSolLevel.Size = new System.Drawing.Size(168, 27);
            this.DeSolLevel.TabIndex = 29;
            this.DeSolLevel.Text = "De Solution Level";
            this.DeSolLevel.Click += new System.EventHandler(this.ButtonDeSolLevelClick);
            // 
            // CtrlParaPID
            // 
            this.CtrlParaPID.Font = new System.Drawing.Font("Times New Roman", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CtrlParaPID.isVisible = true;
            this.CtrlParaPID.Location = new System.Drawing.Point(33, 182);
            this.CtrlParaPID.Name = "CtrlParaPID";
            this.CtrlParaPID.Size = new System.Drawing.Size(150, 27);
            this.CtrlParaPID.TabIndex = 32;
            this.CtrlParaPID.Text = "Control Parameters";
            this.CtrlParaPID.UseVisualStyleBackColor = true;
            this.CtrlParaPID.Click += new System.EventHandler(this.ButtonctrlparaClick);
            // 
            // AutoControl
            // 
            this.AutoControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.AutoControl.BackColor = System.Drawing.Color.Transparent;
            this.AutoControl.BoardNumber = null;
            this.AutoControl.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.AutoControl.Cursor = System.Windows.Forms.Cursors.Hand;
            this.AutoControl.DeviceName = "";
            this.AutoControl.Location = new System.Drawing.Point(798, 569);
            this.AutoControl.Name = "AutoControl";
            this.AutoControl.PortBind = null;
            this.AutoControl.PortData = null;
            this.AutoControl.RelatedDeviceType = "";
            this.AutoControl.RelatedPort = null;
            this.AutoControl.Size = new System.Drawing.Size(57, 23);
            this.AutoControl.TabIndex = 33;
            this.AutoControl.Click += new System.EventHandler(this.AutoControl_Click);
            // 
            // lable5
            // 
            this.lable5.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable5.AutoSize = true;
            this.lable5.bHaveAction = false;
            this.lable5.ClickEvent = null;
            this.lable5.DoubleEvent = null;
            this.lable5.FillColorName = null;
            this.lable5.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable5.Format = "{0:F2}单位";
            this.lable5.heightName = null;
            this.lable5.isVisible = true;
            this.lable5.Location = new System.Drawing.Point(721, 575);
            this.lable5.Name = "lable5";
            this.lable5.newFillColor = System.Drawing.Color.Red;
            this.lable5.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable5.Size = new System.Drawing.Size(77, 13);
            this.lable5.TabIndex = 34;
            this.lable5.Text = "AutoControl:";
            this.lable5.textName = null;
            this.lable5.visibleName = null;
            this.lable5.widthName = null;
            this.lable5.xName = null;
            this.lable5.yName = null;
            // 
            // Dehumidifier3
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.BackgroundImage = global::Library.Properties.Resources.de940730;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Controls.Add(this.lable5);
            this.Controls.Add(this.AutoControl);
            this.Controls.Add(this.CtrlParaPID);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.lable3);
            this.Controls.Add(this.lable1);
            this.Controls.Add(this.lable7);
            this.Controls.Add(this.lable9);
            this.Controls.Add(this.lable6);
            this.Controls.Add(this.lable10);
            this.Controls.Add(this.lable8);
            this.Controls.Add(this.lable4);
            this.Controls.Add(this.lable2);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.lable15);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label24);
            this.Controls.Add(this.label27);
            this.Controls.Add(this.lable12);
            this.Controls.Add(this.label28);
            this.Controls.Add(this.ButtonFan);
            this.Controls.Add(this.label30);
            this.Controls.Add(this.AirTempIn);
            this.Controls.Add(this.AirHumIn);
            this.Controls.Add(this.AirTempOut);
            this.Controls.Add(this.AirHumOut);
            this.Controls.Add(this.SolFlow);
            this.Controls.Add(this.PumpFb);
            this.Controls.Add(this.FanFb);
            this.Controls.Add(this.VavFb);
            this.Controls.Add(this.SolTempIn);
            this.Controls.Add(this.SolTempOut);
            this.Controls.Add(this.WaterTempIn);
            this.Controls.Add(this.WaterTempOut);
            this.Controls.Add(this.Runstatus);
            this.Controls.Add(this.PanelControl);
            this.Controls.Add(this.SetVavSet);
            this.Controls.Add(this.StrSLevelLow);
            this.Controls.Add(this.PumpSet);
            this.Controls.Add(this.DeSLevelOpt);
            this.Controls.Add(this.StrSLevelHigh);
            this.Controls.Add(this.FanSet);
            this.Controls.Add(this.DeSLevelLow);
            this.Controls.Add(this.DeSLevelTrasf);
            this.Controls.Add(this.CtrlParaD);
            this.Controls.Add(this.DeSLevelHigh);
            this.Controls.Add(this.CtrlParaI);
            this.Controls.Add(this.CtrlParaP);
            this.Controls.Add(this.HumidityRatio);
            this.Controls.Add(this.DeviceRun);
            this.Controls.Add(this.TsfPump);
            this.Controls.Add(this.Startblock);
            this.Controls.Add(this.StrSolVav);
            this.Controls.Add(this.SolLevelDe);
            this.Controls.Add(this.SolLevelST);
            this.Controls.Add(this.DeSolLevel);
            this.Controls.Add(this.StongSolLevel);
            this.Controls.Add(this.ButtonPump);
            this.Controls.Add(this.ButtonVav);
            this.DoubleBuffered = true;
            this.Name = "Dehumidifier3";
            this.Size = new System.Drawing.Size(900, 724);
            this.ResumeLayout(false);
            this.PerformLayout();

        }



        #endregion

        private Library.Lable label1;
        private Library.Lable label2;
        private Library.Lable label3;
        private Library.Lable label4;
        private Library.Lable label5;
        private Library.Lable label6;
        //private Library.Lable label7;
        private Library.Lable label8;
        //  private Library.Lable label9;
        private Library.Lable label10;
        private Library.Lable label11;
        //private Library.Lable label12;
        private Library.Lable label13;
        private Library.Lable label15;
        // private Library.Lable label16;
        // private Library.Lable label17;
        private Library.Lable label18;
        private Library.Lable label19;
        private Library.Lable label20;
        public Library.Lable label21;
        public Library.Lable label22;
        // private Library.Lable label23;
        private Library.Lable label24;
        private Library.Lable label27;
        private Library.Lable label28;
        // public Library.Lable label29;
        private Library.Lable label30;

        public Library.TextBox AirTempIn;
        public Library.TextBox AirHumIn;
        public Library.TextBox AirTempOut;
        public Library.TextBox AirHumOut;
        public Library.TextBox SolFlow;
        public Library.TextBox PumpFb;
        public Library.TextBox FanFb;
        public Library.TextBox VavFb;
        //  public Library.TextBox De_SolLevelDe;
        //  public Library.TextBox De_SolLevelST;
        public Library.TextBox SolTempIn;
        public Library.TextBox SolTempOut;
        public Library.TextBox WaterTempIn;
        public Library.TextBox WaterTempOut;
        //    public Library.TextBox De_HumidityRatio;

        public Library.statusIndicator Runstatus;
        public Library.statusIndicator PanelControl;

        public DataGridViewTextBoxColumn outletair;//创建文本框字段

        //   List<TextBox> Textcollection = new List<TextBox>();

        public Library.SendButton SetVavSet;
        private Library.SendButton PumpSet;
        private Library.SendButton FanSet;
        private Library.SendButton HumidityRatio;

        private Library.Button StongSolLevel;
        private Library.Button ButtonPump;
        private Library.Button ButtonVav;

        private Library.Common.levelmeter SolLevelDe;
        private Library.Common.levelmeter SolLevelST;

        private Library.Common.ButtonCheck StrSolVav;

        private Library.Common.ButtonCheckFun Startblock;

        private Library.Common.ButtonCheck DeviceRun;
        private Lable lable2;
        private Lable lable1;
        private Lable lable3;
        private SendButton CtrlParaP;
        private SendButton CtrlParaI;
        private SendButton CtrlParaD;
        private SendButton DeSLevelHigh;
        private SendButton DeSLevelTrasf;
        private SendButton DeSLevelOpt;
        private Lable lable4;
        private SendButton StrSLevelHigh;
        private SendButton StrSLevelLow;
        private SendButton DeSLevelLow;
        private Lable lable6;
        private Lable lable7;
        private Lable lable10;
        private Lable lable8;
        private Lable lable9;
        private Lable lable12;
        private Common.ButtonCheck TsfPump;
        private Lable lable15;
        private Button DeSolLevel;
        private Button ButtonFan;
        private Button CtrlParaPID;
        private Common.ButtonCheck AutoControl;
        private Lable lable5;
    }




}
