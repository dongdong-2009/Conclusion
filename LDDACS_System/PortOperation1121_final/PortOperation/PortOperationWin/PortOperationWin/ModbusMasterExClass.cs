using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Modbus;
using Modbus.Device;
using System.Data;
using System.IO.Ports;
using NLog;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Net;




namespace ModbusDAQ
{
    public class ModbusMasterExClass
    {
        #region 【成员变量】

        #region [m_Logger] 日志
        private Logger m_Logger;
        #endregion

        #region [StationName] 站点名称
        private string m_StationName;
        /// <summary>
        /// 站点名称
        /// </summary>
        public string StationName
        {
            get { return m_StationName; }
            set { m_StationName = value; }
        }
        #endregion

        #region [Name] 组名称
        private string m_Name;
        /// <summary>
        /// 组名称
        /// </summary>
        public string Name
        {
            get { return m_Name; }
            set { m_Name = value; }
        }

        #endregion

        #region [IMaster] 主站
        private IModbusMaster m_IMaster;

        public IModbusMaster IMaster
        {
            get { return m_IMaster; }
            set { m_IMaster = value; }
        }
        #endregion 
        
        #region [FunctionCode] 功能码
        private ModbusDAQ.ModbusCommonClass.MODBUS_FunctionCode m_FunctionCode;

        /// <summary>
        /// 功能码
        /// 
        /// 01（0X01）读线圈
        /// 02（0X02）读离散量输入
        /// 03（0X03）读保持寄存器
        /// 04（0X04）读输入寄存器
        /// 05（0X05）写单个线圈
        /// 06（0X06）写单个寄存器
        /// 15（0X0F）写多个线圈
        /// 16（0X10）写多个寄存器
        /// </summary>
        public ModbusDAQ.ModbusCommonClass.MODBUS_FunctionCode FunctionCode
        {
            get { return m_FunctionCode; }
            set { m_FunctionCode = value; }
        }
        #endregion

        #region [MasterType] 主站类别
        private ModbusDAQ.ModbusCommonClass.MODBUS_StationType m_MasterType;
        /// <summary>
        /// 主站类别
        /// SerialAscii = 0,
        /// SerialRtu   = 1,
        /// Tcp         = 2,
        /// Udp         = 3
        /// </summary>
        public ModbusDAQ.ModbusCommonClass.MODBUS_StationType MasterType
        {
            get { return m_MasterType; }
            set { m_MasterType = value; }
        }
        #endregion

        #region [HostName] IP地址
        private string m_HostName;

        public string HostName
        {
            get { return m_HostName; }
            set { m_HostName = value; }
        }
        #endregion

        #region [HostPort] 端口号，默认502
        private int m_HostPort;
        /// <summary>
        /// 端口号，默认502
        /// </summary>
        public int HostPort
        {
            get { return m_HostPort; }
            set { m_HostPort = value; }
        }
        #endregion

        #region [SerialPortObj] 串口
        private SerialPort m_SerialPortObj;
        /// <summary>
        /// 串口
        /// </summary>
        public SerialPort SerialPortObj
        {
            get { return m_SerialPortObj; }
            set { m_SerialPortObj = value; }
        }
        #endregion

        #region [ComName] 串口名称，如“COM2”
        private string m_ComName;
        /// <summary>
        /// 串口名称，如“COM2”
        /// </summary>
        public string ComName
        {
            get { return m_ComName; }
            set { m_ComName = value; }
        }
        #endregion

        #region [BaudRate] 波特率，默认：9600
        private int m_BaudRate;
        /// <summary>
        /// 波特率，默认：9600
        /// </summary>
        public int BaudRate
        {
            get { return m_BaudRate; }
            set { m_BaudRate = value; }
        }
        #endregion

        #region [DataBits] 数据位，默认为8
        private int m_DataBits;
        /// <summary>
        /// 数据位，默认为8
        /// </summary>
        public int DataBits
        {
            get { return m_DataBits; }
            set { m_DataBits = value; }
        }
        #endregion

        #region [ParitySet] 奇偶校验，默认：奇校验
        private Parity m_ParitySet;
        /// <summary>
        /// 奇偶校验，默认：奇校验
        /// 
        /// Odd:   设置奇偶校验位，使位数等于奇数
        /// Even： 设置奇偶校验位，使位数等于偶数
        /// Space: 将奇偶校验位保留为0
        //  Mark:  将奇偶校验位保留为1
        //  None: 不发生奇偶校验
        /// </summary>
        public Parity ParitySet
        {
            get { return m_ParitySet; }
            set { m_ParitySet = value; }
        }
        #endregion

