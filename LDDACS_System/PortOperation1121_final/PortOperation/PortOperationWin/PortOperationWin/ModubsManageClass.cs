using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using NLog;
using System.Threading.Tasks;
using System.Threading;

namespace ModbusDAQ
{
    public class ModubsManageClass
    {
        #region 【成员变量】

        ///<summary>
        /// 获取或设置从站设备的列表
        //// </summary>
        public List<ModbusMasterExClass> StationList
        {
            get
            {
                return m_StationList;
            }
            set
            {
                m_StationList = value;
            }
        }
        private List<ModbusMasterExClass> m_StationList;
        private StationCollection m_ReadStationCollection;
        private StationCollection m_WriteStationCollection;

        //private PortOperationWin.Boardstatus.Modbus_Group m_GroupTable;
        //private PortOperationWin.Boardstatus.Modbus_Stationinfo m_StationInfoTable;
        //private PortOperationWin.Boardstatus.modbus_distribution m_DistributionTable;

        #region [IsHasReadStaion] 是否存在[读站点]
        private bool m_IsHasReadStaion;
        /// <summary>
        /// 是否存在[读站点]
        /// </summary>
        public bool IsHasReadStaion
        {
            get { return m_IsHasReadStaion; }
            set { m_IsHasReadStaion = value; }
        }
        #endregion

        #region [IsHasWriteStaion] 是否存在[写站点]
        private bool m_IsHasWriteStaion;
        /// <summary>
        /// 是否存在[写站点]
        /// </summary>
        public bool IsHasWriteStaion
        {
            get { return m_IsHasWriteStaion; }
            set { m_IsHasWriteStaion = value; }
        }
        #endregion

        #region [m_Logger] 日志
        private Logger m_Logger;
        #endregion

        private static object m_Obj = new object();

        #endregion

