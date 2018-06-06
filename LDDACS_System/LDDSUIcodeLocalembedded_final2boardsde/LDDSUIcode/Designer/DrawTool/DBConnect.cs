//====================================================================
// 文件名: DBConnect.cs
//
// 文件描述:
// ------------------------------------------------------------------
// 关联数据库
// ------------------------------------------------------------------
// 
// 时间: 2015.08
// 编程: xuehaoyuan
// ------------------------------------------------------------------
// 修改说明(请按格式说明)...
// ------------------------------------------------------------------
// 请对 较复杂函数 所实现功能、输入输出做较细致说明
//====================================================================

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;

namespace Designer.DrawTool
{
    public partial class DBConnect : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        private static string DATABASECON = "connSys";
        private static int GETALLDATA = -1;     
        private static int CHANGEBYCLICK = 0;   //通过鼠标点击改变combobox选项
        private static int CHANGEBYFUN = 1;     //通过函数改变combobox选项

        private DataTable ProjectDataTable;
        private DataTable ModulesDataTable;
        private DataTable FunUnitsDataTable;
        private DataTable DevicesDataTable;

        public MainForm mainForm;
        
        private string selectedProID;//已经选择的项目id
        private string selectedModuleTypeID;
        private string selectedModuleTypeName;
        private string selectedModuleID;
        private string selectedFunUnitID;
        private string selectedDeviceID;
        private string selectedDeviceTypeName;
        private string selectedDeviceTypeIndex;

        //DataBus
        private DataBus.DataForDBTool.CDataForDBTool dataForDBTool = new DataBus.DataForDBTool.CDataForDBTool();
        
        private enum ModuleType
        {
            
            LDDS= 1,
            Dehumidifier,
            Regenerator
        };
        private enum DeviceType
        {
            Sensor = 1,
            Actuator,
            Fan
        };

        public DBConnect()
        {
            InitializeComponent();
//不需要
//             ProjectDataTable = new DataTable();
//             ModulesDataTable = new DataTable();
//             FunUnitsDataTable = new DataTable(); 
//             DevicesDataTable = new DataTable(); 
            InitCombobox();
        }
        public void InitCombobox()
        {
            SetProjectComboBox(GETALLDATA, CHANGEBYCLICK);
        }