        #region [StopBit] 停止位
        private StopBits m_StopBit;
        /// <summary>
        /// 停止位
        /// 
        /// None：不使用停止位
        /// One:  使用一个停止位
        /// OnePointFive:使用1.5个停止位
        /// Two:使用两个停止位
        /// </summary>
        public StopBits StopBit
        {
            get { return m_StopBit; }
            set { m_StopBit = value; }
        }

        #endregion

        #region [StationID] 站点ID
        private byte m_StationID;
        /// <summary>
        /// 站点ID
        /// </summary>
        public byte StationID
        {
            get { return m_StationID; }
            set { m_StationID = value; }
        }
        #endregion

        #region [StartAddress] 起始地址
        private ushort m_StartAddress;
        /// <summary>
        /// 起始地址
        /// </summary>
        public ushort StartAddress
        {
            get { return m_StartAddress; }
            set { m_StartAddress = value; }
        }
        #endregion

        #region [m_RegisterLength] 寄存器单位长度
      //  private int m_RegisterLength = 2;

        #endregion

        #region [DataType] 数据类型
        private string m_DataType;

        public string DataType
        {
            get { return m_DataType; }
            set { m_DataType = value; }
        } 
        #endregion

        #region [DataNum] 数据个数
        private ushort m_DataNum;
        /// <summary>
        /// 数据个数
        /// </summary>
        public ushort DataNum
        {
            get { return m_DataNum; }
            set { m_DataNum = value; }
        }

        #endregion

        #region [Values] 收发的数据
        private List<string> m_Values;
        /// <summary>
        /// 收发的数据
        /// 
        /// 在数据库中：
        /// 单个数据：123
        /// 多个数据：123,1.25
        /// </summary>
        public List<string> Values
        {
            get { return m_Values; }
            set { m_Values = value; }
        }
        #endregion

        #region [Handle] 发送标志位
        private int m_Handle;
        /// <summary>
        /// 发送标志位
        /// Handle置1，将下发values中的数据，之后程序自动置0
        /// </summary>
        public int Handle
        {
            get { return m_Handle; }
            set { m_Handle = value; }
        }

        #endregion

        #region [TimeOutMilliSeconds] 超时毫秒数
        private int m_TimeOutMilliSeconds;

        public int TimeOutMilliSeconds
        {
            get { return m_TimeOutMilliSeconds; }
            set { m_TimeOutMilliSeconds = value; }
        }
        #endregion

        //private string m_ConnString;
        private string m_StationInfoTableName;
        #endregion

        #region [ModbusMasterExClass] 构造函数
        public ModbusMasterExClass()
        {
            m_Logger = LogManager.GetCurrentClassLogger();
        }
        #endregion

        #region [Init] 初始化
        /// <summary>
        /// 初始化站点
        /// </summary>
        /// <param name="connString">连接字符串</param>
        /// <param name="groupTable">组 表</param>
        /// <param name="oneRow">站点信息表information</param>
        /// <returns></returns>
        public bool Initmaster(int cnti)
        {
            try
            {
               // m_Logger = LogManager.GetCurrentClassLogger();
                m_StationInfoTableName = PortOperationWin.Boardstatus.Modbus_Stationinfo.TableName;
                bool result = true;

                m_StationName = PortOperationWin.Boardstatus.Modbus_Stationinfo.Name[cnti];



                string stationType = PortOperationWin.Boardstatus.Modbus_Group.StationType;

                m_MasterType = (ModbusCommonClass.MODBUS_StationType)Enum.Parse(typeof(ModbusCommonClass.MODBUS_StationType), stationType);

                m_FunctionCode = ModbusCommonClass.ParseFunctionCode(PortOperationWin.Boardstatus.Modbus_Stationinfo.FunctionCode[cnti].ToString());

                if (m_FunctionCode == ModbusCommonClass.MODBUS_FunctionCode.UnKnown)
                {
                    m_Logger.Warn(string.Format("The function code '{0}' of station '{1}' is NOT valid!", m_FunctionCode.ToString(), m_StationName));
                    return false;
                }

            
                m_StationID = Convert.ToByte(PortOperationWin.Boardstatus.Modbus_Stationinfo.StationID[cnti]);
                m_StartAddress = Convert.ToUInt16(PortOperationWin.Boardstatus.Modbus_Stationinfo.StartAddress[cnti]);

               // m_RegisterLength = 2;
                m_DataType = PortOperationWin.Boardstatus.Modbus_Stationinfo.DataType[cnti];
                m_DataNum = Convert.ToUInt16(PortOperationWin.Boardstatus.Modbus_Stationinfo.DataNum[cnti]);
              //  m_Values = oneRow["Values"].ToString().Split(',').ToList();
                m_Handle = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Stationinfo.Handle[cnti]);
                m_TimeOutMilliSeconds = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Group.TimeOutMilliSeconds);

