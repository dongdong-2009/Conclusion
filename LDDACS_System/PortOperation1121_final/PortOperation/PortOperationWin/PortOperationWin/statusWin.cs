using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using System.IO.Ports;


namespace PortOperationWin
{
    public partial class statusWin : Form
    {
   
        public MainForm mf;
        private string[] vBaudRate = { "9600", "19200", "38400" };
        private string[] vParity = { "None", "Odd", "Even" };
        private string[] vDataBits = { "8", "7", "6" };
        private string[] vStopBits = { "1", "2", "0" };
        public string[] ports;


        public statusWin(MainForm mainform)
        {
            mf = mainform;
            InitializeComponent();
            ports = System.IO.Ports.SerialPort.GetPortNames();
            sw_parity.Text = "None";
            sw_baudrate.Text = "9600";
            sw_databits.Text = "8";
            sw_stopbits.Text = "One";
            deviceAdd.Text = "5";
            foreach (string port in ports)
            {
                sw_port.Items.Add(port);
            }
            if (PortOperationWin.Boardstatus.PortSelected == 1)
            {
              //  sw_baudrate.SelectedIndex= PortOperationWin.Boardstatus.port.Parity;
                deviceAdd.Text = PortOperationWin.Boardstatus.slaveId.ToString();
                int index = Array.IndexOf(ports,PortOperationWin.Boardstatus.port.PortName);
                sw_port.SelectedIndex=index;
              
                
            }

        }
        private void Form_SerialSetting_Load(object sender, EventArgs e)
        {

                int iPortNum = ports.Length;
                if (iPortNum < 1) //当前电脑不存在可用串口
                {
                    MessageBox.Show(this, "There is no available COM! Please check the hardware!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                 sw_parity.Text   = "None";
                 sw_baudrate.Text = "9600";
                 sw_databits.Text = "8";
                 sw_stopbits.Text = "One";
                 deviceAdd.Text = "5";

        }

        private void btn_reset_Click(object sender, EventArgs e)
        {
            string[] ports =  
                System.IO.Ports.SerialPort.GetPortNames();
            int iPortNum = ports.Length;
            if (iPortNum < 1) //当前电脑不存在可用串口
            {
                MessageBox.Show(this, "There is no available COM! Please check the hardware!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            foreach (string port in ports)
            {
                sw_port.Items.Add(port);
            }

            if (PortOperationWin.Boardstatus.port.IsOpen)
            {
                PortOperationWin.Boardstatus.port.Close();
               
            }
        }
        private void btn_ok_Click(object sender, EventArgs e)
        {
            //存入公共变量
            try
            {
                PortOperationWin.Boardstatus.port.PortName = sw_port.SelectedItem.ToString();
                PortOperationWin.Boardstatus.port.Parity = (Parity)Enum.Parse(typeof(Parity), sw_parity.Text);
                PortOperationWin.Boardstatus.port.BaudRate = int.Parse(sw_baudrate.Text);
                PortOperationWin.Boardstatus.port.DataBits = int.Parse(sw_databits.Text);
                PortOperationWin.Boardstatus.port.StopBits = (StopBits)Enum.Parse(typeof(StopBits), sw_stopbits.Text);

                PortOperationWin.Boardstatus.PortSelected = 1;
                mf.power.currentState = "1";

                if (PortOperationWin.Boardstatus.port.IsOpen == false)
                    PortOperationWin.Boardstatus.port.Open();

                try
                {

                    if (deviceAdd.Text != null)
                        PortOperationWin.Boardstatus.slaveId = byte.Parse(deviceAdd.Text);
                    this.DialogResult = System.Windows.Forms.DialogResult.OK;
                    
                    mf.DO8.Enabled = true;
                    mf.DO7.Enabled = true;
                    mf.DO6.Enabled = true;
                    mf.DO5.Enabled = true;
                    mf.DO4.Enabled = true;
                    mf.DO3.Enabled = true;
                    mf.DO2.Enabled = true;
                    mf.DO1.Enabled = true;

                    mf.AOmodeI8.Enabled = true;
                    mf.AOmodeI6.Enabled = true;
                    mf.AOmodeI4.Enabled = true;
                    mf.AOmodeI2.Enabled = true;
                    mf.AOmodeI7.Enabled = true;
                    mf.AOmodeI5.Enabled = true;
                    mf.AOmodeI3.Enabled = true;
                    mf.AOmodeI1.Enabled = true;

                    mf.AImodeI7.Enabled = true;
                    mf.AImodeI5.Enabled = true;
                    mf.AImodeI12.Enabled = true;
                    mf.AImodeI3.Enabled = true;
                    mf.AImodeI1.Enabled = true;
                    mf.AImodeI9.Enabled = true;
                    mf.AImodeI11.Enabled = true;
                    mf.AImodeI10.Enabled = true;
                    mf.AImodeI8.Enabled = true;
                    mf.AImodeI6.Enabled = true;
                    mf.AImodeI4.Enabled = true;
                    mf.AImodeI2.Enabled = true;

                    mf.AO8.Enabled = true;
                    mf.AO4.Enabled = true;
                    mf.AO7.Enabled = true;
                    mf.AO3.Enabled = true;
                    mf.AO6.Enabled = true;
                    mf.AO2.Enabled = true;
                    mf.AO5.Enabled = true;
                    mf.AO1.Enabled = true;

                    mf.PWM21.Enabled = true;
                    mf.PWM12.Enabled = true;

                    mf.status.currentState = "1";
                    this.Close();
                }
                catch
                {
                    MessageBox.Show("Please keyin the address");
                }
            }
            catch
            {
                MessageBox.Show("Please select the port");
            }
        }

        private void btn_cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
