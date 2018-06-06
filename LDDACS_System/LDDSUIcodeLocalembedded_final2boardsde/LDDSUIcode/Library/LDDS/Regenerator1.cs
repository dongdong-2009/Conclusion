using System;
using Library.Common;
using System.Reflection;

namespace Library.LDDS
{
    public partial class Regenerator1 : Module
    {
        public DataBus.DataRefresh.CRealTimeDataManager comp_rtdm;
        public DataBus.DataAccess.CData_PointTable dataPT;
        public DataBus.DataRefresh.CRealTimeDataManager rtdm;



        public Regenerator1()
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

            string currentName = "Readjhw_" + t.Name.ToString();
            dataPT.GetBoardPortByNameBdnum(currentName, BoardNumber, ref RelatedPort, ref DeviceType);
            dataPT.GetBoardSendPortByNameBdnum(currentName, BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
            bool isSuccess = dataSend.SendControlData(tb.sendData.Text, RelatedPort, PortBind, this.BoardNumber);

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
             //   dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);

                int i = 0, j = 0, k = 0, l = 0, a = 0;
                a = this.Controls.Count;
                object[] comps = new object[a];
                foreach (object o in this.Controls)
                {
                    comps[k] = o;
                    Type t = comps[k].GetType();
                    if (t.Name.Equals("TextBox"))
                    {

                        TextBox currentcomp = (TextBox)comps[k];
                        stringName = "Readjhw_"+currentcomp.Name;
                        dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        currentcomp.rtdm = rtdm;
                        currentcomp.Name = stringName;
                        if (currentcomp.rtdm == null)
                            return;

                        i++;

                    }
                    else if (t.Name.Equals("statusIndicator"))
                    {
                        statusIndicator currentcomp = (statusIndicator)comps[k];
                        stringName = "Readjhw_"+currentcomp.Name;
                        dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        currentcomp.currentState = rtdm.GetDataByBoardPort(BoardNumber,  RelatedPort);
                        currentcomp.rtdm = rtdm;
                        if (currentcomp.rtdm == null)
                            return;
                        //    this.Start();
                        j++;

                    }
                    else if (t.Name.Equals("levelmeter"))
                    {
                        levelmeter currentcomp = (levelmeter)comps[k];
                        stringName = "Readjhw_" + currentcomp.Name;
                        dataPT.GetBoardPortByNameBdnum(stringName, BoardNumber, ref RelatedPort, ref DeviceType);
                        currentcomp.BoardNumber = BoardNumber;
                        currentcomp.RelatedPort = RelatedPort;
                        //string decVal = rtdm.GetDataByBoardPort(BoardNumber, RelatedPort);
                        //string[] decValMatix = decVal.Split('.');
                        //int value = int.Parse(decValMatix[0]);
                        currentcomp.stringName = stringName;
                        currentcomp.rtdm = rtdm;
                        currentcomp.Value = (int)(float.Parse(rtdm.GetDataByBoardPort(this.BoardNumber,RelatedPort)));
                        //  currentcomp.Value = int.Parse(rtdm.GetDataByBoardPort(BoardNumber, RelatedPort));
                        currentcomp.rtdm = rtdm;
                        if (currentcomp.rtdm == null)
                            return;
                        //    this.Start();
                        l++;

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
            currentName =  comp.Name;
            dataPT.GetBoardSendPortByNameBdnum(currentName, BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
            dataSend.SendControlData(this.DeviceRun.currentState, RelatedPort, PortBind, this.BoardNumber);

        }
        private void ButtonFanClick(object sender, EventArgs e)
        {

            if (label2.Visible)
            {
                this.FanFb.Visible = false;
                this.label2.Visible = false;
                this.label3.Visible = false;
                this.FanSet.Visible = false;

            }
            else
            {
                this.FanFb.Visible = true;
                this.label2.Visible = true;
                this.label3.Visible = true;
                this.FanSet.Visible = true;
            }
        }
        private void ButtonVavClick(object sender, EventArgs e)
        {

            if (label22.Visible)
            {
                this.label22.Visible = false;
                this.VavFb.Visible = false;
                this.label21.Visible = false;
                this.SetVavSet.Visible = false;

            }
            else
            {
                this.label22.Visible = true;
                this.VavFb.Visible = true;
                this.label21.Visible = true;
                this.SetVavSet.Visible = true;
            }
        }
        private void ButtonPumpClick(object sender, EventArgs e)
        {

            if (label13.Visible)
            {
                this.label13.Visible = false;
                this.PumpFb.Visible = false;
                this.label4.Visible = false;
                this.PumpSet.Visible = false;

            }
            else
            {
                this.label13.Visible = true;
                this.PumpFb.Visible = true;
                this.label4.Visible = true;
                this.PumpSet.Visible = true;
            }
        }

    //    private void ButtonWeakSolLevelClick(object sender, EventArgs e)
    //    {

    //        if (lable8.Visible)
    //        {
    //            this.lable8.Visible = false;
    //            this.WkSLevelHigh.Visible = false;
    //            this.lable9.Visible = false;
    //            this.WkSLevelLow.Visible = false;

    //        }
    //        else
    //        {
    //            this.lable8.Visible = true;
    //            this.WkSLevelHigh.Visible = true;
    //            this.lable9.Visible = true;
    //            this.WkSLevelLow.Visible = true;
    //        }
    //    }

    //    private void ButtonReSolLevelClick(object sender, EventArgs e)
    //    {

    //        if (lable4.Visible)
    //        {
    //            this.lable4.Visible = false;
    //            this.lable10.Visible = false;
    //            this.lable7.Visible = false;
    //            this.lable6.Visible = false;

    //            this.ReSLevelHigh.Visible = false;
    //            this.ReSLevelTrasf.Visible = false;
    //            this.ReSLevelOpt.Visible = false;
    //            this.ReSLevelLow.Visible = false;
    //        }
    //        else
    //        {
    //            this.lable4.Visible = true;
    //            this.lable10.Visible = true;
    //            this.lable7.Visible = true;
    //            this.lable6.Visible = true;

    //            this.ReSLevelHigh.Visible = true;
    //            this.ReSLevelTrasf.Visible = true;
    //            this.ReSLevelOpt.Visible = true;
    //            this.ReSLevelLow.Visible = true;
    //        }
    //    }

    }




}
