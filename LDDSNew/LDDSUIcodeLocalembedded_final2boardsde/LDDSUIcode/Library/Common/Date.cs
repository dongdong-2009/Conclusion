using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Library
{
    [ToolboxBitmap(typeof(Date))]
    public partial class Date : System.Windows.Forms.Label
    {
        private Timer mTimer;
        public Date()
        {
            InitializeComponent();
            mTimer = new Timer();
            mTimer.Interval = 1000;
            mTimer.Tick += new EventHandler(mTimer_Tick);
            mTimer.Start();
        }

        void mTimer_Tick(object sender, EventArgs e)
        {
            this.Text = DateTime.Now.ToString();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码

            // 调用基类 OnPaint
            base.OnPaint(pe);
        }
    }
}
