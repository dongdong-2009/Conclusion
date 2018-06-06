//====================================================================
// 文件名: DBProgram.cs
//
// 文件描述:  显示数据库相关表，增删改
// ------------------------------------------------------------------
// DBTOOL功能类
// ------------------------------------------------------------------
// 
// 时间: 2015.07
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
using System.Drawing.Design;
using System.Drawing.Drawing2D;
using System.Data.SqlClient;
using System.Collections;
using System.ComponentModel.Design;
using MySql.Data.MySqlClient;

namespace Designer.DBTool
{
    public class DBProgram
    {
        #region 变量
        //主窗口
        public MainForm m_mainform;
        private TreeBoxWindow m_treeBoxWin;
        private GridWindow m_gridWin;
        private int sampleTableLength=57;
       //DataBus
        private DataBus.DataForDBTool.CDataForDBTool dataForDBTool = new DataBus.DataForDBTool.CDataForDBTool();

        private List<boardType> btDeCoilCwList;
        private List<boardType> btDeNoCoilCwList;
        private List<boardType> btDeCoilHpList;
        private List<boardType> btDeNoCoilHpList;

        private List<boardType> btReAdjHwList;
        private List<boardType> btReNoAdjHwList;
        private List<boardType> btReAdjHpList;
        private List<boardType> btReNoAdjHpList;
       
        //存库
        private DataSet dataGridViewDataSet;

        //mysql存库
        private MySqlConnection msqlCnt;
        private MySqlDataAdapter mysql_dataGridViewDataAdapter;

        private String currentTableName;
        //名称索引
        private DataTable typeNamedt = new DataTable();

        //表是否编辑
        private int boardNumInt = 0;
        //编辑之前的原始表     未使用                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        private DataTable originalDataTable = new DataTable();

        //private static readonly string connectionString = System.Configuration.ConfigurationManager.AppSettings["con"].ToString().Trim();

        //LoopConfigurer
 //       private LoopConfigurer.FormLoopConfig flcfg;

        #endregion 变量

    
        #region Private 方法



        //TreeItem单击事项
        private void TreeItemClicked(object sender, TreeNodeMouseClickEventArgs e)
        {

            TreeNode tn = e.Node;
            m_gridWin.dataGridView1.DataSource = null;
            m_gridWin.dataGridView1.Rows.Clear();
            originalDataTable.Clear();
            currentTableName = tn.Text;
            m_gridWin.TabText = tn.Text;

            string sql = "select * from ide_point";
             sql += " where Number = '" + currentTableName+"'";

            msqlCnt = DataBus.DataForDBTool.CDataForDBTool.GetConn();
            try
            {
                msqlCnt.Open();
                mysql_dataGridViewDataAdapter = new MySqlDataAdapter(sql, msqlCnt);
                dataGridViewDataSet = new DataSet();
                mysql_dataGridViewDataAdapter.Fill(dataGridViewDataSet, currentTableName);
                //originalDataTable = dataGridViewDataSet.Tables[FormName].Clone();
                DataTable sourceDt = dataGridViewDataSet.Tables[currentTableName];
                m_gridWin.dataGridView1.DataSource = sourceDt;

                m_gridWin.Show(m_mainform.dockPanel1);
                m_gridWin.TabText = currentTableName;

            }
            catch
            {

            }


        }

