using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace PortOperationWin
{
    public partial class Vo_AmV : UserControl
    {
        public string currentState = "0";
        private Bitmap bitMapOn = Properties.Resources.selectorb1;
        private Bitmap bitMapOff = Properties.Resources.selector_switchb2;
        public string rtdm;

        public Vo_AmV()
        {
            InitializeComponent();
            SetStyle(ControlStyles.SupportsTransparentBackColor
                     | ControlStyles.UserPaint
                     | ControlStyles.AllPaintingInWmPaint, true);
        }
        protected override void OnPaint(PaintEventArgs pe)
        {
            Graphics g = pe.Graphics;
            Rectangle rec = new Rectangle(0, 0, this.Size.Width, this.Size.Height);

            if (currentState == "1")
            {
                g.DrawImage(bitMapOn, rec);
            }
            else
            {
                g.DrawImage(bitMapOff, rec);
            }

            base.OnPaint(pe);
        }

        private void Vo_AmV_Click(object sender, EventArgs e)
        {
            if (currentState == "0")
            {
                currentState = "1";
            }
            else
            {
                currentState = "0";
            }
            //   dataSend.SendButtonCheckData(RelatedPort, PortBind, BoardNumber, currentState);
            this.Invalidate();
        }
    }
}
