//下发指令的数据库实现 xuehaoyuan
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace DataBus.DataSend
{
    public class CDataSend
    {
        //修改数据库下发控制指令
        public bool SendControlData(string Data, string RelatedPort, string PortBind, string DeviceID)
        {
            if (RelatedPort == null || PortBind == null || DeviceID == null)
                return false;
            //增加对于PID的特殊处理 AO_AUTOMANUAL
            try
            {
                if (RelatedPort.Substring(0, 2) == "AO")
                {
                    //string automaunal_str = RelatedPort + "_AUTOMANUAL";
                    //string querysql = "select * from dat_datawrite  where Code ='" + DeviceID + "' ";
                    //DataTable dt = DataBus_MySqlHelper.QuerySql(querysql);
                    //if (dt.Rows[0][automaunal_str].ToString() == "1")
                    //    return false;
                }
            }
            catch
            {
                return false;
            }
            //string savesql = "update td_datasmallwrite set " + RelatedPort + " = '" + Data + "', " + PortBind + " = '1', Handle = '1' where code ='" + DeviceID + "' ";
            string savesql = "update dat_datawrite set " + RelatedPort + " = '" + Data + "', " + PortBind + " = '1' where Code ='" + DeviceID + "' ";
            int i = DataBus_MySqlHelper.ExecuteSql(savesql);
            return true;
            //DataBus_MySqlHelper.ExecuteSql(savesql);  mysql
        }
        //修改数据库  buttoncheck指令 1开 0关
        public bool SendButtonCheckData(string RelatedPort, string PortBind, string DeviceID, string state)
        {
            if (RelatedPort == null || PortBind == null || DeviceID == null)
                return false;
            string savesql = "update dat_datawrite set " + RelatedPort + " = '" + state + "', " + PortBind + " = '1' where Code ='" + DeviceID + "' ";
            int i = DataBus_MySqlHelper.ExecuteSql(savesql);
            return true;
        }
        //下发ONOFF指令
        public void SendOnOffData(string DeviceID, string state)
        {
            if (state != "" && state != null)
            {
                string savesql = "update dat_datawrite set ONOFF = '" + state + "', Handle = '1' where code ='" + DeviceID + "' ";
                //DataBus_DAStaticFunctions.exeSql(savesql, "connSys");
                DataBus_MySqlHelper.ExecuteSql(savesql); // mysql
            }
        }
    }
}
