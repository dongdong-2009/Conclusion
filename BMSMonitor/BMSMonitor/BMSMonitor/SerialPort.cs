using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace BMSMonitor
{
    public partial class SerialPortCfg : Form
    {
        public static Int16 serial;
        public SerialPortCfg()
        {
            InitializeComponent();
            Form.CheckForIllegalCrossThreadCalls = false;
        }
        
        private void SPBtnOpen_Click(object sender, EventArgs e)
        {
            Port_Check();
            if (Serial_Params.Serial_Flag == 0)
            {
                SPStatus.BackColor = Color.Green;  
            }
        }

        //DataReceived 事件委托的方法
        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                string currentLine = " ";
                //循环接收串口中的数据
                while (Serial_Params.my_serialPort.BytesToRead > 0)
                {
                    char ch = (char)Serial_Params.my_serialPort.ReadByte();
                    currentLine += ch.ToString();
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message.ToString());
            }
        }

        private void Port_Check()
        {
            try
            {
                //设置串口端口
                Serial_Params.my_serialPort.PortName = SPCmbCom.Text;
                //设置波特率
                Serial_Params.my_serialPort.BaudRate = Convert.ToInt32(SPCmbBaud.Text);

                //设置数据位
                if (SPCmbDataB.SelectedIndex == 0)
                    Serial_Params.my_serialPort.DataBits = 8;
                if (SPCmbDataB.SelectedIndex == 1)
                    Serial_Params.my_serialPort.DataBits = 9;

                //设置校验位
                if (SPCmbDataP.SelectedIndex == 0)
                    Serial_Params.my_serialPort.Parity = Parity.None;
                if (SPCmbDataP.SelectedIndex == 1)
                    Serial_Params.my_serialPort.Parity = Parity.Odd;
                if (SPCmbDataP.SelectedIndex == 2)
                    Serial_Params.my_serialPort.Parity = Parity.Even;

                //设置停止位
                if (SPCmbStopB.SelectedIndex == 0)
                    Serial_Params.my_serialPort.StopBits = StopBits.One;
                if (SPCmbStopB.SelectedIndex == 1)
                    Serial_Params.my_serialPort.StopBits = StopBits.OnePointFive;
                if (SPCmbStopB.SelectedIndex == 2)
                    Serial_Params.my_serialPort.StopBits = StopBits.Two;

                Serial_Params.my_serialPort.DataReceived += new SerialDataReceivedEventHandler(Port_DataReceived);

                Serial_Params.my_serialPort.Open();
                if (Serial_Params.my_serialPort.IsOpen)
                {
                    Serial_Params.Serial_Flag = 0;
                    MessageBox.Show("The port is opened");
                }
                else
                {
                    Serial_Params.Serial_Flag = 1;
                    MessageBox.Show("Failure to open the port");
                }
            }
            catch (Exception ex)
            {
                Serial_Params.Serial_Flag = 1;
                MessageBox.Show("Failure to open the port " + ex.Message.ToString());
            }
        }

        private void Tools_Enable()
        {
            SPCmbCom.Enabled = true;
            SPCmbBaud.Enabled = true;
            SPCmbDataB.Enabled = true;
            SPCmbDataP.Enabled = true;
            SPCmbStopB.Enabled = true;
        }

        private void Tools_Disable()
        {
            SPCmbCom.Enabled = false;
            SPCmbBaud.Enabled = false;
            SPCmbDataB.Enabled = false;
            SPCmbDataP.Enabled = false;
            SPCmbStopB.Enabled = false;
        }

        private void CanBtn_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void SerialPort_Load(object sender, EventArgs e)
        {
            string[] PortList = SerialPort.GetPortNames();
            for (int i = 0; i < PortList.Length; i++)
            {
                string name = PortList[i];
                SPCmbCom.Items.Add(name); 
            }

            SPCmbBaud.SelectedIndex = 6;
            SPCmbDataB.SelectedIndex = 0;
            SPCmbDataP.SelectedIndex = 0;
            SPCmbStopB.SelectedIndex = 0;
            SPCmbName.SelectedIndex = 0;//默认是串口连接方式
        }

        private void SPCmbName_SelectedIndexChanged(object sender, EventArgs e)
        {
            //判断是串口连接还是TCP/IP连接
            if (SPCmbName.SelectedIndex == 0) //串口连接
            {
                Tools_Enable();
                Serial_Params.Modbus_Type = 0;
            }

            if (SPCmbName.SelectedIndex == 1) //TCP/IP连接
            {
                Tools_Disable();
                Serial_Params.Modbus_Type = 1;
            }
        }

        private void RTUrdo_CheckedChanged(object sender, EventArgs e)
        {
            ASCIIrdo.Enabled = false;
            Serial_Params.Modbus_Mode = 0;  //默认是RTU模式
        }

        private void RTUrdo_Click(object sender, EventArgs e)
        {
            RTUrdo.Enabled = true;
            RTUrdo.AutoCheck = false;
            //RTUrdo.Checked = !RTUrdo.Checked;
            if (RTUrdo.Checked == true)
            {
                RTUrdo.Checked = false;
                ASCIIrdo.Enabled = true;
            }
            else
            {
                RTUrdo.Checked = true;
            }
        }

        private void ASCIIrdo_CheckedChanged(object sender, EventArgs e)
        {
            Serial_Params.Modbus_Mode = 1;   //切换成ASCII模式
            RTUrdo.Enabled = false;
        }

        private void ASCIIrdo_Click(object sender, EventArgs e)
        {
            ASCIIrdo.Enabled = true;
            ASCIIrdo.AutoCheck = false;
            //ASCIIrdo.Checked = !ASCIIrdo.Checked;
            if (ASCIIrdo.Checked == true)
            {
                ASCIIrdo.Checked = false;
                RTUrdo.Enabled = true;
            }
            else
            {
                ASCIIrdo.Checked = true;                
            }
        }

        private void ComBtn_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(Restxt.Text) ||string.IsNullOrWhiteSpace(Delaytxt.Text))
            {
                MessageBox.Show("Please fill the data first");
            }
            if (Serial_Params.Serial_Flag == 1)
            {
                MessageBox.Show("Please check the Serial Port first");
            }

            if (RTUrdo.Checked == false && ASCIIrdo.Checked == false)
            {
                MessageBox.Show("Please select the Modbus communicaiton mode first !");
            }

            if (Serial_Params.Serial_Flag == 0 && !string.IsNullOrWhiteSpace(Restxt.Text)&& !string.IsNullOrWhiteSpace(Delaytxt.Text)&&(RTUrdo.Checked==true||ASCIIrdo.Checked==true))
            {
                if (Int16.TryParse(Restxt.Text, out Serial_Params.ReTimeOut))
                {
                    Serial_Params.ReTimeOut = Convert.ToInt16(Restxt.Text);
                }
                if (Int16.TryParse(Delaytxt.Text, out Serial_Params.DelayTime))
                {
                    Serial_Params.DelayTime = Convert.ToInt16(Delaytxt.Text);
                }
                this.Hide();

            }
        }
    }

    public static class Serial_Params
    {
        public static SerialPort my_serialPort = new SerialPort();
        public static Int16 Modbus_Mode = 0;     //mobus通信模式，RTU和ASCII模式，默认是RTU模式
        public static Int16 Serial_Flag = 0;         //串口配置标志位,0表示串口打开正常，1表示串口未打开
        public static Int16 ReTimeOut=1000;              //响应超时时间
        public static Int16 DelayTime=250;               //两次查询间隔时间
        public static Int16 Modbus_Type = 0;  //判断是串口连接还是TCP/IP连接
    }




}
