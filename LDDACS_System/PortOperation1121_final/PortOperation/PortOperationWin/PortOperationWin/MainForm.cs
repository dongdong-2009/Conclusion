using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ClockTick;
using NLog;
using Modbus.Device;
using ModbusDAQ;

namespace PortOperationWin
{
    public partial class MainForm : Form
    {
        #region 【成员变量】
        public Timer timertest;
        private Logger m_Logger;
        private string m_TableNameGroup;
        private string m_TableNameStationInfo;
        private string m_TableNameDistribution;

        private CyclicRunThreadClass m_ClockTickRead;
        private CyclicRunThreadClass m_ClockTickWrite;
        private ModubsManageClass    m_ModbusManager;

        /// <summary>
        /// 用以表示是否已经运行，以便标识按钮状态
        /// </summary>
        private bool m_IsRunning = false;
        #endregion

        public MainForm()
        {
            InitializeComponent();

            timertest = new Timer();
            timertest.Interval = 5000;
            timertest.Tick += new EventHandler(ShowData);
            

        }

        #region [TickClockWrite]
        /// <summary>
        /// [写站点]的滴答时钟响应函数
        /// </summary>
        private void TickClockWrite()
        {
            // UpdateWorkStatus("Writing...");
            List<string[]> existed;
            existed=m_ModbusManager.CheckWriteStatus();
            if(existed.Count()!=0)
            m_ModbusManager.ExecuteWrite(this, existed);
            
            // UpdateWorkStatus("Writing done!");
        }
        #endregion

        #region [TickClockRead]
        /// <summary>
        /// [读站点]的滴答时钟响应函数
        /// </summary>
        private void TickClockRead()
        {
            UpdateWorkStatus("Reading...");
            m_ModbusManager.ExecuteRead();
            UpdateWorkStatus("Reading done!");
        }
        #endregion
        #region [responseMain]
        private void FormMain_SizeChanged(object sender, EventArgs e)
        {
            this.ShowInTaskbar = false;  //不显示在系统任务栏
            notifyIcon1.Visible = true;  //托盘图标可见
        }

        private void notifyIcon1_DoubleClick(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.ShowInTaskbar = true;  //显示在系统任务栏
                this.WindowState = FormWindowState.Normal;  //还原窗体
                notifyIcon1.Visible = false;  //托盘图标隐藏
            }
        }
        private void Config_user485_Click(object sender, EventArgs e)
        {
            ModbusWin fm = new ModbusWin(this);
            fm.Show();
        }

        private void Status_config_Click(object sender, EventArgs e)
        {
            statusWin sw = new statusWin(this);
            sw.ShowDialog();
        }
        #region [GetNow] 获取当前时间，样式：[10:29:18]
        /// <summary>
        /// 获取当前时间，样式：[10:29:18]
        /// </summary>
        /// <returns></returns>
        private string GetNow()
        {
            DateTime DT = DateTime.Now;
            string Now = "[" + DT.ToLongTimeString() + "]";
            return Now;
        }
        #endregion
        private void UpdateWorkStatus(string status)
        {

            this.Invoke((EventHandler)delegate
            {
                tlb_Status.Text = GetNow() + " " + status;
                //notifyIcon1.Text = GetNow() + " " + status;
            });

        }
       
        private void FormMain_Load(object sender, EventArgs e)
        {
            try
            {
                m_Logger = LogManager.GetCurrentClassLogger();
                m_TableNameGroup = System.Configuration.ConfigurationManager.AppSettings["ModbusDBTable_Group"];
                m_TableNameStationInfo = System.Configuration.ConfigurationManager.AppSettings["ModbusDBTable_StationInfo"];
                m_TableNameDistribution = System.Configuration.ConfigurationManager.AppSettings["ModbusDBTable_Distribution"];
                m_IsRunning = false;
            }
            catch (Exception Ex)
            {
                m_Logger.Error(Ex);
            }

        }
        #region[board manipulate]
       