        private void ShowDataTable(String tableName)
        {
            DataTable sourceDt = new DataTable();
            sourceDt = dataGridViewDataSet.Tables["point"];
            m_gridWin.dataGridView1.DataSource = sourceDt;

            //去掉自动排序
            for (int i = 0; i < m_gridWin.dataGridView1.Columns.Count; i++)
            {
                m_gridWin.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            m_gridWin.dataGridView1.Columns["ID"].ReadOnly = true;

        }

    
        private void CloseSql()
        {
            //xhy 2016年1月26日13:08:28
            //dataGridViewDataSet.Dispose();          // 释放DataSet对象
            //dataGridViewDataAdapter.Dispose();      // 释放SqlDataAdapter对象
           // mysql_dataGridViewDataAdapter.Dispose();
            //sqlCnt.Close();                         // 关闭数据库连接
            //sqlCnt.Dispose();                       // 释放数据库连接对象
        }

        private void checkDatabase()
        {
            string sql = "";
            int typeCount = 0;

            msqlCnt = DataBus.DataForDBTool.CDataForDBTool.GetConn();

            if (msqlCnt.State != ConnectionState.Open)
                msqlCnt.Open();

            sql = "CREATE TABLE IF NOT EXISTS ide_point" +
                  "(Id int not null auto_increment," +
                  "Number varchar(255)," +
                  "Port varchar(255)," +
                  "Description varchar(255)," +
                  "Name varchar(255)," +
                  "Bindport varchar(255)," +
                  "Status varchar(255)," +
                  "Senddataport varchar(255)," +
                  "Type varchar(255)," +
                  "Primary key(id) )";

            int dt = DataBus.DataBus_MySqlHelper.ExecuteSql(sql);

            sql = "SELECT COUNT(ID) FROM ide_point";

            dt = int.Parse(DataBus.DataBus_MySqlHelper.GetSingle(sql).ToString());

            typeCount = btDeCoilCwList.Count() + btDeNoCoilCwList.Count() + btDeCoilHpList.Count() + btDeNoCoilHpList.Count() +
                         btReAdjHwList.Count() + btReNoAdjHwList.Count() + btReAdjHpList.Count() + btReNoAdjHpList.Count();


            if (dt != typeCount * sampleTableLength)
            {
                sql = "TRUNCATE table ide_point";
                dt = DataBus.DataBus_MySqlHelper.ExecuteSql(sql);

                for (int i = 0; i < btDeCoilCwList.Count(); i++)
                {
                    addNewContent("DeCoilCw");
                }
                for (int i = 0; i < btDeNoCoilCwList.Count(); i++)
                {
                    addNewContent("DeNoCoilCw");
                }
                for (int i = 0; i < btDeCoilHpList.Count(); i++)
                {
                    addNewContent("DeCoilHp");
                }
                for (int i = 0; i < btDeNoCoilHpList.Count(); i++)
                {
                    addNewContent("DeNoCoilHp");
                }
                for (int i = 0; i < btReAdjHwList.Count(); i++)
                {
                    addNewContent("ReAdjHw");
                }
                for (int i = 0; i < btReNoAdjHwList.Count(); i++)
                {
                    addNewContent("ReNoAdjHw");
                }
                for (int i = 0; i < btReAdjHpList.Count(); i++)
                {
                    addNewContent("ReAdjHp");
                }
                for (int i = 0; i < btReNoAdjHpList.Count(); i++)
                {
                    addNewContent("ReNoAdjHp");

                }
            }
        }

        private void addNewContent(string myboard)
        {
            string sql = "";
           
            sql = "SELECT COUNT(ID) FROM ide_point";

            int cnt = int.Parse(DataBus.DataBus_MySqlHelper.GetSingle(sql).ToString());

            if (cnt == 0)
            {
                sql = "INSERT INTO ide_point" +
                        "(Port,Description,Name,Bindport,Status,Senddataport,Type)" +
                        "SELECT Port,Description,Name,Bindport,Status,Senddataport,Type FROM " +
                         myboard + "_sample";
                DataBus.DataBus_MySqlHelper.ExecuteSql(sql);

                sql = "UPDATE ide_point SET Number ='" + 0 +
                     0.ToString().PadLeft(3, '0') +
                    "0000' where id <= " + sampleTableLength + " and id>" + 0;

                int dt = DataBus.DataBus_MySqlHelper.ExecuteSql(sql);

            }
            else
            {
              
                sql = "SELECT number FROM ide_point ORDER BY id DESC LIMIT 1";
                string str = DataBus.DataBus_MySqlHelper.GetSingle(sql).ToString();

                string boardnum = str.Trim('0');

                if (boardnum == "")
                    boardNumInt = 1;
                else
                    boardNumInt++;

                sql = "INSERT INTO ide_point" +
                      "(Port,Description,Name,Bindport,Status,Senddataport,Type)" +
                      "SELECT Port,Description,Name,Bindport,Status,Senddataport,Type FROM " +
                       myboard + "_sample";
                DataBus.DataBus_MySqlHelper.ExecuteSql(sql);

                sql = "SELECT id FROM ide_point ORDER BY id DESC LIMIT 1";
                int num = int.Parse(DataBus.DataBus_MySqlHelper.GetSingle(sql).ToString());

                sql = "UPDATE ide_point SET Number ='" + boardNumInt .ToString().PadLeft(4, '0')+
                    "0000' where id <= " + num + " and id>" + (num - sampleTableLength);

                 int dt = DataBus.DataBus_MySqlHelper.ExecuteSql(sql);

            }

        }
        #endregion Private 方法

        #region Public方法
        //构造函数
        public DBProgram(MainForm mf)
        {
          
            m_mainform = mf;
            btDeCoilCwList = m_mainform.btDeCoilCwList;
            btDeNoCoilCwList = m_mainform.btDeNoCoilCwList;
            btDeCoilHpList = m_mainform.btDeCoilHpList;
            btDeNoCoilHpList = m_mainform.btDeNoCoilHpList;
            btReAdjHwList = m_mainform.btReAdjHwList;
            btReNoAdjHwList = m_mainform.btReNoAdjHwList;
            btReAdjHpList = m_mainform.btReAdjHpList;
            btReNoAdjHpList = m_mainform.btReNoAdjHpList;
            checkDatabase();
            m_treeBoxWin = new TreeBoxWindow(m_mainform);
            m_treeBoxWin.Show(m_mainform.dockPanel1);
            m_gridWin = new GridWindow();

            m_treeBoxWin.treeView.NodeMouseDoubleClick += new TreeNodeMouseClickEventHandler(TreeItemClicked);
            m_treeBoxWin.treeView1.NodeMouseDoubleClick += new TreeNodeMouseClickEventHandler(TreeItemClicked);

        }

        #endregion Public方法
    }
}
