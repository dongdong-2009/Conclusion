using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Library.Common
{
    public partial class NumTextbox : TextBox
    {
        public NumTextbox()
        {
            InitializeComponent();
          //  NumTextbox_KeyDown += new System.EventHandler(this.button1_Click);
        }
        private bool nonNumberEntered = false;
        private void NumTextbox_KeyDown(object sender, KeyEventArgs e)
        {
            nonNumberEntered = false;
            if ((e.KeyCode < Keys.D0) || (e.KeyCode > Keys.D9 && e.KeyCode < Keys.NumPad0) || (e.KeyCode > Keys.NumPad9))
            {
                if (e.KeyCode != Keys.Back)
                {
                    nonNumberEntered = true;
                }
            }
        }

        private void NumTextbox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (nonNumberEntered)
            {
                e.Handled = true;
            }
        }
    }
}