        //根据ID获取project表
        private DataTable GetProjectByID(int id)
        {
//             string sql = "select name, id from Project";
//             if (id != GETALLDATA)
//             {
//                // sql += " where id = '" + id + "'";
//                 sql += " where id = " + id ;
//             }
//             
            DataTable dt = new DataTable();
            dt = dataForDBTool.GetProjectByID(id, GETALLDATA);
            return dt;
        }
        //根据ProjectID和ModuleID ModuleType获取FunctionUnit表
        private DataTable GetSelectedFunctionUnit()
        {
            string sql = "select name, id from functionUnit";
            if (selectedProID != "")
            {
                // sql += " where id = '" + id + "'";
                sql += " where projectid = " + selectedProID;
            }
            if (selectedModuleTypeID != "")
            {
                // sql += " where id = '" + id + "'";
                sql += " and ModuleType = " + selectedModuleTypeID;
            }
            if (selectedModuleID != "")
            {
                // sql += " where id = '" + id + "'";
                sql += " and ModuleID = " + selectedModuleID;
            }
            DataTable dt = new DataTable();
            //dt = StaticFunctions.DAStaticFunctions.querySql(sql, DATABASECON);
            dt = dataForDBTool.MySqlQuery(sql);
            return dt;
        }
        //根据ProjectID和ModuleID, ModuleType, FunctionUnitID获取Device表
        private DataTable GetSelectedDevice(string deviceType)
        {
            string sql = "select * from " + deviceType;
            if (selectedProID != "")
            {
                // sql += " where id = '" + id + "'";
                sql += " where projectid = " + selectedProID;
            }
            if (selectedModuleTypeID != "")
            {
                // sql += " where id = '" + id + "'";
                sql += " and ModuleType = " + selectedModuleTypeID;
            }
            if (selectedModuleID != "")
            {
                // sql += " where id = '" + id + "'";
                sql += " and ModuleID = " + selectedModuleID;
            }
            if (selectedFunUnitID != "")
            {
                // sql += " where id = '" + id + "'";
                sql += " and FunctionUnitID = " + selectedFunUnitID;
            }
            DataTable dt = new DataTable();
            //dt = StaticFunctions.DAStaticFunctions.querySql(sql, DATABASECON);
            dt = dataForDBTool.MySqlQuery(sql);
            return dt;
        }
        private void SetProjectComboBox(int currentIndex, int changeType)
        {
            ProjectComboBox.SelectedValueChanged -= new EventHandler(ProjectComboBoxValueChanged);
            ProjectDataTable = GetProjectByID(GETALLDATA);
            ProjectComboBox.DisplayMember = "name";
            //ProjectComboBox.ValueMember = "name";
            ProjectComboBox.DataSource = ProjectDataTable;
            ProjectComboBox.SelectedIndex = currentIndex;
            if (CHANGEBYFUN == changeType)
            {
            }
            else 
            {
            }
            ProjectComboBox.SelectedValueChanged += new EventHandler(ProjectComboBoxValueChanged);
        }
        private void SetModuleTypeComboBox(int currentIndex, int changeType)
        {
            ModuleTypeComboBox.SelectedValueChanged -= new EventHandler(ModuleTypeComboBoxValueChanged);
            ModuleTypeComboBox.Items.Clear();
            foreach (string i in Enum.GetNames(typeof(ModuleType)))
            {
                ModuleTypeComboBox.Items.Add(i);
            }
            ModuleTypeComboBox.SelectedIndex = currentIndex;
           
            ModuleTypeComboBox.SelectedValueChanged += new EventHandler(ModuleTypeComboBoxValueChanged);
        }
        private void SetModuleNameComboBox(int currentIndex, int changeType)
        {
            ModuleNameComboBox.SelectedValueChanged -= new EventHandler(ModuleNameComboBoxValueChanged);
            if (selectedModuleTypeName == "" || selectedModuleTypeName == null)
                return;
            string sql = "select name, id, projectid from " + selectedModuleTypeName + " where projectid = " + selectedProID;

            //ModulesDataTable = StaticFunctions.DAStaticFunctions.querySql(sql, DATABASECON);
            ModulesDataTable = dataForDBTool.MySqlQuery(sql);

            ModuleNameComboBox.ValueMember = "name";
            ModuleNameComboBox.DisplayMember = "name";
            ModuleNameComboBox.DataSource = ModulesDataTable;
            
            if (CHANGEBYFUN == changeType)
            {
                DataRow[] matches = ModulesDataTable.Select(" id = " + currentIndex);
                ModuleNameComboBox.SelectedValue = matches[0]["name"];
            }
            else
            {
                ModuleNameComboBox.SelectedIndex = -1;
            }
            ModuleNameComboBox.SelectedValueChanged += new EventHandler(ModuleNameComboBoxValueChanged);
            
        }
        private void SetFunUnitComboBox(int currentIndex, int changeType)
        {
            FunctionUnitComboBox.SelectedValueChanged -= new EventHandler(FunctionUnitComboBoxValueChanged);
            FunUnitsDataTable = GetSelectedFunctionUnit();
            FunctionUnitComboBox.ValueMember = "name";
            FunctionUnitComboBox.DisplayMember = "name";
            FunctionUnitComboBox.DataSource = FunUnitsDataTable;
            if (CHANGEBYFUN == changeType)
            {
                DataRow[] matches = FunUnitsDataTable.Select(" id = " + currentIndex);
                FunctionUnitComboBox.SelectedValue = matches[0]["name"];
            }
            else
            {
                FunctionUnitComboBox.SelectedIndex = -1;
            }
            FunctionUnitComboBox.SelectedValueChanged += new EventHandler(FunctionUnitComboBoxValueChanged);
        }
        private void SetDeviceTypeComboBox(string typeName, int changeType)
        {
            DeviceTypeComboBox.SelectedValueChanged -= new EventHandler(DeviceTypeComboBoxValueChanged);
            DeviceTypeComboBox.Items.Clear();
            foreach (string i in Enum.GetNames(typeof(DeviceType)))
            {
                DeviceTypeComboBox.Items.Add(i);
            }
            if (CHANGEBYFUN == changeType)
            {
                DeviceTypeComboBox.SelectedItem = typeName;
            }
            else
            {
                DeviceTypeComboBox.SelectedIndex = -1;
            }
            DeviceTypeComboBox.SelectedValueChanged += new EventHandler(DeviceTypeComboBoxValueChanged);
        }
        private void SetDeviceComboBox(int currentIndex, int changeType)
        {
            DeviceNameComboBox.SelectedValueChanged -= new EventHandler(DeviceComboBoxValueChanged);
            DevicesDataTable = GetSelectedDevice(selectedDeviceTypeName);
            DeviceNameComboBox.ValueMember = "name";
            DeviceNameComboBox.DisplayMember = "name";
            DeviceNameComboBox.DataSource = DevicesDataTable;
            if (CHANGEBYFUN == changeType)
            {
                DataRow[] matches = DevicesDataTable.Select(" id = " + currentIndex);
                DeviceNameComboBox.SelectedValue = matches[0]["name"];
            }
            else
            {
                DeviceNameComboBox.SelectedIndex = -1;
            }
            DeviceNameComboBox.SelectedValueChanged += new EventHandler(DeviceComboBoxValueChanged);
        }

