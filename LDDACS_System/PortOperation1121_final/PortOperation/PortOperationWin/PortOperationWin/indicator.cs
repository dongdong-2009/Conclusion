using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PortOperationWin
{
    public partial class indicator : UserControl
    {
        public string currentState;
        public string data;
        public string rtdm;
        public Timer timertest;

        private Bitmap bitMapOn = Properties.Resources.button_glossy_yellowtras;
        private Bitmap bitMapOff = Properties.Resources.button_glossy_bluetrans;

        public indicator()
        {
            InitializeComponent();
            SetStyle(ControlStyles.SupportsTransparentBackColor
          | ControlStyles.UserPaint
          | ControlStyles.AllPaintingInWmPaint, true);
     

            timertest = new Timer();
            timertest.Interval = 20000;  //五分钟判断一次状态
            timertest.Tick += new EventHandler(Timer_Tick);
            timertest.Enabled = true;
        }
        public void CheckCurrentState()
        {
                if (data == "1")
                {
                    currentState = "1";
                }
                else if (data == "0")
                {
                    currentState = "0";
                }
          
            this.Invalidate();
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            CheckCurrentState();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            Graphics g = pe.Graphics;
            Rectangle rec = new Rectangle(0, 0, this.Size.Width, this.Size.Height);

            if (currentState == "1")
            {
                g.DrawImage(bitMapOn, rec);
            }
            else
            {
                g.DrawImage(bitMapOff, rec);
            }

            base.OnPaint(pe);
        }


    }
}


