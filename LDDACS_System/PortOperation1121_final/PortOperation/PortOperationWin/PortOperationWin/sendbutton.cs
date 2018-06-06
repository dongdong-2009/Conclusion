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
    public partial class sendbutton : UserControl
    {

        public string value;
        public event BtnclickHandle UserControlBtnClicked;
        public delegate void BtnclickHandle(object sender, EventArgs e);

        public sendbutton()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, EventArgs e)
        {
            if (UserControlBtnClicked != null)
                UserControlBtnClicked(this, new EventArgs());

        }
    }
}
