using System.Windows.Forms;
using System.Drawing;

namespace Library.LDDS
{
    partial class Regenerator3
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
            this.label5 = new Library.Lable();
            this.label6 = new Library.Lable();
            this.label7 = new Library.Lable();
            this.label8 = new Library.Lable();
            this.label10 = new Library.Lable();
            this.label11 = new Library.Lable();
            this.label12 = new Library.Lable();
            this.label17 = new Library.Lable();
            this.label18 = new Library.Lable();
            this.label19 = new Library.Lable();
            this.label20 = new Library.Lable();
            this.label22 = new Library.Lable();
            this.label27 = new Library.Lable();
            this.label28 = new Library.Lable();
            this.AirTempIn = new Library.TextBox();
            this.AirHumIn = new Library.TextBox();
            this.AirTempOut = new Library.TextBox();
            this.AirHumOut = new Library.TextBox();
            this.SolTempIn = new Library.TextBox();
            this.SolTempOut = new Library.TextBox();
            this.WaterTempIn = new Library.TextBox();
            this.WaterTempOut = new Library.TextBox();
            this.PanelControl = new Library.statusIndicator();
            this.Runstatus = new Library.statusIndicator();
            this.SetVavSet = new Library.SendButton();
            this.SolLevelRe = new Library.Common.levelmeter();
            this.DeviceRun = new Library.Common.ButtonCheck();
            this.Startblock = new Library.Common.ButtonCheckFun();
            this.Wkvalve = new Library.Common.ButtonCheck();
            this.ButtonVav = new Library.Button();
            this.lable7 = new Library.Lable();
            this.lable9 = new Library.Lable();
            this.lable6 = new Library.Lable();
            this.lable10 = new Library.Lable();
            this.lable8 = new Library.Lable();
            this.lable4 = new Library.Lable();
            this.lable12 = new Library.Lable();
            this.WkSLevelHigh = new Library.SendButton();
            this.ReSLevelStop = new Library.SendButton();
            this.WkSLevelHAlm = new Library.SendButton();
            this.ReSLevelLAlm = new Library.SendButton();
            this.ReSLevelStart = new Library.SendButton();
            this.ReSLevelHAlm = new Library.SendButton();
            this.DeltaCon = new Library.SendButton();
            this.WeakSolLevel = new Library.Button();
            this.ReSolLevel = new Library.Button();
            this.FanOnOff = new Library.Common.ButtonCheck();
            this.lable1 = new Library.Lable();
            this.PumpOnOff = new Library.Common.ButtonCheck();
            this.lable2 = new Library.Lable();
            this.SSLevelAlm = new Library.SendButton();
            this.SSLevelHigh = new Library.SendButton();
            this.lable3 = new Library.Lable();
            this.lable5 = new Library.Lable();
            this.StrongSolLevel = new Library.Button();
            this.SolLevelWT = new Library.Common.levelmeter();
            this.lable11 = new Library.Lable();
            this.AutoControl = new Library.Common.ButtonCheck();
            this.lable13 = new Library.Lable();
            this.SuspendLayout();
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
            this.label5.Location = new System.Drawing.Point(295, 472);
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
            this.label6.Location = new System.Drawing.Point(355, 472);
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
            this.label7.Location = new System.Drawing.Point(295, 502);
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
            this.label8.Location = new System.Drawing.Point(355, 502);
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
            this.label10.Location = new System.Drawing.Point(373, 87);
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
            this.label11.Location = new System.Drawing.Point(433, 87);
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
            this.label12.Location = new System.Drawing.Point(24, 625);
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
            this.label17.Location = new System.Drawing.Point(24, 656);
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
            this.label18.Location = new System.Drawing.Point(533, 87);
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
            this.label19.Location = new System.Drawing.Point(593, 87);
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
            this.label20.Font = new System.Drawing.Font("Times New Roman", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label20.Format = "{0:F2}单位";
            this.label20.heightName = null;
            this.label20.isVisible = true;
            this.label20.Location = new System.Drawing.Point(18, 407);
            this.label20.Name = "label20";
            this.label20.newFillColor = System.Drawing.Color.Red;
            this.label20.oldFillColor = System.Drawing.Color.DarkGray;
            this.label20.Size = new System.Drawing.Size(152, 19);
            this.label20.TabIndex = 9;
            this.label20.Text = "Solution Transfer Valve:";
            this.label20.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label20.textName = null;
            this.label20.visibleName = null;
            this.label20.widthName = null;
            this.label20.xName = null;
            this.label20.yName = null;
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
            this.label22.Location = new System.Drawing.Point(371, 365);
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
            this.label27.Location = new System.Drawing.Point(24, 23);
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
            this.label28.Location = new System.Drawing.Point(74, 23);
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
            this.AirTempIn.Location = new System.Drawing.Point(533, 102);
            this.AirTempIn.Name = "AirTempIn";
            this.AirTempIn.RelatedDeviceType = "";
            this.AirTempIn.RelatedPort = null;
            this.AirTempIn.Size = new System.Drawing.Size(60, 20);
            this.AirTempIn.TabIndex = 13;
            this.AirTempIn.Text = "AirTempIn";
            this.AirTempIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirHumIn
            // 
            this.AirHumIn.BoardNumber = null;
            this.AirHumIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirHumIn.DeviceName = "";
            this.AirHumIn.ID = "";
            this.AirHumIn.isVisible = true;
            this.AirHumIn.Location = new System.Drawing.Point(593, 102);
            this.AirHumIn.Name = "AirHumIn";
            this.AirHumIn.RelatedDeviceType = "";
            this.AirHumIn.RelatedPort = null;
            this.AirHumIn.Size = new System.Drawing.Size(60, 20);
            this.AirHumIn.TabIndex = 14;
            this.AirHumIn.Text = "AirHumIn";
            this.AirHumIn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirTempOut
            // 
            this.AirTempOut.BoardNumber = null;
            this.AirTempOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirTempOut.DeviceName = "";
            this.AirTempOut.ID = "";
            this.AirTempOut.isVisible = true;
            this.AirTempOut.Location = new System.Drawing.Point(373, 102);
            this.AirTempOut.Name = "AirTempOut";
            this.AirTempOut.RelatedDeviceType = "";
            this.AirTempOut.RelatedPort = null;
            this.AirTempOut.Size = new System.Drawing.Size(60, 20);
            this.AirTempOut.TabIndex = 15;
            this.AirTempOut.Text = "AirTempOut";
            this.AirTempOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // AirHumOut
            // 
            this.AirHumOut.BoardNumber = null;
            this.AirHumOut.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AirHumOut.DeviceName = "";
            this.AirHumOut.ID = "";
            this.AirHumOut.isVisible = true;
            this.AirHumOut.Location = new System.Drawing.Point(433, 102);
            this.AirHumOut.Name = "AirHumOut";
            this.AirHumOut.RelatedDeviceType = "";
            this.AirHumOut.RelatedPort = null;
            this.AirHumOut.Size = new System.Drawing.Size(60, 20);
            this.AirHumOut.TabIndex = 16;
            this.AirHumOut.Text = "AirHumOut";
            this.AirHumOut.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // SolTempIn
            // 
            this.SolTempIn.BoardNumber = null;
            this.SolTempIn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.SolTempIn.DeviceName = "";
            this.SolTempIn.ID = "";
            this.SolTempIn.isVisible = true;
            this.SolTempIn.Location = new System.Drawing.Point(295, 487);
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
            this.SolTempOut.Location = new System.Drawing.Point(355, 487);
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
            this.WaterTempIn.Location = new System.Drawing.Point(295, 517);
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
            this.WaterTempOut.Location = new System.Drawing.Point(355, 517);
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
            this.PanelControl.Location = new System.Drawing.Point(29, 43);
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
            this.Runstatus.Location = new System.Drawing.Point(79, 43);
            this.Runstatus.Name = "Runstatus";
            this.Runstatus.RelatedDeviceType = "";
            this.Runstatus.RelatedPort = null;
            this.Runstatus.Size = new System.Drawing.Size(20, 20);
            this.Runstatus.TabIndex = 4;
            this.Runstatus.Text = "Runstatus:";
            // 
            // SetVavSet
            // 
            this.SetVavSet.BoardNumber = null;
            this.SetVavSet.DeviceName = "";
            this.SetVavSet.ID = "";
            this.SetVavSet.Location = new System.Drawing.Point(401, 365);
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
            this.SolLevelRe.Location = new System.Drawing.Point(551, 533);
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
            this.DeviceRun.Location = new System.Drawing.Point(111, 622);
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
            this.Startblock.CheckStyleX = Library.Common.ButtonCheckFun.CheckStyle.style2;
            this.Startblock.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Startblock.DeviceName = "";
            this.Startblock.Location = new System.Drawing.Point(111, 652);
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
            this.Wkvalve.Location = new System.Drawing.Point(94, 433);
            this.Wkvalve.Name = "Wkvalve";
            this.Wkvalve.PortBind = "DO4_Handle";
            this.Wkvalve.PortData = null;
            this.Wkvalve.RelatedDeviceType = "";
            this.Wkvalve.RelatedPort = "DO4";
            this.Wkvalve.Size = new System.Drawing.Size(60, 20);
            this.Wkvalve.TabIndex = 5;
            // 
            // ButtonVav
            // 
            this.ButtonVav.AutoSize = true;
            this.ButtonVav.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.ButtonVav.isVisible = true;
            this.ButtonVav.Location = new System.Drawing.Point(369, 339);
            this.ButtonVav.Name = "ButtonVav";
            this.ButtonVav.Size = new System.Drawing.Size(46, 23);
            this.ButtonVav.TabIndex = 32;
            this.ButtonVav.Text = "HWV";
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
            this.lable7.isVisible = true;
            this.lable7.Location = new System.Drawing.Point(683, 556);
            this.lable7.Name = "lable7";
            this.lable7.newFillColor = System.Drawing.Color.Red;
            this.lable7.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable7.Size = new System.Drawing.Size(107, 20);
            this.lable7.TabIndex = 43;
            this.lable7.Text = "StopLevel:";
            this.lable7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable7.textName = null;
            this.lable7.Visible = false;
            this.lable7.visibleName = null;
            this.lable7.widthName = null;
            this.lable7.xName = null;
            this.lable7.yName = null;
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
            this.lable9.isVisible = true;
            this.lable9.Location = new System.Drawing.Point(684, 326);
            this.lable9.Name = "lable9";
            this.lable9.newFillColor = System.Drawing.Color.Red;
            this.lable9.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable9.Size = new System.Drawing.Size(107, 20);
            this.lable9.TabIndex = 42;
            this.lable9.Text = "HighLevel:";
            this.lable9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable9.textName = null;
            this.lable9.Visible = false;
            this.lable9.visibleName = null;
            this.lable9.widthName = null;
            this.lable9.xName = null;
            this.lable9.yName = null;
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
            this.lable6.isVisible = true;
            this.lable6.Location = new System.Drawing.Point(683, 577);
            this.lable6.Name = "lable6";
            this.lable6.newFillColor = System.Drawing.Color.Red;
            this.lable6.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable6.Size = new System.Drawing.Size(107, 20);
            this.lable6.TabIndex = 41;
            this.lable6.Text = "LowLevel Alarm:";
            this.lable6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable6.textName = null;
            this.lable6.Visible = false;
            this.lable6.visibleName = null;
            this.lable6.widthName = null;
            this.lable6.xName = null;
            this.lable6.yName = null;
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
            this.lable10.isVisible = true;
            this.lable10.Location = new System.Drawing.Point(683, 533);
            this.lable10.Name = "lable10";
            this.lable10.newFillColor = System.Drawing.Color.Red;
            this.lable10.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable10.Size = new System.Drawing.Size(107, 20);
            this.lable10.TabIndex = 40;
            this.lable10.Text = "StartLevel:";
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
            this.lable8.isVisible = true;
            this.lable8.Location = new System.Drawing.Point(684, 303);
            this.lable8.Name = "lable8";
            this.lable8.newFillColor = System.Drawing.Color.Red;
            this.lable8.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable8.Size = new System.Drawing.Size(107, 20);
            this.lable8.TabIndex = 45;
            this.lable8.Text = "HighLevel Alarm:";
            this.lable8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable8.textName = null;
            this.lable8.Visible = false;
            this.lable8.visibleName = null;
            this.lable8.widthName = null;
            this.lable8.xName = null;
            this.lable8.yName = null;
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
            this.lable4.isVisible = true;
            this.lable4.Location = new System.Drawing.Point(683, 510);
            this.lable4.Name = "lable4";
            this.lable4.newFillColor = System.Drawing.Color.Red;
            this.lable4.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable4.Size = new System.Drawing.Size(107, 20);
            this.lable4.TabIndex = 38;
            this.lable4.Text = "HighLevel Alarm:";
            this.lable4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable4.textName = null;
            this.lable4.Visible = false;
            this.lable4.visibleName = null;
            this.lable4.widthName = null;
            this.lable4.xName = null;
            this.lable4.yName = null;
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
            this.lable12.Location = new System.Drawing.Point(20, 301);
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
            // WkSLevelHigh
            // 
            this.WkSLevelHigh.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.WkSLevelHigh.BoardNumber = null;
            this.WkSLevelHigh.DeviceName = "";
            this.WkSLevelHigh.ID = "";
            this.WkSLevelHigh.Location = new System.Drawing.Point(792, 326);
            this.WkSLevelHigh.Name = "WkSLevelHigh";
            this.WkSLevelHigh.PortBind = null;
            this.WkSLevelHigh.PortData = null;
            this.WkSLevelHigh.RelatedDeviceType = "";
            this.WkSLevelHigh.RelatedPort = null;
            this.WkSLevelHigh.Size = new System.Drawing.Size(60, 20);
            this.WkSLevelHigh.TabIndex = 47;
            this.WkSLevelHigh.Visible = false;
            this.WkSLevelHigh.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // ReSLevelStop
            // 
            this.ReSLevelStop.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ReSLevelStop.BoardNumber = null;
            this.ReSLevelStop.DeviceName = "";
            this.ReSLevelStop.ID = "";
            this.ReSLevelStop.Location = new System.Drawing.Point(792, 556);
            this.ReSLevelStop.Name = "ReSLevelStop";
            this.ReSLevelStop.PortBind = null;
            this.ReSLevelStop.PortData = null;
            this.ReSLevelStop.RelatedDeviceType = "";
            this.ReSLevelStop.RelatedPort = null;
            this.ReSLevelStop.Size = new System.Drawing.Size(60, 20);
            this.ReSLevelStop.TabIndex = 48;
            this.ReSLevelStop.Visible = false;
            // 
            // WkSLevelHAlm
            // 
            this.WkSLevelHAlm.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.WkSLevelHAlm.BoardNumber = null;
            this.WkSLevelHAlm.DeviceName = "";
            this.WkSLevelHAlm.ID = "";
            this.WkSLevelHAlm.Location = new System.Drawing.Point(792, 303);
            this.WkSLevelHAlm.Name = "WkSLevelHAlm";
            this.WkSLevelHAlm.PortBind = null;
            this.WkSLevelHAlm.PortData = null;
            this.WkSLevelHAlm.RelatedDeviceType = "";
            this.WkSLevelHAlm.RelatedPort = null;
            this.WkSLevelHAlm.Size = new System.Drawing.Size(60, 20);
            this.WkSLevelHAlm.TabIndex = 49;
            this.WkSLevelHAlm.Visible = false;
            this.WkSLevelHAlm.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // ReSLevelLAlm
            // 
            this.ReSLevelLAlm.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ReSLevelLAlm.BoardNumber = null;
            this.ReSLevelLAlm.DeviceName = "";
            this.ReSLevelLAlm.ID = "";
            this.ReSLevelLAlm.Location = new System.Drawing.Point(792, 577);
            this.ReSLevelLAlm.Name = "ReSLevelLAlm";
            this.ReSLevelLAlm.PortBind = null;
            this.ReSLevelLAlm.PortData = null;
            this.ReSLevelLAlm.RelatedDeviceType = "";
            this.ReSLevelLAlm.RelatedPort = null;
            this.ReSLevelLAlm.Size = new System.Drawing.Size(60, 20);
            this.ReSLevelLAlm.TabIndex = 50;
            this.ReSLevelLAlm.Visible = false;
            this.ReSLevelLAlm.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // ReSLevelStart
            // 
            this.ReSLevelStart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ReSLevelStart.BoardNumber = null;
            this.ReSLevelStart.DeviceName = "";
            this.ReSLevelStart.ID = "";
            this.ReSLevelStart.Location = new System.Drawing.Point(792, 533);
            this.ReSLevelStart.Name = "ReSLevelStart";
            this.ReSLevelStart.PortBind = null;
            this.ReSLevelStart.PortData = null;
            this.ReSLevelStart.RelatedDeviceType = "";
            this.ReSLevelStart.RelatedPort = null;
            this.ReSLevelStart.Size = new System.Drawing.Size(60, 20);
            this.ReSLevelStart.TabIndex = 51;
            this.ReSLevelStart.Visible = false;
            this.ReSLevelStart.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // ReSLevelHAlm
            // 
            this.ReSLevelHAlm.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ReSLevelHAlm.BoardNumber = null;
            this.ReSLevelHAlm.DeviceName = "";
            this.ReSLevelHAlm.ID = "";
            this.ReSLevelHAlm.Location = new System.Drawing.Point(792, 510);
            this.ReSLevelHAlm.Name = "ReSLevelHAlm";
            this.ReSLevelHAlm.PortBind = null;
            this.ReSLevelHAlm.PortData = null;
            this.ReSLevelHAlm.RelatedDeviceType = "";
            this.ReSLevelHAlm.RelatedPort = null;
            this.ReSLevelHAlm.Size = new System.Drawing.Size(60, 20);
            this.ReSLevelHAlm.TabIndex = 53;
            this.ReSLevelHAlm.Visible = false;
            this.ReSLevelHAlm.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // DeltaCon
            // 
            this.DeltaCon.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DeltaCon.BoardNumber = null;
            this.DeltaCon.DeviceName = "";
            this.DeltaCon.ID = "";
            this.DeltaCon.Location = new System.Drawing.Point(96, 323);
            this.DeltaCon.Name = "DeltaCon";
            this.DeltaCon.PortBind = null;
            this.DeltaCon.PortData = null;
            this.DeltaCon.RelatedDeviceType = "";
            this.DeltaCon.RelatedPort = null;
            this.DeltaCon.Size = new System.Drawing.Size(60, 20);
            this.DeltaCon.TabIndex = 55;
            this.DeltaCon.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // WeakSolLevel
            // 
            this.WeakSolLevel.AutoSize = true;
            this.WeakSolLevel.Font = new System.Drawing.Font("Times New Roman", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WeakSolLevel.isVisible = true;
            this.WeakSolLevel.Location = new System.Drawing.Point(681, 270);
            this.WeakSolLevel.Name = "WeakSolLevel";
            this.WeakSolLevel.Size = new System.Drawing.Size(168, 27);
            this.WeakSolLevel.TabIndex = 56;
            this.WeakSolLevel.Text = "Weak Solution Level";
            this.WeakSolLevel.Click += new System.EventHandler(this.ButtonWeakSolLevelClick);
            // 
            // ReSolLevel
            // 
            this.ReSolLevel.AutoSize = true;
            this.ReSolLevel.Font = new System.Drawing.Font("Times New Roman", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReSolLevel.isVisible = false;
            this.ReSolLevel.Location = new System.Drawing.Point(683, 474);
            this.ReSolLevel.Name = "ReSolLevel";
            this.ReSolLevel.Size = new System.Drawing.Size(168, 27);
            this.ReSolLevel.TabIndex = 57;
            this.ReSolLevel.Text = "Re Solution Level";
            this.ReSolLevel.Click += new System.EventHandler(this.ButtonReSolLevelClick);
            // 
            // FanOnOff
            // 
            this.FanOnOff.BackColor = System.Drawing.Color.Transparent;
            this.FanOnOff.BoardNumber = null;
            this.FanOnOff.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.FanOnOff.Cursor = System.Windows.Forms.Cursors.Hand;
            this.FanOnOff.DeviceName = "";
            this.FanOnOff.Location = new System.Drawing.Point(533, 174);
            this.FanOnOff.Name = "FanOnOff";
            this.FanOnOff.PortBind = "DO4_Handle";
            this.FanOnOff.PortData = null;
            this.FanOnOff.RelatedDeviceType = "";
            this.FanOnOff.RelatedPort = "DO4";
            this.FanOnOff.Size = new System.Drawing.Size(60, 20);
            this.FanOnOff.TabIndex = 5;
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
            this.lable1.Font = new System.Drawing.Font("Times New Roman", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lable1.Format = "{0:F2}单位";
            this.lable1.heightName = null;
            this.lable1.isVisible = true;
            this.lable1.Location = new System.Drawing.Point(111, 104);
            this.lable1.Name = "lable1";
            this.lable1.newFillColor = System.Drawing.Color.Red;
            this.lable1.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable1.Size = new System.Drawing.Size(95, 18);
            this.lable1.TabIndex = 9;
            this.lable1.Text = "WeakSolLevel:";
            this.lable1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable1.textName = null;
            this.lable1.visibleName = null;
            this.lable1.widthName = null;
            this.lable1.xName = null;
            this.lable1.yName = null;
            // 
            // PumpOnOff
            // 
            this.PumpOnOff.BackColor = System.Drawing.Color.Transparent;
            this.PumpOnOff.BoardNumber = null;
            this.PumpOnOff.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.PumpOnOff.Cursor = System.Windows.Forms.Cursors.Hand;
            this.PumpOnOff.DeviceName = "";
            this.PumpOnOff.Location = new System.Drawing.Point(584, 419);
            this.PumpOnOff.Name = "PumpOnOff";
            this.PumpOnOff.PortBind = "DO4_Handle";
            this.PumpOnOff.PortData = null;
            this.PumpOnOff.RelatedDeviceType = "";
            this.PumpOnOff.RelatedPort = "DO4";
            this.PumpOnOff.Size = new System.Drawing.Size(60, 20);
            this.PumpOnOff.TabIndex = 5;
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
            this.lable2.Location = new System.Drawing.Point(467, 176);
            this.lable2.Name = "lable2";
            this.lable2.newFillColor = System.Drawing.Color.Red;
            this.lable2.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable2.Size = new System.Drawing.Size(60, 19);
            this.lable2.TabIndex = 9;
            this.lable2.Text = "Fan:";
            this.lable2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable2.textName = null;
            this.lable2.visibleName = null;
            this.lable2.widthName = null;
            this.lable2.xName = null;
            this.lable2.yName = null;
            // 
            // SSLevelAlm
            // 
            this.SSLevelAlm.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SSLevelAlm.BoardNumber = null;
            this.SSLevelAlm.DeviceName = "";
            this.SSLevelAlm.ID = "";
            this.SSLevelAlm.Location = new System.Drawing.Point(790, 201);
            this.SSLevelAlm.Name = "SSLevelAlm";
            this.SSLevelAlm.PortBind = null;
            this.SSLevelAlm.PortData = null;
            this.SSLevelAlm.RelatedDeviceType = "";
            this.SSLevelAlm.RelatedPort = null;
            this.SSLevelAlm.Size = new System.Drawing.Size(60, 20);
            this.SSLevelAlm.TabIndex = 49;
            this.SSLevelAlm.Visible = false;
            this.SSLevelAlm.Click += new System.EventHandler(this.sendButtonClick);
            // 
            // SSLevelHigh
            // 
            this.SSLevelHigh.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SSLevelHigh.BoardNumber = null;
            this.SSLevelHigh.DeviceName = "";
            this.SSLevelHigh.ID = "";
            this.SSLevelHigh.Location = new System.Drawing.Point(790, 224);
            this.SSLevelHigh.Name = "SSLevelHigh";
            this.SSLevelHigh.PortBind = null;
            this.SSLevelHigh.PortData = null;
            this.SSLevelHigh.RelatedDeviceType = "";
            this.SSLevelHigh.RelatedPort = null;
            this.SSLevelHigh.Size = new System.Drawing.Size(60, 20);
            this.SSLevelHigh.TabIndex = 47;
            this.SSLevelHigh.Visible = false;
            this.SSLevelHigh.Click += new System.EventHandler(this.sendButtonClick);
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
            this.lable3.Location = new System.Drawing.Point(682, 201);
            this.lable3.Name = "lable3";
            this.lable3.newFillColor = System.Drawing.Color.Red;
            this.lable3.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable3.Size = new System.Drawing.Size(107, 20);
            this.lable3.TabIndex = 45;
            this.lable3.Text = "HighLevel Alarm:";
            this.lable3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable3.textName = null;
            this.lable3.Visible = false;
            this.lable3.visibleName = null;
            this.lable3.widthName = null;
            this.lable3.xName = null;
            this.lable3.yName = null;
            // 
            // lable5
            // 
            this.lable5.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable5.BackColor = System.Drawing.Color.White;
            this.lable5.bHaveAction = false;
            this.lable5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable5.ClickEvent = null;
            this.lable5.DoubleEvent = null;
            this.lable5.FillColorName = null;
            this.lable5.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable5.Format = "{0:F2}单位";
            this.lable5.heightName = null;
            this.lable5.isVisible = true;
            this.lable5.Location = new System.Drawing.Point(682, 224);
            this.lable5.Name = "lable5";
            this.lable5.newFillColor = System.Drawing.Color.Red;
            this.lable5.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable5.Size = new System.Drawing.Size(107, 20);
            this.lable5.TabIndex = 42;
            this.lable5.Text = "HighLevel:";
            this.lable5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable5.textName = null;
            this.lable5.Visible = false;
            this.lable5.visibleName = null;
            this.lable5.widthName = null;
            this.lable5.xName = null;
            this.lable5.yName = null;
            // 
            // StrongSolLevel
            // 
            this.StrongSolLevel.AutoSize = true;
            this.StrongSolLevel.Font = new System.Drawing.Font("Times New Roman", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StrongSolLevel.isVisible = true;
            this.StrongSolLevel.Location = new System.Drawing.Point(679, 168);
            this.StrongSolLevel.Name = "StrongSolLevel";
            this.StrongSolLevel.Size = new System.Drawing.Size(168, 27);
            this.StrongSolLevel.TabIndex = 56;
            this.StrongSolLevel.Text = "Strong Solution Level";
            this.StrongSolLevel.Click += new System.EventHandler(this.ButtonStrSolClick);
            // 
            // SolLevelWT
            // 
            this.SolLevelWT.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SolLevelWT.BoardNumber = null;
            this.SolLevelWT.DeviceName = "";
            this.SolLevelWT.ID = "";
            this.SolLevelWT.LevelRange = "";
            this.SolLevelWT.Location = new System.Drawing.Point(186, 131);
            this.SolLevelWT.Name = "SolLevelWT";
            this.SolLevelWT.RelatedDeviceType = "";
            this.SolLevelWT.RelatedPort = null;
            this.SolLevelWT.Size = new System.Drawing.Size(14, 308);
            this.SolLevelWT.TabIndex = 24;
            this.SolLevelWT.Text = "Re_SolLevelRe";
            // 
            // lable11
            // 
            this.lable11.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lable11.BackColor = System.Drawing.Color.White;
            this.lable11.bHaveAction = false;
            this.lable11.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lable11.ClickEvent = null;
            this.lable11.DoubleEvent = null;
            this.lable11.FillColorName = null;
            this.lable11.Font = new System.Drawing.Font("Times New Roman", 8F, System.Drawing.FontStyle.Bold);
            this.lable11.Format = "{0:F2}单位";
            this.lable11.heightName = null;
            this.lable11.isVisible = true;
            this.lable11.Location = new System.Drawing.Point(518, 419);
            this.lable11.Name = "lable11";
            this.lable11.newFillColor = System.Drawing.Color.Red;
            this.lable11.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable11.Size = new System.Drawing.Size(60, 19);
            this.lable11.TabIndex = 9;
            this.lable11.Text = "Pump:";
            this.lable11.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lable11.textName = null;
            this.lable11.visibleName = null;
            this.lable11.widthName = null;
            this.lable11.xName = null;
            this.lable11.yName = null;
            // 
            // AutoControl
            // 
            this.AutoControl.BackColor = System.Drawing.Color.Transparent;
            this.AutoControl.BoardNumber = null;
            this.AutoControl.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.AutoControl.Cursor = System.Windows.Forms.Cursors.Hand;
            this.AutoControl.DeviceName = "";
            this.AutoControl.Location = new System.Drawing.Point(111, 593);
            this.AutoControl.Name = "AutoControl";
            this.AutoControl.PortBind = "Reg3_Handle";
            this.AutoControl.PortData = null;
            this.AutoControl.RelatedDeviceType = "";
            this.AutoControl.RelatedPort = "Reg3";
            this.AutoControl.Size = new System.Drawing.Size(57, 23);
            this.AutoControl.TabIndex = 58;
            this.AutoControl.Click += new System.EventHandler(this.AutoControl_Click);
            
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
            this.lable13.Location = new System.Drawing.Point(23, 595);
            this.lable13.Name = "lable13";
            this.lable13.newFillColor = System.Drawing.Color.Red;
            this.lable13.oldFillColor = System.Drawing.Color.DarkGray;
            this.lable13.Size = new System.Drawing.Size(77, 13);
            this.lable13.TabIndex = 59;
            this.lable13.Text = "AutoControl:";
            this.lable13.textName = null;
            this.lable13.visibleName = null;
            this.lable13.widthName = null;
            this.lable13.xName = null;
            this.lable13.yName = null;
            // 
            // Regenerator3
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.BackgroundImage = global::Library.Properties.Resources.reg940730;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Controls.Add(this.lable13);
            this.Controls.Add(this.AutoControl);
            this.Controls.Add(this.ReSolLevel);
            this.Controls.Add(this.StrongSolLevel);
            this.Controls.Add(this.WeakSolLevel);
            this.Controls.Add(this.lable5);
            this.Controls.Add(this.lable7);
            this.Controls.Add(this.lable9);
            this.Controls.Add(this.lable6);
            this.Controls.Add(this.lable3);
            this.Controls.Add(this.lable10);
            this.Controls.Add(this.lable8);
            this.Controls.Add(this.lable4);
            this.Controls.Add(this.SSLevelHigh);
            this.Controls.Add(this.lable12);
            this.Controls.Add(this.WkSLevelHigh);
            this.Controls.Add(this.SSLevelAlm);
            this.Controls.Add(this.ReSLevelStop);
            this.Controls.Add(this.WkSLevelHAlm);
            this.Controls.Add(this.ReSLevelLAlm);
            this.Controls.Add(this.ReSLevelStart);
            this.Controls.Add(this.ReSLevelHAlm);
            this.Controls.Add(this.DeltaCon);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.lable11);
            this.Controls.Add(this.lable2);
            this.Controls.Add(this.lable1);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label27);
            this.Controls.Add(this.label28);
            this.Controls.Add(this.AirTempIn);
            this.Controls.Add(this.AirHumIn);
            this.Controls.Add(this.AirTempOut);
            this.Controls.Add(this.AirHumOut);
            this.Controls.Add(this.SolTempIn);
            this.Controls.Add(this.SolTempOut);
            this.Controls.Add(this.WaterTempIn);
            this.Controls.Add(this.WaterTempOut);
            this.Controls.Add(this.Runstatus);
            this.Controls.Add(this.PanelControl);
            this.Controls.Add(this.SolLevelWT);
            this.Controls.Add(this.SolLevelRe);
            this.Controls.Add(this.SetVavSet);
            this.Controls.Add(this.ButtonVav);
            this.Controls.Add(this.PumpOnOff);
            this.Controls.Add(this.DeviceRun);
            this.Controls.Add(this.FanOnOff);
            this.Controls.Add(this.Startblock);
            this.Controls.Add(this.Wkvalve);
            this.DoubleBuffered = true;
            this.Name = "Regenerator3";
            this.Size = new System.Drawing.Size(900, 724);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private Library.Lable label5;
        private Library.Lable label6;
        private Library.Lable label7;
        private Library.Lable label8;
        //private Library.Lable label9;
        private Library.Lable label10;
        private Library.Lable label11;
        private Library.Lable label12;
        //  private Library.Lable label16;
        private Library.Lable label17;
        private Library.Lable label18;
        private Library.Lable label19;
        private Library.Lable label20;
        private Library.Lable label22;
        private Library.Lable label27;
        private Library.Lable label28;

        public Library.TextBox AirTempIn;
        public Library.TextBox AirHumIn;
        public Library.TextBox AirTempOut;
        public Library.TextBox AirHumOut;
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

        private Library.Common.levelmeter SolLevelRe;
        private Library.Button ButtonVav;

        private Library.Common.ButtonCheck DeviceRun;
        private Library.Common.ButtonCheckFun Startblock;
        private Library.Common.ButtonCheck Wkvalve;
        private Lable lable7;
        private Lable lable9;
        private Lable lable6;
        private Lable lable10;
        private Lable lable8;
        private Lable lable4;
        private Lable lable12;
        private SendButton WkSLevelHigh;
        private SendButton ReSLevelStop;
        private SendButton WkSLevelHAlm;
        private SendButton ReSLevelLAlm;
        private SendButton ReSLevelStart;
        private SendButton ReSLevelHAlm;
        private SendButton DeltaCon;
        private Button WeakSolLevel;
        private Button ReSolLevel;
        private Common.ButtonCheck FanOnOff;
        private Lable lable1;
        private Common.ButtonCheck PumpOnOff;
        private Lable lable2;
        private SendButton SSLevelAlm;
        private SendButton SSLevelHigh;
        private Lable lable3;
        private Lable lable5;
        private Button StrongSolLevel;
        private Common.levelmeter SolLevelWT;
        private Lable lable11;
        private Common.ButtonCheck AutoControl;
        private Lable lable13;
    }
}
