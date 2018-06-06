using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Library
{
    [ToolboxBitmap(typeof(System.Windows.Forms.RadioButton))]
    public partial class RadioButton : System.Windows.Forms.RadioButton
    {
        public RadioButton()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码

            // 调用基类 OnPaint
            base.OnPaint(pe);
        }
        //event setup
        //mouse click event
        private string _ClickEvent = null;
        public string ClickEvent
        {
            get
            {
                return _ClickEvent;
            }
            set
            {
                _ClickEvent = value;
            }
        }
        //mouse double click event
        private string _DoubleEvent = null;
        public string DoubleEvent
        {
            get
            {
                return _DoubleEvent;
            }
            set
            {
                _DoubleEvent = value;
            }
        }
    }
}