        public void ShowData(object sender, EventArgs e)
        {
          string porttype;
          string subporttype;
          int cnt;
          string scnt;
          
            try
            {
                foreach (Control ctrl in this.Controls)
                {
                    if (ctrl is TextBox)
                    {
                        porttype = ctrl.Name.Substring(0, 2);

                        switch (porttype)
                        {
                            case "AI":
                                {
                                    cnt = int.Parse(ctrl.Name.Substring(ctrl.Name.Length - 1, 1));
                                    scnt = ctrl.Name.Substring(ctrl.Name.Length - 2, 1);

                                    if ((cnt == 1) | (cnt == 2) | (cnt == 0))
                                    {
                                        if (scnt == "1")
                                            ctrl.Text = PortOperationWin.Boardstatus.AIdataF[cnt + 10 - 1];
                                        else
                                            ctrl.Text = PortOperationWin.Boardstatus.AIdataF[cnt - 1];
                                    }
                                    else
                                        ctrl.Text = PortOperationWin.Boardstatus.AIdataF[cnt - 1];
                                    break;
                                }


                            case "RT":
                                {
                                    cnt = int.Parse(ctrl.Name.Substring(ctrl.Name.Length - 1, 1));
                                    ctrl.Text = PortOperationWin.Boardstatus.RTDdataF[cnt - 1];

                                    break;
                                }

                            default: //uint16, boolean
                                {
                                    //sqlCmdpart = string.Format(" {0} = {1} ", columnName, station.Values[dataPos]);
                                    break;
                                }
                       
                        }
                    }
                    else if (ctrl is indicator)
                    {
                        porttype = ctrl.Name.Substring(0, 2);
                        if (porttype == "DI")
                        {
                            cnt = int.Parse(ctrl.Name.Substring(ctrl.Name.Length - 1, 1));
                            ctrl.Text = PortOperationWin.Boardstatus.DIdataI[cnt - 1];

                        }

                    }
                    else if (ctrl is Panel)
                    {
                        foreach (Control subctrl in ctrl.Controls)
                        {

                            if (subctrl is TextBox)
                            {
                                subporttype = subctrl.Name.Substring(0, 2);

                                switch (subporttype)
                                {
                                    case "RT":
                                        {
                                            cnt = int.Parse(subctrl.Name.Substring(subctrl.Name.Length - 1, 1));
                                            subctrl.Text = PortOperationWin.Boardstatus.RTDdataF[cnt - 1];

                                            break;
                                        }
                                    default: //uint16, boolean
                                        {
                                            //sqlCmdpart = string.Format(" {0} = {1} ", columnName, station.Values[dataPos]);
                                            break;
                                        }
                                }

                            }
                            else if (subctrl is indicator)
                            {
                                subporttype = subctrl.Name.Substring(0, 2);
                                indicator b = subctrl as indicator;
                                if (subporttype == "DI")
                                {

                                    cnt = int.Parse(subctrl.Name.Substring(subctrl.Name.Length - 1, 1));
                                    b.currentState = PortOperationWin.Boardstatus.DIdataI[cnt - 1];

                                }

                            }


                        }
                    }

                }
            }

            catch (Exception Ex)
            {
                m_Logger.Error(Ex);
            }
        }
  
