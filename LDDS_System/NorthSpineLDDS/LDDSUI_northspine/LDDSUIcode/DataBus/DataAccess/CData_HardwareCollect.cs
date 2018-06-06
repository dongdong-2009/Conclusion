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
            string codenum1;
            string codenum2;

            DataTable dt = new DataTable();
            //string sql = "select top 1 * from td_datasmallcon where Code='" + BroadNumber + "' order by RecvDt DESC";
            //dt = DataBus_DAStaticFunctions.querySql(sql, DataBus_DAStaticFunctions.DATABASECON);
            //mysql
            if (BroadNumber == "00000000")
            {
                codenum1 = "353334333334";
                codenum2 = "353334333335";
            }
            else
            {
                codenum1 = "353334333336";
                codenum2 = "353334333337";
            }
            string sql = "select * from daq_datacheck where ( Code='" + codenum1 + "' "+ "and Code='"+ codenum2+"')";
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
            sql = "select  * from daq_datacheck ";
            DataTable dt = DataBus_MySqlHelper.QuerySql(sql);
            return dt;
        }
    }
}
