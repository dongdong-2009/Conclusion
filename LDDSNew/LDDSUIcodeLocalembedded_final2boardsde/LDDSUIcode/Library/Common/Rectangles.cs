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
    [ToolboxBitmap(typeof(Rectangles))]
    public partial class Rectangles : Control
    {
        public enum FillPatternStyle
        {
            Color, Hatch, None
        }
        //fill
        private FillPatternStyle _fillPattern = FillPatternStyle.Color;
        [Description("填充图案"), Category("外观")]
        public FillPatternStyle FillPattern
        {
            get { return _fillPattern; }
            set { _fillPattern = value; this.Invalidate(); }
        }
        private Color _FillColor = Color.White;
        [Description("填充颜色"), Category("外观")]
        public Color FillColor
        {
            get { return _FillColor; }
            set
            {
                _FillColor = value;
                this.Invalidate();
            }
        }

        private HatchStyle _hatchStyle = HatchStyle.Cross;
        [Description("填充风格"), Category("外观")]
        public HatchStyle HatchStyle
        {
            get { return _hatchStyle; }
            set
            {
                _hatchStyle = value;
                this.Invalidate();
            }
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
        public Rectangles()
        {
            InitializeComponent();
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
            path.AddRectangle (rc);

            Brush bsh = null;

            switch (FillPattern)
            {
                case FillPatternStyle.Color:
                    bsh = new SolidBrush(FillColor);
                    break;
                case FillPatternStyle.Hatch:
                    bsh = new HatchBrush(HatchStyle, FillColor);
                    break;
            }

            if (bsh != null)
            {
                g.FillPath(bsh, path);
                bsh.Dispose();
            }


            // Draw
            Pen pen = null;

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
