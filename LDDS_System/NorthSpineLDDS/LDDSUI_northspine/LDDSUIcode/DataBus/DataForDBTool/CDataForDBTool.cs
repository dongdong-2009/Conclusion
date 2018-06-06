//对数据库读写的方法  xuehaoyuan
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Data.SqlClient;
using System.Data;
using MySql.Data.MySqlClient;

namespace DataBus.DataForDBTool
{
    public class CDataForDBTool
    {
        public DataTableCollection GetAllTypeName()
        {
            string sql = "select * from IDE_TypeName";
            DataTableCollection tpn = DataBus_MySqlHelper.QueryForDataTableCollection(sql);
            return tpn;
        }
        public static MySqlConnection GetConn()
        {
            MySqlConnection conn = DataBus_MySqlHelper.getConn();
            return conn;
        }
        //根据ID获取project表
        public DataTable GetProjectByID(int id, int GETALLDATA)
        {
            string sql = "select name, id from IDE_Project";
            if (id != GETALLDATA)
            {
                // sql += " where id = '" + id + "'";
                sql += " where id = " + id;
            }
            DataTable dt = new DataTable();
            dt = DataBus_MySqlHelper.QuerySql(sql);
            return dt;
        }

        public DataTable MySqlQuery(string sql)
        {
            DataTable dt = new DataTable();
            dt = DataBus_MySqlHelper.QuerySql(sql);
            return dt;
        }

        public int MySqlExe(string sql)
        {
            int rows = DataBus_MySqlHelper.ExecuteSql(sql);
            return rows;
        }
    }
}
