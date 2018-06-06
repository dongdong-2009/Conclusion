using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
namespace Library
{
    [ToolboxBitmap(typeof(Led))]
    public partial class Led : Control
    {
        public Led()
        {
            InitializeComponent();
     //       SetStyle(ControlStyles.SupportsTransparentBackColor
     //| ControlStyles.UserPaint
     //| ControlStyles.AllPaintingInWmPaint
     //| ControlStyles.Opaque, true);
     //       BackColor = Color.Transparent;
        }
        protected override void OnLocationChanged(EventArgs e)
        {
            // pick up the container's surface again. 
            Visible = false;
            Visible = true;
        }

        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x00000020; //WS_EX_TRANSPARENT 
                return cp;
            }
        }
        //action setup
        private bool _bHaveAction = false;
        public bool bHaveAction
        {
            get
            {
                return _bHaveAction;
            }
            set
            {
                _bHaveAction = value;
            }
        }
        private string _ledName = null;
        
        public string LedName
        {
            get
            {
                return _ledName;
            }
            set
            {
                _ledName = value;
                this.Invalidate();
            }
        }
        private Color _newFillColor = Color.Red;
        public Color newFillColor
        {
            get
            {
                return _newFillColor;
            }
            set
            {
                _newFillColor = value;
            }
        }
        //原背景色
        private Color _oldFillColor = Color.DarkGray;
        public Color oldFillColor
        {
            get
            {
                return _oldFillColor;
            }
            set
            {
                _oldFillColor = value;
            }
        }
        private Color _centerColor = Color.White;
        [Description("中心色"), Category("外观")]
        public Color CenterColor
        {
            get
            {
                return _centerColor;

            }
            set
            {
                _centerColor = value;
                this.Invalidate();
            }
        }
      
        private Color _fillColor = Color.Green;
        [Description("填充色"), Category("外观")]
        public Color FillColor
        {
            get
            {
                return _fillColor;

            }
            set
            {
                _fillColor = value;
                this.Invalidate();
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
        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码
            Graphics g = pe.Graphics;
            GraphicsPath path = new GraphicsPath();
            Rectangle rc = new Rectangle(0, 0, this.ClientSize.Width - 1, this.ClientSize.Height - 1);

            path.AddEllipse(rc);

            PathGradientBrush pathBrush = new PathGradientBrush(path);
            pathBrush.CenterColor = _centerColor;
            Color[] surColor ={ _fillColor };
            pathBrush.SurroundColors = surColor;
            g.FillPath(pathBrush, path);

            pathBrush.Dispose();
            path.Dispose();
            // 调用基类 OnPaint
            base.OnPaint(pe);
        }
    }
}