        #region [Init] 初始化
        /// <summary>
        /// 初始化
        /// </summary>
        /// <param name="clientId">当前客户端id</param>
        /// <param name="connString">连接字符串</param>
        /// <param name="stationInfoTableName">站点信息表的名称</param>
        /// <param name="groupTableName">组信息表的名称</param>
        /// <param name="distributionTableName">分发表的名称</param>
        /// <returns></returns>
        public bool Init(string stationInfoTableName, string groupTableName, string distributionTableName)
        {
            bool result = false;
            try
            {
                m_Logger = LogManager.GetCurrentClassLogger();
                //m_ConnString = connString;
                PortOperationWin.Boardstatus.Modbus_Stationinfo.TableName = stationInfoTableName;

                m_StationList = new List<ModbusMasterExClass>();
                m_ReadStationCollection = new StationCollection();
                m_WriteStationCollection = new StationCollection();

                for (int i = 0; i < PortOperationWin.Boardstatus.Modbus_Stationinfo.Name.Length; i++)
                {
                    ModbusMasterExClass masterObj = new ModbusMasterExClass();
                    bool isInitSuccess = masterObj.Initmaster(i);

                    //DataRow currentRow = m_StationInfoTable.Rows[i];

                    //if (!isInitSuccess)
                    //{
                    //    m_Logger.Info(string.Format("The station '{0}' in group '{1}' init failed!"));
                    //    continue;
                    //}
                    //m_Logger.Info(string.Format("The station '{0}' in group '{1}' init succeed!"));

                    switch (masterObj.FunctionCode)
                    {
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadCoils:
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadDiscreteInputs:
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadHoldingRegisters:
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadInputRegisters:
                            {
                                m_ReadStationCollection.Add(masterObj);
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteSingleCoil:
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteSingleRegister:
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteMultipleCoils:
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteMultipleRegisters:
                            {
                                m_WriteStationCollection.Add(masterObj);
                                break;
                            }
                        default:
                            break;
                    }

                    m_StationList.Add(masterObj);

                }
                if (m_ReadStationCollection.Count > 0)
                {
                    m_IsHasReadStaion = true;
                }
                else
                {
                    m_IsHasReadStaion = false;
                }
                if (m_WriteStationCollection.Count > 0)
                {
                    m_IsHasWriteStaion = true;
                }
                else
                {
                    m_IsHasWriteStaion = false;
                }
                result = true;
                return result;
            }
            catch (Exception ex)
            {
                m_Logger.Error(ex.Message);
                return false;
            }
        }
        #endregion

        #region [ExecuteCommon] 执行 读操作
        /// <summary>
        /// 执行
        /// </summary>
        /// <param name="stationCollection"></param>
        /// <returns></returns>
        private bool ExecuteCommon(StationCollection stationCollection)
        {
            try
            {
                if (stationCollection.WebStationList.Count == 0 && stationCollection.SerialStationList.Count > 0)
                {
                    //同步方式
                    for (int i = 0; i < stationCollection.SerialStationList.Count; i++)
                    {
                        GetData(stationCollection.SerialStationList[i]);
                    }

                }
                else
                {
                    m_Logger.Warn("[ModubsManageClass.ExecuteCommon] else!");
                }
                return true;
            }
            catch (Exception ex)
            {
                m_Logger.Error(ex);
                return false;
            }
        }
        #endregion
        #region [getphsicalvalue] get phsical value

        /// <summary>

        public void GetData(ModbusDAQ.ModbusMasterExClass statlist)
        {
            
            ushort j;
            // int m = PortOperationWin.Boardstatus.Modbus_Stationinfo.Name.Length;
            // int numofReadstat = m_ReadStationCollection.SerialStationList.Count();
            string currentTableName = statlist.StationName;
            ushort n = statlist.DataNum;
            ushort startAddressbase = (ushort)(statlist.StartAddress);
            try
            {
              if(currentTableName!= "UserModbusRevdataI")
               {
                 for (j = 0; j < n; j++)
                {
                    ushort startAddress = (ushort)(startAddressbase + j);

                    switch (currentTableName)
                    {

                        case "AIdataF":
                            {
                                // 两个ushort拼接一个float
                                ushort[] tempValues = new ushort[1];
                                tempValues = Driver.ModbusSerialRtuMasterReadRegisters(PortOperationWin.Boardstatus.port, startAddress, 1, PortOperationWin.Boardstatus.slaveId, tempValues);
                                float temps = (float)(tempValues[0] / 100.0);
                                PortOperationWin.Boardstatus.AIdataF[j] = temps.ToString();

                                break;
                            }

                        case "DIdataI":
                            {
                                // 两个ushort拼接一个float
                                ushort[] tempValues = new ushort[1];
                                tempValues = Driver.ModbusSerialRtuMasterReadRegisters(PortOperationWin.Boardstatus.port, startAddress, 1, PortOperationWin.Boardstatus.slaveId, tempValues);
                                PortOperationWin.Boardstatus.DIdataI[j] = tempValues[0].ToString();

                                break;
                            }

                        case "RTDdataF":
                            {

                                ushort[] tempValues = new ushort[1];
                                tempValues = Driver.ModbusSerialRtuMasterReadRegisters(PortOperationWin.Boardstatus.port, startAddress, 1, PortOperationWin.Boardstatus.slaveId, tempValues);
                                float temps = (float)(tempValues[0] / 100.0);
                                PortOperationWin.Boardstatus.RTDdataF[j] = temps.ToString();


                                break;
                            }


                        default: //uint16, boolean
                            {
                                //sqlCmdpart = string.Format(" {0} = {1} ", columnName, station.Values[dataPos]);

                                break;
                            }


                    }
                  }
                }
                else if ((PortOperationWin.Boardstatus.userPortReadEn == 1) & (PortOperationWin.Boardstatus.userPortSelected == 1))
                {
                     ushort[] tempValues = new ushort[PortOperationWin.Boardstatus.UserModbusRevdataI.Length];
                    //ushort[] tempValues = new ushort[1];
                    tempValues = Driver.ModbusSerialRtuMasterReadRegisters(PortOperationWin.Boardstatus.userport, PortOperationWin.Boardstatus.Modbus_Stationinfo.StartAddress[9], (ushort)PortOperationWin.Boardstatus.UserModbusRevdataI.Length, PortOperationWin.Boardstatus.userslaveId, tempValues);
                    for (int cnt = 0; cnt < PortOperationWin.Boardstatus.UserModbusRevdataI.Length; cnt++)
                    {
                        PortOperationWin.Boardstatus.UserModbusRevdataI[cnt] = (tempValues[0] / 100).ToString();
                    }
                }

          }
          catch (Exception ex)
          {
                Logger log = LogManager.GetCurrentClassLogger();
                log.Error(ex);
          }
        }
        #endregion






        #region [ExecuteRead] 执行读操作
        /// <summary>
        /// 执行读操作
        /// </summary>
        ///// <returns></returns>
        public bool ExecuteRead()
        {
            try
            {
                bool result;

                if (Monitor.TryEnter(m_Obj))
                {
                    lock (m_Obj)
                    {
                        result = ExecuteCommon(m_ReadStationCollection);


                    }

                }
                else
                {
                    m_Logger.Warn("[ExecuteRead] The last reading has not finished!");
                    result = false;
                }

                return result;
            }
            catch (Exception ex)
            {
                m_Logger.Error(ex);
                return false;
            }
        }
        #endregion

        #region [ExecuteWrite] 执行写操作
        /// <summary>
        /// 执行写操作
        /// </summary>
        /// <returns></returns>
        /// 
        public List<string[]> CheckWriteStatus()
        {
            string[] namepos = new string[3];
            List<string[]> nameposlist =new List<string[]>();

            string[] handlearray = PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle;
            string[] namearray = PortOperationWin.Boardstatus.Modbus_Stationinfo.Name;
            ushort[] startaddarray= PortOperationWin.Boardstatus.Modbus_Stationinfo.StartAddress;
            int lenhandle = handlearray.Length;
            int lenname = namearray.Length;
            bool existed;

            for (int i = 0; i < lenhandle; i++)
            {

                existed = handlearray[i].Contains("1");

                if (existed == true)
                {
                    int pos=handlearray[i].IndexOf("1");

                    namepos[0] = namearray[i];
                    namepos[1] = (pos+1).ToString();
                    namepos[2] = startaddarray[i].ToString();
                    nameposlist.Add(namepos);

                }

            }
            return nameposlist;
 
        }

        public bool ExecuteWrite(PortOperationWin.MainForm mf, List<string[]> nameposlist)
        {
            try
            {
                int n = nameposlist.Count();
                string curname;
                ushort curhandlepos, curbaseadd;
                ushort startAddress;
            
                for (int i = 0; i < n; i++)
                {
                    curname      = nameposlist[i][0];
                    curhandlepos = (ushort)(ushort.Parse(nameposlist[i][1])-1);
                    curbaseadd   = ushort.Parse(nameposlist[i][2]);
                    startAddress =(ushort)(curbaseadd+ curhandlepos);

                        switch (curname)
                        {
                            case "AOdataF":
                                {
                                    ushort tempvalue ;
                                    string str = string.Format("{0:f2}", PortOperationWin.Boardstatus.AOdataF[curhandlepos]);
                                    int intvalue = (int)float.Parse(str) * 100;
                                    tempvalue = (ushort)intvalue;
                                    Driver.ModbusSerialRtuMasterWriteRegisters(PortOperationWin.Boardstatus.port, startAddress, PortOperationWin.Boardstatus.slaveId, tempvalue);
                                    mf.ClearHandle("AOdataF", (ushort)(curhandlepos + 1));

                                    break;
                                }

                            case "AImodeI":
                                {
                                    ushort tempvalue;
                                    string str = string.Format("{0:f2}", PortOperationWin.Boardstatus.AImodeI[curhandlepos]);
                                    int intvalue = (int)float.Parse(str) * 100;
                                    tempvalue = (ushort)intvalue;
                                    Driver.ModbusSerialRtuMasterWriteRegisters(PortOperationWin.Boardstatus.port, startAddress, PortOperationWin.Boardstatus.slaveId, tempvalue);
                                    mf.ClearHandle("AImodeI", (ushort)(curhandlepos + 1));
                                    break;
                                }
                            case "AOmodeI":
                                {
                                    ushort tempvalue;
                                    string str = string.Format("{0:f2}", PortOperationWin.Boardstatus.AOmodeI[curhandlepos]);
                                    int intvalue = (int)float.Parse(str) * 100;
                                    tempvalue = (ushort)intvalue;
                                    Driver.ModbusSerialRtuMasterWriteRegisters(PortOperationWin.Boardstatus.port, startAddress, PortOperationWin.Boardstatus.slaveId, tempvalue);
                                    mf.ClearHandle("AOmodeI", (ushort)(curhandlepos + 1));
                                    break;

                                }


                            case "DOdataI":
                                {
                                    ushort tempvalue;
                                    string str = string.Format("{0:f2}", PortOperationWin.Boardstatus.DOdataI[curhandlepos]);
                                        
                                    tempvalue = ushort.Parse(str);
                                    Driver.ModbusSerialRtuMasterWriteRegisters(PortOperationWin.Boardstatus.port, startAddress, PortOperationWin.Boardstatus.slaveId, tempvalue);
                                    mf.ClearHandle("DOdataI", (ushort)(curhandlepos+1));                                
                                    break;
                                }

                            case "PWM1dataF":
                                {

                                    ushort tempvalue;
                                    string str = string.Format("{0:f2}", PortOperationWin.Boardstatus.PWM1dataF[curhandlepos]);
                                    int intvalue = (int)float.Parse(str) * 100;
                                    tempvalue = (ushort)intvalue;
                                    Driver.ModbusSerialRtuMasterWriteRegisters(PortOperationWin.Boardstatus.port, startAddress, PortOperationWin.Boardstatus.slaveId, tempvalue);
                                    mf.ClearHandle("PWM1dataF", (ushort)(curhandlepos + 1));
                                    break;

                                }
                            case "PWM2dataF":
                                {
                                    ushort tempvalue;
                                    string str = string.Format("{0:f2}", PortOperationWin.Boardstatus.PWM2dataF[curhandlepos]);
                                    int intvalue = (int)float.Parse(str) * 100;
                                    tempvalue = (ushort)intvalue;
                                    Driver.ModbusSerialRtuMasterWriteRegisters(PortOperationWin.Boardstatus.port, startAddress, PortOperationWin.Boardstatus.slaveId, tempvalue);                          
                                    mf.ClearHandle("PWM2dataF", (ushort)(curhandlepos + 1));
                                    break;

                                }
                            case "UserModbusSenddataI":
                                {
                                    ushort tempvalue ;
                                    for (int cnt = 0; cnt < PortOperationWin.Boardstatus.UserModbusSenddataI.Length; cnt++)
                                    {
                                        string tempstr = PortOperationWin.Boardstatus.UserModbusSenddataI[cnt];
                                        tempvalue= (ushort)Convert.ToUInt16(tempstr);
                                        Driver.ModbusSerialRtuMasterWriteRegisters(PortOperationWin.Boardstatus.userport, startAddress, PortOperationWin.Boardstatus.userslaveId, tempvalue);
                                        mf.ClearHandle("UserModbusSenddataI", 0);
                                }
                                break;
                                }
                    
                        default: //uint16, boolean
                                {
                                    //sqlCmdpart = string.Format(" {0} = {1} ", columnName, station.Values[dataPos]);
                                    break;
                                }

                        }

                }
            }
            catch (Exception ex)
            {
                m_Logger.Error(ex);
                return false;
            }

            return true;
        }
        #endregion

        #region [JustWait]
        private bool JustWait()
        {
            Thread.Sleep(2000);
            return true;
        }

        #endregion
    }

