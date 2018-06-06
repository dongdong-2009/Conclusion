using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
//using DataBus;
using System.Runtime.InteropServices;
namespace Library.Common
{
    public partial class levelmeter : VerticalProgressBar
    {

        public Timer timertest;

 //       DataBus.DataAccess.CData_PointTable dataPT;
 //       public DataBus.DataRefresh.CRealTimeDataManager rtdm;

        public levelmeter()
        {
            InitializeComponent();

         //   SetProcessValue(Value);
 //           dataPT = new DataBus.DataAccess.CData_PointTable();
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
  

        private void Timer_Tick(object sender, EventArgs e)
       {
            float midvalue = 0;
          //if (rtdm != null)
          //      midvalue = float.Parse(rtdm.GetDataByBoardPort(BoardNumber, RelatedPort));
          //  this.Value = (int)midvalue;
          //  SetProcessValue(Value);
            if (Value > 40)
                this.ForeColor = Color.Yellow;
            else
                this.ForeColor = Color.Blue;
        }



        private void levelmeter_Click(object sender, EventArgs e)
        {

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
        private string _range = "";
        [Description("Level Range"), Category("Property")]
        public string LevelRange
        {
            get
            {
                return _range;
            }
            set
            {
                _range = value;
            }
        }
        public void SetProcessValue( float value)
        {
            // this.Text = TitleName;
            //string str = int.Parse(value.ToString() + "%");
            //Font font = new Font("Times New Roman", (float)6, FontStyle.Bold);
            // PointF pt = new PointF(this.Width / 2 - 10, this.Height / 2 - 10);
            // this.CreateGraphics().DrawString(str, font, Brushes.Black, pt);
            //int midvalue = int(value);
            //this.Value = int.Parse(int(value));
        }

    }

    public class VerticalProgressBar : ProgressBar
    {
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.Style |= 0x04;
                return cp;
            }
        }
    }

}
