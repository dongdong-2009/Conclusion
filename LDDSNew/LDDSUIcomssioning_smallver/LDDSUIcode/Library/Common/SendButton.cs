using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Library
{
    public partial class SendButton : UserControl
    {
   //     private DataBus.DataSend.CDataSend dataSend;
        public Timer timertest;
   //     DataBus.DataAccess.CData_PointTable dataPT;
   //     public DataBus.DataRefresh.CRealTimeDataManager rtdm;



        public SendButton()
        {
            InitializeComponent();
            //dataSend = new DataBus.DataSend.CDataSend();
            //dataPT = new DataBus.DataAccess.CData_PointTable();
            timertest = new Timer();
            timertest.Interval = 50000;
            timertest.Tick += new EventHandler(Timer_Tick);
            timertest.Enabled = true;

            if (LicenseManager.UsageMode == LicenseUsageMode.Designtime)

            {
                timertest.Stop();
            }
            else
            {
                timertest.Start();
            }

        }

        private void Timer_Tick(object sender, EventArgs e)
        {
     //       if (rtdm != null)
     //           this.sendData.Text = rtdm.GetDataByBoardPort(BoardNumber, RelatedPort);
        }
        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码

            // 调用基类 OnPaint
            base.OnPaint(pe);
        }

        private void button_Click(object sender, EventArgs e)
        {


            if (sendData.Text == "")
            {
                MessageBox.Show("Please input a value!", "Alert", MessageBoxButtons.OK);
                return;
            }


//            bool isSuccess = dataSend.SendControlData(sendData.Text, this.RelatedPort, this.PortBind, this.BoardNumber);

            //if (isSuccess == true)
            //{
            //    MessageBox.Show("Success!");
            //}
            //else
            //{
            //    MessageBox.Show("Failed!");
            //}
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

        private void sendData_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }
    }
}