    /// <summary>
    /// 站点集合类
    /// 主要作用是在初始化时即可划分出 网络类型的站点 和 串口类型的站点
    /// </summary>
    public class StationCollection
    {
        private List<ModbusMasterExClass> m_AllStationList;
        /// <summary>
        /// 所有的站点集合
        /// </summary>
        public List<ModbusMasterExClass> AllStationList
        {
            get { return m_AllStationList; }
            set { m_AllStationList = value; }
        }

        private List<ModbusMasterExClass> m_WebStationList;
        /// <summary>
        /// Modbus TCP/UPD类型的站点集合
        /// </summary>
        public List<ModbusMasterExClass> WebStationList
        {
            get { return m_WebStationList; }
            set { m_WebStationList = value; }
        }
        private List<ModbusMasterExClass> m_SerialStationList;
        /// <summary>
        /// Modbus ASCII/RTU类型的站点集合
        /// </summary>
        public List<ModbusMasterExClass> SerialStationList
        {
            get { return m_SerialStationList; }
            set { m_SerialStationList = value; }
        }

        /// <summary>
        /// 所有站点的总个数
        /// </summary>
        public int Count
        {
            get
            {
                return m_AllStationList.Count;
            }
        }

        private Logger m_Logger;


        public StationCollection()
        {
            m_WebStationList = new List<ModbusMasterExClass>();
            m_SerialStationList = new List<ModbusMasterExClass>();
            m_AllStationList = new List<ModbusMasterExClass>();

            m_Logger = LogManager.GetCurrentClassLogger();
        }

        public bool Add(ModbusMasterExClass obj)
        {
            try
            {
                if (obj == null)
                {
                    return false;
                }
                m_AllStationList.Add(obj);
                if (obj.MasterType == ModbusCommonClass.MODBUS_StationType.Tcp || obj.MasterType == ModbusCommonClass.MODBUS_StationType.Udp)
                {
                    m_WebStationList.Add(obj);
                }
                else if (obj.MasterType == ModbusCommonClass.MODBUS_StationType.SerialRtu || obj.MasterType == ModbusCommonClass.MODBUS_StationType.SerialAscii)
                {
                    m_SerialStationList.Add(obj);
                }
                else
                {
                    return false;
                }
                return true;
            }
            catch (Exception ex)
            {
                m_Logger.Warn("[StationCollection.Add]" + ex.Message);
                return false;
            }
        }



    }
}
