using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ModbusDAQ
{
    public class ModbusCommonClass
    {
        #region 【成员变量】

        #region [MODBUS_FunctionCode] 功能码（枚举类型）
        /// <summary>
        /// 功能码枚举
        /// </summary>
        public enum MODBUS_FunctionCode : byte
        {
            /// <summary>
            /// 未知功能码
            /// </summary>
            UnKnown = 0,

            /// <summary>
            /// 01 (0x01): 读取线圈（ReadCoils）
            /// </summary>
            ReadCoils = 1,

            /// <summary>
            /// 02 (0x02): 读取离散线圈（ReadDiscreteInputs）
            /// </summary>
            ReadDiscreteInputs = 2,

            /// <summary>
            /// 03 (0x03): 读取保持寄存器(Read Holding Registers)
            /// </summary>
            ReadHoldingRegisters = 3,

            /// <summary>
            /// 04 (0x04): 读取输入寄存器（Read Input Registers）
            /// </summary>
            ReadInputRegisters = 4,

            /// <summary>
            /// 05 (0x05): 写单个线圈（Write Single Coil）
            /// </summary>
            WriteSingleCoil = 5,

            /// <summary>
            /// 06 (0x06): 写单个寄存器（Write Single Register）
            /// </summary>
            WriteSingleRegister = 6,

            /// <summary>
            /// 15 (0x0F): 写多个线圈（Write Multiple Coils）
            /// </summary>
            WriteMultipleCoils = 15,

            /// <summary>
            /// 16 (0x10): 写多个寄存器(Write Multiple registers)
            /// </summary>
            WriteMultipleRegisters = 16

        }
        #endregion

        #region [MODBUS_StationType] 主/从站类别
        public enum MODBUS_StationType : byte
        {
            SerialAscii = 0,
            SerialRtu   = 1,
            Tcp         = 2,
            Udp         = 3
        }
        #endregion

        
        #endregion

        #region [ParseFunctionCode] 由字符串转功能码
        /// <summary>
        /// 由字符串转功能码
        /// </summary>
        /// <param name="functionCodeString"></param>
        /// <returns></returns>
        public static MODBUS_FunctionCode ParseFunctionCode(string functionCodeString)
        {
            MODBUS_FunctionCode result = MODBUS_FunctionCode.UnKnown;
            switch (functionCodeString.Trim())
            {
                case "01(0x01)":
                    {
                        result = MODBUS_FunctionCode.ReadCoils;
                        break;
                    }
                case "02(0x02)":
                    {
                        result = MODBUS_FunctionCode.ReadDiscreteInputs;
                        break;
                    }
                case "03(0x03)":
                    {
                        result = MODBUS_FunctionCode.ReadHoldingRegisters;
                        break;
                    }
                case "04(0x04)":
                    {
                        result = MODBUS_FunctionCode.ReadInputRegisters;
                        break;
                    }
                case "05(0x05)":
                    {
                        result = MODBUS_FunctionCode.WriteSingleCoil;
                        break;
                    }
                case "06(0x06)":
                    {
                        result = MODBUS_FunctionCode.WriteSingleRegister;
                        break;
                    }
                case "15(0x0F)":
                    {
                        result = MODBUS_FunctionCode.WriteMultipleCoils;
                        break;
                    }
                case "16(0x10)":
                    {
                        result = MODBUS_FunctionCode.WriteMultipleRegisters;
                        break;
                    }
                default:
                    {
                        break;
                    }
            }
            return result;
        }
        #endregion

        #region [UInt32ToNetworkBytes] UInt32转byte[]
        /// <summary>
        /// UInt32转byte[]
        /// 网络字节顺序NBO(Network Byte Order): 按从高到低的顺序存储
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static byte[] UInt32ToNetworkBytes(UInt32 number)
        {
            byte[] result = new byte[4];
            result[3] = (byte)(number);
            result[2] = (byte)(number >> 8);
            result[1] = (byte)(number >> 16);
            result[0] = (byte)(number >> 24);
            return result;
        }
        #endregion

    }
}
