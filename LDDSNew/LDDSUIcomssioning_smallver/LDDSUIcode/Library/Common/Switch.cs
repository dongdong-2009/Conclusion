using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing;
using System.Xml.Serialization;
using System.IO;
namespace Library
{
    [ToolboxBitmap(typeof(Switch))]
    public partial class Switch : Control
    {
        private Rectangle rectangele;
        private Image _image1 = null;
        private Image _originalImage1 = null;
        private Image _image2 = null;
        private Image _originalImage2 = null;
        public Switch()
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

        [Description("当条件为true时的图片"), Category("图片")]
        public Image BitOnImage
        {
            get
            {
                return _image1;
            }
            set
            {
                if (this.ClientSize.Width != 0 && this.ClientSize.Height != 0)
                {
                    Rect = new Rectangle(new Point(0, 0), new Size(this.ClientSize.Width, this.ClientSize.Height));
                    _originalImage1 = value;

                    ResizeImage1(rectangele.Width, rectangele.Height);
                    this.Invalidate();
                }
              
            }
        }
        [Description("当条件为false时的图片"), Category("图片")]
        public Image BitOffImage
        {
            get
            {
                return _image2;
            }
            set
            {
                if (this.ClientSize.Width != 0 && this.ClientSize.Height != 0)
                {
                    Rect = new Rectangle(new Point(0, 0), new Size(this.ClientSize.Width, this.ClientSize.Height));
                    _originalImage2 = value;

                    ResizeImage2(rectangele.Width, rectangele.Height);
                    this.Invalidate();
                }
               
            }
        }
        
        public Rectangle Rect
        {
            get
            {
                return rectangele;
            }
            set
            {
                rectangele = value;

            }
        }

        private string _path1 = "";
      
        public string Path1
        {
            get { return _path1; }
            set { _path1 = value; }
        }
        private string _path2 = "";
      
        public string Path2
        {
            get { return _path2; }
            set { _path2 = value; }
        }
        private bool _infront = true;
        [Description("选择当前显示的图片"), Category("图片选择")]
        public bool BitisOn
        {
            get { return _infront; }
            set
            {
                _infront = value;
                this.Invalidate();

            }
        }
        protected void ResizeImage1(int width, int height)
        {
            if (_originalImage1 != null)
            {
                if (width < 1) width = 2;
                if (height < 1) height = 2;
                Bitmap b = new Bitmap(_originalImage1, new Size(width, height));
                _image1 = (Bitmap)b.Clone();
                b.Dispose();
                Path1 = ImageToString(_originalImage1);
            }
        }
        protected void ResizeImage2(int width, int height)
        {
            if (_originalImage2 != null)
            {
                if (width < 1) width = 2;
                if (height < 1) height = 2;
                Bitmap b = new Bitmap(_originalImage2, new Size(width, height));
                _image2 = (Bitmap)b.Clone();
                b.Dispose();
                Path2 = ImageToString(_originalImage2);
            }
        }
        public static string ImageToString(Image img)
        {
            using (MemoryStream stream = new MemoryStream())
            {
               // img.Save(stream, img.RawFormat);
               
                img.Save(stream, System.Drawing.Imaging.ImageFormat.Bmp);

                return Convert.ToBase64String(stream.GetBuffer());
            }
        }
        public static Image StringToImage(string sz)
        {
            byte[] buffer = Convert.FromBase64String(sz);
            MemoryStream stream = new MemoryStream();
            stream.Write(buffer, 0, buffer.Length);
            Bitmap bm = new Bitmap(stream);
            bm.MakeTransparent();

            return Image.FromHbitmap((IntPtr)bm.GetHbitmap());

        }

        private void Switch_Paint(object sender, PaintEventArgs e)
        {
            Graphics _canvas = e.Graphics;
           // GraphicsPath path = new GraphicsPath();
            Rectangle rect = new Rectangle(0, 0, this.ClientSize.Width, this.ClientSize.Height);
            //path.AddRectangle(rc);
           // Rectangle rect = new Rectangle(_startPoint.X, _startPoint.Y, _width, _height);
            if (_path1.Length == 0)
            {
                BitOnImage = new Bitmap("switchon.bmp");
            }
            else
            {
                if (_image1 == null)
                {
                    BitOnImage = (Bitmap)StringToImage(_path1);
                }

            }
            if (_path2.Length == 0)
            {
                BitOffImage = new Bitmap("switchoff.bmp");
            }
            else
            {
                if (_image2 == null)
                {
                    BitOffImage = (Bitmap)StringToImage(_path2);
                }

            }
            if (BitisOn)
            {
                if (_image1 == null)
                {
                }
                else
                {
                    _canvas.DrawImage(_image1, new Point(rect.X, rect.Y));
                    if (Rect.Height != rect.Height || Rect.Width != rect.Width)
                    {
                        ResizeImage1(Rect.Width, Rect.Height);
                        Rect = rect;
                    }
                }

            }
            else
            {
                if (_image2 == null)
                {

                }
                else
                {

                    _canvas.DrawImage(_image2, new Point(rect.X, rect.Y));
                    if (Rect.Height != rect.Height || Rect.Width != rect.Width)
                    {
                        ResizeImage2(Rect.Width, Rect.Height);
                        Rect = rect;
                    }
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
        private string _Name = null;
        public string vName
        {
            get
            {
                return _Name;
            }
            set
            {
                _Name = value;
            }
        }
    }
}
