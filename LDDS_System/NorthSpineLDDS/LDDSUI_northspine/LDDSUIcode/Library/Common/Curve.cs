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
    [ToolboxBitmap(typeof(Curve))]
    public partial class Curve : Control
    {
       
        public Curve()
        {
            InitializeComponent();
            SetStyle(ControlStyles.UserPaint |
                    ControlStyles.DoubleBuffer |
                    ControlStyles.ResizeRedraw |
                    ControlStyles.AllPaintingInWmPaint |
                    ControlStyles.SupportsTransparentBackColor,
                    true);
        }
        private string strTitle = "曲线图"; //标题
        private Color clrAxisTextColor = Color.Black; //轴说明文字颜色
        private Color clrSliceTextColor = Color.Black; //刻度文字颜色
        private int _MaxValue = 200;
        float[] m_pvalues = new float[10000];		// value array
        long m_lNoValues = 0;	// no values (used for array size)
        long m_lend = 0;			// list end
        long m_lMaxDataPrSerie = 9999;
        #region 公共属性
        private Font _font = null;
        [Description("文本字体"), Category("曲线文本")]
        public Font mFont
        {
            get { return _font; }
            set { _font = value; this.Invalidate(); }
        }
        [Description("Y轴最大值"), Category("曲线")]
        public int MaxValue
        {
            set { _MaxValue = value; this.Invalidate(); }
            get { return _MaxValue; }
        }
        private float _CurrentValue = 0f;
  
        public float CurrentValue
        {
            set { _CurrentValue = value; }
            get { return _CurrentValue; }
        }
        private string _sName = "CurveName";
        [Description("曲线名称"), Category("曲线")]
        public string sName
        {
            set { _sName = value; this.Invalidate(); }
            get { return _sName; }
        }
        /// <summary>
        /// 标题
        /// </summary>
        /// 
        [Description("图表标题"), Category("曲线")]
        public string Title
        {
            set { strTitle = value; this.Invalidate(); }
            get { return strTitle; }
        }
        /// <summary>
        /// 文字颜色
        /// </summary>
        /// 
        private Color clrTextColor = Color.Green;
        [Description("数字和文本的颜色"), Category("曲线文本")]
        public Color TextColor
        {
            set { clrTextColor = value; this.Invalidate(); }
            get { return clrTextColor; }
        }
        /// <summary>
        /// 轴线颜色
        /// </summary>
        /// 
        private Color clrAxisColor = Color.Black;
        [Description("坐标系的颜色"), Category("曲线")]
        public Color AxisColor
        {
            set { clrAxisColor = value; this.Invalidate(); }
            get { return clrAxisColor; }
        }
        /// <summary>
        /// 曲线颜色
        /// </summary>
        /// 
        private Color clrsCurveColors = Color.Red;
        [Description("曲线颜色"), Category("曲线")]
        public Color CurveColor
        {
            set { clrsCurveColors = value; this.Invalidate(); }
            get { return clrsCurveColors; }
        }
        private DashStyle _dashStyle = DashStyle.Solid;
        [Description("边框风格"), Category("边框")]
        public DashStyle DashStyle
        {
            get { return _dashStyle; }
            set { _dashStyle = value; this.Invalidate(); }
        }
        private DashStyle _LineStyle = DashStyle.Solid;
        [Description("曲线风格"), Category("曲线")]
        public DashStyle LineStyle
        {
            get { return _LineStyle; }
            set { _LineStyle = value; this.Invalidate(); }
        }
        /// <summary>
        /// 字体大小号数
        /// </summary>
        /// 
        private int intFontSize = 9;
        [Description("数字和文本的字号"), Category("曲线文本")]
        public int FontSize
        {
            get { return intFontSize; }
            set { intFontSize = value; this.Invalidate(); }
        }
        /// <summary>
        /// 曲线线条大小
        /// </summary>
        /// 
        private int intCurveSize = 1;
        [Description("曲线线宽"), Category("曲线")]
        public int CurveSize
        {
            get { return intCurveSize; }
            set { intCurveSize = value; this.Invalidate(); }
        }
        //
        //line style
        private Color _LineColor = Color.Black;
        [Description("边框颜色"), Category("边框")]
        public Color LineColor
        {
            get { return _LineColor; }
            set { _LineColor = value; this.Invalidate(); }
        }
        private int _LineWidth = 2;
        [Description("边框线宽"), Category("边框")]
        public int LineWidth
        {
            get { return _LineWidth; }
            set { _LineWidth = value; this.Invalidate(); }
        }
        private int _LineAlpha = 255;
        [Description("边框线色透明值0~255"), Category("边框")]
        public int LineAlpha
        {
            get { return _LineAlpha; }
            set { _LineAlpha = value; this.Invalidate(); }
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
        private string _scalename = null;
        public string ScaleName
        {
            get
            {
                return _scalename;
            }
            set
            {
                _scalename = value;
            }
        }
        #endregion
        public void AddPoint(float y)
        {
            CurrentValue = y;
            m_pvalues[m_lend] = y;
            m_lNoValues++;
            m_lend++;
            if (m_lend >= m_lMaxDataPrSerie)
            {
                m_lend = 0;
                m_lNoValues = 0;
            }
            this.Refresh();
        }
        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码
            Graphics g = pe.Graphics;
            GraphicsPath path = new GraphicsPath();
            Rectangle rect = new Rectangle(new Point(0, 0), new Size(this.ClientSize.Width, this.ClientSize.Height));
            path.AddRectangle(rect);
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
            //draw cordniate
            if (_font == null)
            {
                _font = new Font("宋体", FontSize, FontStyle.Regular);
            }
            SolidBrush b1 = new SolidBrush(clrAxisColor);
            Pen b2 = new Pen(AxisColor, 1);
            for (int j = -2; j < 3; j++)//-2 3
            {
                int i;
                int slice = (j * MaxValue / 2);
                g.DrawString(slice.ToString(), _font, b1, rect.Left, rect.Top + rect.Height / 2 - j * rect.Height / 6);                
                for (i = 0; i < 60; i += 2)
                {
                    float fltX1 = rect.Left + 9 * rect.Width * i / 600;
                    float fltY1 = rect.Top + rect.Height / 2 - j * rect.Height / 6;
                    float fltX2 = rect.Left + 9 * rect.Width * (i + 1) / 600;
                    float fltY2 = rect.Top + rect.Height / 2 - j * rect.Height / 6;                
                    g.DrawLine(b2, fltX1, fltY1, fltX2, fltY2);              
               }              
            }
            b2.Dispose();
            b1.Dispose();
            SolidBrush sb = new SolidBrush(clrTextColor);
            //Font ft = new Font("宋体", FontSize);
            g.DrawString(strTitle, _font, sb, rect.Width / 2 - strTitle.Length, rect.Top + 15);
            g.DrawString("当前值： " + CurrentValue.ToString(), _font, sb, rect.Left + 5, rect.Top + 15);
            g.DrawString("曲线名称： " + sName, _font, sb, rect.Left + 5, rect.Bottom - 15);
            sb.Dispose();
            //draw curve
            float maxheight = MaxValue;
            float widthsegment = (float)(rect.Width * 0.9) / 400f;
            long a = m_lNoValues;
            Pen b3 = new Pen(clrsCurveColors, intCurveSize);
            b3.DashStyle = LineStyle;
            if (a < 400)
            {
                float fltX1 = rect.Left;
                float fltY1 = rect.Top + rect.Height / 2;
                
                for (long i = 0; (i < 400) && (i < a); i++)
                {
                    float fltX2 = rect.Left + i * widthsegment;
                    float fltY2 = rect.Top + rect.Height / 2 - ((m_pvalues[i] * rect.Height) / (2 * maxheight)) * 2 / 3;                  
                    g.DrawLine(b3, fltX1, fltY1, fltX2, fltY2);                   
                    fltX1 = fltX2;
                    fltY1 = fltY2;
                }
               
            }
            else
            {
                int tempc = 0;
                float fltX1 = rect.Left;
                float fltY1 = rect.Top + rect.Height / 2;
                for (long i = a - 400; i < a; i++)
                {
                    float fltX2 = rect.Left + tempc * widthsegment;
                    float fltY2 = rect.Top + rect.Height / 2 - ((m_pvalues[i] * rect.Height) / (2 * maxheight)) * 2 / 3;
                    g.DrawLine(b3, fltX1, fltY1, fltX2, fltY2);
                    tempc++;
                    fltX1 = fltX2;
                    fltY1 = fltY2;
                }
            }
            b3.Dispose();
            // 调用基类 OnPaint
            base.OnPaint(pe);
        }
    }
}
