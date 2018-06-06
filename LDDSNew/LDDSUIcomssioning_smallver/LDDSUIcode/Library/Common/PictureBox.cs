using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
//using System.Drawing.Drawing2D;
//using System.Drawing.Imaging;
using System.Runtime.Serialization;


namespace Library
{
    [ToolboxBitmap(typeof(System.Windows.Forms.PictureBox))]
    public partial class PictureBox : System.Windows.Forms.PictureBox
    {
        public PictureBox()
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


        protected override void OnMouseDown(System.Windows.Forms.MouseEventArgs e)
        {
//             if (e.Button == MouseButtons.Left)
//             {
//                 MessageBox.Show("2");
//             }
        }
    }
}
