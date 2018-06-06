using System;
using Library.Common;
using System.Reflection;

namespace Library.LDDS
{
    public partial class Regenerator4 : Module
    {
        public DataBus.DataRefresh.CRealTimeDataManager comp_rtdm;
        public DataBus.DataAccess.CData_PointTable dataPT;
        public DataBus.DataRefresh.CRealTimeDataManager rtdm;



        public Regenerator4()
        {
            InitializeComponent();
            dataPT = new DataBus.DataAccess.CData_PointTable();

        }

        private void sendButtonClick(object sender, EventArgs e)
        {

            Type t = sender.GetType();
            Library.SendButton tb = (Library.SendButton)sender;
            DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
            DataBus.DataSend.CDataSend dataSend;
            dataSend = new DataBus.DataSend.CDataSend();

            string RelatedPort = "";
            string PortData = "";
            string PortBind = "";
            string DeviceType = "";
            PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
            PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
            PropertyInfo m_PortData = t.GetProperty("PortData");
            PropertyInfo m_PortBind = t.GetProperty("PortBind");
            PropertyInfo m_DeviceName = t.GetProperty("DeviceName");
            PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
            string currentName = "Renoadjhp_" + t.Name.ToString();

            dataPT.GetBoardPortByNameBdnum(currentName, BoardNumber, ref RelatedPort, ref DeviceType);
            dataPT.GetBoardSendPortByNameBdnum(currentName, BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
            bool isSuccess=dataSend.SendControlData(this.DeviceRun.currentState, RelatedPort, PortBind, this.BoardNumber);

            if (isSuccess == true)
            {
                System.Windows.Forms.MessageBox.Show("Success!");
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Failed!");
            }

            m_BoardNumber.SetValue(tb, BoardNumber, null);
            m_RelatedPort.SetValue(tb, RelatedPort, null);
            //m_DeviceType.SetValue(tb, currentType, null);
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
            string PortData = "";
            string PortBind = "";
         
            if (this.Startblock.currentState == "1")
            {

                //dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);

                int k = 0, a = 0;
                a = this.Controls.Count;
                object[] comps = new object[a];
                foreach (object o in this.Controls)
                {
                    comps[k] = o;
                    Type t = comps[k].GetType();
                    if (t.Name.Equals("TextBox"))
                    {

                        TextBox currentcomp = (TextBox)comps[k];
                        stringName = "Renoadjhp_" + currentcomp.Name;
                        dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = this.BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        currentcomp.rtdm = rtdm;
                        // currentcomp.Name = stringName;
                        if (currentcomp.rtdm == null)
                            return;

                    }
                    if (t.Name.Equals("ButtonCheck"))
                    {

                        ButtonCheck currentcomp = (ButtonCheck)comps[k];
                        stringName = "Renoadjhp_" + currentcomp.Name;
                        dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = this.BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        currentcomp.CDrtdm = rtdm;
                        // currentcomp.Name = stringName;
                        if (currentcomp.rtdm == null)
                            return;

                    }
                    else if (t.Name.Equals("statusIndicator"))
                    {
                        statusIndicator currentcomp = (statusIndicator)comps[k];
                        stringName = "Renoadjhp_" + currentcomp.Name;
                        dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = this.BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        currentcomp.currentState = rtdm.GetDataByBoardPort(BoardNumber, RelatedPort);
                        currentcomp.rtdm = rtdm;
                        if (currentcomp.rtdm == null)
                            return;

                    }
                    else if (t.Name.Equals("levelmeter"))
                    {
                        levelmeter currentcomp = (levelmeter)comps[k];
                        stringName = "Renoadjhp_" + currentcomp.Name;
                        dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = this.BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        currentcomp.stringName = stringName;
                        currentcomp.rtdm = rtdm;
                        try
                        {
                            currentcomp.Value = (int)(float.Parse(rtdm.GetDataByBoardPort(this.BoardNumber, RelatedPort)));
                        }
                        catch
                        {
                        }
                        if (currentcomp.rtdm == null)
                            return;
                    }
                    else if (t.Name.Equals("SendButton"))
                    {
                        SendButton currentcomp = (SendButton)comps[k];
                        stringName = "Renoadjhp_" + currentcomp.Name;
                       // dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        dataPT.GetBoardSendPortByNameBdnum(stringName, this.BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                        currentcomp.PortBind = PortBind;
                        currentcomp.sendData.Text = rtdm.GetDataByBoardPort(this.BoardNumber, RelatedPort);
                        currentcomp.rtdm = rtdm;
                        if (currentcomp.rtdm == null)
                            return;
                    }

                    k++;
                }

            }
        }

        private void LDDSonoff_Click(object sender, EventArgs e)
        {

            string currentName = "";
            string RelatedPort = "";
            // string DeviceType = "";
            string PortData = "";
            string PortBind = "";
            
            string BoardNumber = this.BoardNumber;
            DataBus.DataSend.CDataSend dataSend;
            dataSend = new DataBus.DataSend.CDataSend();

            Library.Common.ButtonCheck comp = (Library.Common.ButtonCheck)sender;
            currentName = "Renoadjhp_" + comp.Name;
            dataPT.GetBoardSendPortByNameBdnum(currentName, BoardNumber, ref RelatedPort, ref PortData, ref PortBind);


            dataSend.SendControlData(this.DeviceRun.currentState, RelatedPort, PortBind, this.BoardNumber);

        }
        private void ButtonStrSolClick(object sender, EventArgs e)
        {
            if (lable3.Visible)
            {
                this.lable3.Visible = false;
                this.SSLevelAlm.Visible = false;
                this.lable5.Visible = false;
                this.SSLevelHigh.Visible = false;

            }
            else
            {
                this.lable3.Visible = true;
                this.SSLevelAlm.Visible = true;
                this.lable5.Visible = true;
                this.SSLevelHigh.Visible = true;
            }

        }
        private void ButtonVavClick(object sender, EventArgs e)
        {
            if (label22.Visible)
            {
                this.label22.Visible = false;
                this.SetVavSet.Visible = false;
            }
            else
            {
                this.label22.Visible = true;
                this.SetVavSet.Visible = true;
            }
        }

        private void ButtonWeakSolLevelClick(object sender, EventArgs e)
        {

            if (lable8.Visible)
            {
                this.lable8.Visible = false;
                this.WkSLevelHAlm.Visible = false;
                this.lable9.Visible = false;
                this.WkSLevelHigh.Visible = false;

            }
            else
            {
                this.lable8.Visible = true;
                this.WkSLevelHAlm.Visible = true;
                this.lable9.Visible = true;
                this.WkSLevelHigh.Visible = true;
            }
        }

        private void ButtonReSolLevelClick(object sender, EventArgs e)
        {

            if (lable4.Visible)
            {
                this.lable4.Visible = false;
                this.lable10.Visible = false;
                this.lable7.Visible = false;
                this.lable6.Visible = false;

                this.ReSLevelHAlm.Visible = false;
                this.ReSLevelStart.Visible = false;
                this.ReSLevelStop.Visible = false;
                this.ReSLevelLAlm.Visible = false;
            }
            else
            {
                this.lable4.Visible = true;
                this.lable10.Visible = true;
                this.lable7.Visible = true;
                this.lable6.Visible = true;

                this.ReSLevelHAlm.Visible = true;
                this.ReSLevelStart.Visible = true;
                this.ReSLevelStop.Visible = true;
                this.ReSLevelLAlm.Visible = true;
            }
        }


        private void AutoControl_Click(object sender, EventArgs e)
        {
            if (AutoControl.currentState == "1")
            {
                SetVavSet.Enabled = false;
                PumpOnOff.Enabled = false;
                FanOnOff.Enabled = false;

            }
            else
            {
                SetVavSet.Enabled = true;
                PumpOnOff.Enabled = true;
                FanOnOff.Enabled = true;

            }
        }

    }




}
