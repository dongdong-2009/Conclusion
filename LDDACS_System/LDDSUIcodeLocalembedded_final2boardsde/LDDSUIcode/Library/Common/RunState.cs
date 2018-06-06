using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Library.Common
{
    public partial class RunState : UserControl
    {
        public Timer m_timer;
        DataBus.DataAccess.CData_PointTable dataPT;
        public DataBus.DataRefresh.CRealTimeDataManager rtdm;
        public RunState()
        {
            InitializeComponent();
            dataPT = new DataBus.DataAccess.CData_PointTable();
            m_timer = new Timer();
            m_timer.Interval = 8000;
            m_timer.Tick += new EventHandler(Timer_Tick);
            m_timer.Enabled = true;

            //判断是否为设计模式
            if (LicenseManager.UsageMode == LicenseUsageMode.Designtime
                )
            {
                m_timer.Stop();
            }
            else
            {
                m_timer.Start();
            }
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // 调用基类 OnPaint
            base.OnPaint(pe);
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
            try
            {
            }
            catch { }
            string stringName = this.Name;
            if (rtdm != null)
            {
               
                string data = rtdm.GetDataByBoardPort(BoardNumber,RelatedPort);

                if (data == "1")
                {
                    pictureBox.Image = global::Library.Properties.Resources.NormalState;
                }
                else if (data == "0")
                {
                    pictureBox.Image = global::Library.Properties.Resources.FailState;
                }
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
