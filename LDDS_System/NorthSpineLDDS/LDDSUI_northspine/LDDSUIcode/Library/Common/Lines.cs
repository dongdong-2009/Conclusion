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
    [ToolboxBitmap(typeof(Lines))]
    public partial class Lines : Control
    {
        Pen pen = null;
        public enum Arrow
        {
            Yes, No
        }
        public enum ArrowDirection
        {
            Left, Right
        }
        public enum LinePatternStyle
        {
            horizontal, vertical, declining
        }
        //fill
        private LinePatternStyle _LinePattern = LinePatternStyle.declining;
        [Description("线条样式"), Category("外观")]
        public LinePatternStyle LinePattern
        {
            get { return _LinePattern; }
            set { _LinePattern = value; this.Invalidate(); }
        }
        //line style
        private Color _LineColor = Color.Black;
        [Description("边缘线色"), Category("外观")]
        public Color LineColor
        {
            get { return _LineColor; }
            set { _LineColor = value; this.Invalidate(); }
        }
        private int _LineWidth = 2;
        [Description("边缘线宽"), Category("外观")]
        public int LineWidth
        {
            get { return _LineWidth; }
            set { _LineWidth = value; this.Invalidate(); }
        }

        private DashStyle _dashStyle = DashStyle.Solid;
        [Description("边缘风格"), Category("外观")]
        public DashStyle DashStyle
        {
            get { return _dashStyle; }
            set { _dashStyle = value; this.Invalidate(); }
        }
        private int _LineAlpha = 255;
        [Description("线色透明值0~255"), Category("外观")]
        public int LineAlpha
        {
            get { return _LineAlpha; }
            set { _LineAlpha = value; this.Invalidate(); }
        }
        public Lines()
        {
            InitializeComponent();
            SetStyle(ControlStyles.SupportsTransparentBackColor
                     | ControlStyles.UserPaint
                     | ControlStyles.AllPaintingInWmPaint
                     | ControlStyles.Opaque, true);
            BackColor = Color.Transparent;
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
        public bool isRuntime = false;
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
                if (isRuntime)
                {
                    this.Visible = _visible;
                }
            }
        }
        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码
            Graphics g = pe.Graphics;
            GraphicsPath path = new GraphicsPath();
            Rectangle rc = new Rectangle(0, 0, this.ClientSize.Width , this.ClientSize.Height );
   
            switch (LinePattern)
            {
                case LinePatternStyle.horizontal:
                    path.AddLine(rc.X,rc.Y,rc.X+rc.Width,rc.Y);
                    break;
                case LinePatternStyle.vertical:
                    path.AddLine(rc.X,rc.Y,rc.X,rc.Y+rc.Height);
                    break;
                case LinePatternStyle.declining:
                    path.AddLine(rc.X,rc.Y,rc.X+rc.Width,rc.Y+rc.Height);
                    break;
            }

            // Draw
            

            pen = new Pen(Color.FromArgb(LineAlpha, LineColor));
            pen.Width = LineWidth;
            pen.DashStyle = DashStyle;
            g.DrawPath(pen, path);

            if (pen != null)
            {
                pen.Dispose();
            }

            path.Dispose();
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


        private string _xName = null;
        public string xName
        {
            get
            {
                return _xName;
            }
            set
            {
                _xName = value;
            }
        }
        private string _yName = null;
        public string yName
        {
            get
            {
                return _yName;
            }
            set
            {
                _yName = value;
            }
        }
        private string _widthName = null;
        public string widthName
        {
            get
            {
                return _widthName;
            }
            set
            {
                _widthName = value;
            }
        }
        private string _heightName = null;
        public string heightName
        {
            get
            {
                return _heightName;
            }
            set
            {
                _heightName = value;
            }
        }
        private string _visibleName = null;
        public string visibleName
        {
            get
            {
                return _visibleName;
            }
            set
            {
                _visibleName = value;
            }
        }
        private string _FillColorName = null;
        public string FillColorName
        {
            get
            {
                return _FillColorName;
            }
            set
            {
                _FillColorName = value;
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
    }
}
