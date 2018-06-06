namespace Library.LDDS
{
    partial class Regenerator2
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
            this.SuspendLayout();
            // 
            this.label1 = new Library.Lable();
            this.label5 = new Library.Lable();
            this.label6 = new Library.Lable();
            this.label7 = new Library.Lable();
            this.label8 = new Library.Lable();
            this.label9 = new Library.Lable();
            this.label10 = new Library.Lable();
            this.label11 = new Library.Lable();
            this.label12 = new Library.Lable();
            this.label14 = new Library.Lable();
            this.label15 = new Library.Lable();
            this.label16 = new Library.Lable();
            this.label17 = new Library.Lable();
            this.label18 = new Library.Lable();
            this.label19 = new Library.Lable();
            this.label20 = new Library.Lable();
            this.label21 = new Library.Lable();
            this.label22 = new Library.Lable();
            this.label23 = new Library.Lable();

            this.Re_AirTempIn = new Library.TextBox();
            this.Re_AirHumIn = new Library.TextBox();
            this.Re_AirTempOut = new Library.TextBox();
            this.Re_AirHumOut = new Library.TextBox();
            this.Re_SolFlow = new Library.TextBox();

            this.Re_VavFb = new Library.TextBox();
            this.Re_SolLevelRe = new Library.TextBox();
            this.Re_SolLevelST = new Library.TextBox();
            this.Re_SolTempIn = new Library.TextBox();
            this.Re_SolTempOut = new Library.TextBox();
            this.Re_WaterTempIn = new Library.TextBox();
            this.Re_WaterTempOut = new Library.TextBox();

            this.sendButtonPump = new Library.Common.ButtonCheck();
            this.sendButtonFan = new Library.Common.ButtonCheck();
            this.sendButtonOnoffvav = new Library.Common.ButtonCheck();
            this.sendButtonRevav = new Library.SendButton();
            this.LDDSonoff = new Library.Common.ButtonCheck();
            this.Startblock = new Library.Common.ButtonCheck();

            this.Controls.Add(this.label1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7); ;
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label23);

            this.Controls.Add(this.Re_AirTempIn);
            this.Controls.Add(this.Re_AirHumIn);
            this.Controls.Add(this.Re_AirTempOut);
            this.Controls.Add(this.Re_AirHumOut);
            this.Controls.Add(this.Re_SolFlow);
            this.Controls.Add(this.Re_VavFb);
            this.Controls.Add(this.Re_SolLevelRe);
            this.Controls.Add(this.Re_SolLevelST);
            this.Controls.Add(this.Re_SolTempIn);
            this.Controls.Add(this.Re_SolTempOut);
            this.Controls.Add(this.Re_WaterTempIn);
            this.Controls.Add(this.Re_WaterTempOut);

            this.Controls.Add(this.sendButtonOnoffvav);
            this.Controls.Add(this.sendButtonRevav);
            this.Controls.Add(this.sendButtonPump);
            this.Controls.Add(this.sendButtonFan);
            this.Controls.Add(this.LDDSonoff);
            this.Controls.Add(this.Startblock);

            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.BackgroundImage = global::Library.Properties.Resources.reg940730;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.DoubleBuffered = true;
            this.Name = "Regenerator2";
            this.Size = new System.Drawing.Size(600, 600);
            this.ResumeLayout(false);
            if (this.BoardNumber == null)
                this.BoardNumber = "00000000";

            ///////////////////////////////////////////////////////////////////////////////////////////////////

            this.LDDSonoff.Location = new System.Drawing.Point(75, 25);
            this.LDDSonoff.Name = "LDDSonoff";
            this.LDDSonoff.Size = new System.Drawing.Size(57, 23);
            this.LDDSonoff.TabIndex = 5;
            this.LDDSonoff.Text = "LDDSonoff";
            this.LDDSonoff.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.LDDSonoff.Click += new System.EventHandler(this.LDDSonoff_Click);
            this.LDDSonoff.PortBind = "Reg3_Handle";
            this.LDDSonoff.RelatedPort = "Reg3";

            this.Startblock.Location = new System.Drawing.Point(75, 55);
            this.Startblock.Name = "Startblock";
            this.Startblock.Size = new System.Drawing.Size(57, 23);
            this.Startblock.TabIndex = 5;
            this.Startblock.Text = "Startblock";
            this.Startblock.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style2;
            this.Startblock.Click += new System.EventHandler(this.Startblock_Click);

            ///////////////////////////////////////////////////////////////////////////////////////////////////           

            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 120);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "SolTempIn:";
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 140);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "SolTempOut:";
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 160);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 12);
            this.label7.TabIndex = 9;
            this.label7.Text = "WTempIn:";
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(10, 180);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 12);
            this.label8.TabIndex = 4;
            this.label8.Text = "WTempOut:";

            //  Text10
            this.Re_SolTempIn.AutoSize = true;
            this.Re_SolTempIn.Location = new System.Drawing.Point(80, 120);
            this.Re_SolTempIn.Name = "Re_SolTempIn";
            this.Re_SolTempIn.Size = new System.Drawing.Size(35, 12);
            this.Re_SolTempIn.Text = "Re_SolTempIn";

            //  Text11
            this.Re_SolTempOut.AutoSize = true;
            this.Re_SolTempOut.Location = new System.Drawing.Point(80, 140);
            this.Re_SolTempOut.Name = "Re_SolTempOut";
            this.Re_SolTempOut.Size = new System.Drawing.Size(35, 12);
            this.Re_SolTempOut.Text = "Re_SolTempOut";
            // 
            //  Text11
            this.Re_WaterTempIn.AutoSize = true;
            this.Re_WaterTempIn.Location = new System.Drawing.Point(80, 160);
            this.Re_WaterTempIn.Name = "Re_WaterTempIn";
            this.Re_WaterTempIn.Size = new System.Drawing.Size(35, 12);
            this.Re_WaterTempIn.Text = "Re_WaterTempIn";
            //
            //  Text12
            this.Re_WaterTempOut.AutoSize = true;
            this.Re_WaterTempOut.Location = new System.Drawing.Point(80, 180);
            this.Re_WaterTempOut.Name = "Re_WaterTempOut";
            this.Re_WaterTempOut.Size = new System.Drawing.Size(35, 12);
            this.Re_WaterTempOut.Name = "Re_WaterTempOut";
            //
            ////////////////////////////////////////////////////////////////
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(428, 10);
            this.label9.Name = "ReAir_outlet";
            this.label9.Size = new System.Drawing.Size(35, 12);
            this.label9.TabIndex = 4;
            this.label9.Text = "ReAir_outlet:";
            // label10
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(428, 30);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 12);
            this.label10.TabIndex = 9;
            this.label10.Text = "Temp:";
            //  Text3
            this.Re_AirTempOut.AutoSize = true;
            this.Re_AirTempOut.Location = new System.Drawing.Point(498, 30);
            this.Re_AirTempOut.Name = "Re_AirTempOut";
            this.Re_AirTempOut.Size = new System.Drawing.Size(35, 12);
            this.Re_AirTempOut.Text = "Re_AirTempOut";
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(428, 50);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(77, 12);
            this.label11.TabIndex = 9;
            this.label11.Text = "Humidity:";
            // 
            //  Text4
            this.Re_AirHumOut.AutoSize = true;
            this.Re_AirHumOut.Location = new System.Drawing.Point(498, 50);
            this.Re_AirHumOut.Name = "Re_AirHumOut";
            this.Re_AirHumOut.Size = new System.Drawing.Size(35, 12);
            this.Re_AirHumOut.Text = "Re_AirHumOut";

            /////////////////////////////////////////////////////////////////////////////
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(420, 200);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(35, 12);
            this.label20.TabIndex = 9;
            this.label20.Text = "WkOnoffVav:";

            this.sendButtonOnoffvav.AutoSize = true;
            this.sendButtonOnoffvav.Location = new System.Drawing.Point(490, 200);
            this.sendButtonOnoffvav.Name = "sendButtonOnoffvav";
            this.sendButtonOnoffvav.Size = new System.Drawing.Size(57, 23);
            this.sendButtonOnoffvav.Text = "sendButtonOnoffvav";

            this.sendButtonOnoffvav.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style4;
            this.sendButtonOnoffvav.Click += new System.EventHandler(this.LDDSonoff_Click);
            this.sendButtonOnoffvav.PortBind = "AO7_Handle";
            this.sendButtonOnoffvav.RelatedPort = "AO7";

           
                      
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(420, 280);
            this.label21.Name = "labe21";
            this.label21.Size = new System.Drawing.Size(35, 12);
            this.label21.TabIndex = 9;
            this.label21.Text = "RewtvavFb:";
            //  Text7
            this.Re_VavFb.AutoSize = true;
            this.Re_VavFb.Location = new System.Drawing.Point(490, 280);
            this.Re_VavFb.Name = "Re_VavFb";
            this.Re_VavFb.Size = new System.Drawing.Size(35, 12);
            this.Re_VavFb.Text = "Re_VavFb";

            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(420, 300);
            this.label22.Name = "labe22";
            this.label22.Size = new System.Drawing.Size(35, 12);
            this.label22.TabIndex = 9;
            this.label22.Text = "Set:";

            this.sendButtonRevav.AutoSize = true;
            this.sendButtonRevav.Location = new System.Drawing.Point(490, 300);
            this.sendButtonRevav.Name = "sendButtonRevav";
            this.sendButtonRevav.Size = new System.Drawing.Size(80, 30);
            this.sendButtonRevav.Text = "sendButtonRevav";
            // this.sendButtonPump.Click += new System.EventHandler(this.senddataset);
            string currentNameRevav = "Re_Revav:";
            string currentTypeRevav = "3";
            senddataset(currentNameRevav, currentTypeRevav, sendButtonRevav, this.BoardNumber);

            //////////////////////////////////////////////////////////////////////////////////////////////
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(10, 540);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(35, 12);
            this.label12.TabIndex = 4;
            this.label12.Text = "Re_Pump";
            // 
            //  sendbutton1
            this.sendButtonPump.AutoSize = true;
            this.sendButtonPump.Location = new System.Drawing.Point(80, 540);
            this.sendButtonPump.Name = "sendButtonPump";
            this.sendButtonPump.Size = new System.Drawing.Size(57, 23);
            this.sendButtonPump.Text = "sendButtonPump";
            // this.sendButtonPump.Click += new System.EventHandler(this.senddataset);

            this.sendButtonPump.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style4;
            this.sendButtonPump.Click += new System.EventHandler(this.LDDSonoff_Click);
            this.sendButtonPump.PortBind = "AO6_Handle";
            this.sendButtonPump.RelatedPort = "AO6";




            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(194, 520);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(35, 12);
            this.label15.TabIndex = 9;
            this.label15.Text = "Re_Flow_Rate:";
            // 
            //  Text5
            this.Re_SolFlow.AutoSize = true;
            this.Re_SolFlow.Location = new System.Drawing.Point(284, 520);
            this.Re_SolFlow.Name = "Re_SolFlow";
            this.Re_SolFlow.Size = new System.Drawing.Size(35, 12);
            this.Re_SolFlow.Name = "Re_SolFlow";

            // label6
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(194, 540);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(35, 12);
            this.label16.TabIndex = 4;
            this.label16.Text = "Re_Level:";

            //  Text8
            this.Re_SolLevelRe.AutoSize = true;
            this.Re_SolLevelRe.Location = new System.Drawing.Point(284, 540);
            this.Re_SolLevelRe.Name = "Re_SolLevelRe";
            this.Re_SolLevelRe.Size = new System.Drawing.Size(35, 12);
            this.Re_SolLevelRe.Text = "Re_SolLevelRe";
            // 

            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(194, 540);
            this.label23.Name = "label22";
            this.label23.Size = new System.Drawing.Size(35, 12);
            this.label23.TabIndex = 4;
            this.label23.Text = "WkSolLevel:";

            //  Text9
            this.Re_SolLevelST.AutoSize = true;
            this.Re_SolLevelST.Location = new System.Drawing.Point(284, 560);
            this.Re_SolLevelST.Name = "Re_SolLevelST";
            this.Re_SolLevelST.Size = new System.Drawing.Size(35, 12);
            this.Re_SolLevelST.Text = "Re_SolLevelST";
            //////////////////////////////////////////////////////
            // label7
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(420, 360);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(35, 12);
            this.label17.TabIndex = 9;
            this.label17.Text = "ReAir_inlet:";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(420, 380);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(35, 12);
            this.label18.TabIndex = 4;
            this.label18.Text = "Temp:";

            //  Text1
            this.Re_AirTempIn.AutoSize = true;
            this.Re_AirTempIn.Location = new System.Drawing.Point(490, 380);
            this.Re_AirTempIn.Name = "Re_AirTempIn";
            this.Re_AirTempIn.Size = new System.Drawing.Size(35, 12);
            this.Re_AirTempIn.Text = "Re_AirTempIn";

            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(420, 400);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(35, 12);
            this.label19.TabIndex = 4;
            this.label19.Text = "Humidity:";

            //  Text2
            this.Re_AirHumIn.AutoSize = true;
            this.Re_AirHumIn.Location = new System.Drawing.Point(490, 400);
            this.Re_AirHumIn.Name = "Re_AirHumIn";
            this.Re_AirHumIn.Size = new System.Drawing.Size(35, 12);
            this.Re_AirHumIn.Text = "Re_AirHumIn";

            ////////////////////////////////////////////////////////////////////
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(410, 540);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "ReFan:";
            // 

            this.sendButtonFan.AutoSize = true;
            this.sendButtonFan.Location = new System.Drawing.Point(480, 540);
            this.sendButtonFan.Name = "sendButtonFan";
            this.sendButtonFan.Size = new System.Drawing.Size(57, 23);
            this.sendButtonFan.Text = "sendButtonFan";

            this.sendButtonFan.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style4;
            this.sendButtonFan.Click += new System.EventHandler(this.LDDSonoff_Click);
            this.sendButtonFan.PortBind = "AO5_Handle";
            this.sendButtonFan.RelatedPort = "AO5";

            //////////////////////////////////////////////////////////////////////////////////////////





        }

        #endregion
        private Library.Lable label1;
      //  private Library.Lable label3;
     //   private Library.Lable label4;
        private Library.Lable label5;
        private Library.Lable label6;
        private Library.Lable label7;
        private Library.Lable label8;
        private Library.Lable label9;
        private Library.Lable label10;
        private Library.Lable label11;
        private Library.Lable label12;
        private Library.Lable label14;
        private Library.Lable label15;
        private Library.Lable label16;
        private Library.Lable label17;
        private Library.Lable label18;
        private Library.Lable label19;
        private Library.Lable label20;
        private Library.Lable label21;
        private Library.Lable label22;
        private Library.Lable label23;

        public Library.TextBox Re_AirTempIn;
        public Library.TextBox Re_AirHumIn;
        public Library.TextBox Re_AirTempOut;
        public Library.TextBox Re_AirHumOut;
        public Library.TextBox Re_SolFlow;
        public Library.TextBox Re_VavFb;
        public Library.TextBox Re_SolLevelRe;
        public Library.TextBox Re_SolLevelST;
        public Library.TextBox Re_SolTempIn;
        public Library.TextBox Re_SolTempOut;
        public Library.TextBox Re_WaterTempIn;
        public Library.TextBox Re_WaterTempOut;


  
        
        private Library.SendButton sendButtonRevav;

        private Library.Common.ButtonCheck sendButtonOnoffvav;
        private Library.Common.ButtonCheck sendButtonPump;
        private Library.Common.ButtonCheck sendButtonFan;

        private Library.Common.ButtonCheck LDDSonoff;
        private Library.Common.ButtonCheck Startblock;
    }
}
