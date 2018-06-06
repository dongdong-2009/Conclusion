using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace PortOperationWin
{

    public partial class ModbusWin : Form
    {
        public MainForm mf;
        public string[] ports;
        private Timer timecnt = new Timer();
        private string recdata = null;

        public ModbusWin(MainForm mainform)
        {
            
            timecnt.Interval = 1000;
            timecnt.Tick += new EventHandler(ShowreadData);

            mf = mainform;
            InitializeComponent();
            ports = System.IO.Ports.SerialPort.GetPortNames();
            w_parity.Text = "None";
            w_baudrate.Text = "9600";
            w_databits.Text = "8";
            w_stopbits.Text = "One";
            w_devadd.Text = "7";
            writeadd.Text = "0";

            foreach (string port in ports)
            {
                w_port.Items.Add(port);
            }
        }
        private void ShowreadData(object sender, EventArgs e)
        {
            
            
            for (int i=0;i< PortOperationWin.Boardstatus.UserModbusRevdataI.Length;i++)
                recdata += PortOperationWin.Boardstatus.UserModbusRevdataI[i];
            this.recevalue.Text = recdata;
        }
        private void write_btn_click(object sender, EventArgs e)
        {
            if (PortOperationWin.Boardstatus.PortSelected == 1)
            {
                if ((writeadd.Text == "") | (writevalue.Text == ""))
                    MessageBox.Show("Please key in the write parameters");
                else
                {
                    mf.SetHandle("UserModbusSenddataI", 1);


                    string[] arr = writevalue.Text.Split(' ');

                    for (int i = 0; i <Math.Min (PortOperationWin.Boardstatus.UserModbusSenddataI.Length,arr.Length); i++)
                    {
                        PortOperationWin.Boardstatus.UserModbusSenddataI[i] = arr[i];

                    }
                        
                }
            }
            else
            {
                MessageBox.Show("Please open the status port first");
            }

        }
        private void read_btn_click(object sender, EventArgs e)
        {
            if (PortOperationWin.Boardstatus.PortSelected == 1)
            {
                if (this.readcommand.Text == "Read")
                {
                    this.readcommand.Text = "Stop";
                    PortOperationWin.Boardstatus.userPortReadEn = 1;
                    timecnt.Start();
                }
                else
                {
                    this.readcommand.Text = "Read";
                    PortOperationWin.Boardstatus.userPortReadEn = 0;
                    timecnt.Stop();
                }
            }
            else
            {
                MessageBox.Show("Please open the status port first");

            }
        }
        private void Form_SerialSetting_Load(object sender, EventArgs e)
        {
            //设置默认串口信息
          
            int iPortNum = ports.Length;
            if (iPortNum < 1) //当前电脑不存在可用串口
            {
                MessageBox.Show(this, "There is no available COM! Please check the hardware!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            w_parity.Text = "None";
            w_baudrate.Text = "9600";
            w_databits.Text = "8";
            w_stopbits.Text = "One";
            w_devadd.Text = "7";

        }


        private void btn_open_Click(object sender, EventArgs e)
        {
            //存入公共变量
            try
            {
                if (PortOperationWin.Boardstatus.PortSelected==1)
                {
                    PortOperationWin.Boardstatus.userport.PortName = w_port.SelectedItem.ToString();
                    PortOperationWin.Boardstatus.userport.Parity = (Parity)Enum.Parse(typeof(Parity), w_parity.Text);
                    PortOperationWin.Boardstatus.userport.BaudRate = int.Parse(w_baudrate.Text);
                    PortOperationWin.Boardstatus.userport.DataBits = int.Parse(w_databits.Text);
                    PortOperationWin.Boardstatus.userport.StopBits = (StopBits)Enum.Parse(typeof(StopBits), w_stopbits.Text);
                    PortOperationWin.Boardstatus.userport.Open();
                    PortOperationWin.Boardstatus.userPortSelected = 1;
                    mf.indicator2.currentState = "1";
                }
                else
                {
                    MessageBox.Show("Please open the status port first");
                }
            }
            catch
            {

                MessageBox.Show("Invalid Port");

            }

        }

        private void btn_exit_Click(object sender, EventArgs e)
        {
           
            if (PortOperationWin.Boardstatus.userport.IsOpen)
                PortOperationWin.Boardstatus.userport.Close();

            mf.indicator2.currentState = "0";
            PortOperationWin.Boardstatus.userPortSelected = 0;
            this.Close();

        }
    }
}
