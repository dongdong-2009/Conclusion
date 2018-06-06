using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Library
{
    [ToolboxBitmap(typeof(System.Windows.Forms.Button))] 
    public partial class Button : System.Windows.Forms.Button
    {
       
        public Button()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码

            // 调用基类 OnPaint
            base.OnPaint(pe);
        }
        private bool _visible = true;
        [Description("Visible"), Category("Action")]
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
    }
}
