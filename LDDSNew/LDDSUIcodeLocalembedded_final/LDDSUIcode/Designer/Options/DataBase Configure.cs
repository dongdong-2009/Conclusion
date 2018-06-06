using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using System.Net;
using System.Text.RegularExpressions;//正则

namespace Designer.Options
{
    public partial class DataBase_Configure : Form
    {
        //public string CONFIGURATION_FILE_NAME = "..\\..\\app.config";
        public string CONFIGURATION_FILE_NAME = "..\\..\\..\\DataBus\\app.config";
        private string oldIP = null;
        public DataBase_Configure()
        {
            InitializeComponent();
            GetAppSettings();
        }

        private void GetAppSettings()
        {
            //string ConnectionString = System.Configuration.ConfigurationManager.ConnectionStrings["connSys"].ToString();
            //Server=(local);uid=sa;pwd=sa;DataBase=BSTAR
            //string ConnectionString = System.Configuration.ConfigurationManager.AppSettings[StaticFunctions.DAStaticFunctions.DATABASECON].ToString();
            string ConnectionString = System.Configuration.ConfigurationManager.OpenMappedExeConfiguration(new ExeConfigurationFileMap() { ExeConfigFilename = CONFIGURATION_FILE_NAME }, ConfigurationUserLevel.None).AppSettings.Settings[StaticFunctions.DAStaticFunctions.DATABASECON].Value;
            string[] sArray = ConnectionString.Split(new char[2] { '=', ';' });

            IP.Text = sArray[1];
            DB.Text = sArray[3];
            UID.Text = sArray[5];
            PWD.Text = sArray[7];
            Port.Text = sArray[9];

            oldIP = IP.Text;
        }
        private void AccessAppSettings(string con)
        {
            //获取Configuration对象

            Configuration config = System.Configuration.ConfigurationManager.OpenMappedExeConfiguration(new ExeConfigurationFileMap() { ExeConfigFilename = CONFIGURATION_FILE_NAME }, ConfigurationUserLevel.None);

            //Configuration config = System.Configuration.ConfigurationManager.OpenMachineConfiguration(s);
            //Configuration configtmp = System.Configuration.ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            //根据Key读取<add>元素的Value
            //string name = config.AppSettings.Settings["connSys"].Value;
            //写入<add>元素的Value
            config.AppSettings.Settings[StaticFunctions.DAStaticFunctions.DATABASECON].Value = con;
            //configtmp.AppSettings.Settings["connSys"].Value = con;
            //增加<add>元素
            //config.AppSettings.Settings.Add("url", "要加的元素");
            //删除<add>元素
            //config.AppSettings.Settings.Remove("name");
            //一定要记得保存，写不带参数的config.Save()也可以
            config.Save(ConfigurationSaveMode.Modified);
            //刷新，否则程序读取的还是之前的值（可能已装入内存）
            //string ConnectionString = System.Configuration.ConfigurationManager.AppSettings["connSys"].ToString();
            
            System.Configuration.ConfigurationManager.RefreshSection("appSettings");
        }

        private void Update_Click(object sender, EventArgs e)
        {
            //server = (local); Database = BSTAR; Uid = sa; Pwd = sa;
            string con = "Server=" + IP.Text +
                ";DataBase=" + DB.Text +
                ";User=" + UID.Text +
                ";Password=" + PWD.Text +
                ";port=" + Port.Text;
            AccessAppSettings(con);
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }


        private void IP_Leave(object sender, EventArgs e)
        {
            Regex objRegex = new Regex(@"^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$");
            if (!(objRegex.IsMatch(IP.Text) || IP.Text == "(local)"))
            {
                IP.Text = oldIP;
                MessageBox.Show("IP格式不正确！请重新输入！", "提示", MessageBoxButtons.OK);
                //this.Focus();
                return;
            }
        }

        private void Test_Click(object sender, EventArgs e)
        {
            string con = "Server=" + IP.Text +
                ";DataBase=" + DB.Text +
                ";User=" + UID.Text +
                ";Password=" + PWD.Text +
                ";port=" + Port.Text;
            try
            {
                if (DataBus.DataBus_MySqlHelper.testConnection(con))
                    MessageBox.Show("Success");
                else
                    MessageBox.Show("failure");
            }
            catch
            { }
            //sqlserver
            /*
            string con = "Server=" + IP.Text + ";uid=" + UID.Text + ";pwd=" + PWD.Text + ";DataBase=" + DB.Text + ";";

            try
            {
                if (StaticFunctions.DAStaticFunctions.testConnection(con))
                     MessageBox.Show("Success");
                 else
                     MessageBox.Show("failure");
            }
            catch
            { }
             */
        }

        private void Port_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != 8 && !Char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        
    }
}
