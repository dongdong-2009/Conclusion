using System;
using System.IO.Ports;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using Modbus.Data;
using Modbus.Device;
using Modbus.Utility;
//using Modbus.Serial;

namespace ModbusDAQ
{
    /// <summary>
    ///     Demonstration of NModbus
    /// </summary>
    public class Driver
    {
   

        /// <summary>
        ///     Simple Modbus serial RTU master write holding registers example.
        /// </summary>
        public static void ModbusSerialRtuMasterWriteRegisters(SerialPort port, ushort startAddress, byte slaveId, ushort registers)
        {

                //var adapter = new SerialPortAdapter(port);
                // create modbus master
                IModbusSerialMaster master = ModbusSerialMaster.CreateRtu(port);

                // write three registers
                master.WriteSingleRegister(slaveId, startAddress, registers);
           
        }

        /// <summary>
        ///     Simple Modbus serial ASCII master read holding registers example.
        /// </summary>
        public static ushort[]  ModbusSerialRtuMasterReadRegisters(SerialPort port, ushort startAddress, ushort numRegisters,byte slaveId, ushort[] registers)
        {
          
                //var adapter = new SerialPortAdapter(port);
                // create modbus master
                IModbusSerialMaster master = ModbusSerialMaster.CreateRtu(port);

                // read five registers		
                registers = master.ReadHoldingRegisters(slaveId, startAddress, numRegisters);

            return registers;
        }

  
        /// <summary>
  
     
        /// <summary>
        ///     Write a 32 bit value.
        /// </summary>
        public static void ReadWrite32BitValue(SerialPort port, ushort startAddress, ushort numRegisters, byte slaveId, ushort[] registers)
        {
          
                //port.Open();

                //var adapter = new SerialPortAdapter(port);
                //// create modbus master
                //ModbusSerialMaster master = ModbusSerialMaster.CreateRtu(adapter);

               
                //uint largeValue = UInt16.MaxValue + 5;

                //ushort lowOrderValue = BitConverter.ToUInt16(BitConverter.GetBytes(largeValue), 0);
                //ushort highOrderValue = BitConverter.ToUInt16(BitConverter.GetBytes(largeValue), 2);

                //// write large value in two 16 bit chunks
                //master.WriteMultipleRegisters(slaveId, startAddress, new ushort[] { lowOrderValue, highOrderValue });

                //// read large value in two 16 bit chunks and perform conversion
                //registers = master.ReadHoldingRegisters(slaveId, startAddress, 2);
                //uint value = ModbusUtility.GetUInt32(registers[1], registers[0]);
           
        }

        internal static void ModbusSerialRtuMasterWriteRegisters(SerialPort port, ushort startAddress, byte slaveId, string[] aOdataF)
        {
            throw new NotImplementedException();
        }
    }
}
