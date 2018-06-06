using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using DataBus;
using System.Reflection;

namespace Designer.DrawTool
{
    public partial class Bind : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public string currentType = "";
        public string currentID = "";
        public string currentName = "";
        public string currentBindName = "";
        public bool   couldBeBind = false;
        public object currentObj = null;
        private DataBus.DataAccess.CData_BindComp cbc = new DataBus.DataAccess.CData_BindComp();
        private ArrayList typeComboBoxCollection = new ArrayList();
        private ArrayList rwComboBoxCollection = new ArrayList();
        public Bind()
        {
            InitializeComponent();
            TypeComboBox.SelectedValueChanged += new EventHandler(TypeComboBox_SelectedValueChanged);
            Init();
        }

        private void Init()
        {
            typeComboBoxCollection.Add(new TextAndValue("Sensor", "1"));
            typeComboBoxCollection.Add(new TextAndValue("Actuator", "2"));
            typeComboBoxCollection.Add(new TextAndValue("Fan", "3"));
            typeComboBoxCollection.Add(new TextAndValue("Pump", "4"));
            typeComboBoxCollection.Add(new TextAndValue("Module", "5"));
            typeComboBoxCollection.Add(new TextAndValue("Control", "6"));
            typeComboBoxCollection.Add(new TextAndValue("Indicator", "7"));

            TypeComboBox.ValueMember = "RealValue";
            TypeComboBox.DisplayMember = "DisplayText";
            TypeComboBox.DataSource = typeComboBoxCollection;
            TypeComboBox.SelectedIndex = -1;

            rwComboBoxCollection.Add(new TextAndValue("Read", "Read"));
            rwComboBoxCollection.Add(new TextAndValue("Write", "Write"));

            RWComboBox.ValueMember = "RealValue";
            RWComboBox.DisplayMember = "DisplayText";
            RWComboBox.DataSource = rwComboBoxCollection;
            RWComboBox.SelectedIndex = -1;
        }
        private void TypeComboBox_SelectedValueChanged(object sender, EventArgs e)
        {
            if (couldBeBind == false)
            {
                TypeComboBox.SelectedIndex = -1;
                NameComboBox.SelectedIndex = -1;
                return;
            }
            try
            {
                currentType = TypeComboBox.SelectedValue.ToString();
            }
            catch { }
            NameComboBox.DataSource = null;
            if (currentType != "")
            //    if (currentType != "" && currentID != "")
            {
                DataTable db = cbc.GetAllName(currentType);
                if (db == null)
                    return;
                NameComboBox.ValueMember = "id";
                NameComboBox.DisplayMember = "Name";
                NameComboBox.DataSource = db;
                NameComboBox.SelectedIndex = -1;
                if (currentBindName != "")
                {
                    currentName = currentBindName;
                    NameComboBox.SelectedIndex = NameComboBox.FindString(currentName);
                    //NameComboBox.SelectedValue = Convert.ToInt32(currentID);
                }
            }
        }

