using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows.Forms;
using System.Text;
using System.Drawing;

namespace Library
{
    public partial class statusIndicator : Control
    {
        public Timer timertest;
        public string currentState = "0";
        public DataBus.DataRefresh.CRealTimeDataManager rtdm;
        private Bitmap bitMapOn  = global::Library.Properties.Resources.button_glossy_yellowtras;
        private Bitmap bitMapOff = global::Library.Properties.Resources.button_glossy_bluetrans;

        public statusIndicator()
        {
            InitializeComponent();

           SetStyle(ControlStyles.SupportsTransparentBackColor
            | ControlStyles.UserPaint
            | ControlStyles.AllPaintingInWmPaint,true
            );
           // | ControlStyles.Opaque, true
            BackColor = Color.Transparent;

            this.Size = new Size(27, 27);
            timertest = new Timer();
            timertest.Interval = 5000;
            timertest.Tick += new EventHandler(Timer_Tick);
            timertest.Enabled = true;

            //判断是否为设计模式
            if (LicenseManager.UsageMode == LicenseUsageMode.Designtime)

            {
                timertest.Stop();
            }
            else
            {
                timertest.Start();
            }

        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            Graphics g = pe.Graphics;
            Rectangle rec = new Rectangle(0, 0, this.Size.Width, this.Size.Height);

            if (currentState == "1")
            {
                g.DrawImage(bitMapOn,rec);
            }
            else
            {
                g.DrawImage(bitMapOff,rec);
            }

            base.OnPaint(pe);
        }
        public void CheckCurrentState()
        {
            string stringName = this.Name;
            if (rtdm != null)
            {
                string data = rtdm.GetDataByBoardPort(BoardNumber,  RelatedPort);
                if (data == "1")
                {
                    currentState = "1";
                }
                else if (data == "0")
                {
                    currentState = "0";
                }
            }
            this.Invalidate();
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            CheckCurrentState();
        }
        private bool _visible = true;
        [Description("Visible or not"), Category("Property")]
        public bool isVisible
        {
            get
            {
                return _visible;
            }
            set
            {
                _visible = value;
            }
        }

        private string _id = "";
        [Description("id"), Category("Property")]
        public string ID
        {
            get
            {
                return _id;
            }
            set
            {
                _id = value;
            }
        }

        private string _type = "";
        [Description("Device Type"), Category("Property")]
        public string RelatedDeviceType
        {
            get
            {
                return _type;
            }
            set
            {
                _type = value;
            }
        }
        private string _boardNumber;
        [Description("BoardNumber"), Category("Property")]
        public string BoardNumber   //板号
        {
            get
            {
                return _boardNumber;
            }
            set
            {
                _boardNumber = value;
            }
        }
        private string _relatedPort;
        [Description("RelatedPort"), Category("Property")]
        public string RelatedPort   //端口
        {
            get
            {
                return _relatedPort;
            }
            set
            {
                _relatedPort = value;
            }
        }

        private string _name = "";
        [Description("Device Name"), Category("Property")]
        public string DeviceName
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
            }
        }
    }
}
