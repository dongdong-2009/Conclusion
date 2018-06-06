//====================================================================
// 文件名: Data_PointTable.cs
//
// 文件描述:
// ------------------------------------------------------------------
// 获取点表数据
// ------------------------------------------------------------------
// 时间: 2015.10
// 编程: xuehaoyuan
// ------------------------------------------------------------------
// 修改说明(请按格式说明)...
// ------------------------------------------------------------------
// 请对 较复杂函数 所实现功能、输入输出做较细致说明
//====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace DataBus.DataAccess
{
    public class CData_PointTable
    {
        //获取整个点表
        public DataTable GetPointTable()
        {
            DataTable PointTable = new DataTable();
            try
            {
                string sql = "select * from IDE_Point";
                //获取point表
                //PointTable = DataBus_DAStaticFunctions.querySql("select * from BSTAR.dbo.Point", DataBus_DAStaticFunctions.DATABASECON);
                //mysql
                PointTable = DataBus_MySqlHelper.QuerySql(sql);

            }
            catch (System.Exception e)
            {
                string errText = e.Message.ToString();
                return null;
            }
            return PointTable;
        }
        //获取点表中所有板号
        public List<string> GetAllBoardNumber()
        {
            List<string> BoardNumberList = new List<string>();
            DataTable PointTable = GetPointTable();
            if (PointTable == null)
                return null;
            foreach (DataRow dr in PointTable.Rows)
            {
                BoardNumberList.Add(dr["Number"].ToString());
            }
            BoardNumberList = BoardNumberList.Distinct<string>().ToList();//去重复
            return BoardNumberList;
        }
        //根据PointID获取板号（number）和Port
        //注意加保护
        public void GetBoardPortByPointID(string PointID, ref string BoardNumber, ref string RelatedPort)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || PointID == "")
                return;
            DataRow[] matches = PointTable.Select(" id = " + PointID);
            try
            {
                BoardNumber = matches[0]["Number"].ToString();
                RelatedPort = matches[0]["Port"].ToString();
            }
            catch
            {
            }
        }

        public void GetBoardPortByNameBdnum(string Name, string Number, ref string RelatedPort, ref string DeviceType)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || Name == null || Number == null)
                return;
            DataRow[] matches = PointTable.Select(" Name = '" + Name + "' and Number = " + Number);
            try
            {
                DeviceType = matches[0]["Type"].ToString();
                RelatedPort = matches[0]["Port"].ToString();
            }
            catch
            {
            }
        }

        public void GetBoardinfoByName(string Name, ref string Number, ref string DeviceType)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || Name == "")
                return;
            DataRow[] matches = PointTable.Select(" Name = '" + Name + "' ");
            try
            {
                Number = matches[0]["Number"].ToString();
                DeviceType = matches[0]["Type"].ToString();
            }
            catch
            {
            }
        }

        //public void SetBoardnumber(string Name,string Number, ref string DeviceType)
        //{
        //    DataTable PointTable = GetPointTable();
        //    if (PointTable == null || Name == "")
        //        return;
        //    DataRow[] matches = PointTable.Select(" Name = '" + Name + "' ");
        //    try
        //    {
        //        Number = matches[0]["Number"].ToString();
        //        DeviceType = matches[0]["Type"].ToString();
        //    }
        //    catch
        //    {
        //    }
        //}

        public void GetBoardPortByNameType(string Name, string Type, ref string BoardNumber, ref string RelatedPort)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || Name == "" || Type == "")
                return;
            DataRow[] matches = PointTable.Select(" Name = '" + Name + "' and Type = " + Type);
            try
            {
                BoardNumber = matches[0]["Number"].ToString();
                RelatedPort = matches[0]["Port"].ToString();
            }
            catch
            {
            }
        }


        public void GetBoardPortByNameTypeBdnum(string Name, string Type, string BoardNumber, ref string RelatedPort)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || Name == "" || Type == "")
                return;
            DataRow[] matches = PointTable.Select(" Name = '" + Name + "' and Type = " + Type);
            try
            {
                BoardNumber = matches[0]["Number"].ToString();
                RelatedPort = matches[0]["Port"].ToString();
            }
            catch
            {
            }
        }


        //根据PointID获取 与下发数据有关的  板号（number）和 Port PortD PortH
        //注意加保护
        public void GetBoardSendPortByPointID(string PointID, ref string BoardNumber, ref string RelatedPort, ref string PortData, ref string PortBind)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || PointID == "")
                return;
            DataRow[] matches = PointTable.Select(" id = " + PointID);
            try
            {
                BoardNumber = matches[0]["Number"].ToString();
                RelatedPort = matches[0]["Port"].ToString();
                PortData = matches[0]["SendDataPort"].ToString();
                PortBind = matches[0]["BindPort"].ToString();
            }
            catch
            {
            }
        }


        public void GetBoardSendPortByNameBdnum(string Name, string Number, ref string RelatedPort, ref string PortData, ref string PortBind)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || Name == "" || Number == "")
                return;
            DataRow[] matches = PointTable.Select(" Name = '" + Name + "' and Number = " + Number);
            try
            {
                // BoardNumber = matches[0]["Number"].ToString();
                RelatedPort = matches[0]["Port"].ToString();
                PortData = matches[0]["SendDataPort"].ToString();
                PortBind = matches[0]["BindPort"].ToString();
            }
            catch
            {
            }
        }

        public void GetBoardSendPortByNameType(string Name, string Type, ref string BoardNumber, ref string RelatedPort, ref string PortData, ref string PortBind)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || Name == "" || Type == "")
                return;
            DataRow[] matches = PointTable.Select(" Name = '" + Name + "' and Type = " + Type);
            try
            {
                BoardNumber = matches[0]["Number"].ToString();
                RelatedPort = matches[0]["Port"].ToString();
                PortData = matches[0]["SendDataPort"].ToString();
                PortBind = matches[0]["BindPort"].ToString();
            }
            catch
            {
            }
        }



        //根据PointID获取 只获取 板号（number）
        //注意加保护
        public void GetBoardSendByPointID(string PointID, ref string BoardNumber)
        {
            DataTable PointTable = GetPointTable();
            if (PointTable == null || PointID == "")
                return;
            DataRow[] matches = PointTable.Select(" id = " + PointID);
            try
            {
                BoardNumber = matches[0]["Number"].ToString();
            }
            catch
            {
            }
        }
        //根据表名，id获取pointid
        public string GetPointID(string type, string id)
        {
            string PointID = "";
            string sql = "select * from " + type + " where id = " + id;
            DataTable dt = new DataTable();
            try
            {
                //dt = DataBus_DAStaticFunctions.querySql(sql, DataBus_DAStaticFunctions.DATABASECON);
                //mysql
                dt = DataBus_MySqlHelper.QuerySql(sql);
                PointID = dt.Rows[0]["PointID"].ToString();
            }
            catch
            {

            }
            return PointID;
        }

        //根据表名，id获取read  pointid
        public string GetReadPointID(string type, string id)
        {
            string PointID = "";
            string sql = "select * from " + type + " where id = " + id;
            DataTable dt = new DataTable();
            try
            {
                dt = DataBus_MySqlHelper.QuerySql(sql);

                if (type == "Sensor")
                {
                    PointID = dt.Rows[0]["PointID"].ToString();
                }
                else if (type == "Actuator")
                {
                    PointID = dt.Rows[0]["FeedBackPTID"].ToString();
                }
                else if (type == "Fan" || type == "Pump")
                {
                    PointID = dt.Rows[0]["FrequencyFeedBackPTID"].ToString();
                }
            }
            catch
            {

            }
            return PointID;
        }

        //根据表名，id获取write  pointid
        public string GetWritePointID(string type, string id)
        {
            string PointID = "";
            string sql = "select * from " + type + " where id = " + id;
            DataTable dt = new DataTable();
            try
            {
                dt = DataBus_MySqlHelper.QuerySql(sql);

                if (type == "Actuator")
                {
                    PointID = dt.Rows[0]["SendPTID"].ToString();
                }
                else if (type == "Fan" || type == "Pump")
                {
                    PointID = dt.Rows[0]["FrequencySetPTID"].ToString();
                }
                else
                {
                    PointID = dt.Rows[0]["PointID"].ToString();
                }
            }
            catch
            {

            }
            return PointID;
        }
    }
}