        //选择project
        private void ProjectComboBoxValueChanged(object sender, EventArgs e)
        {
            if (ProjectDataTable == null)
                return;
            int row = ProjectComboBox.SelectedIndex;
            selectedProID = ProjectDataTable.Rows[row]["id"].ToString();
            SetModuleTypeComboBox(GETALLDATA, CHANGEBYCLICK);
        }
        //选择ModuleType
        private void ModuleTypeComboBoxValueChanged(object sender, EventArgs e)
        {
            selectedModuleTypeName = ModuleTypeComboBox.SelectedItem.ToString();
            selectedModuleTypeID = (ModuleTypeComboBox.SelectedIndex+1).ToString();
            SetModuleNameComboBox(GETALLDATA, CHANGEBYCLICK);
        }
        //选择Module
        private void ModuleNameComboBoxValueChanged(object sender, EventArgs e)
        {
            if (ModulesDataTable == null)
                return;
            int row = ModuleNameComboBox.SelectedIndex;
            if (row == -1)
                selectedModuleID = "";
            else
                selectedModuleID = ModulesDataTable.Rows[row]["id"].ToString();
            SetFunUnitComboBox(GETALLDATA, CHANGEBYCLICK);
        }
        //选择FunUnit
        private void FunctionUnitComboBoxValueChanged(object sender, EventArgs e)
        {
            selectedFunUnitID = (FunctionUnitComboBox.SelectedIndex + 1).ToString();
            SetDeviceTypeComboBox("", CHANGEBYCLICK);
        }
        //选择DeviceType
        private void DeviceTypeComboBoxValueChanged(object sender, EventArgs e)
        {
            selectedDeviceTypeName = DeviceTypeComboBox.SelectedItem.ToString();
            selectedDeviceTypeIndex = (DeviceTypeComboBox.SelectedIndex + 1).ToString();
            SetDeviceComboBox(GETALLDATA, CHANGEBYCLICK);
        }
        //选择device
        private void DeviceComboBoxValueChanged(object sender, EventArgs e)
        {
            selectedDeviceID = DevicesDataTable.Rows[DeviceNameComboBox.SelectedIndex]["id"].ToString();
        }

        private void Update_Click(object sender, EventArgs e)
        {
            object selectedObj = mainForm.drawToolWindow.getCurrentSelectedObj();
            if (selectedObj == null)
            {
                MessageBox.Show("请选择组件", "提示", MessageBoxButtons.OK);
                return;
            }
            if (selectedDeviceID == null)
            {
                MessageBox.Show("请选择数据库", "提示", MessageBoxButtons.OK);
                return;
            }
            Type type = selectedObj.GetType();
            if (type.Name == "PictureBox" || type.Name == "TextBox")
            {
                //可能会有问题暂时未处理 2015-8-12 22:03:11已处理
                //Type examType = typeof(PictureBox);
                // Change the static property value.
                PropertyInfo m_id = type.GetProperty("ID");
                PropertyInfo m_type = type.GetProperty("Type");

                //更新值前去掉原始值
                string oldID = m_id.GetValue(selectedObj, null).ToString();
                string oldType = m_type.GetValue(selectedObj, null).ToString();
                

                m_id.SetValue(selectedObj, selectedDeviceID, null);
                m_type.SetValue(selectedObj, selectedDeviceTypeName, null);
                if (type.Name == "TextBox")
                {
                    string sql = "update " + oldType + " set TextBoxName =  '' where id = " + oldID;
                    //StaticFunctions.DAStaticFunctions.exeSql(sql, StaticFunctions.DAStaticFunctions.DATABASECON);
                    dataForDBTool.MySqlExe(sql);

                    Library.TextBox s = selectedObj as Library.TextBox;
                    sql = "update " + selectedDeviceTypeName + " set TextBoxName =  '" + s.Name + "' where id = " + selectedDeviceID;
                    //StaticFunctions.DAStaticFunctions.exeSql(sql,StaticFunctions.DAStaticFunctions.DATABASECON);
                    dataForDBTool.MySqlExe(sql);
                
                }
                if (type.Name == "Dehumidifier1")
                {
                    string sql = "update " + oldType + " set TextBoxName =  '' where id = " + oldID;
                    //StaticFunctions.DAStaticFunctions.exeSql(sql, StaticFunctions.DAStaticFunctions.DATABASECON);
                    dataForDBTool.MySqlExe(sql);

                    Library.LDDS.Dehumidifier1 s = selectedObj as Library.LDDS.Dehumidifier1;
                    sql = "update " + selectedDeviceTypeName + " set TextBoxName =  '" + s.Name + "' where id = " + selectedDeviceID;
                    //StaticFunctions.DAStaticFunctions.exeSql(sql,StaticFunctions.DAStaticFunctions.DATABASECON);
                    dataForDBTool.MySqlExe(sql);

                }
                else if (type.Name == "PictureBox")
                {
                    string sql = "update " + oldType + " set PictureName =  '' where id = " + oldID;
                    //StaticFunctions.DAStaticFunctions.exeSql(sql, StaticFunctions.DAStaticFunctions.DATABASECON);
                    dataForDBTool.MySqlExe(sql);

                    Library.PictureBox s = selectedObj as Library.PictureBox;
                    sql = "update " + selectedDeviceTypeName + " set PictureName =  '" + s.Name + "' where id = " + selectedDeviceID;
                    //StaticFunctions.DAStaticFunctions.exeSql(sql, StaticFunctions.DAStaticFunctions.DATABASECON);
                    dataForDBTool.MySqlExe(sql);

                }
            }
        }

