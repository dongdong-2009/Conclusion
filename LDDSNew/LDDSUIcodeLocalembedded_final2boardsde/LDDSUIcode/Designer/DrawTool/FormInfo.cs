using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
namespace Designer.DrawTool
{
    public class FormInfo
    {
        private string _name = "";
        [Description("Can be changed!"), Category("Name")]
        public string FormName
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
            }
        }
    }
}

