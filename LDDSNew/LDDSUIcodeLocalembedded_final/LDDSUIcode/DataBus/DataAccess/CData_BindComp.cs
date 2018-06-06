//绑定组件与数据库用到的方法 xhy 2016年1月7日
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace DataBus.DataAccess
{
    public class CData_BindComp
    {
        //获取所有设备名字
        public DataTable GetAllName(string type)
        {
            DataTable PointTable = new DataTable();
            //string sql = "select id,name from " + type + " order by id asc";
            string sql = "select id,name from ide_point " + " where type =  " + type + " order by id asc";
            try
            {
                PointTable = DataBus_MySqlHelper.QuerySql(sql);
            }
            catch (System.Exception e)
            {
                string errText = e.Message.ToString();
                return null;
            }
            return PointTable;
        }

        //根据ID type获取名字
        public string GetOneName(string id, string type)
        {
            DataTable PointTable = new DataTable();
            string sql = "select name from " + "ide_" + type + " where id = " + id + "order by id desc";
            try
            {
                PointTable = DataBus_MySqlHelper.QuerySql(sql);
            }
            catch (System.Exception e)
            {
                string errText = e.Message.ToString();
                return null;
            }
            string name = PointTable.Rows[0]["name"].ToString();
            return name;
        }
    }
}
