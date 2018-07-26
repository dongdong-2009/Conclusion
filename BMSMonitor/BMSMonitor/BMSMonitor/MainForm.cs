using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Modbus.Device;
using System.IO.Ports;
using System.Timers;
using System.Threading;


namespace BMSMonitor
{
    public partial class MainForm : Form
    {
      
        public MainForm()
        {
            InitializeComponent();
        }

        System.Timers.Timer My_Timer2 = new System.Timers.Timer(1000);
        IModbusSerialMaster master = ModbusSerialMaster.CreateRtu(Serial_Params.my_serialPort);
        private void DO1lbl_Click(object sender, EventArgs e)
        {
            if (DO1lbl.BackColor == Color.Green)
            { 
                DO1lbl.BackColor = Color.Gray;
                GlobalPramas.DO1_Value = 0;
            }
            else if (DO1lbl.BackColor == Color.Gray)
            {
                DO1lbl.BackColor = Color.Green;
                GlobalPramas.DO1_Value = 1;
            }       
        }

        private void DO2lbl_Click(object sender, EventArgs e)
        {
            if (DO2lbl.BackColor == Color.Green)
            {
                DO2lbl.BackColor = Color.Gray;
                GlobalPramas.DO2_Value = 0;
            }
            else if (DO2lbl.BackColor == Color.Gray)
            {
                DO2lbl.BackColor = Color.Green;
                GlobalPramas.DO2_Value = 1;
            }   
        }

        private void DO3lbl_Click(object sender, EventArgs e)
        {
            if (DO3lbl.BackColor == Color.Green)
            {
                DO3lbl.BackColor = Color.Gray;
                GlobalPramas.DO3_Value = 0;
            }
            else if (DO3lbl.BackColor == Color.Gray)
            {
                DO3lbl.BackColor = Color.Green;
                GlobalPramas.DO3_Value = 1;
            }   
        }

        private void DO4lbl_Click(object sender, EventArgs e)
        {
            if (DO4lbl.BackColor == Color.Green)
            {
                DO4lbl.BackColor = Color.Gray;
                GlobalPramas.DO4_Value = 0;
            }
            else if (DO4lbl.BackColor == Color.Gray)
            {
                DO4lbl.BackColor = Color.Green;
                GlobalPramas.DO4_Value = 1;
            }   
        }

        private void serialToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SerialPortCfg SPset = new SerialPortCfg();
            SPset.Show();
        }

