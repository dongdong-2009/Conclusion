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
    public partial class Alarm : UserControl
    {
        public Timer timertest;
        DataBus.DataAccess.CData_PointTable dataPT;
        public DataBus.DataRefresh.CRealTimeDataManager rtdm;
        public Alarm()
        {
            InitializeComponent();
            dataPT = new DataBus.DataAccess.CData_PointTable();
            timertest = new Timer();
            timertest.Interval = 5000;
            timertest.Tick += new EventHandler(Timer_Tick);
            timertest.Enabled = true;

            //判断是否为设计模式
            if (LicenseManager.UsageMode == LicenseUsageMode.Designtime
                )
            {
                timertest.Stop();
            }
            else
            {
                timertest.Start();
            }
        }

        double uplimit = 0;
        double downlimit = 0;
        double currentData;
        private void Timer_Tick(object sender, EventArgs e)
        {
            pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
            try
            {
                uplimit = Convert.ToDouble(UpLimit);
                downlimit = Convert.ToDouble(DownLimit);
            }
            catch { }
            string stringName = this.Name;
            if (rtdm != null)
            {
         
                string data = rtdm.GetDataByBoardPort(BoardNumber,  RelatedPort);

                if (data!= "")
                    currentData = Convert.ToDouble(data);
                if (currentData < downlimit || currentData > uplimit)
                {
                    pictureBox.Image = global::Library.Properties.Resources.alarmOn;
                }
                else
                {
                    pictureBox.Image = null;

                }
            }
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // 调用基类 OnPaint
            base.OnPaint(pe);
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
                if (_id != "" && _id != null)
                {
                    //设置板号、端口号
                    //                     string a = "";
                    //                     string b = "";
                    //                     dataPT.GetBoardPortByPointID(dataPT.GetPointID(_type, _id),ref a,ref b);
                    //                     BoardNumber = a;
                }
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

        private string _upLimit;
        [Description("UpLimit"), Category("Property")]
        public string UpLimit   //端口
        {
            get
            {
                return _upLimit;
            }
            set
            {
                _upLimit = value;
            }
        }
        private string _downLimit;
        [Description("DownLimit"), Category("Property")]
        public string DownLimit   //端口
        {
            get
            {
                return _downLimit;
            }
            set
            {
                _downLimit = value;
            }
        }

        private void pictureBox_Click(object sender, EventArgs e)
        {

        }
    }
}
