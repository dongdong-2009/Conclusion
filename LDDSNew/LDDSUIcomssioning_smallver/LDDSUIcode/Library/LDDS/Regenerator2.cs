using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Reflection;

namespace Library.LDDS
{
    public partial class Regenerator2 : Module
    {
        public Regenerator2()
        {
            InitializeComponent();

            Re_AirTempIn.Text = "Re_AirTempIn ";
            Re_AirHumIn.Text = " Re_AirHumIn";
            Re_AirTempOut.Text = "Re_AirTempOut";
            Re_AirHumOut.Text = "Re_AirHumOut";
            Re_SolFlow.Text = "Re_SolFlow";
            Re_VavFb.Text = "Re_VavFb";
            Re_SolLevelRe.Text = "Re_SolLevelDe";
            Re_SolLevelST.Text = "Re_SolLevelST";
            Re_SolTempIn.Text = "Re_SolTempIn";
            Re_SolTempOut.Text = "Re_SolTempOut";
            Re_WaterTempIn.Text = "Re_WaterTempIn";
            Re_WaterTempOut.Text = "Re_WaterTempOut";

     //       dataPT = new DataBus.DataAccess.CData_PointTable();
            //if (this.BoardNumber == null)
            //    this.BoardNumber = "00000000";
        }

        //public DataBus.DataAccess.CData_PointTable dataPT;
        //public DataBus.DataRefresh.CRealTimeDataManager rtdm;

        private List<CompInfo> m_RealTimelines = new List<CompInfo>();
        public class CompInfo
        {
            public string BoardNumber;
            public string RelatedPort;
            public string CompName;
         //   public DataBus.DataRefresh.CRealTimeDataManager comp_rtdm;
            public Regenerator2 parentRegenerator2;
            private System.Windows.Forms.Timer m_timer;


            public void Start()
            {
                m_timer = new Timer();
                this.m_timer.Interval = 2000;
                m_timer.Tick += new System.EventHandler(this.M_timerTick);
                m_timer.Enabled = true;
                m_timer.Start();
            }
            public void Stop()
            {
                m_timer = new Timer();
                m_timer.Enabled = false;
                m_timer.Stop();
            }

            public void Dispose()
            {
                m_timer = new Timer();
                m_timer.Stop();
            }
            public void M_timerTick(object sender, System.EventArgs e)
            {

                string data = "";
                //if (parentRegenerator2.rtdm == null)
                //    return;

                //data = parentRegenerator2.rtdm.GetDataByBoardPort(BoardNumber, RelatedPort);
                if (data == null)
                    return;
                try
                {
                    parentRegenerator2.Controls[CompName].Text = data;

                    //((Library.TextBox)Controls[stringName]).Text = data;
                }
                catch { }

            }
        }

        private void senddataset(string currentName, string currentType, Library.SendButton sendButton, string BoardNumber)
        {
            Type t = sendButton.GetType();
            Library.SendButton tb = (Library.SendButton)sendButton;
 //           DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

            string RelatedPort = "";
            string PortData = "";
            string PortBind = "";

            PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
            PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
            PropertyInfo m_PortData = t.GetProperty("PortData");
            PropertyInfo m_PortBind = t.GetProperty("PortBind");
            PropertyInfo m_DeviceName = t.GetProperty("DeviceName");
            PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");

            //dataPT.GetBoardSendPortByNameBdnum(currentName, BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
            // dataPT.GetBoardSendPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind); m_BoardNumber.SetValue(tb, BoardNumber, null);
            m_BoardNumber.SetValue(tb, BoardNumber, null);
            m_RelatedPort.SetValue(tb, RelatedPort, null);
            m_DeviceType.SetValue(tb, currentType, null);
            //m_DeviceID.SetValue(tb, currentID, null);
            m_DeviceName.SetValue(tb, currentName, null);
            m_PortData.SetValue(tb, PortData, null);
            m_PortBind.SetValue(tb, PortBind, null);

        }


        private void Startblock_Click(object sender, EventArgs e)
        {

            string BoardNumber = this.BoardNumber;
            string RelatedPort = "";
            string DeviceType = "";
            string stringName = "";




            // dataSend.SendControlData(this.Startblock.currentState, Startblock.RelatedPort, Startblock.PortBind, this.BoardNumber);

            if (this.Startblock.currentState == "1")
            {
                string[] textNameArraySen = new string[12]{ 
               Re_AirTempIn.Name,
               Re_AirHumIn.Name,
               Re_AirTempOut.Name,
               Re_AirHumOut.Name,
               Re_SolFlow.Name ,
               Re_VavFb.Name ,
               Re_SolLevelRe.Name,
               Re_SolLevelST.Name ,
               Re_SolTempIn.Name ,
               Re_SolTempOut.Name,
               Re_WaterTempIn.Name ,
               Re_WaterTempOut.Name };

 //               dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);

                int i = 0, a = 0;
                a = this.Controls.Count;
                object[] comps = new object[a];
                foreach (object o in this.Controls)
                {
                    comps[i] = o;
                    Type t = comps[i].GetType();
                    if (t.Name.Equals("TextBox"))
                    {
                        //CompInfo tmpLine = new CompInfo();
                        //stringName = textNameArraySen[i];
                        //dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        //tmpLine.parentRegenerator2 = this;
                        //tmpLine.BoardNumber = BoardNumber;
                        //tmpLine.RelatedPort = RelatedPort;
                        //tmpLine.comp_rtdm = rtdm;
                        //tmpLine.CompName = stringName;
                        //if (tmpLine.comp_rtdm == null)
                        //    return;
                        //tmpLine.Start();
                        //i++;
                    }
                }

            }
            else
            {
                string[] textNameArraySen = new string[12]{ 
               Re_AirTempIn.Name,
               Re_AirHumIn.Name,
               Re_AirTempOut.Name,
               Re_AirHumOut.Name,
               Re_SolFlow.Name ,
               Re_VavFb.Name ,
               Re_SolLevelRe.Name,
               Re_SolLevelST.Name ,
               Re_SolTempIn.Name ,
               Re_SolTempOut.Name,
               Re_WaterTempIn.Name ,
               Re_WaterTempOut.Name };

                int i = 0, a = 0;
                a = this.Controls.Count;
                object[] comps = new object[a];
                foreach (object o in this.Controls)
                {
                    comps[i] = o;

                    Type t = comps[i].GetType();
                    if (t.Name.Equals("TextBox"))
                    {
                        CompInfo tmpLine = new CompInfo();
                        stringName = textNameArraySen[i];
 //                       dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        tmpLine.parentRegenerator2 = this;
                        tmpLine.BoardNumber = BoardNumber;
                        tmpLine.RelatedPort = RelatedPort;
 //                       tmpLine.comp_rtdm = null;
                        tmpLine.CompName = stringName;
                        tmpLine.Stop();
                        i++;
                    }
                }
            }
        }

        private void LDDSonoff_Click(object sender, EventArgs e)
        {

            //DataBus.DataSend.CDataSend dataSend;
            //dataSend = new DataBus.DataSend.CDataSend();
            //dataSend.SendControlData(this.LDDSonoff.currentState, LDDSonoff.RelatedPort, LDDSonoff.PortBind, this.BoardNumber);

        }

    }




}
