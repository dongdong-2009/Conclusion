//对自定义dll文件的处理， 当存在第三方dll，或其他编程人员编写的dll文件时，可以将其直接拷贝到目录（如下代码中目录）
//并需要对Component.xml文件进行修改，即可在程序中载入dll，拖拽和使用
//AddedComponent
//Component.xml文件修改：
//例如：
//  <AddedComponent FullName="Controls.MetroCombox" Name="MetroCombox" Namespace="System.Windows.Forms" Asm="DMSkin.dll">
//    <Propertys>
//      <Property Name="Location" Caption="Location" Group=""/>
//      <Property Name="Name" Caption="Name" Group=""/>
//    </Propertys>
//  </AddedComponent>
//其中   AddedComponent为固定名称  
//       Controls.MetroCombox为具体控件所在dll目录
//       Asm为dll名称
//       Propertys中的内容为控件的属性名称
//填入这些信息即可
//xuehaoyuan   2016-5-31 14:59:31
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.IO;

namespace Designer.DllManager
{
    public class CDllManager
    {
        #if DEBUG
            public string DLLPATH = System.IO.Directory.GetParent(System.Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "\\Release\\Plugins\\";
            public string RUNTIMEDLLPATH = System.IO.Directory.GetParent(System.Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "\\Release\\Plugins\\";
            //public string DLLPATH = "E:\\Bstar\\Dlls\\";
#else
        public string RUNTIMEDLLPATH = System.IO.Directory.GetParent(System.Environment.CurrentDirectory) + "\\Plugins\\";
            public string DLLPATH = System.Environment.CurrentDirectory + "\\Plugins\\";  
        #endif
        public string BackupDLLPATH = "E:\\Bstar\\Dlls\\";

        public ArrayList GetAll(DirectoryInfo dir)//搜索文件夹中的文件
        {
            ArrayList FileList = new ArrayList();
            if (!System.IO.Directory.Exists(@DLLPATH))
            {
                try
                {
                    System.IO.Directory.CreateDirectory(@DLLPATH);//不存在就创建目录 
                }
                catch
                {
                    System.IO.Directory.CreateDirectory(@BackupDLLPATH);//不存在就创建目录
                    dir = new DirectoryInfo(BackupDLLPATH);
                }
            } 
            FileInfo[] allFile = dir.GetFiles();
            foreach (FileInfo fi in allFile)
            {
                if (fi.Name.Substring(fi.Name.Length - 4, 4) == ".dll")//字符串截取
                    FileList.Add(fi.Name);
            }

            DirectoryInfo[] allDir = dir.GetDirectories();
            foreach (DirectoryInfo d in allDir)
            {
                GetAll(d);
            }
            return FileList;
        }
        public ArrayList GetAllDLL(DirectoryInfo dir)//搜索文件夹中的文件
        {
            ArrayList FileList = new ArrayList();

            FileInfo[] allFile = dir.GetFiles();
            foreach (FileInfo fi in allFile)
            {
                FileList.Add(fi.Name);
            }

            DirectoryInfo[] allDir = dir.GetDirectories();
            foreach (DirectoryInfo d in allDir)
            {
                GetAll(d);
            }
            return FileList;
        }
    }
}
