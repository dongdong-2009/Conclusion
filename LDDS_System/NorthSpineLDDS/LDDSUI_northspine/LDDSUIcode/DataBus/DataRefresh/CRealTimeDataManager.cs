//因为要定时获取最新数据，获取数据的方法都放在这里，使用一个获取函数，一次将所有数据拿到，
//避免频繁访问数据库，对数据库服务器形成压力   xuehaoyuan 
using System;
using System.Data;
using System.Windows.Forms;

namespace DataBus.DataRefresh
{
    public class CRealTimeDataManager
    {
        public Timer getDataTimer;
        public DataTable RealTimeDataTable;
        public DataBus.DataAccess.CData_HardwareCollect dhc;

        public CRealTimeDataManager()
        {
            dhc = new DataAccess.CData_HardwareCollect();
            RealTimeDataTable = new DataTable();
            //使用定时器定时获取所有数据，这样不需要每个组件获取数据都需要访问一次数据库，
            //在大量组件存在的情况下减少访问数据库的次数 xhy
            getDataTimer = new Timer();
            getDataTimer.Interval = 5000;
            getDataTimer.Tick += new EventHandler(Timer_Tick);
            getDataTimer.Enabled = true;
            getDataTimer.Start();
            RealTimeDataTable = dhc.GetAllRealTimeData();
        }
        public void stop()
        {
            getDataTimer.Stop();
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            RealTimeDataTable = dhc.GetAllRealTimeData();
        }

        public string GetDataByBoardPort(string boardNumber, string stringname, string Port)
        {
            string _data = "";
            
            
            if (RealTimeDataTable.Rows.Count < 1)
                return _data;
            try
            {
                 DataRow[] matches = RealTimeDataTable.Select("Code = " + boardNumber);
                    _data = matches[0][Port].ToString(); 
                
            }
            catch
            {

            }
            return _data;
        }


    
    
    }
}
