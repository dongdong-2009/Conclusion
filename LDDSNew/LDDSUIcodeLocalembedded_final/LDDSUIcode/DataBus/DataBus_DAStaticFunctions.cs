//通用方法  sqlserver xuehaoyuan
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.OleDb;
using System.Xml;
using System.Data.SqlClient;
using System.Data;
using System.Configuration;

namespace DataBus
{
    class DataBus_DAStaticFunctions
    {
        public static string DATABASECON = "connSys";
        public static string CONFIGURATION_FILE_NAME = "..\\..\\app.config";
        
        //public static string CONFIGURATION_FILE_NAME = "F:\\H\\BSTAR\\Designer\\Designer\\app.config";


        #region Sql Server
        //获取指定数据库的连接
        //参数connString：指明服务器、用户名、密码和数据库名
        public static SqlConnection getConn(string connString)
        {
            string str = System.Environment.CurrentDirectory;

            SqlConnection conn = new SqlConnection();
            try
            {
                conn.ConnectionString = System.Configuration.ConfigurationManager.OpenMappedExeConfiguration(new ExeConfigurationFileMap() { ExeConfigFilename = CONFIGURATION_FILE_NAME }, ConfigurationUserLevel.None).AppSettings.Settings[DATABASECON].Value;
            }
            catch(System.Exception e)
            {

            }
            //conn.ConnectionString = System.Configuration.ConfigurationManager.AppSettings[connString].ToString();
            //            conn.ConnectionString = System.Configuration.ConfigurationManager.ConnectionStrings[connString].ToString();
            return conn;
        }

