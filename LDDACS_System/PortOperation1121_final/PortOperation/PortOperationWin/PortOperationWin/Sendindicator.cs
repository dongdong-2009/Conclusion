using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PortOperationWin
{
    public partial class Sendindicator : UserControl
    {
        public string currentState = "0";
        private Bitmap bitMapOn = Properties.Resources.button_glossy_yellowtras;
        private Bitmap bitMapOff = Properties.Resources.button_glossy_bluetrans;
        public delegate void BtnclickHandle(object sender, EventArgs e);
        public event BtnclickHandle UserControlBtnClicked;

        public Sendindicator()
        {
            InitializeComponent();
            //设置Style支持透明背景色并且双缓冲
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.DoubleBuffer, true);
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            this.SetStyle(ControlStyles.Selectable, true);
            this.SetStyle(ControlStyles.SupportsTransparentBackColor, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            this.BackColor = Color.Transparent;
        }

        private void button_Click(object sender, EventArgs e)
        {
            if (currentState == "0")
            {
                currentState = "1";
            }
            else
            {
                currentState = "0";
            }
  
            this.Invalidate();
            if (UserControlBtnClicked != null)
                UserControlBtnClicked(this, new EventArgs());
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Rectangle rec = new Rectangle(this.button1.Height, 0, this.Height-3, this.Height - 3);

            if (currentState == "1")
            {
                g.DrawImage(bitMapOn, rec);
           //     this.indicator1.data = "1";
            }
            else
            {
                g.DrawImage(bitMapOff, rec);
               // this.indicator1.data = "0";
            }
            base.OnPaint(e);

        }
    }
}