                switch (m_MasterType)
                {
                    case ModbusCommonClass.MODBUS_StationType.SerialAscii:
                        {
                            m_ParitySet = (Parity)(Enum.Parse(typeof(Parity), (PortOperationWin.Boardstatus.Modbus_Group.Parity)));
                            m_ComName = PortOperationWin.Boardstatus.Modbus_Group.COM;
                            m_BaudRate = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Group.BaudRate);
                            m_DataBits = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Group.DataBits);
                            m_StopBit = (StopBits)(Enum.Parse(typeof(StopBits), (PortOperationWin.Boardstatus.Modbus_Group.StopBit)));
                            break;
                        }
                    case ModbusCommonClass.MODBUS_StationType.SerialRtu:
                        {
                            m_ParitySet = (Parity)(Enum.Parse(typeof(Parity), (PortOperationWin.Boardstatus.Modbus_Group.Parity)));
                            m_ComName = PortOperationWin.Boardstatus.Modbus_Group.COM;
                            m_BaudRate = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Group.BaudRate);
                            m_DataBits = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Group.DataBits);
                            m_StopBit = (StopBits)(Enum.Parse(typeof(StopBits), (PortOperationWin.Boardstatus.Modbus_Group.StopBit)));
                            break;
                        }
                    case ModbusCommonClass.MODBUS_StationType.Tcp:
                        {
                            m_HostName = PortOperationWin.Boardstatus.Modbus_Group.HostName;
                            m_HostPort = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Group.HostPort);
                            break;
                        }
                    case ModbusCommonClass.MODBUS_StationType.Udp:
                        {
                            m_HostName = PortOperationWin.Boardstatus.Modbus_Group.HostName;
                            m_HostPort = Convert.ToInt32(PortOperationWin.Boardstatus.Modbus_Group.HostPort);
                            break;
                        }
                    default:
                        {
                            m_Logger.Warn(string.Format("The station type '{0}' of station '{1}' is NOT supported!", stationType, m_StationName));
                            return false;
                        }
                }
                return result;
            }
            catch (Exception Ex)
            {
                m_Logger.Error(Ex);
                return false;
            }
        }
        #endregion

        #region [Execute] 执行
        public bool Execute()
        {
            bool result = false;
            // 针对写的情况，如果handle位不是1，即当前站点不需要写入操作，直接退出该函数
            switch (m_FunctionCode)
            {
                case ModbusCommonClass.MODBUS_FunctionCode.WriteSingleCoil:
                case ModbusCommonClass.MODBUS_FunctionCode.WriteSingleRegister:
                case ModbusCommonClass.MODBUS_FunctionCode.WriteMultipleCoils:
                case ModbusCommonClass.MODBUS_FunctionCode.WriteMultipleRegisters:
                    {
                        if (m_Handle != 1)
                        {
                            return true;
                        }
                        break;
                    }
                default:
                    break;
            }
            switch (m_MasterType)
            {
                case ModbusCommonClass.MODBUS_StationType.SerialAscii:
                    {
                        SerialPort port = new SerialPort(m_ComName);
                        try
                        {
                            port.BaudRate = m_BaudRate;
                            port.DataBits = m_DataBits;
                            port.Parity = m_ParitySet;
                            port.StopBits = m_StopBit;
                            port.Open();

                            m_IMaster = ModbusSerialMaster.CreateAscii(port);
                            result = ExecuteCommon();
                            port.Close();
                            result = true;
                        }
                        catch (Exception ex)
                        {
                            m_Logger.Error(ex);
                            result = false;
                        }
                        finally
                        {
                            if (port != null)
                            {
                                if (port.IsOpen)
                                {
                                    port.Close();
                                }
                                port.Dispose();
                            }
                        }
                        break;
                    }
                case ModbusCommonClass.MODBUS_StationType.SerialRtu:
                    {
                        SerialPort port = new SerialPort(m_ComName);
                        try
                        {
                            port.BaudRate = m_BaudRate;
                            port.DataBits = m_DataBits;
                            port.Parity = m_ParitySet;
                            port.StopBits = m_StopBit;
                            port.Open();

                            m_IMaster = ModbusSerialMaster.CreateRtu(port);
                            result = ExecuteCommon();
                            port.Close();
                            result = true;
                        }
                        catch (Exception ex)
                        {
                            m_Logger.Error(ex);
                            result = false;
                        }
                        finally
                        {
                            if (port != null)
                            {
                                if (port.IsOpen)
                                {
                                    port.Close();
                                }
                                port.Dispose();
                            }
                        }
                        break;
                    }
                case ModbusCommonClass.MODBUS_StationType.Tcp:
                    {
                        TcpClient client = new TcpClient(m_HostName, m_HostPort);
                        try
                        {
                            if (!client.Connected)
                            {
                                client.Connect(m_HostName, m_HostPort);
                            }
                            if (m_IMaster != null)
                            {
                                m_IMaster.Dispose();
                            }
                            m_IMaster = ModbusIpMaster.CreateIp(client);
                            result = ExecuteCommon();
                            client.Close();
                          
                            result = true;
                        }
                        catch (Exception ex)
                        {
                            m_Logger.Error(ex);
                            return false;
                        }
                        finally
                        {
                            if (client.Client != null)
                            {
                                if (client.Connected)
                                {
                                    client.Close();
                                }
                            }
                        }
                        break;
                    }
                case ModbusCommonClass.MODBUS_StationType.Udp:
                    {
                        UdpClient client = new UdpClient();
                        try
                        {
                            IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(m_HostName), m_HostPort);
                            client.Connect(endPoint);
                            if (m_IMaster != null)
                            {
                                m_IMaster.Dispose();
                            }
                            m_IMaster = ModbusIpMaster.CreateIp(client);
                            result = ExecuteCommon();
                            client.Close();
                            result = true;
                        }
                        catch (Exception ex)
                        {
                            m_Logger.Error(ex);
                            return false;
                        }
                        finally
                        {
                            
                        }
                        break;
                    }
                default:
                    break;
            }
            return result;
        } //end execute
        #endregion

        #region [ExecuteCommon] 公共代码片段，该函数功能不独立
        /// <summary>
        /// Execute的公共代码片段，该函数功能不独立
        /// </summary>
        /// <returns></returns>
            private bool ExecuteCommon()
            {
                bool result = false;
                try 
	            {
                    //一个数据占用多少个单位寄存器（默认16位）长度
                    ushort unitPointRegistersLength = 1;
                    switch (m_DataType.Trim().ToLower())
                    {
                        case "uint32": // 两个ushort拼接一个uint32
                        case "float":  // 两个ushort拼接一个float
                            {
                                unitPointRegistersLength = 2;
                                break;
                            }
                        case "double":  // 四个ushort拼接一个float
                            {
                                unitPointRegistersLength = 4;
                                break;
                            }
                        default: // boolean, uint16
                            {
                                unitPointRegistersLength = 1;
                                break;
                            }
                    }
		            switch (m_FunctionCode)
                    {
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadCoils:
                            {
                                Task<bool[]> tmpTask = m_IMaster.ReadCoilsAsync(m_StationID, m_StartAddress, Convert.ToUInt16(m_DataNum * unitPointRegistersLength) );
                                if( tmpTask.Wait(m_TimeOutMilliSeconds) )
                                {
                                    m_Values = new List<string>();
                                    foreach (var item in tmpTask.Result)
                                    {
                                        m_Values.Add(item.ToString());
                                    }
                                    result = true;
                                }
                                else
                                {
                                    m_Logger.Error(string.Format("The station '{0}' ReadCoils timeout!", m_StationName));
                                    result = false;
                                }
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadDiscreteInputs:
                            {
                                Task<bool[]> tmpTask = m_IMaster.ReadInputsAsync(m_StationID, m_StartAddress, Convert.ToUInt16(m_DataNum * unitPointRegistersLength));
                                if( tmpTask.Wait(m_TimeOutMilliSeconds) )
                                {
                                    m_Values = new List<string>();
                                    foreach (var item in tmpTask.Result)
                                    {
                                        m_Values.Add(item.ToString());
                                    }
                                    result = true;
                                }
                                else
                                {
                                    m_Logger.Error(string.Format("The station '{0}' ReadDiscreteInputs timeout!", m_StationName));
                                    result = false;
                                }
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadHoldingRegisters:
                            {
                                Task<ushort[]> tmpTask = m_IMaster.ReadHoldingRegistersAsync(m_StationID, m_StartAddress, Convert.ToUInt16(m_DataNum * unitPointRegistersLength));
                                
                                if( tmpTask.Wait(m_TimeOutMilliSeconds) )
                                {
                                    m_Values = new List<string>();
                                    if (tmpTask.Result == null)
                                    {
                                        result = false;
                                        break;
                                    }
                                    foreach (var item in tmpTask.Result)
                                    {
                                        m_Values.Add(item.ToString());

                                    }
                                    result = true;
                                }
                                else
                                {
                                    m_Logger.Error(string.Format("The station '{0}' ReadHoldingRegisters timeout!", m_StationName));
                                    result = false;
                                }
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.ReadInputRegisters:
                            {
                                Task<ushort[]> tmpTask = m_IMaster.ReadInputRegistersAsync(m_StationID, m_StartAddress, Convert.ToUInt16(m_DataNum * unitPointRegistersLength));
                                if( tmpTask.Wait(m_TimeOutMilliSeconds) )
                                {
                                    m_Values = new List<string>();
                                    foreach (var item in tmpTask.Result)
                                    {
                                        m_Values.Add(item.ToString());
                                    }
                                    result = true;
                                }
                                else
                                {
                                    m_Logger.Error(string.Format("The station '{0}' ReadInputRegisters timeout!", m_StationName));
                                    result = false;
                                }
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteSingleCoil:
                            {
                                try
                                {
                                    if (m_Values == null || m_Values.Count < 1)
                                    {
                                        m_Logger.Error(string.Format("The WriteSingleCoil value of station '{0}' is empty!", m_StationName));
                                        result = false;
                                        return result;
                                    }
                                    bool writeValue;

                                    bool convertResult = bool.TryParse(m_Values.ElementAt(0), out writeValue);
                                    if (!convertResult)
                                    {
                                        m_Logger.Error(string.Format("The WriteSingleCoil value '{0}' of station '{1}' is NOT valid!", m_Values.ElementAt(0), m_StationName));
                                        result = false;
                                        return result;
                                    }
                                    Task tmpTask = m_IMaster.WriteSingleCoilAsync(m_StationID, m_StartAddress, writeValue);
                                    if (tmpTask.Wait(m_TimeOutMilliSeconds))
                                    {
                                        result = true;
                                    }
                                    else
                                    {
                                        m_Logger.Error(string.Format("The station '{0}' WriteSingleCoil timeout!", m_StationName));
                                        result = false;
                                    }
                                }
                                catch (Exception ex)
                                {
                                    m_Logger.Error(ex);
                                    result = false;
                                }
                                finally 
                                {
                                    // 不管写入是否成功，都要清handle位。写入失败会在日志中体现出来。
                                 //   DbHelperClass dbhelp = new DbHelperClass();
                                    //dbhelp.ClearHandle(m_ConnString, m_StationInfoTableName, m_StationName);
                                }
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteSingleRegister:
                            {
                                try
                                {
                                    if (m_Values == null || m_Values.Count < 1)
                                    {
                                        m_Logger.Error(string.Format("The WriteSingleRegister value of station '{0}' is empty!", m_StationName));
                                        result = false;
                                        return result;
                                    }
                                    ushort writeValue;
                                    bool convertResult = ushort.TryParse(m_Values.ElementAt(0), out writeValue);
                                    if (!convertResult)
                                    {
                                        m_Logger.Error(string.Format("The WriteSingleRegister value '{0}' of station '{1}' is NOT valid!", m_Values.ElementAt(0), m_StationName));
                                        result = false;
                                        return result;
                                    }

                                    Task tmpTask = m_IMaster.WriteSingleRegisterAsync(m_StationID, m_StartAddress, writeValue);
                                    if (tmpTask.Wait(m_TimeOutMilliSeconds))
                                    {
                                        result = true;
                                    }
                                    else
                                    {
                                        m_Logger.Error(string.Format("The station '{0}' WriteSingleRegister timeout!", m_StationName));
                                        result = false;
                                    }
                                }
                                catch (Exception ex)
                                {
                                    m_Logger.Error(ex);
                                    result = false;
                                }
                                finally
                                {
                                    // 不管写入是否成功，都要清handle位。写入失败会在日志中体现出来。
                               //     DbHelperClass dbhelp = new DbHelperClass();
                                    //dbhelp.ClearHandle(m_ConnString, m_StationInfoTableName, m_StationName);
                                }
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteMultipleCoils:
                            {
                                try
                                {
                                    if (m_Values == null || m_Values.Count < 1)
                                    {
                                        m_Logger.Error(string.Format("The WriteMultipleCoils value of station '{0}' is empty!", m_StationName));
                                        result = false;
                                        return result;
                                    }
                                    List<bool> writeValue = new List<bool>();
                                    for (int i = 0; i < m_Values.Count; i++)
                                    {
                                        bool tempValue;
                                        bool convertResult = bool.TryParse(m_Values.ElementAt(i), out tempValue);
                                        if (!convertResult)
                                        {
                                            m_Logger.Error(string.Format("The {0} WriteMultipleCoils value '{1}' of station '{2}' is NOT valid!", i.ToString(), m_Values.ElementAt(i), m_StationName));
                                            result = false;
                                            return result;
                                        }
                                        writeValue.Add(tempValue);
                                    }
                                    Task tmpTask = m_IMaster.WriteMultipleCoilsAsync(m_StationID, m_StartAddress, writeValue.ToArray());
                                    if (tmpTask.Wait(m_TimeOutMilliSeconds))
                                    {
                                        result = true;
                                    }
                                    else
                                    {
                                        m_Logger.Error(string.Format("The station '{0}' WriteMultipleCoils timeout!", m_StationName));
                                        result = false;
                                    }
                                }
                                catch (Exception ex)
                                {
                                    m_Logger.Error(ex);
                                    result = false;
                                }
                                finally
                                {
                                    // 不管写入是否成功，都要清handle位。写入失败会在日志中体现出来。
                                  //  DbHelperClass dbhelp = new DbHelperClass();
                                    //dbhelp.ClearHandle(m_ConnString, m_StationInfoTableName, m_StationName);
                                }
                                break;
                            }
                        case ModbusCommonClass.MODBUS_FunctionCode.WriteMultipleRegisters:
                            {
                                try
                                {
                                    if (m_Values == null || m_Values.Count < 1)
                                    {
                                        m_Logger.Error(string.Format("The WriteMultipleRegisters value of station '{0}' is empty!", m_StationName));
                                        result = false;
                                        return result;
                                    }
                                    List<ushort> writeValue = new List<ushort>();
                                    for (int i = 0; i < m_Values.Count; i++)
                                    {
                                        ushort tempValue;

                                        bool convertResult = ushort.TryParse(m_Values.ElementAt(i), out tempValue);
                                        if (!convertResult)
                                        {
                                            m_Logger.Error(string.Format("The {0} WriteMultipleRegisters value '{1}' of station '{2}' is NOT valid!", i.ToString(), m_Values.ElementAt(i), m_StationName));
                                            result = false;
                                            return result;
                                        }
                                        writeValue.Add(tempValue);
                                    }
                                    Task tmpTask = m_IMaster.WriteMultipleRegistersAsync(m_StationID, m_StartAddress, writeValue.ToArray());
                                    if (tmpTask.Wait(m_TimeOutMilliSeconds))
                                    {
                                        result = true;
                                    }
                                    else
                                    {
                                        m_Logger.Error(string.Format("The station '{0}' WriteMultipleRegisters timeout!", m_StationName));
                                        result = false;
                                    }
                                }
                                catch (Exception ex)
                                {
                                    m_Logger.Error(ex);
                                    result = false;
                                }
                                finally
                                {
                                    // 不管写入是否成功，都要清handle位。写入失败会在日志中体现出来。
                                    //DbHelperClass dbhelp = new DbHelperClass();
                                    //dbhelp.ClearHandle(m_ConnString, m_StationInfoTableName, m_StationName);
                                }
                                break;
                            }
                        default:
                            {
                                m_Logger.Error(string.Format("The function code of station '{1}' is unknown!", m_StationName));
                                result = false;
                                break;
                            }
                    } // end switch functioncode
                    return result;
	            }
	            catch (Exception ex)
	            {
		            m_Logger.Error(ex);
                    return false;
	            }
            } // end ExecuteCommon
        #endregion

    }
}
