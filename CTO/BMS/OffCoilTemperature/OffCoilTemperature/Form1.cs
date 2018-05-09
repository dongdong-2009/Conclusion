using Modbus.Device;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//using static System.Windows.Forms.DataGrid;

namespace OffCoilTemperature
{
    public partial class Form1 : Form
    {
        private SerialPort _SerialPort;
        private Timer _Timer;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            if (this.Height> 60)
            {
                splitContainer1.SplitterDistance = 40;
            }
            
        }

        private void btn_Start_Click(object sender, EventArgs e)
        {
            Button button = sender as Button;
            if (!_Timer.Enabled)
            {
                chart1.Series[0].Points.Clear();
                if (chk_ShowValue.Checked)
                {
                    chart1.Series[0].Label = "#VALY";
                }
                else
                {
                    chart1.Series[0].Label = "";
                }
                
                _Timer.Enabled = true;
                _Timer.Start();
                button.Text = "Stop";
            }
            else
            {
                _Timer.Enabled = false;
                _Timer.Stop();
                button.Text = "Start";
            }
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _Timer = new Timer();
            _Timer.Interval = 1000;
            _Timer.Tick += _Timer_Tick;

            SetChart(chart1, 2);
            chart1.ChartAreas["ChartArea1"].AxisX.LabelStyle.Format = "HH:mm:ss";
            //chart1.ChartAreas["ChartArea1"].AxisX.ScrollBar.Enabled = true;
            //// 设置滚动条的大小
            //chart1.ChartAreas["ChartArea1"].AxisX.ScrollBar.Size = 10;
            //chart1.ChartAreas[0].AxisX.ScrollBar.IsPositionedInside = true;

            GetComList(comboBox1);
            
        }
        private ushort ModbusReadValue(string com, ushort startAddress)
        {
            try
            {
                ushort readValue = 0;
                using (SerialPort port = new SerialPort(com))
                {
                    // configure serial port
                    port.BaudRate = 9600;
                    port.DataBits = 8;
                    port.Parity = Parity.None;
                    port.StopBits = StopBits.One;
                    port.Open();


                    // create modbus master
                    IModbusSerialMaster master = ModbusSerialMaster.CreateRtu(port);
                    master.Transport.ReadTimeout = 2000;
                    byte slaveId = 1;
                    ushort numOfPoints = 1;

                    ushort[] values = master.ReadHoldingRegisters(slaveId, startAddress, numOfPoints);
                    readValue = values[0];
                    Console.WriteLine("{0}, 当前读取到数值：{1};", DateTime.Now.ToString(), readValue);
                }
                return readValue;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                System.IO.File.AppendAllText("log.txt", "\r\n Read TimeOut Exception:" + ex.Message.ToString());
                return 0;
            }
        }
        private void _Timer_Tick(object sender, EventArgs e)
        {
            ushort value = 0;
            value = ModbusReadValue(comboBox1.Text, Convert.ToUInt16( tb_StartAddress.Text.Trim()));
            double val = (double)value / 10;
            //不能在下面两条曲线中直接使用DateTime.Now
            //直接使用会产生两个X轴的量，会报错
            //DateTime now = DateTime.Now;
            //Random rand = new Random();
            //rand.Next(0, 100);

            DateTime now = DateTime.Now;
            chart1.Series[0].Points.AddXY(now, val);
            

            //清理一段时间之前的数据
            TimeSpan timeSpan = DateTime.FromOADate(chart1.Series[0].Points.ElementAt(0).XValue).TimeOfDay;
            int showRangeSec = now.TimeOfDay.Seconds - timeSpan.Seconds;
            if (showRangeSec > 600) 
            {
                chart1.Series[0].Points.RemoveAt(0);
            }
            // chart1.Series[1].Points.AddXY(now, rand.Next(0, 100));
            //   chart1.ChartAreas[0].AxisX.ScaleView.Position = chart1.Series[0].Points.Count - 5;
            if (MouseButtons != System.Windows.Forms.MouseButtons.Left)
            {
                //水平滚动条始终居于最右边
                chart1.ChartAreas["ChartArea1"].AxisX.ScaleView.Scroll(System.Windows.Forms.DataVisualization.Charting.ScrollType.Last);
                chart1.Update();
            }
            
        }
        private void SetChart(System.Windows.Forms.DataVisualization.Charting.Chart chart, Int32 iTimeInterval)
        {
            chart.ChartAreas["ChartArea1"].CursorX.AutoScroll = true;
            chart.ChartAreas["ChartArea1"].AxisX.ScrollBar.Enabled = true;
            chart.ChartAreas["ChartArea1"].CursorX.IsUserEnabled = true;
            chart.ChartAreas["ChartArea1"].CursorX.IsUserSelectionEnabled = true;
            chart.ChartAreas["ChartArea1"].AxisX.Interval = iTimeInterval;
            chart.ChartAreas["ChartArea1"].AxisX.ScaleView.Zoomable = true;
            chart.ChartAreas["ChartArea1"].AxisX.ScaleView.Position = 0;
            chart.ChartAreas["ChartArea1"].AxisX.ScaleView.Size = iTimeInterval * 10;
        }

        #region [获取串口列表]

        /// <summary>
        /// 获取串口列表
        /// </summary>
        /// <returns>返回系统可用的串口列表，如：COM1，COM2</returns>
        public IList<string> GetComList()
        {
            Microsoft.Win32.RegistryKey keyCom = Microsoft.Win32.Registry.LocalMachine.OpenSubKey("Hardware\\DeviceMap\\SerialComm");
            List<string> list = new List<string>();
            if (keyCom != null)
            {
                string[] sSubKeys = keyCom.GetValueNames();
                foreach (string sName in sSubKeys)
                {
                    string sValue = (string)keyCom.GetValue(sName);
                    list.Add(sValue);
                }
            }
            return list;
        }

        /// <summary>
        /// 获取串口列表，添加到ComboBox控件中
        /// </summary>
        /// <param name="comboBox">选择串口的ComboBox控件</param>
        /// <param name="cacheCom">上次缓存的串口号，如："COM1"，默认为空</param>
        public void GetComList(ComboBox comboBox, string cacheCom="")
        {
            Microsoft.Win32.RegistryKey keyCom = Microsoft.Win32.Registry.LocalMachine.OpenSubKey("Hardware\\DeviceMap\\SerialComm");
            if (keyCom != null)
            {
                string[] sSubKeys = keyCom.GetValueNames();
                foreach (string sName in sSubKeys)
                {
                    string sValue = (string)keyCom.GetValue(sName);
                    comboBox.Items.Add(sValue);
                }
                //cacheCom为空，现有串口列表的第一个作为当前串口；
                //cacheCom不为空，在现有串口列表查找与之匹配的，作为当前串口，否则，选择第一个；
                comboBox.SelectedIndex = 0;
                if (cacheCom != string.Empty)
                {
                    for (int i = 0; i < comboBox.Items.Count; i++)
                    {
                        if (comboBox.Items[i].ToString() == cacheCom)
                        {
                            comboBox.SelectedIndex = i;
                            break;
                        }
                    }
                }
            }
        }
        #endregion

        private void chart1_MouseMove(object sender, MouseEventArgs e)
        {
            
        }
    }
}
