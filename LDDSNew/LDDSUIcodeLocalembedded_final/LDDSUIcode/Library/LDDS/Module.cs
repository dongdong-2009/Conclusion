using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Library.LDDS
{
    public partial class Module : UserControl
    {
        public Module()
        {
            InitializeComponent();
        }
        private string _interfaceName = "";
        [Description("InterfaceName"), Category("Property")]

        public string InterfaceName
        {
            get
            {
                return _interfaceName;
            }
            set
            {
                _interfaceName = value;
            }
        }

        //定义委托
        public delegate void OnDrawLineEventHandle(object sender, EventArgs e);
        //定义事件
        public event OnDrawLineEventHandle OnDrawLineClick;
        public void Module_DoubleClick(string formName)
        {
            if (OnDrawLineClick != null)
                OnDrawLineClick(this, new Module_DoubleClickEventArgs(formName));
        }
        private string _boardNumber;
        [Description("BoardNumber"), Category("Property")]
        public string BoardNumber   //板号
        {
            get
            {
                return _boardNumber;
            }
            set
            {
                _boardNumber = value;
            }
        }
        private string _name = "";
        [Description("Device Name"), Category("Property")]
        public string DeviceName
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
        private string _type = "";
        [Description("Device Type"), Category("Property")]
        public string RelatedDeviceType
        {
            get
            {
                return _type;
            }
            set
            {
                _type = value;
               
            }
        }
        private void Module_DoubleClick(object sender, EventArgs e)
        {
            this.Module_DoubleClick(InterfaceName);
        }

   
    }

    public class Module_DoubleClickEventArgs : EventArgs
    {
        private string formName;//可以有多个参数
        public Module_DoubleClickEventArgs(string formName)
        {
            this.formName = formName;
        }
        public string FormName
        {
            get { return formName; }
        }
    }

  

}
