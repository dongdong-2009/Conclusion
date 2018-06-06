
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace DataBus.DataAccess
{
    public class CData_ControlDataManager
    {
        public DataTable GetAllRealTimeData()
        {
            string sql;
            sql = "select  * from daq_control ";
            DataTable dt = new DataTable();
            try
            {
                dt = DataBus_MySqlHelper.QuerySql(sql);
            }
            catch
            {

            }
            return dt;
        }
        public string GetDataByBoardPort(string boardNumber, string Port)
        {
            string _data = "";
            DataTable RealTimeDataTable = GetAllRealTimeData();
            if (RealTimeDataTable.Rows.Count < 1)
                return _data;
            try
            {
                DataRow[] matches = RealTimeDataTable.Select(" Address = " + boardNumber);
                _data = matches[0][Port].ToString();
            }
            catch
            {

            }
            return _data;
        }
    }
}
