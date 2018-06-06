using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace DataBus.DataAccess
{
    public class CData_HardwareCollect
    {
        //根据板号获取最新一条记录
        public DataTable GetNewRecordByBroadNumber(string BroadNumber)
        {
            DataTable dt = new DataTable();
            //string sql = "select top 1 * from td_datasmallcon where Code='" + BroadNumber + "' order by RecvDt DESC";
            //dt = DataBus_DAStaticFunctions.querySql(sql, DataBus_DAStaticFunctions.DATABASECON);
            //mysql
            string sql = "select * from daq_read where Address='" + BroadNumber + "' ";
            dt = DataBus_MySqlHelper.QuerySql(sql);
            return dt;
        }
        //一次获取所有板的最新数据
        public DataTable GetAllRealTimeData()
        {
            List<string> BoardNumberList;
            CData_PointTable dtp = new CData_PointTable();
            BoardNumberList = dtp.GetAllBoardNumber();
            DataTable AllRealTimeData = new DataTable();
            //if (BoardNumberList == null)
            //    return AllRealTimeData;//返回错误信息
            string sql;

            //需改为从实时表中读取数据
            /*
            foreach (string bn in BoardNumberList)
            {
                //sql = "select top 1 * from td_datasmallcon where Code='" + bn + "' order by RecvDt DESC";
                //DataTable dt = DataBus_DAStaticFunctions.querySql(sql, DataBus_DAStaticFunctions.DATABASECON);
                //mysql
                sql = "select  * from td_datasmallcon where Code='" + bn + "' order by RecvDt DESC  limit 1";//mysql不能用top 1*
                DataTable dt = DataBus_MySqlHelper.QuerySql(sql);
                AllRealTimeData.Merge(dt);
            }
             * */
            sql = "select  * from daq_read ";
            DataTable dt = DataBus_MySqlHelper.QuerySql(sql);
            return dt;
        }
    }
}