        //载入对应的数据库属性
        private void Load_Click(object sender, EventArgs e)
        {
            object selectedObj = mainForm.drawToolWindow.getCurrentSelectedObj();
            if (selectedObj == null)
            {
                MessageBox.Show("请选择组件", "提示", MessageBoxButtons.OK);
                return;
            }
            //Type type = selectedObj.GetType().Name.ToString();
            if (selectedObj.GetType().Name.ToString() == "PictureBox" || selectedObj.GetType().Name.ToString() == "TextBox")
            {
                string type = null;
                string id   = null;
                switch (selectedObj.GetType().Name.ToString())
                {
                    case "PictureBox" :
                        Library.PictureBox pb = (Library.PictureBox)selectedObj;
                        if (pb.ID == null || pb.RelatedDeviceType == null)
                        {
                            MessageBox.Show("组件未绑定", "提示", MessageBoxButtons.OK);
                            return;
                        }
                        type = pb.RelatedDeviceType.ToString();
                        id = pb.ID.ToString();
                        break;
                    case "TextBox" :
                        Library.TextBox tb = (Library.TextBox)selectedObj;
                        if (tb.ID == null || tb.RelatedDeviceType == null)
                        {
                            MessageBox.Show("组件未绑定", "提示", MessageBoxButtons.OK);
                            return;
                        }
                        type = tb.RelatedDeviceType.ToString();
                        id = tb.ID.ToString();
                        break;
                    default:
                        break;
                }

                string sql = "select * from " + type + " where id = " + id;
                DataTable dt = new DataTable();
                //dt = StaticFunctions.DAStaticFunctions.querySql(sql, DATABASECON);
                dt = dataForDBTool.MySqlQuery(sql);

                //获取组件对应的数据库信息
                selectedProID = dt.Rows[0]["Projectid"].ToString();
                SetProjectComboBox(Int32.Parse(selectedProID) - 1, CHANGEBYFUN);
                selectedModuleTypeID = dt.Rows[0]["moduletype"].ToString();
                selectedModuleTypeName = Enum.GetName(typeof(ModuleType), Int32.Parse(selectedModuleTypeID));
                SetModuleTypeComboBox(Int32.Parse(selectedModuleTypeID) - 1, CHANGEBYFUN);
                selectedModuleID = dt.Rows[0]["Moduleid"].ToString();
                SetModuleNameComboBox(Int32.Parse(selectedModuleID) , CHANGEBYFUN);
                selectedFunUnitID = dt.Rows[0]["functionUnitid"].ToString();
                SetFunUnitComboBox(Int32.Parse(selectedFunUnitID), CHANGEBYFUN);
                selectedDeviceID = id;
                selectedDeviceTypeName = type;
                SetDeviceTypeComboBox(selectedDeviceTypeName, CHANGEBYFUN);
                SetDeviceComboBox(Int32.Parse(selectedDeviceID) , CHANGEBYFUN);
            }
        }
    }
}
