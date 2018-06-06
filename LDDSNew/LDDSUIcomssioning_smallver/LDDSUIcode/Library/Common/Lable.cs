using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Library
{
    [ToolboxBitmap(typeof(System.Windows.Forms.Label))] 
    public partial class Lable : System.Windows.Forms.Label
    {
        public Lable()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            // TODO: 在此处添加自定义绘制代码

            // 调用基类 OnPaint
            base.OnPaint(pe);
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
        private string _format = "{0:F2}单位";
        public string Format
        {
            get
            {
                return _format;
            }
            set
            {
                _format = value;
            }
        }
        private string _textName = null;
        public string textName
        {
            get
            {
                return _textName;
            }
            set
            {
                _textName = value;
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
