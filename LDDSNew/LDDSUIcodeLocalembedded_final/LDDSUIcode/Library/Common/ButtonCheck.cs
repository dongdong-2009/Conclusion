using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;


namespace Library.Common
{
    public partial class ButtonCheck : UserControl
    {
        public Timer timertest;
        public string currentState = "0";
        private DataBus.DataSend.CDataSend dataSend;
        public DataBus.DataAccess.CData_ControlDataManager rtdm;
        public DataBus.DataRefresh.CRealTimeDataManager CDrtdm;
        private Bitmap bitMapOn = null;
        private Bitmap bitMapOff = null;
        public ButtonCheck()
        {
            InitializeComponent();
            dataSend = new DataBus.DataSend.CDataSend();
            rtdm = new DataBus.DataAccess.CData_ControlDataManager();
            //设置Style支持透明背景色并且双缓冲
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.DoubleBuffer, true);
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            this.SetStyle(ControlStyles.Selectable, true);
            this.SetStyle(ControlStyles.SupportsTransparentBackColor, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            this.BackColor = Color.Transparent;

            this.Cursor = Cursors.Hand;
            this.Size = new Size(87, 27);

            timertest = new Timer();
            timertest.Interval = 20000;  //五分钟判断一次状态
            timertest.Tick += new EventHandler(Timer_Tick);
            timertest.Enabled = true;

        }

        protected override void OnPaint(PaintEventArgs e)
        {

            
            if (checkStyle == CheckStyle.style1)
            {
                bitMapOn  = global::Library.Properties.Resources.btncheckon1;
                bitMapOff = global::Library.Properties.Resources.btncheckoff1;
            }
            else if (checkStyle == CheckStyle.style2)
            {
                bitMapOn = global::Library.Properties.Resources.btncheckon2;
                bitMapOff = global::Library.Properties.Resources.btncheckoff2;
            }
            else if (checkStyle == CheckStyle.style3)
            {
                bitMapOn = global::Library.Properties.Resources.btncheckon3;
                bitMapOff = global::Library.Properties.Resources.btncheckoff3;
            }
            else if (checkStyle == CheckStyle.style4)
            {
                bitMapOn = global::Library.Properties.Resources.btncheckon4;
                bitMapOff = global::Library.Properties.Resources.btncheckoff4;
            }
            else if (checkStyle == CheckStyle.style5)
            {
                bitMapOn = global::Library.Properties.Resources.btncheckon5;
                bitMapOff = global::Library.Properties.Resources.btncheckoff5;
            }
            else if (checkStyle == CheckStyle.style6)
            {
                bitMapOn = global::Library.Properties.Resources.btncheckon6;
                bitMapOff = global::Library.Properties.Resources.btncheckoff6;
            }
            
            Graphics g = e.Graphics;
            Rectangle rec = new Rectangle(0, 0, this.Size.Width, this.Size.Height);

            if (currentState == "1")
            {
                g.DrawImage(bitMapOn, rec);
            }
            else
            {
                g.DrawImage(bitMapOff, rec);
            }
            base.OnPaint(e);
            
        }
        public enum CheckStyle
        {
            style1 = 0,
            style2 = 1,
            style3 = 2,
            style4 = 3,
            style5 = 4,
            style6 = 5
        };

        #region properties
        CheckStyle checkStyle = CheckStyle.style1;
        /// <summary>
        /// 样式
        /// </summary>
        [Description("CheckStyle"), Category("Property")]
        public CheckStyle CheckStyleX
        {
            set { checkStyle = value; this.Invalidate(); }
            get { return checkStyle; }
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
        private string _portData; // sendDataPort
        [Description("PortData"), Category("Property")]
        public string PortData
        {
            get
            {
                return _portData;
            }
            set
            {
                _portData = value;
            }
        }
        private string _portBind; //bindPort
        [Description("PortBind"), Category("Property")]
        public string PortBind
        {
            get
            {
                return _portBind;
            }
            set
            {
                _portBind = value;
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

        #endregion

        private void ButtonCheck_Click(object sender, EventArgs e)
        {
            if (currentState == "0")
            {
                currentState = "1";
            }
            else
            {
                currentState = "0";
            }
            dataSend.SendButtonCheckData(RelatedPort, PortBind, BoardNumber, currentState);
            this.Invalidate();
        }
        public void CheckCurrentState()
        {
            string stringName = this.Name;
            if (CDrtdm != null)
            {
                string data = CDrtdm.GetDataByBoardPort(BoardNumber, RelatedPort);

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
    }
}