        private void configToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MBConfig ModbusConfig = new MBConfig();
            ModbusConfig.Show();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            InitTimer1();
            InitTimer2();
        }

        private void My_Timer1_Elapsed(object sender, EventArgs e)
        {
            ModbusReadValue();
        }

        private void InitTimer1()
        {
            //设置Timer空间可用，已经定时时间，1000ms 
            System.Timers.Timer My_Timer1 = new System.Timers.Timer(1000);
            My_Timer1.Enabled = true;
            My_Timer1.AutoReset = true;   //是否不断重复定时器操作
            My_Timer1.Elapsed+=My_Timer1_Elapsed;  //绑定出发事件
        }

        private void ModbusReadValue()
        {
            try
            {
                if (Serial_Params.Modbus_Type == 0)
                {
                    if (Serial_Params.Serial_Flag == 0)
                    {
                        if (Serial_Params.Modbus_Mode == 0)
                        {
                            //create modbus master
                              //IModbusSerialMaster master = ModbusSerialMaster.CreateRtu(Serial_Params.my_serialPort);

                            //配置参数
                            master.Transport.ReadTimeout = Serial_Params.ReTimeOut;  //读取串口超时时间  1000ms
                            master.Transport.WriteTimeout = 1000;                                    //写入串口超时时间 1000ms
                            master.Transport.Retries = 3;                                                    //重试间隔次数 3次
                            master.Transport.WaitToRetryMilliseconds = Serial_Params.DelayTime;                //重试时间间隔  250ms

                            GlobalPramas.DataRead = master.ReadHoldingRegisters(MBConfig_Params.Slave_ID, MBConfig_Params.Start_Addr, MBConfig_Params.Reg_Num);
                        }
                        if (Serial_Params.Modbus_Mode == 1)
                        {
                            //IModbusSerialMaster master = ModbusSerialMaster.CreateAscii(Serial_Params.my_serialPort);
                            MessageBox.Show("Please select the RTU Mode, not support the ASCII Mode");
                        }
                    }
                    if (Serial_Params.Serial_Flag == 1)
                    {
                        MessageBox.Show("Please check the Serial Port first");
                    }
                }
                if (Serial_Params.Modbus_Type == 1)
                {
                    MessageBox.Show("Please select the Serial Port, not support the TCP/IP Connection");
                }
            }
            catch (Exception ex)
            {
                 //MessageBox.Show(ex.Message);
                System.IO.File.AppendAllText("log.txt", "\r\n Read TimeOut Exception:" + ex.Message.ToString());
            }
        }


        public void InitTimer2()
        {
            //设置Timer空间可用，已经定时时间，500ms 
            My_Timer2.Enabled = false;        //是否触发Elapsed事件
            My_Timer2.AutoReset = false;   //是否不断重复定时器操作，执行一次(false),一直执行(true)
            My_Timer2.Elapsed += My_Timer2_Elapsed;  //绑定出发事件
        }

        private void My_Timer2_Elapsed(object sender, ElapsedEventArgs e)
        {
            DataProcess();
            DataDisplay();
        }

        //数据处理
        private void DataProcess()
        {
            //Address0-9,only read
            GlobalPramas.AI_Ch1_Value = (GlobalPramas.DataRead[0]/10.0);
            GlobalPramas.AI_Ch2_Value = (GlobalPramas.DataRead[1] /10.0);
            GlobalPramas.AI_Ch3_Value = (GlobalPramas.DataRead[2] / 10.0);
            GlobalPramas.AI_Ch4_Value = (GlobalPramas.DataRead[3] / 10.0);
            GlobalPramas.AI_Ch5_Value = (GlobalPramas.DataRead[4] / 10.0);
            GlobalPramas.AI_Ch6_Value = (GlobalPramas.DataRead[5] / 10.0);

            GlobalPramas.DI1_Value = (GlobalPramas.DataRead[6]);
            GlobalPramas.DI2_Value = (GlobalPramas.DataRead[7]);
            GlobalPramas.DI3_Value = (GlobalPramas.DataRead[8]);
            GlobalPramas.DI4_Value = (GlobalPramas.DataRead[9]);

            //Address 10-24 can read/write
            GlobalPramas.AO_Ch1_Value = (GlobalPramas.DataRead[10] /10.0);
            GlobalPramas.AO_Ch1_Value = (GlobalPramas.DataRead[11] / 10.0);
            GlobalPramas.AO_Ch1_Value = (GlobalPramas.DataRead[12] / 10.0);
            GlobalPramas.AO_Ch1_Value = (GlobalPramas.DataRead[13] / 10.0);

            GlobalPramas.DO1_Value=GlobalPramas.DataRead[14];
            GlobalPramas.DO2_Value = GlobalPramas.DataRead[15];
            GlobalPramas.DO3_Value = GlobalPramas.DataRead[16];
            GlobalPramas.DO4_Value = GlobalPramas.DataRead[17];

            GlobalPramas.PWM1_Cycle = GlobalPramas.DataRead[18];
            GlobalPramas.PWM1_Duty = GlobalPramas.DataRead[19];
            GlobalPramas.PWM2_Cycle = GlobalPramas.DataRead[20];
            GlobalPramas.PWM2_Duty = GlobalPramas.DataRead[21];

            GlobalPramas.Start_Comm = GlobalPramas.DataRead[22];
            GlobalPramas.Stop_Comm = GlobalPramas.DataRead[23];
            GlobalPramas.SetValue = (GlobalPramas.DataRead[24] / 10.0);
        }

        private void DataDisplay()
        {
            AI1Tb.Text=GlobalPramas.AI_Ch1_Value.ToString();
            AI2Tb.Text = GlobalPramas.AI_Ch2_Value.ToString();
            AI3Tb.Text = GlobalPramas.AI_Ch3_Value.ToString();
            AI4Tb.Text = GlobalPramas.AI_Ch4_Value.ToString();
            AI5Tb.Text = GlobalPramas.AI_Ch5_Value.ToString();
            AI6Tb.Text = GlobalPramas.AI_Ch6_Value.ToString();

            if (GlobalPramas.DI1_Value == 1)
            {
                DI1lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DI1_Value == 0)
            {
                DI1lbl.BackColor = Color.Gray;
            }

            if (GlobalPramas.DI2_Value == 1)
            {
                DI2lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DI2_Value == 0)
            {
                DI2lbl.BackColor = Color.Gray;
            }

            if (GlobalPramas.DI3_Value == 1)
            {
                DI3lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DI3_Value == 0)
            {
                DI3lbl.BackColor = Color.Gray;
            }

            if (GlobalPramas.DI4_Value == 1)
            {
                DI4lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DI4_Value == 0)
            {
                DI4lbl.BackColor = Color.Gray;
            }
            AO1Tb.Text = GlobalPramas.AO_Ch1_Value.ToString();
            AO2Tb.Text = GlobalPramas.AO_Ch2_Value.ToString();
            AO3Tb.Text = GlobalPramas.AO_Ch3_Value.ToString();
            AO4Tb.Text = GlobalPramas.AO_Ch4_Value.ToString();

            if (GlobalPramas.DO1_Value == 1)
            {
                DO1lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DO1_Value == 0)
            {
                DO1lbl.BackColor = Color.Gray;
            }

            if (GlobalPramas.DO2_Value == 1)
            {
                DO2lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DO2_Value == 0)
            {
                DO2lbl.BackColor = Color.Gray;
            }

            if (GlobalPramas.DO3_Value == 1)
            {
                DO3lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DO3_Value == 0)
            {
                DO3lbl.BackColor = Color.Gray;
            }

            if (GlobalPramas.DO4_Value == 1)
            {
                DO4lbl.BackColor = Color.Green;
            }
            else if (GlobalPramas.DO4_Value == 0)
            {
                DO4lbl.BackColor = Color.Gray;
            }

            PWMCycTb1.Text = GlobalPramas.PWM1_Cycle.ToString();
            PWMDutyTb1.Text = GlobalPramas.PWM1_Duty.ToString();
            PWMCycTb2.Text = GlobalPramas.PWM2_Cycle.ToString();
            PWMDutyTb2.Text = GlobalPramas.PWM2_Duty.ToString();

            if (GlobalPramas.Start_Comm == 1)
            {
                BMStart.BackColor = Color.Green;
                GlobalPramas.Stop_Comm = 0;
                BMStop.BackColor = Color.Gray;
            }
            else if (GlobalPramas.Start_Comm == 0)
            {
                BMStart.BackColor = Color.Gray;
            }

            if (GlobalPramas.Stop_Comm == 1)
            {
                BMStop.BackColor = Color.Green;
                GlobalPramas.Start_Comm = 0;
                BMStart.BackColor = Color.Gray;
            }
            else if (GlobalPramas.Stop_Comm == 0)
            {
                BMStop.BackColor = Color.Gray;
            }

            if (GlobalPramas.Start_Comm == 1 && GlobalPramas.Stop_Comm == 1)
            {
                MessageBox.Show("Please check the BMS start and stop command");
            }

            BMSetVal.Text = GlobalPramas.SetValue.ToString();
        }


        private void ModeRead_Click(object sender, EventArgs e)
        {
            My_Timer2.Enabled = true;
            My_Timer2.Start();
        }

        private void WritePackage()
        {
            try
            {
                System.Threading.Thread.Sleep(10000);
                DataCheck();
                if ((GlobalPramas.PWM1_Cycle < GlobalPramas.PWM1_Duty) || (GlobalPramas.PWM2_Cycle < GlobalPramas.PWM2_Duty))
                {
                    MessageBox.Show("Please check the PWM Set Value");
                }
                if ((GlobalPramas.PWM1_Cycle >= GlobalPramas.PWM1_Duty) && (GlobalPramas.PWM2_Cycle >= GlobalPramas.PWM2_Duty))
                {
                    GlobalPramas.DataWrite[0] = Convert.ToUInt16(GlobalPramas.AO_Ch1_Value);
                    GlobalPramas.DataWrite[1] = Convert.ToUInt16(GlobalPramas.AO_Ch2_Value);
                    GlobalPramas.DataWrite[2] = Convert.ToUInt16(GlobalPramas.AO_Ch3_Value);
                    GlobalPramas.DataWrite[3] = Convert.ToUInt16(GlobalPramas.AO_Ch4_Value);
                    GlobalPramas.DataWrite[4] = GlobalPramas.DO1_Value;
                    GlobalPramas.DataWrite[5] = GlobalPramas.DO1_Value;
                    GlobalPramas.DataWrite[6] = GlobalPramas.DO1_Value;
                    GlobalPramas.DataWrite[7] = GlobalPramas.DO1_Value;
                    GlobalPramas.DataWrite[8] = GlobalPramas.PWM1_Cycle;
                    GlobalPramas.DataWrite[9] = GlobalPramas.PWM1_Duty;
                    GlobalPramas.DataWrite[10] = GlobalPramas.PWM2_Cycle;
                    GlobalPramas.DataWrite[11] = GlobalPramas.PWM2_Duty;
                    GlobalPramas.DataWrite[12] = GlobalPramas.Start_Comm;
                    GlobalPramas.DataWrite[13] = GlobalPramas.Stop_Comm;
                    GlobalPramas.DataWrite[14] = Convert.ToUInt16(GlobalPramas.SetValue);
                }
                //create modbus master
               // IModbusSerialMaster master = ModbusSerialMaster.CreateRtu(Serial_Params.my_serialPort);

                //配置参数
                master.Transport.ReadTimeout = Serial_Params.ReTimeOut;  //读取串口超时时间  1000ms
                master.Transport.WriteTimeout = 1000;                                    //写入串口超时时间 1000ms
                master.Transport.Retries = 3;                                                    //重试间隔次数 3次
                master.Transport.WaitToRetryMilliseconds = Serial_Params.DelayTime;                //重试时间间隔  250ms
                master.WriteMultipleRegisters(MBConfig_Params.Slave_ID, MBConfig_Params.Start_Addr, GlobalPramas.DataWrite);
                //master.WriteSingleRegister(MBConfig_Params.Slave_ID, MBConfig_Params.Start_Addr, GlobalPramas.DataWrite[0]);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void DataCheck()
        {
            if (GlobalPramas.Stop_Comm == 1 && GlobalPramas.Start_Comm == 1)
            {
                MessageBox.Show("Please check the BMS start and stop command");
            }

            if (AO1Tb.Text.ToString() != GlobalPramas.AO_Ch1_Value.ToString())
            {
                if (ushort.TryParse(AO1Tb.Text, out GlobalPramas.AODataWrite[0]))
                {
                    GlobalPramas.AODataWrite[0] = Convert.ToUInt16(AO1Tb.Text);
                    GlobalPramas.AO_Ch1_Value = GlobalPramas.AODataWrite[0] * 10.0;
                }
            }

            if (AO2Tb.Text.ToString() != GlobalPramas.AO_Ch2_Value.ToString())
            {
                if (ushort.TryParse(AO2Tb.Text, out GlobalPramas.AODataWrite[1]))
                {
                    GlobalPramas.AODataWrite[1] = Convert.ToUInt16(AO2Tb.Text);
                    GlobalPramas.AO_Ch2_Value = GlobalPramas.AODataWrite[1] * 10.0;
                }
            }

            if (AO3Tb.Text.ToString() != GlobalPramas.AO_Ch3_Value.ToString())
            {
                if (ushort.TryParse(AO3Tb.Text, out GlobalPramas.AODataWrite[2]))
                {
                    GlobalPramas.AODataWrite[2] = Convert.ToUInt16(AO3Tb.Text);
                    GlobalPramas.AO_Ch3_Value = GlobalPramas.AODataWrite[2] * 10.0;
                }
            }

            if (AO4Tb.Text.ToString() != GlobalPramas.AO_Ch4_Value.ToString())
            {
                if (ushort.TryParse(AO4Tb.Text, out GlobalPramas.AODataWrite[3]))
                {
                    GlobalPramas.AODataWrite[3] = Convert.ToUInt16(AO4Tb.Text);
                    GlobalPramas.AO_Ch4_Value = GlobalPramas.AODataWrite[3] * 10.0;
                }
            }

            if (PWMCycTb1.Text.ToString() != GlobalPramas.PWM1_Cycle.ToString())
            {
                if (ushort.TryParse(PWMCycTb1.Text, out GlobalPramas.PWMDataWrite[0]))
                {
                    GlobalPramas.PWMDataWrite[0] = Convert.ToUInt16(PWMCycTb1.Text);
                    GlobalPramas.PWM1_Cycle = Convert.ToUInt16(GlobalPramas.PWMDataWrite[0] *10);
                }
            }

            if (PWMDutyTb1.Text.ToString() != GlobalPramas.PWM1_Duty.ToString())
            {
                if (ushort.TryParse(PWMDutyTb1.Text, out GlobalPramas.PWMDataWrite[1]))
                {
                    GlobalPramas.PWMDataWrite[1] = Convert.ToUInt16(PWMDutyTb1.Text);
                    GlobalPramas.PWM1_Duty = Convert.ToUInt16(GlobalPramas.PWMDataWrite[1] * 10);
                }
            }

            if (PWMCycTb2.Text.ToString() != GlobalPramas.PWM2_Cycle.ToString())
            {
                if (ushort.TryParse(PWMCycTb2.Text, out GlobalPramas.PWMDataWrite[2]))
                {
                    GlobalPramas.PWMDataWrite[2] = Convert.ToUInt16(PWMCycTb2.Text);
                    GlobalPramas.PWM2_Cycle = Convert.ToUInt16(GlobalPramas.PWMDataWrite[2] * 10);
                }
            }

            if (PWMDutyTb2.Text.ToString() != GlobalPramas.PWM2_Duty.ToString())
            {
                if (ushort.TryParse(PWMDutyTb2.Text, out GlobalPramas.PWMDataWrite[3]))
                {
                    GlobalPramas.PWMDataWrite[3] = Convert.ToUInt16(PWMDutyTb2.Text);
                    GlobalPramas.PWM2_Duty = Convert.ToUInt16(GlobalPramas.PWMDataWrite[3] * 10);
                }
            }

            if (BMSetVal.Text.ToString() != GlobalPramas.SetValue.ToString())
            {
                if (ushort.TryParse(BMSetVal.Text, out GlobalPramas.CmdDataWrite[3]))
                {
                    GlobalPramas.CmdDataWrite[3] = Convert.ToUInt16(BMSetVal.Text);
                    GlobalPramas.SetValue = GlobalPramas.CmdDataWrite[3] * 10.0;
                }
            }

        }

        private void BMStart_Click(object sender, EventArgs e)
        {
            if (BMStart.BackColor == Color.Green)
            {
                BMStart.BackColor = Color.Gray;
                GlobalPramas.Start_Comm = 0;
            }
            else if (BMStart.BackColor == Color.Gray)
            {
                BMStart.BackColor = Color.Green;
                GlobalPramas.Start_Comm = 1;
            }    
        }

        private void BMStop_Click(object sender, EventArgs e)
        {
            if (BMStop.BackColor == Color.Green)
            {
                BMStop.BackColor = Color.Gray;
                GlobalPramas.Stop_Comm = 0;
            }
            else if (BMStop.BackColor == Color.Gray)
            {
                BMStop.BackColor = Color.Green;
                GlobalPramas.Stop_Comm = 1;
            } 
        }

        private void ModeWrite_Click(object sender, EventArgs e)
        {
            CheckForIllegalCrossThreadCalls = false;
            Application.DoEvents();
            WritePackage(); 
        }

        private void AI1RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if (AI1RdbU.Checked == true)
            {
                AI1RdbI.Enabled = false;
                AI1lblmin.Text = "0V";
                AI1lblmax.Text = "10V";
                AI1Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch1_Value);
            }
            else if (AI1RdbU.Checked == false)
            {
                AI1RdbI.Enabled = true;
            }
        }

        private void AI1RdbU_Click(object sender, EventArgs e)
        {
            AI1RdbU.Enabled = true;
            AI1RdbU.AutoCheck = false;
            AI1RdbU.Checked = !AI1RdbU.Checked;
        }

        private void AI1RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if (AI1RdbI.Checked == true)
            {
                AI1RdbU.Enabled = false;
                AI1lblmin.Text = "0mA";
                AI1lblmax.Text = "20mA";
                AI1Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch1_Value);
            }
            else if(AI1RdbI.Checked==false)
            {
                AI1RdbU.Enabled = true;
            }
        }

        private void AI1RdbI_Click(object sender, EventArgs e)
        {
            AI1RdbI.Enabled = true;
            AI1RdbI.AutoCheck = false;
            AI1RdbI.Checked = !AI1RdbI.Checked;
        }

        private void AI2RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if (AI2RdbU.Checked == true)
            {
                AI2RdbI.Enabled = false;
                AI2lblmin.Text = "0V";
                AI2lblmax.Text = "10V";
                AI2Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch2_Value);
            }
            else if (AI2RdbU.Checked == false)
            {
                AI2RdbI.Enabled = true;
            }
        }

        private void AI2RdbU_Click(object sender, EventArgs e)
        {
            AI2RdbU.Enabled = true;
            AI2RdbU.AutoCheck = false;
            AI2RdbU.Checked = !AI2RdbU.Checked;
        }

        private void AI2RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if (AI2RdbI.Checked == true)
            {
                AI2RdbU.Enabled = false;
                AI2lblmin.Text = "0mA";
                AI2lblmax.Text = "20mA";
                AI2Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch2_Value);
            }
            else if (AI2RdbI.Checked == false)
            {
                AI2RdbU.Enabled = true;
            }
        }

        private void AI2RdbI_Click(object sender, EventArgs e)
        {
            AI2RdbI.Enabled = true;
            AI2RdbI.AutoCheck = false;
            AI2RdbI.Checked = !AI2RdbI.Checked;
        }

        private void AI3RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if(AI3RdbU.Checked==true)
            {
                AI3RdbI.Enabled = false;
                AI3lblmin.Text = "0V";
                AI3lblmax.Text = "10V";
                AI3Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch3_Value);
            }
            else if (AI3RdbU.Checked == false)
            {
                AI3RdbI.Enabled = true;
            }
        }

        private void AI3RdbU_Click(object sender, EventArgs e)
        {
            AI3RdbU.Enabled = true;
            AI3RdbU.AutoCheck = false;
            AI3RdbU.Checked = !AI3RdbU.Checked;
        }

        private void AI3RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if(AI3RdbI.Checked==true)
            {
                AI3RdbU.Enabled = false;
                AI3lblmin.Text = "0mA";
                AI3lblmax.Text = "20mA";
                AI3Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch3_Value);
            }
            else if(AI3RdbI.Checked==false)
            {
                AI3RdbU.Enabled = true;
            }
        }

        private void AI3RdbI_Click(object sender, EventArgs e)
        {
            AI3RdbI.Enabled = true;
            AI3RdbI.AutoCheck = false;
            AI3RdbI.Checked = !AI3RdbI.Checked;
        }

        private void AI4RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if(AI4RdbU.Checked==true)
            {
                AI4RdbI.Enabled = false;
                AI4lblmin.Text = "0V";
                AI4lblmax.Text = "10V";
                AI4Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch4_Value);
            }
            else if(AI4RdbU.Checked==false)
            {
                AI4RdbI.Enabled = true;
            }
        }

        private void AI4RdbU_Click(object sender, EventArgs e)
        {
            AI4RdbU.Enabled = true;
            AI4RdbU.AutoCheck = false;
            AI4RdbU.Checked = !AI4RdbU.Checked;
        }

        private void AI4RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if(AI4RdbI.Checked==true)
            {
                AI4RdbU.Enabled = false;
                AI4lblmin.Text = "0mA";
                AI4lblmax.Text = "20mA";
                AI4Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch4_Value);
            }
            else if(AI4RdbI.Checked==false)
            {
                AI4RdbU.Enabled = true;
            }
        }

        private void AI4RdbI_Click(object sender, EventArgs e)
        {
            AI4RdbI.Enabled = true;
            AI4RdbI.AutoCheck = false;
            AI4RdbI.Checked = !AI4RdbI.Checked;
        }

        private void AI5RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if(AI5RdbU.Checked==true)
            {
                AI5RdbI.Enabled = false;
                AI5lblmin.Text = "0V";
                AI5lblmax.Text = "10V";
                AI5Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch5_Value);
            }
            else if(AI5RdbU.Checked==false)
            {
                AI5RdbI.Enabled = true;
            }
        }

        private void AI5RdbU_Click(object sender, EventArgs e)
        {
            AI5RdbU.Enabled = true;
            AI5RdbU.AutoCheck = false;
            AI5RdbU.Checked = !AI5RdbU.Checked;
        }

        private void AI5RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if(AI5RdbI.Checked==true)
            {
                AI5RdbU.Enabled = false;
                AI5lblmin.Text = "0mA";
                AI5lblmax.Text = "20mA";
                AI5Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch5_Value);
            }
            else if(AI5RdbI.Checked==false)
            {
                AI5RdbU.Enabled = true;
            }
        }

        private void AI5RdbI_Click(object sender, EventArgs e)
        {
            AI5RdbI.Enabled = true;
            AI5RdbI.AutoCheck = false;
            AI5RdbI.Checked = !AI5RdbI.Checked;
        }

        private void AI6RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if(AI6RdbU.Checked==true)
            {
                AI6RdbI.Enabled = false;
                AI6lblmin.Text = "0V";
                AI6lblmax.Text = "10V";
                AI6Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch6_Value);
            }
            else if(AI6RdbU.Checked==false)
            {
                AI6RdbI.Enabled = true;
            }
        }

        private void AI6RdbU_Click(object sender, EventArgs e)
        {
            AI6RdbU.Enabled = true;
            AI6RdbU.AutoCheck = false;
            AI6RdbU.Checked = !AI6RdbU.Checked;
        }

        private void AI6RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if(AI6RdbI.Checked==true)
            {
                AI6RdbU.Enabled = false;
                AI6lblmin.Text = "0mA";
                AI6lblmax.Text = "20mA";
                AI6Pb.Value = Convert.ToInt16(GlobalPramas.AI_Ch6_Value);
            }
            else if(AI6RdbI.Checked==false)
            {
                AI6RdbU.Enabled = true;
            }
        }

        private void AI6RdbI_Click(object sender, EventArgs e)
        {
            AI6RdbI.Enabled = true;
            AI6RdbI.AutoCheck = false;
            AI6RdbI.Checked = !AI6RdbI.Checked;
        }

        private void AO1RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if(AO1RdbU.Checked==true)
            {
                AO1RdbI.Enabled = false;
                AO1lblmin.Text = "0V";
                AO1lblmax.Text = "10V";
                AO1Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch1_Value/10);
            }
            else if(AO1RdbU.Checked==false)
            {
                AO1RdbI.Enabled = true;
            }
        }

        private void AO1RdbU_Click(object sender, EventArgs e)
        {
            AO1RdbU.Enabled = true;
            AO1RdbU.AutoCheck = false;
            AO1RdbU.Checked = !AO1RdbU.Checked;
        }

        private void AO1RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if(AO1RdbI.Checked==true)
            {
                AO1RdbU.Enabled = false;
                AO1lblmin.Text = "0mA";
                AO1lblmax.Text = "20mA";
                AO1Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch1_Value);
            }
            else if(AO1RdbI.Checked==false)
            {
                AO1RdbU.Enabled = true;
            }
        }

        private void AO1RdbI_Click(object sender, EventArgs e)
        {
            AO1RdbI.Enabled = true;
            AO1RdbI.AutoCheck = false;
            AO1RdbI.Checked = !AO1RdbI.Checked;
        }

        private void AO2RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if (AO2RdbU.Checked == true)
            {
                AO2RdbI.Enabled = false;
                AO2lblmin.Text = "0V";
                AO2lblmax.Text = "10V";
                AO2Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch2_Value);
            }
            else if (AO2RdbU.Checked == false)
            {
                AO2RdbI.Enabled = true;
            }
        }

        private void AO2RdbU_Click(object sender, EventArgs e)
        {
            AO2RdbU.Enabled = true;
            AO2RdbU.AutoCheck = false;
            AO2RdbU.Checked = !AO2RdbU.Checked;
        }

        private void AO2RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if (AO2RdbI.Checked == true)
            {
                AO2RdbU.Enabled = false;
                AO2lblmin.Text = "0mA";
                AO2lblmax.Text = "20mA";
                AO2Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch2_Value);
            }
            else if (AO2RdbI.Checked == false)
            {
                AO2RdbU.Enabled = true;
            }
        }

        private void AO2RdbI_Click(object sender, EventArgs e)
        {
            AO2RdbI.Enabled = true;
            AO2RdbI.AutoCheck = false;
            AO2RdbI.Checked = !AO2RdbI.Checked;
        }

        private void AO3RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if (AO3RdbU.Checked == true)
            {
                AO3RdbI.Enabled = false;
                AO3lblmin.Text = "0V";
                AO3lblmax.Text = "10V";
                AO3Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch3_Value);
            }
            else if (AO3RdbU.Checked == false)
            {
                AO3RdbI.Enabled = true;
            }
        }

        private void AO3RdbU_Click(object sender, EventArgs e)
        {
            AO3RdbU.Enabled = true;
            AO3RdbU.AutoCheck = false;
            AO3RdbU.Checked = !AO3RdbU.Checked;
        }

        private void AO3RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if (AO3RdbI.Checked == true)
            {
                AO3RdbU.Enabled = false;
                AO3lblmin.Text = "0mA";
                AO3lblmax.Text = "20mA";
                AO3Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch3_Value);
            }
            else if (AO3RdbI.Checked == false)
            {
                AO3RdbU.Enabled = true;
            }
        }

        private void AO3RdbI_Click(object sender, EventArgs e)
        {
            AO3RdbI.Enabled = true;
            AO3RdbI.AutoCheck = false;
            AO3RdbI.Checked = !AO3RdbI.Checked;
        }

        private void AO4RdbU_CheckedChanged(object sender, EventArgs e)
        {
            if (AO4RdbU.Checked == true)
            {
                AO4RdbI.Enabled = false;
                AO4lblmin.Text = "0V";
                AO4lblmax.Text = "10V";
                AO4Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch4_Value);
            }
            else if (AO4RdbU.Checked == false)
            {
                AO4RdbI.Enabled = true;
            }
        }

        private void AO4RdbU_Click(object sender, EventArgs e)
        {
            AO4RdbU.Enabled = true;
            AO4RdbU.AutoCheck = false;
            AO4RdbU.Checked = !AO4RdbU.Checked;
        }

        private void AO4RdbI_CheckedChanged(object sender, EventArgs e)
        {
            if (AO4RdbI.Checked == true)
            {
                AO4RdbU.Enabled = false;
                AO4lblmin.Text = "0mA";
                AO4lblmax.Text = "20mA";
                AO4Pb.Value = Convert.ToInt16(GlobalPramas.AO_Ch4_Value);
            }
            else if (AO4RdbI.Checked == false)
            {
                AO4RdbU.Enabled = true;
            }
        }

        private void AO4RdbI_Click(object sender, EventArgs e)
        {
            AO4RdbI.Enabled = true;
            AO4RdbI.AutoCheck = false;
            AO4RdbI.Checked = !AO4RdbI.Checked;
        }






    }

    /// <summary>
    /// 定义全局变量
    /// </summary>
    public class GlobalPramas
    {
        //DI端口数据
        public static ushort DI1_Value = 0;
        public static ushort DI2_Value = 0;
        public static ushort DI3_Value = 0;
        public static ushort DI4_Value = 0;

        //DO端口数据
        public static ushort DO1_Value = 0;
        public static ushort DO2_Value = 0;
        public static ushort DO3_Value = 0;
        public static ushort DO4_Value = 0;

        //AI端口数据
        public static double AI_Ch1_Value = 0.0;
        public static double AI_Ch2_Value = 0.0;
        public static double AI_Ch3_Value = 0.0;
        public static double AI_Ch4_Value = 0.0;
        public static double AI_Ch5_Value = 0.0;
        public static double AI_Ch6_Value = 0.0;

        //AO端口数据
        public static double AO_Ch1_Value = 0.0;
        public static double AO_Ch2_Value = 0.0;
        public static double AO_Ch3_Value = 0.0;
        public static double AO_Ch4_Value = 0.0;

        //PWM参数
        public static ushort PWM1_Cycle = 0;
        public static ushort PWM1_Duty = 0;
        public static ushort PWM2_Cycle = 0;
        public static ushort PWM2_Duty = 0;

        //Command端命令变量
        public static ushort Start_Comm = 0;
        public static ushort Stop_Comm = 0;
        public static double SetValue = 0.0;

        //定义数据接收数组
       public static ushort [] DataRead = new ushort [200];
        public static ushort [] DataWrite =new ushort[15];
        public static ushort[] AODataWrite = new ushort[4];
        public static ushort[] PWMDataWrite = new ushort[4];
        public static ushort[] CmdDataWrite = new ushort[3];
    }


}
