using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DataBus;

namespace Library
{
    [ToolboxBitmap(typeof(System.Windows.Forms.TextBox))]
    public partial class TextBox : System.Windows.Forms.TextBox
    {
        public Timer timertest;

        DataBus.DataAccess.CData_PointTable dataPT;
        public DataBus.DataRefresh.CRealTimeDataManager rtdm;

        private System.Windows.Forms.ToolStripMenuItem MenuItemOpenDataChart;
        private System.Windows.Forms.ContextMenuStrip RightClickMenuLook;

        public TextBox()
        {
            InitializeComponent();

            RightClickMenuLook = new System.Windows.Forms.ContextMenuStrip(this.components);
            MenuItemOpenDataChart = new System.Windows.Forms.ToolStripMenuItem();
            this.ContextMenuStrip = RightClickMenuLook;
            this.MouseClick += new MouseEventHandler(TextBox_MouseClick);
            dataPT = new DataBus.DataAccess.CData_PointTable();
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

        private void TextBox_MouseClick(object sender, EventArgs e)
        {

            RightClickMenuLook.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            MenuItemOpenDataChart});
            MenuItemOpenDataChart.Text = "OpenDataChart";
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            string stringName = this.Name;
            if (rtdm != null)
                this.Text = rtdm.GetDataByBoardPort(BoardNumber, RelatedPort);
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // 调用基类 OnPaint
            base.OnPaint(pe);
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
