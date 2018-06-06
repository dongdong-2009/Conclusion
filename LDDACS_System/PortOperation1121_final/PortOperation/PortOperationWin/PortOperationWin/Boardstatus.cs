using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PortOperationWin
{
    public class Boardstatus
    {
        public static System.IO.Ports.SerialPort port = new System.IO.Ports.SerialPort();
        public static System.IO.Ports.SerialPort userport = new System.IO.Ports.SerialPort();

        public static byte PortSelected = 0;
        public static byte userPortSelected = 0;

        public static byte userPortReadEn = 0;
        public static byte slaveId = 5;

        public static byte userslaveId = 7;

        public static ushort AIdataCnt = 12;
        public static ushort AOdataCnt = 8;

        public static string[] AIdataF = new string[AIdataCnt];
        public static float[] AOdataF = new float[AOdataCnt];

        public static ushort AImodeCnt = 12;
        public static ushort AOmodeCnt = 8;

        public static string[] AImodeI = new string[AImodeCnt];
        public static string[] AOmodeI = new string[AOmodeCnt];

        public static ushort DIdataCnt = 8;
        public static ushort DOdataCnt = 8;

        public static string[] DIdataI = new string[DIdataCnt];
        public static string[] DOdataI = new string[DOdataCnt];

        public static ushort CntRTDdata = 4;
        public static string[] RTDdataF = new string[CntRTDdata];

        public static float[] PWM1dataF = new float[2] ;
        public static float[] PWM2dataF = new float[2] ;

        public static string[] UserModbusSenddataI = new string[1];
        public static string[] UserModbusRevdataI  = new string[1];

    
        public struct Modbus_Stationinfo
        {
            public static string TableName;
            public static int Statnum =1;
            public static string[] Name = { "AIdataF", "AOdataF", "AImodeI", "AOmodeI", "DIdataI", "DOdataI", "RTDdataF", "PWM1dataF", "PWM2dataF", "UserModbusSenddataI", "UserModbusRevdataI" };
            public static string Enable = "true";
            public static string GroupName = "board";
            public static string[] StationID = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" };
            public static string[] FunctionCode = { "03(0x03)", "06(0x06)", "06(0x06)", "06(0x06)", "03(0x03)", "06(0x06)", "03(0x03)", "06(0x06)", "06(0x06)", "06(0x06)", "03(0x03)" };
            public static ushort[] StartAddress = { 0x0, 0x0, 0x10, 0x1D, 0x10, 0x08, 0xC, 0x26, 0x29, 0, 0 };

            public static string RegisterLength = "2";
            public static string[] DataType = { "float", "float", "UInt16", "UInt16", "UInt16", "UInt16", "float", "float", "float", "UInt16", "UInt16" };
            public static ushort[] DataNum = { 12, 8, 12, 8, 8, 8, 4, 1, 1, 24, 24 };

            public static string Values = "Values";
            public static string[] Handle = { "0", "00000000", "000000000000", "00000000", "0", "00000000", "0", "00", "00", "0", "0" };
            public static string Description = "Description";
            public static string DateTime = "time";
        }

        public struct Modbus_Group
        {
            public static string ID = "1";
            public static string GroupName = "singleboard";
            public static string ClientID = "1";

            public static string Enable = "true";
            public static string IsAsync = "true";
            public static string TimeOutMilliSeconds = "1000";

            public static string StationType = "SerialRtu";
            public static string HostName = "";
            public static string HostPort = "502";

            public static string COM = "COM3";
            public static string BaudRate = "9600";
            public static string DataBits = "8";

            public static string Parity = "Odd";
            public static string StopBit = "One";
            public static string Description = "Description";

        }


    }
}
