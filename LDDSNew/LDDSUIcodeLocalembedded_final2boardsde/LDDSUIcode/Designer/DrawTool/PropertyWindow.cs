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
    public partial class PropertyWindow : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public PropertyWindow()
        {
            InitializeComponent();
        }

        public PropertyGridEx.PropertyGridEx propertyGrid
        {
            get
            {
                return this.propertyGridEx1;
            }
        }
    }
}
