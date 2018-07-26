using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BMSMonitor
{
    public partial class MBConfig : Form
    {
        public MBConfig()
        {
            InitializeComponent();
        }

        private void MBCan_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void MBConOK_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(IDTxt.Text) || string.IsNullOrWhiteSpace(FuncTxt.Text) || string.IsNullOrWhiteSpace(AddrTxt.Text) || string.IsNullOrWhiteSpace(NumTxt.Text) || string.IsNullOrWhiteSpace(ScanTxt.Text))
            {
                MessageBox.Show("Please fill the text first");
            }
            else
            {
                if (byte.TryParse(IDTxt.Text, out MBConfig_Params.Slave_ID))
                {
                    MBConfig_Params.Slave_ID = Convert.ToByte(MBConfig_Params.Slave_ID);
                }
                if (Int16.TryParse(FuncTxt.Text, out MBConfig_Params.Func_Code))
                {
                    MBConfig_Params.Func_Code = Convert.ToInt16(FuncTxt.Text);
                }
                if (ushort.TryParse(AddrTxt.Text, out MBConfig_Params.Start_Addr))
                {
                    MBConfig_Params.Start_Addr = Convert.ToUInt16(AddrTxt.Text);
                }
                if (ushort.TryParse(NumTxt.Text, out MBConfig_Params.Reg_Num))
                {
                    MBConfig_Params.Reg_Num = Convert.ToUInt16(NumTxt.Text);
                }
                if (Int16.TryParse(ScanTxt.Text, out MBConfig_Params.Scan_Rate))
                {
                    MBConfig_Params.Scan_Rate = Convert.ToInt16(ScanTxt.Text);
                }

                this.Hide();
            }
        }
    
    }

    public static class MBConfig_Params
    {
        public static byte Slave_ID;
        public static Int16 Func_Code;
        public static ushort Start_Addr;
        public static ushort Reg_Num=1;
        public static Int16 Scan_Rate;
    }
}