        private void NameComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (NameComboBox.SelectedValue == null)
                return;
            currentName = NameComboBox.SelectedText.ToString();
        }

        class TextAndValue
        {
            private string _RealValue = "";
            private string _DisplayText = "";

            public string DisplayText
            {
                get
                {
                    return _DisplayText;
                }
            }

            public string RealValue
            {
                get
                {
                    return _RealValue;
                }
            }

            public TextAndValue(string ShowText, string RealVal)
            {
                _DisplayText = ShowText;
                _RealValue = RealVal;
            }

            public override string ToString()
            {
                return _RealValue.ToString();
            }

        }

        private void UpdataButton_Click(object sender, EventArgs e)
        {
            if (couldBeBind == false)
                return;
            Type t = currentObj.GetType();

            if (t.Name.Equals("TextBox"))
            {
                Library.TextBox tb = (Library.TextBox)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);

                dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                //PropertyInfo m_DeviceID = t.GetProperty("ID");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                //m_DeviceID.SetValue(tb, currentID, null);
                m_DeviceName.SetValue(tb, currentName, null);
                currentType = "";
                currentName = "";
                /*  ================旧方法，不再使用，使用新的数据表及绑定方法，2016-3-26 xuehaoyuan
                currentID = NameComboBox.SelectedValue.ToString();
                dataPT.GetBoardPortByPointID(dataPT.GetReadPointID(currentType, currentID), ref BoardNumber, ref RelatedPort);
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                PropertyInfo m_DeviceID = t.GetProperty("ID");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                m_DeviceID.SetValue(tb, currentID, null);
                m_DeviceName.SetValue(tb, currentName, null);
                currentType = "";
                currentID = "";
                currentName = "";
                */
            }
            if (t.Name.Equals("levelmeter"))
            {
                Library.Common.levelmeter tb = (Library.Common.levelmeter)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);
                dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);

                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                PropertyInfo m_LevelRange = t.GetProperty("LevelRange");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
           //     m_LevelRange.SetValue(tb, currentLevelRange, null);
                m_DeviceName.SetValue(tb, currentName, null);

                currentType = "";
                currentName = "";
 
            }
            if (t.Name.Equals("statusIndicator"))
            {
                Library.statusIndicator tb = (Library.statusIndicator)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                 if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);
                if (RWComboBox.SelectedValue == null)
                    MessageBox.Show("Please Select R/W Model", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);
    
                dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                // 
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");

                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");
          

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                m_DeviceName.SetValue(tb, currentName, null);
                //m_DeviceID.SetValue(tb, currentID, null);

                currentType = "";
                //currentID = "";
                currentName = "";
      
            }
            if (t.Name.Equals("Led"))
            {
                Library.Led tb = (Library.Led)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                string PortData = "";
                string PortBind = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);
                if (RWComboBox.SelectedValue == null)
                    MessageBox.Show("Please Select R/W Model", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);
                else if (RWComboBox.SelectedValue.ToString() == "Read")
                    dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                else if (RWComboBox.SelectedValue.ToString() == "Write")
                    dataPT.GetBoardSendPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                // 
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                //PropertyInfo m_DeviceID = t.GetProperty("ID");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");
                PropertyInfo m_PortData = t.GetProperty("PortData");
                PropertyInfo m_PortBind = t.GetProperty("PortBind");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                //m_DeviceID.SetValue(tb, currentID, null);
                m_DeviceName.SetValue(tb, currentName, null);
                m_PortData.SetValue(tb, PortData, null);
                m_PortBind.SetValue(tb, PortBind, null);
                currentType = "";
                //currentID = "";
                currentName = "";
                PortData = "";
                PortBind = "";
            }

            if (t.Name.Equals("SendButton"))
            {
                Library.SendButton tb = (Library.SendButton)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                string PortData = "";
                string PortBind = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);
                if (RWComboBox.SelectedValue == null)
                    MessageBox.Show("Please Select R/W Model", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);
                else if (RWComboBox.SelectedValue.ToString() == "Read")
                    dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                else if (RWComboBox.SelectedValue.ToString() == "Write")
                    dataPT.GetBoardSendPortByNameType(currentName, currentType,  ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                // 
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                //PropertyInfo m_DeviceID = t.GetProperty("ID");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");
                PropertyInfo m_PortData = t.GetProperty("PortData");
                PropertyInfo m_PortBind = t.GetProperty("PortBind");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                //m_DeviceID.SetValue(tb, currentID, null);
                m_DeviceName.SetValue(tb, currentName, null);
                m_PortData.SetValue(tb, PortData, null);
                m_PortBind.SetValue(tb, PortBind, null);
                currentType = "";
                //currentID = "";
                currentName = "";
                PortData = "";
                PortBind = "";
           
            }
            if (t.Name.Equals("Regenerator1"))
            {
                Library.LDDS.Regenerator1 tb = (Library.LDDS.Regenerator1)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);

                dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");

                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");

                m_BoardNumber.SetValue(tb, BoardNumber, null);

                m_DeviceName.SetValue(tb, currentName, null);
                currentType = "";
                currentName = "";
            }
            if (t.Name.Equals("Regenerator3"))
            {
                Library.LDDS.Regenerator3 tb = (Library.LDDS.Regenerator3)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);

                dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");

                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");

                m_BoardNumber.SetValue(tb, BoardNumber, null);

                m_DeviceName.SetValue(tb, currentName, null);
                currentType = "";
                currentName = "";
            }
            if (t.Name.Equals("Dehumidifier1"))
            {
                Library.LDDS.Dehumidifier1 tb = (Library.LDDS.Dehumidifier1)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);

                dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");

                m_BoardNumber.SetValue(tb, BoardNumber, null);

                m_DeviceName.SetValue(tb, currentName, null);
                currentType = "";
                currentName = "";
            }
            if (t.Name.Equals("ButtonCheck"))
            {
                Library.Common.ButtonCheck tb = (Library.Common.ButtonCheck)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                string PortData = "";
                string PortBind = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);
                if (RWComboBox.SelectedValue == null)
                    MessageBox.Show("Please Select R/W Model", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);
                else if (RWComboBox.SelectedValue.ToString() == "Read")
                    dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                else if (RWComboBox.SelectedValue.ToString() == "Write")
                    dataPT.GetBoardSendPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                // 
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");
                PropertyInfo m_PortData = t.GetProperty("PortData");
                PropertyInfo m_PortBind = t.GetProperty("PortBind");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                //m_DeviceID.SetValue(tb, currentID, null);
                m_DeviceName.SetValue(tb, currentName, null);
                m_PortData.SetValue(tb, PortData, null);
                m_PortBind.SetValue(tb, PortBind, null);
                currentType = "";
                currentName = "";
                PortData = "";
                PortBind = "";
            }
            if (t.Name.Equals("ButtonCheckFun"))
            {
                Library.Common.ButtonCheckFun tb = (Library.Common.ButtonCheckFun)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                string PortData = "";
                string PortBind = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);
                if (RWComboBox.SelectedValue == null)
                    MessageBox.Show("Please Select R/W Model", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);
                else if (RWComboBox.SelectedValue.ToString() == "Read")
                    dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                else if (RWComboBox.SelectedValue.ToString() == "Write")
                    dataPT.GetBoardSendPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                // 
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");
                PropertyInfo m_PortData = t.GetProperty("PortData");
                PropertyInfo m_PortBind = t.GetProperty("PortBind");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                //m_DeviceID.SetValue(tb, currentID, null);
                m_DeviceName.SetValue(tb, currentName, null);
                m_PortData.SetValue(tb, PortData, null);
                m_PortBind.SetValue(tb, PortBind, null);
                currentType = "";
                currentName = "";
                PortData = "";
                PortBind = "";
            }
            if (t.Name.Equals("RunState"))
            {
                Library.Common.RunState tb = (Library.Common.RunState)currentObj;
                DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                string BoardNumber = "";
                string RelatedPort = "";
                if (TypeComboBox.SelectedValue == null)
                {
                    MessageBox.Show("Please select a Type!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (NameComboBox.SelectedItem == null)
                {
                    MessageBox.Show("Please select a name!", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                currentType = TypeComboBox.SelectedValue.ToString();
                currentName = NameComboBox.GetItemText(NameComboBox.SelectedItem);
                if (RWComboBox.SelectedValue == null)
                    MessageBox.Show("Please Select R/W Model", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);
                else
                    dataPT.GetBoardPortByNameType(currentName, currentType, ref BoardNumber, ref RelatedPort);
                PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                PropertyInfo m_DeviceName = t.GetProperty("DeviceName");

                m_BoardNumber.SetValue(tb, BoardNumber, null);
                m_RelatedPort.SetValue(tb, RelatedPort, null);
                m_DeviceType.SetValue(tb, currentType, null);
                m_DeviceName.SetValue(tb, currentName, null);
                currentType = "";
                currentName = "";
            }
          
        }

    }
}