        //对指定的数据库中的表进行查询
        //参数querySql：sql查询的语句
        //参数connString：指明服务器、用户名、密码和数据库名
        public static DataTable querySql(string querySql, string connString)
        {
            SqlConnection conn = getConn(connString);
            SqlCommand cmd = new SqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = querySql;
            SqlDataAdapter da = new SqlDataAdapter();
            da.SelectCommand = cmd;
            DataTable dt = new DataTable("tmp");
            da.Fill(dt);
            conn.Dispose();
            return dt;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="querySql"></param>
        /// <param name="conn"></param>
        /// <returns></returns>
        public static DataTable querySql(string querySql, SqlConnection conn)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = querySql;
            SqlDataAdapter da = new SqlDataAdapter();
            da.SelectCommand = cmd;
            DataTable dt = new DataTable("tmp");
            da.Fill(dt);
            return dt;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="exeSql"></param>
        /// <param name="connString"></param>
        /// <returns></returns>
        public static int exeSql(string exeSql, string connString)
        {
            SqlConnection conn = openConn(connString);
            SqlCommand cmd = new SqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = exeSql;
            int i = cmd.ExecuteNonQuery();
            conn.Dispose();
            return i;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="exeSql"></param>
        /// <param name="conn"></param>
        /// <returns></returns>
        public static int exeSql(string exeSql, SqlConnection conn)
        {

            SqlCommand cmd = new SqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = exeSql;
            int i = cmd.ExecuteNonQuery();
            conn.Dispose();
            return i;
        }
        //打开指定数据库的连接
        public static SqlConnection openConn(string connString)
        {
            SqlConnection conn = getConn(connString);
            conn.Open();
            return conn;
        }
        /// <summary>
        /// 参数为conn
        /// </summary>
        /// <param name="conn"></param>
        /// <returns></returns>
        public static SqlConnection openConn(SqlConnection conn)
        {

            conn.Open();
            return conn;
        }

        public static object getvalue(string exeSql, string connString)
        {
            SqlConnection conn = openConn(connString);
            SqlCommand cmd = new SqlCommand();
            cmd.Connection = conn;
            cmd.CommandText = exeSql;

            SqlDataReader dr = null;
            try
            {
                dr = cmd.ExecuteReader();
                dr.Read();
                return dr.GetValue(0);
            }
            catch
            {
                return -1;
            }
            finally
            {
                dr.Close();
                cmd.Dispose();
                conn.Close();
            }
        }


        /// <summary>
        /// text the connection
        /// </summary>
        /// <returns>true false</returns>
        public static bool testConnection(string connString)
        {
            SqlConnection conn = new SqlConnection();
            conn.ConnectionString = connString;
            try
            {
                conn.Open();
                return true;
            }
            catch
            {
                return false;
            }
            finally
            {
                SqlConnection.ClearPool(conn);
            }
            //             if (conn.State == ConnectionState.Open)
            //                 return true;
            //             else
            //                 return false;

        }
        #endregion Sql Server

        #region OleDB
        public static OleDbConnection getOleDBConn(string connString)
        {
            string virtualPath = System.Configuration.ConfigurationManager.AppSettings["virtualPath"].ToString();
            string filePath = System.Configuration.ConfigurationManager.AppSettings[connString].ToString();

            //OleDbConnection oledbConn = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\数据库\\xiaofang\\GstFireSystem.mdb");
            //OleDbConnection oledbConn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=F:\\学智项目\\阳光大厦\\20125yue\\王超\\消防部分\\GstFireSystem.mdb");
            string path = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + filePath;
            //OleDbConnection oledbConn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\Program Files\\Gst Software\\GM9000\\Project\\GstFireSystem.mdb");
            OleDbConnection oledbConn = new OleDbConnection(@"" + path);
            return oledbConn;
        }

        public static OleDbConnection openOleDBConn(string connString)
        {
            OleDbConnection conn = getOleDBConn(connString);
            conn.Open();
            return conn;
        }

        public static DataTable queryOleDBSql(string querySql, string connString)
        {
            OleDbConnection conn = getOleDBConn(connString);
            OleDbCommand cmd = new OleDbCommand();
            cmd.Connection = conn;
            cmd.CommandText = querySql;
            OleDbDataAdapter da = new OleDbDataAdapter();
            da.SelectCommand = cmd;
            DataTable dt = new DataTable("tmp");
            da.Fill(dt);
            return dt;
        }

        public static int exeOleDBSql(string exeSql, string connString)
        {
            OleDbConnection conn = openOleDBConn(connString);
            OleDbCommand cmd = new OleDbCommand();
            cmd.Connection = conn;
            cmd.CommandText = exeSql;
            return cmd.ExecuteNonQuery();
        }
        #endregion OleDB

        #region 反序列化
        public static DataTable DeCode(string xmlData)
        {
            DataTable dt = new DataTable("result");
            System.Xml.XmlDocument xDoc = new System.Xml.XmlDocument();
            xDoc.LoadXml(xmlData);
            int columnsCount = 0;
            foreach (XmlNode columnND in xDoc.FirstChild.ChildNodes[0].ChildNodes)
            {
                dt.Columns.Add(columnND.FirstChild.Value);
                columnsCount++;
            }
            foreach (XmlNode rowND in xDoc.FirstChild.ChildNodes[1].ChildNodes)
            {
                DataRow dr = dt.NewRow();
                for (int i = 0; i < columnsCount; i++)
                {
                    dr[i] = rowND.ChildNodes[i].FirstChild.Value;
                }
                dt.Rows.Add(dr);
            }
            return dt;
        }
        #endregion 反序列化

        #region 序列化
        public static string EnCode(DataTable table)
        {
            string result = "<XMLDataTable>";
            result += "<DataColumns>";
            int columnsCount = 0;
            foreach (DataColumn dc in table.Columns)
            {
                result += "<column" + columnsCount + ">" + dc.ColumnName + "</column" + columnsCount + ">";
                columnsCount++;
            }
            result += "</DataColumns>";
            result += "<DataRows>";
            foreach (DataRow dr in table.Rows)
            {
                result += "<DataRow>";
                for (int i = 0; i < columnsCount; i++)
                {
                    result += "<column" + i + ">" + dr[i].ToString() + "</column" + i + ">";
                }
                result += "</DataRow>";
            }
            result += "</DataRows>";
            result += "</XMLDataTable>";
            return result;
        }
        #endregion
    }
}

