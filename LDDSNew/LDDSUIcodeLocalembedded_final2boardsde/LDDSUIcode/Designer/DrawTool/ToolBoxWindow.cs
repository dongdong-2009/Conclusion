using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Designer
{
    public partial class ToolBoxWindow : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public ToolBoxWindow()
        {
            InitializeComponent();
        }
        public ToolboxLibrary.Toolbox ToolBox
        {
            get
            {
                return this.toolbox1;
            }
        }
    }
}
