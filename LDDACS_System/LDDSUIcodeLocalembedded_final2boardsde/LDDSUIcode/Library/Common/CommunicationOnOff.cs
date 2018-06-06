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
    public partial class CommunicationOnOff : UserControl
    {
        private DataBus.DataSend.CDataSend dataSend;
        public CommunicationOnOff()
        {
            InitializeComponent();
            dataSend = new DataBus.DataSend.CDataSend();
        }
        protected override void OnPaint(PaintEventArgs pe)
        {
            // 调用基类 OnPaint
            base.OnPaint(pe);
        }

        private void button_Click(object sender, EventArgs e)
        {
            //判断目前状态 决定onoff

            string state = "";
//             if()
//             {
// 
//             }
            dataSend.SendOnOffData(BoardNumber, state);
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
    }
}
