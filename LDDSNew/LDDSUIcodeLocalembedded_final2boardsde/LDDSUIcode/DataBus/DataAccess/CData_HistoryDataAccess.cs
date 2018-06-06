//历史数据获取，历史时间段的处理方式：
// 曲线图最多只显示1000条数据（可更改），超过这一数目后，改为查询另一张时间跨度更大的表。xuehaoyuan
// 历史数据表分为：分钟、小时、日数据
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
namespace DataBus.DataAccess
{
    public class CData_HistoryDataAccess
    {
        public DataTable GetHistoryDataByTimeZone(string BroadNumber, DateTime timeBegin, DateTime timeEnd, string tableName)
        {
            DataTable dt = new DataTable();
            try
            {
                string tb = timeBegin.ToString("yyyy-MM-dd HH:mm:ss");
                string te = timeEnd.ToString("yyyy-MM-dd HH:mm:ss");
                //最多显示1000条数据，如果超过，改为查询另一张表
                string sql = " select * from " + tableName + " where Address='" + BroadNumber + "' and TimeStamp > '" + tb + "' and TimeStamp < '" + te + "' order by TimeStamp DESC";
                //string countsql = " select count(*) from daq_read_history where Address='" + BroadNumber + "' and TimeStamp > '" + timeBegin.ToString() + "' and TimeStamp < '" + timeEnd.ToString() + "'";
                //string sql = " select * from daq_read_history order by TimeStamp DESC limit 1000 ";
                dt = DataBus_MySqlHelper.QuerySql(sql);

            }
            catch { }
            return dt;
        }
        //BroadNumber 板号  maxNum 能显示的最大条数
        public int GetHistoryDataCountByTimeZone(string BroadNumber, DateTime timeBegin, DateTime timeEnd, string tableName)
        {
            int num= 0;
            string tb = timeBegin.ToString("yyyy-MM-dd HH:mm:ss");
            string te = timeEnd.ToString("yyyy-MM-dd HH:mm:ss"); 
            DataTable dt = new DataTable();
            try
            {
                string countsql = " select count(*) from " + tableName + " where Address='" + BroadNumber + "' and TimeStamp > '" + tb + "' and TimeStamp < '" +te + "'";
                dt = DataBus_MySqlHelper.QuerySql(countsql);
                num = Convert.ToInt32(dt.Rows[0][0].ToString());
            }
            catch { }
            return num;
        }
    }
}
