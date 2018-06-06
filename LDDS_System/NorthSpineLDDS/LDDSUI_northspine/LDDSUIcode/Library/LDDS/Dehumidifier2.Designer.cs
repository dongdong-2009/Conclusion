using System;
using System.Collections;
using System.Collections.Generic;



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
            this.SuspendLayout();

            this.label1 = new Library.Lable();
            this.label2 = new Library.Lable();
            this.label3 = new Library.Lable();
            this.label4 = new Library.Lable();
            this.label5 = new Library.Lable();
            this.label6 = new Library.Lable();
            this.label7 = new Library.Lable();
            this.label8 = new Library.Lable();
            this.label9 = new Library.Lable();
            this.label10 = new Library.Lable();
            this.label11 = new Library.Lable();
            this.label12 = new Library.Lable();
            this.label13 = new Library.Lable();
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

            this.De_AirTempIn = new Library.TextBox();
            this.De_AirHumIn = new Library.TextBox();
            this.De_AirTempOut = new Library.TextBox();
            this.De_AirHumOut = new Library.TextBox();
            this.De_SolFlow = new Library.TextBox();
            this.De_PumpFb = new Library.TextBox();
            this.De_FanFb = new Library.TextBox();
            this.De_VavFb = new Library.TextBox();
            this.De_SolLevelDe = new Library.TextBox();
            this.De_SolLevelST = new Library.TextBox();
            this.De_SolTempIn = new Library.TextBox();
            this.De_SolTempOut = new Library.TextBox();
            this.De_WaterTempIn = new Library.TextBox();
            this.De_WaterTempOut = new Library.TextBox();

            this.sendButtonPump = new Library.SendButton();
            this.sendButtonFan = new Library.SendButton();
            this.sendButtonOnoffvav = new Library.SendButton();
            this.sendButtonRevav = new Library.SendButton();

            this.LDDSonoff = new Library.Common.ButtonCheck();
            this.Startblock = new Library.Common.ButtonCheck();

            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7); ;
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label13);
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

            this.Controls.Add(this.De_AirTempIn);
            this.Controls.Add(this.De_AirHumIn);
            this.Controls.Add(this.De_AirTempOut);
            this.Controls.Add(this.De_AirHumOut);
            this.Controls.Add(this.De_SolFlow);
            this.Controls.Add(this.De_PumpFb);
            this.Controls.Add(this.De_FanFb);
            this.Controls.Add(this.De_VavFb);
            this.Controls.Add(this.De_SolLevelDe);
            this.Controls.Add(this.De_SolLevelST);
            this.Controls.Add(this.De_SolTempIn);
            this.Controls.Add(this.De_SolTempOut);
            this.Controls.Add(this.De_WaterTempIn);
            this.Controls.Add(this.De_WaterTempOut);

            this.Controls.Add(this.sendButtonOnoffvav);
            this.Controls.Add(this.sendButtonRevav);
            this.Controls.Add(this.sendButtonPump);
            this.Controls.Add(this.sendButtonFan);
            this.Controls.Add(this.LDDSonoff);
            this.Controls.Add(this.Startblock);


            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.BackgroundImage = global::Library.Properties.Resources.Dehumidifier2;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.DoubleBuffered = true;
            this.Name = "Dehumidifier2";
            this.Size = new System.Drawing.Size(600, 600);
            this.ResumeLayout(false);
            if (this.BoardNumber == null)
                this.BoardNumber = "00000000";

            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(410, 500);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "DeFan:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(410, 520);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Feedback:";
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(410, 540);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "Set:";

            // 
            //  Text6
            this.De_FanFb.AutoSize = true;
            this.De_FanFb.Location = new System.Drawing.Point(480, 520);
            this.De_FanFb.Name = "De_FanFb";
            this.De_FanFb.Size = new System.Drawing.Size(35, 12);
            this.De_FanFb.Text = "De_FanFb";
            // 


            this.sendButtonFan.AutoSize = true;
            this.sendButtonFan.Location = new System.Drawing.Point(480, 540);
            this.sendButtonFan.Name = "sendButtonFan";
            this.sendButtonFan.Size = new System.Drawing.Size(80, 30);
            this.sendButtonFan.Text = "sendButtonFan";
            //  this.sendButtonFan.Click += new System.EventHandler(this.senddataset);
            string currentNameF = "De_FanSet";
            string currentTypeF = "3";
            senddataset(currentNameF, currentTypeF, sendButtonFan, this.BoardNumber);

            ///////////////////////////////////////////////////////////////////////////////////       
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 150);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "SolTempIn:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 170);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "SolTempOut:";
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 190);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(77, 12);
            this.label7.TabIndex = 9;
            this.label7.Text = "WTempIn:";
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(10, 210);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(35, 12);
            this.label8.TabIndex = 4;
            this.label8.Text = "WTempOut:";

            //  Text10
            this.De_SolTempIn.AutoSize = true;
            this.De_SolTempIn.Location = new System.Drawing.Point(80, 150);
            this.De_SolTempIn.Name = "De_SolTempIn";
            this.De_SolTempIn.Size = new System.Drawing.Size(35, 12);
            this.De_SolTempIn.Text = "De_SolTempIn";

            //  Text11
            this.De_SolTempOut.AutoSize = true;
            this.De_SolTempOut.Location = new System.Drawing.Point(80, 170);
            this.De_SolTempOut.Name = "De_SolTempOut";
            this.De_SolTempOut.Size = new System.Drawing.Size(35, 12);
            this.De_SolTempOut.Text = "De_SolTempOut";
            // 
            //  Text11
            this.De_WaterTempIn.AutoSize = true;
            this.De_WaterTempIn.Location = new System.Drawing.Point(80, 190);
            this.De_WaterTempIn.Name = "De_WaterTempIn";
            this.De_WaterTempIn.Size = new System.Drawing.Size(35, 12);
            this.De_WaterTempIn.Text = "De_WaterTempIn";
            //
            //  Text12
            this.De_WaterTempOut.AutoSize = true;
            this.De_WaterTempOut.Location = new System.Drawing.Point(80, 210);
            this.De_WaterTempOut.Name = "De_WaterTempOut";
            this.De_WaterTempOut.Size = new System.Drawing.Size(35, 12);
            this.De_WaterTempOut.Name = "De_WaterTempOut";
            //
            ///////////////////////////////////////////////////////////////////////////////////////
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(250, 10);
            this.label9.Name = "DeAir_outlet";
            this.label9.Size = new System.Drawing.Size(35, 12);
            this.label9.TabIndex = 4;
            this.label9.Text = "DeAir_outlet:";
            // label10
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(250, 30);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(77, 12);
            this.label10.TabIndex = 9;
            this.label10.Text = "Temp:";
            //  Text3
            this.De_AirTempOut.AutoSize = true;
            this.De_AirTempOut.Location = new System.Drawing.Point(320, 30);
            this.De_AirTempOut.Name = "De_AirTempOut";
            this.De_AirTempOut.Size = new System.Drawing.Size(35, 12);
            this.De_AirTempOut.Text = "De_AirTempOut";
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(250, 50);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(77, 12);
            this.label11.TabIndex = 9;
            this.label11.Text = "Humidity:";
            // 
            //  Text4
            this.De_AirHumOut.AutoSize = true;
            this.De_AirHumOut.Location = new System.Drawing.Point(320, 50);
            this.De_AirHumOut.Name = "De_AirHumOut";
            this.De_AirHumOut.Size = new System.Drawing.Size(35, 12);
            this.De_AirHumOut.Text = "De_AirHumOut";

            /////////////////////////////////////////////////////////////////////////////
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(430, 200);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(35, 12);
            this.label20.TabIndex = 9;
            this.label20.Text = "StrOnoffVav:";

            this.sendButtonOnoffvav.AutoSize = true;
            this.sendButtonOnoffvav.Location = new System.Drawing.Point(500, 200);
            this.sendButtonOnoffvav.Name = "sendButtonOnoffvav";
            this.sendButtonOnoffvav.Size = new System.Drawing.Size(80, 30);
            this.sendButtonOnoffvav.Text = "sendButtonOnoffvav";
            // this.sendButtonPump.Click += new System.EventHandler(this.senddataset);
            string currentNameOnoffvav = "Strsol_Onoffvav";
            string currentTypeOnoffvav = "3";
            senddataset(currentNameOnoffvav, currentTypeOnoffvav, sendButtonOnoffvav, this.BoardNumber);
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(430, 350);
            this.label21.Name = "labe21";
            this.label21.Size = new System.Drawing.Size(35, 12);
            this.label21.TabIndex = 9;
            this.label21.Text = "DewtvavFb:";
            //  Text7
            this.De_VavFb.AutoSize = true;
            this.De_VavFb.Location = new System.Drawing.Point(500, 350);
            this.De_VavFb.Name = "De_VavFb";
            this.De_VavFb.Size = new System.Drawing.Size(35, 12);
            this.De_VavFb.Text = "De_VavFb";

            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(430, 370);
            this.label22.Name = "labe22";
            this.label22.Size = new System.Drawing.Size(35, 12);
            this.label22.TabIndex = 9;
            this.label22.Text = "Set:";

            this.sendButtonRevav.AutoSize = true;
            this.sendButtonRevav.Location = new System.Drawing.Point(500, 370);
            this.sendButtonRevav.Name = "sendButtonRevav";
            this.sendButtonRevav.Size = new System.Drawing.Size(80, 30);
            this.sendButtonRevav.Text = "sendButtonRevav";
            // this.sendButtonPump.Click += new System.EventHandler(this.senddataset);
            string currentNameRevav = "De_Revav:";
            string currentTypeRevav = "3";
            senddataset(currentNameRevav, currentTypeRevav, sendButtonRevav, this.BoardNumber);

            //////////////////////////////////////////////////////////////////////////////////////////////
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(10, 500);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(35, 12);
            this.label12.TabIndex = 4;
            this.label12.Text = "De_Pump";
            // 
            // label3
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(10, 520);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(35, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "Feedback:";
            // 
            //  Text5
            // 
            this.De_PumpFb.AutoSize = true;
            this.De_PumpFb.Location = new System.Drawing.Point(80, 520);
            this.De_PumpFb.Name = "De_PumpFb";
            this.De_PumpFb.Size = new System.Drawing.Size(35, 12);
            this.De_PumpFb.Name = "De_PumpFb";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 540);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 12);
            this.label4.TabIndex = 9;
            this.label4.Text = "Set:";
            // 
            //  sendbutton1
            this.sendButtonPump.AutoSize = true;
            this.sendButtonPump.Location = new System.Drawing.Point(80, 540);
            this.sendButtonPump.Name = "sendButtonPump";
            this.sendButtonPump.Size = new System.Drawing.Size(80, 30);
            this.sendButtonPump.Text = "sendButtonPump";
            // this.sendButtonPump.Click += new System.EventHandler(this.senddataset);
            string currentNameP = "De_PumpSet";
            string currentTypeP = "3";
            senddataset(currentNameP, currentTypeP, sendButtonPump, this.BoardNumber);
            /////////////////////////////////////////////////////////////////////////////////////////////
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(204, 520);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(35, 12);
            this.label15.TabIndex = 9;
            this.label15.Text = "De_Flow_Rate:";
            // 
            //  Text5
            this.De_SolFlow.AutoSize = true;
            this.De_SolFlow.Location = new System.Drawing.Point(294, 520);
            this.De_SolFlow.Name = "De_SolFlow";
            this.De_SolFlow.Size = new System.Drawing.Size(35, 12);
            this.De_SolFlow.Name = "De_SolFlow";

            // label6
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(204, 540);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(35, 12);
            this.label16.TabIndex = 4;
            this.label16.Text = "De_Level:";

            //  Text8
            this.De_SolLevelDe.AutoSize = true;
            this.De_SolLevelDe.Location = new System.Drawing.Point(294, 540);
            this.De_SolLevelDe.Name = "De_SolLevelDe";
            this.De_SolLevelDe.Size = new System.Drawing.Size(35, 12);
            this.De_SolLevelDe.Text = "De_SolLevelDe";
            // 

            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(204, 560);
            this.label23.Name = "label16";
            this.label23.Size = new System.Drawing.Size(35, 12);
            this.label23.TabIndex = 4;
            this.label23.Text = "Str_Level:";


            //  Text9
            this.De_SolLevelST.AutoSize = true;
            this.De_SolLevelST.Location = new System.Drawing.Point(294, 560);
            this.De_SolLevelST.Name = "De_SolLevelST";
            this.De_SolLevelST.Size = new System.Drawing.Size(35, 12);
            this.De_SolLevelST.Text = "De_SolLevelST";
            //////////////////////////////////////////////////////////////////////
            // label7
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(460, 440);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(35, 12);
            this.label17.TabIndex = 9;
            this.label17.Text = "DeAir_inlet:";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(460, 460);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(35, 12);
            this.label18.TabIndex = 4;
            this.label18.Text = "Temp:";

            //  Text1
            this.De_AirTempIn.AutoSize = true;
            this.De_AirTempIn.Location = new System.Drawing.Point(530, 460);
            this.De_AirTempIn.Name = "De_AirTempIn";
            this.De_AirTempIn.Size = new System.Drawing.Size(35, 12);
            this.De_AirTempIn.Text = "De_AirTempIn";

            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(460, 480);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(35, 12);
            this.label19.TabIndex = 4;
            this.label19.Text = "Humidity:";

            //  Text2
            this.De_AirHumIn.AutoSize = true;
            this.De_AirHumIn.Location = new System.Drawing.Point(530, 480);
            this.De_AirHumIn.Name = "De_AirHumIn";
            this.De_AirHumIn.Size = new System.Drawing.Size(35, 12);
            this.De_AirHumIn.Text = "De_AirHumIn";

 ////////////////////////////////////////////////////////////////////////////////////////////
            this.LDDSonoff.Location = new System.Drawing.Point(520, 25);
            this.LDDSonoff.Name = "LDDSonoff";
            this.LDDSonoff.Size = new System.Drawing.Size(57, 23);
            this.LDDSonoff.TabIndex = 5;
            this.LDDSonoff.Text = "LDDSonoff";
            this.LDDSonoff.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style3;
            this.LDDSonoff.Click += new System.EventHandler(this.LDDSonoff_Click);
            this.LDDSonoff.PortBind = "Reg3_Handle";
            this.LDDSonoff.RelatedPort = "Reg3";

            this.Startblock.Location = new System.Drawing.Point(520, 55);
            this.Startblock.Name = "Startblock";
            this.Startblock.Size = new System.Drawing.Size(57, 23);
            this.Startblock.TabIndex = 5;
            this.Startblock.Text = "Startblock";
            this.Startblock.CheckStyleX = Library.Common.ButtonCheck.CheckStyle.style2;
            this.Startblock.Click += new System.EventHandler(this.Startblock_Click);

        }



        #endregion

        private Library.Lable label1;
        private Library.Lable label2;
        private Library.Lable label3;
        private Library.Lable label4;
        private Library.Lable label5;
        private Library.Lable label6;
        private Library.Lable label7;
        private Library.Lable label8;
        private Library.Lable label9;
        private Library.Lable label10;
        private Library.Lable label11;
        private Library.Lable label12;
        private Library.Lable label13;
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

        public Library.TextBox De_AirTempIn;
        public Library.TextBox De_AirHumIn;
        public Library.TextBox De_AirTempOut;
        public Library.TextBox De_AirHumOut;
        public Library.TextBox De_SolFlow;
        public Library.TextBox De_PumpFb;
        public Library.TextBox De_FanFb;
        public Library.TextBox De_VavFb;
        public Library.TextBox De_SolLevelDe;
        public Library.TextBox De_SolLevelST;
        public Library.TextBox De_SolTempIn;
        public Library.TextBox De_SolTempOut;
        public Library.TextBox De_WaterTempIn;
        public Library.TextBox De_WaterTempOut;


        //   List<TextBox> Textcollection = new List<TextBox>();
        private Library.SendButton sendButtonOnoffvav;
        private Library.SendButton sendButtonRevav;

        private Library.SendButton sendButtonPump;
        private Library.SendButton sendButtonFan;
        private Library.Common.ButtonCheck LDDSonoff;
        private Library.Common.ButtonCheck Startblock;
    }




}