       private void DObuttonClick(object sender, System.EventArgs e)
        {
            Sendindicator b = sender as Sendindicator;
            String buttonName = b.Name;
            ushort cnt = ushort.Parse(buttonName.Substring(buttonName.Length - 1, 1));
            SetHandle("DOdataI",cnt);
            PortOperationWin.Boardstatus.DOdataI[cnt - 1] = b.currentState;

        }
        private void AObuttonClick(object sender, System.EventArgs e)
        {
            Type type = sender.GetType();
            sendbutton obj = sender as sendbutton;
            string buttonName = obj.Name;
            string value = obj.textBox1.Text;
            ushort cnt = ushort.Parse(buttonName.Substring(buttonName.Length - 1, 1));
            SetHandle("AOdataF",cnt);
            if (value != "")
            {
                if ((cnt > 0) & (cnt <= 8))
                    PortOperationWin.Boardstatus.AOdataF[cnt - 1] = float.Parse(value);
            }
     
            else
                MessageBox.Show("please input the send value");
        }
        private void AOModebuttonClick(object sender, System.EventArgs e)
        {
            Vo_Am b = sender as Vo_Am;
            String buttonName = b.Name;
            
            ushort cnt = ushort.Parse(buttonName.Substring(buttonName.Length - 1, 1));
            SetHandle("AOmodeI", cnt);
            PortOperationWin.Boardstatus.AOmodeI[cnt-1] = b.currentState;
        }
        private void PWMbuttonClick(object sender, System.EventArgs e)
        {
            sendbutton b = sender as sendbutton;
            String buttonName = b.Name;
            ushort cnt = ushort.Parse(buttonName.Substring(buttonName.Length - 1, 1));
            ushort subcnt = ushort.Parse(buttonName.Substring(buttonName.Length - 2, 1));

            if (subcnt == 1)
            {
                SetHandle("PWM1dataF", cnt);
                PortOperationWin.Boardstatus.PWM1dataF[cnt - 1] = float.Parse(b.textBox1.Text);
            }
            else if (subcnt == 2)
            {
                SetHandle("PWM2dataF", cnt);
                PortOperationWin.Boardstatus.PWM2dataF[cnt - 1] = float.Parse(b.textBox1.Text);
            }

            
        }
        private void AIModebuttonClick(object sender, System.EventArgs e)
        {
            Vo_AmV b = sender as Vo_AmV;
            String buttonName = b.Name;
            ushort cntt;
            ushort cnt = ushort.Parse(buttonName.Substring(buttonName.Length - 1, 1));
            string scnt = buttonName.Substring(buttonName.Length - 2, 1);

            if ((cnt == 1) | (cnt == 2) | (cnt == 0))
            {
                if (scnt == "1")
                {
                    PortOperationWin.Boardstatus.AImodeI[cnt + 10 - 1] = b.currentState;
                    cntt = (ushort)(cnt + 10);
                }
                else
                {
                    PortOperationWin.Boardstatus.AImodeI[cnt - 1] = b.currentState;
                    cntt = cnt;
                }
            }
            else
            { PortOperationWin.Boardstatus.AImodeI[cnt - 1] = b.currentState;
                cntt = cnt;
            }
            SetHandle("AImodeI",cntt);
        }
        #endregion
        private void Startboard_Click(object sender, EventArgs e)
        { 
            if (PortOperationWin.Boardstatus.PortSelected == 0)
            {
                MessageBox.Show("Please select the status port");
                return;
            }

            if (PortOperationWin.Boardstatus.PortSelected != 0)
            {
                if (m_IsRunning == false)
                {
                    m_ModbusManager = new ModubsManageClass();
                    bool initResult = m_ModbusManager.Init(m_TableNameStationInfo, m_TableNameGroup, m_TableNameDistribution);

                    if (m_ModbusManager.IsHasReadStaion)
                    {
                        m_ClockTickRead = new CyclicRunThreadClass();
                        m_ClockTickRead.Interval = 10 * 1000;
                        m_ClockTickRead.TimingPattern = eTimingPattern.SleepSec;
                        m_ClockTickRead.CyclicRun += TickClockRead;
                        m_ClockTickRead.StartThead();
                        m_IsRunning = true;
                        Startboard.Text = "Stop";
                        timertest.Enabled = true;
                    }
                    if (m_ModbusManager.IsHasWriteStaion)
                    {
                        m_ClockTickWrite = new CyclicRunThreadClass();
                        m_ClockTickWrite.Interval = 5 * 100;
                        m_ClockTickWrite.TimingPattern = eTimingPattern.SleepSec;
                        m_ClockTickWrite.CyclicRun += TickClockWrite;
                        m_ClockTickWrite.StartThead();
                        m_IsRunning = true;
                        Startboard.Text = "Stop";
                    }
                }
                else
                {
                    m_IsRunning = false;
                //    m_ClockTickWrite.StopThead();
                //    m_ClockTickRead.StopThead();
                    Startboard.Text = "Start";
                    PortOperationWin.Boardstatus.port.Close();
                    this.status.currentState = "0";


                }
            }
            else
            {
                m_Logger.Info("Init failed! ");
                UpdateWorkStatus("Init failed!");
                m_IsRunning = false;
                Startboard.Text = "Start";
            }

        }
        #endregion

        #region [Handle] 处理handle位
        /// <summary>
        /// 清理handle位
        /// </summary>
        /// <param name="connString"></param>
        /// <param name="stationInfoTableName"></param>
        /// <param name="stationPointName"></param>
        public void ClearHandle(string str,ushort pos)
        {
            try
            {
                if (str == "UserModbusSenddataI")
                {

                    //       PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle.Length - 1] = "1";
                    PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle.Length - 2] = "0";

                }
                else
                {
                    int id = Array.IndexOf(PortOperationWin.Boardstatus.Modbus_Stationinfo.Name, str);
                    //int n = str.Length;
                    string orgstr = PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[id];
                    string newstr = orgstr.Insert(pos, "0");
                    newstr = newstr.Remove(pos - 1, 1);
                    PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[id] = newstr;
                }
            }
            catch (Exception ex)
            {
                Logger log = LogManager.GetCurrentClassLogger();
                log.Error(ex);
                throw;
            }
        }

        public void SetHandle(string str,ushort pos)
        {


            try
            {

                if (str == "UserModbusSenddataI")
                {

             //       PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle.Length - 1] = "1";
                    PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle.Length - 2] = "1";

                }
              
                else
                {

                    int id = Array.IndexOf(PortOperationWin.Boardstatus.Modbus_Stationinfo.Name, str);
                    string orgstr = PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[id];
                    string newstr = orgstr.Insert(pos, "1");
                    newstr = newstr.Remove(pos - 1, 1);
                    PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[id] = newstr;
                }
              
            }
            catch (Exception ex)
            {
                Logger log = LogManager.GetCurrentClassLogger();
                log.Error(ex);
               
            }
        }
        #endregion


    }
}

