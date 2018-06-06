//====================================================================
// 文件名: MainForm.cs
//
// 文件描述:
// ------------------------------------------------------------------
// 绘图工具主界面
// ------------------------------------------------------------------
// 
// 时间: 2015.06
// 编程: xuehaoyuan
// ------------------------------------------------------------------
// 修改说明(请按格式说明)...
// ------------------------------------------------------------------
// 请对 较复杂函数 所实现功能、输入输出做较细致说明
//====================================================================

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.IO;
using WeifenLuo.WinFormsUI.Docking;
using Host;
using System.Xml;
using System.Runtime.Serialization.Formatters.Binary;
using Loader;
using System.Drawing.Design;
using System.Drawing.Drawing2D;
using System.Reflection;
using System.Runtime.InteropServices;
namespace Designer
{
    public partial class MainForm : Form
    {
        #region 变量

        private DrawTool.DBConnect  m_dbConnect;

        private HostControl         hc                = null;
        private List<HostControl>   hcList            = new List<HostControl>();
        private List<EditWin>       editWinList       = new List<EditWin>();

        public List<boardType>     btDeCoilCwList   = new List<boardType>();
        public List<boardType>     btDeNoCoilCwList = new List<boardType>();
        public List<boardType>     btDeCoilHpList   = new List<boardType>();
        public List<boardType>     btDeNoCoilHpList  = new List<boardType>();

        public List<boardType>     btReAdjHwList = new List<boardType>();
        public List<boardType>     btReNoAdjHwList = new List<boardType>();
        public List<boardType>     btReAdjHpList = new List<boardType>();
        public List<boardType>     btReNoAdjHpList = new List<boardType>();
        public string myProjectPath = "";

        private XmlDocument         mXDoc             = new XmlDocument();
        private string              myProjectFullName = "";
        private string              MainFirstForm     = "";

        public DBTool.DBProgram                 dbMainWindow;
        public DrawTool.DrawToolProgram         drawToolWindow;
        public Options.DataBase_Configure       dbConfigWindow;
        public DAQ.DAQ                          daqWindow;
        public enum ControlChangeType
        {
            ComponentChange = 1,
            FormChange = 2,
        }
        //----< 判断当前是否在操作程序 xuehaoyuan 
        [DllImport("user32.dll")]
        private static extern IntPtr GetForegroundWindow();
        [DllImport("user32.dll", EntryPoint = "FindWindow")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        //---->
        private DllManager.CDllManager dllmng; //自定义dll功能
        #endregion 变量

        public MainForm()
        {
            InitializeComponent();
            DLLInit();

           string curPath = AppDomain.CurrentDomain.BaseDirectory+ "configdoc.xml";//获取基目录，它由程序集冲突解决程序用来探测程序集。 
           XmlDocument configDoc = new XmlDocument();
           configDoc.Load(curPath);
           XmlNode configDocelement = configDoc.DocumentElement;

            if (configDocelement.HasChildNodes)
            {
                foreach(XmlNode node in configDocelement.ChildNodes)
                {
                    if (node.Attributes.Count>0)
                    {
                        boardType myBoardType = new boardType();
                      switch (node.Attributes["name"].Value)
                        { 
                          case "DeCoilCw":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btDeCoilCwList.Add(myBoardType);
                                break;
                        case "DeNoCoilCw":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btDeNoCoilCwList.Add(myBoardType);
                                break;
                        case "DeCoilHp":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btDeCoilHpList.Add(myBoardType);
                                break;
                        case "DeNoCoilHp":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btDeNoCoilHpList.Add(myBoardType);
                                break;

                        case "ReAdjHw":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btReAdjHwList.Add(myBoardType);
                                break;
                        case "ReNoAdjHw":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btReNoAdjHwList.Add(myBoardType);
                                break;
                        case "ReAdjHp":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btReAdjHpList.Add(myBoardType);
                                break;
                        case "ReNoAdjHp":
                                myBoardType.boardName = node.Attributes["name"].Value;
                                myBoardType.boardNumber = node.Attributes["boardNumber"].Value;
                                myBoardType.targetType = node.Attributes["targetType"].Value;
                                btReNoAdjHpList.Add(myBoardType);
                                break;
                        }
                    }
                }
            }

            //configDoc.Save(myProjectFullName);

            try { dbMainWindow = new DBTool.DBProgram(this); }
            catch {MessageBox.Show("Failed to link the Database！"); }
            drawToolWindow = new DrawTool.DrawToolProgram(this);



        }

        #region 新建工程 打开工程 等等
        //新建工程
        public void NewProject()
        {
            if (myProjectPath != "")
            {
                if (DialogResult.No == MessageBox.Show("工程已存在，确实要新建吗？", "Alert", MessageBoxButtons.YesNo))
                {
                    return;
                }

                SaveButton.PerformClick();
                //关闭工程
                CloseProject();
                myProjectPath = "";
            }

            foreach (EditWin m_edit in drawToolWindow.editWinList)
            {
                m_edit.Close();
            }
            drawToolWindow.editWinList.Clear();

            FormNewProject proj = new FormNewProject();
            if (proj.ShowDialog() == DialogResult.OK)
            {
                string ProjPath = proj.projPath;
                string myProjName = proj.projName;
                string s = ProjPath.Substring(ProjPath.Length - 1, 1);
                if (s == "\\")
                {
                    myProjectPath = ProjPath + myProjName + "\\";
                    myProjectFullName = myProjectPath + myProjName + ".mproj";
                }
                else
                {
                    myProjectPath = ProjPath + "\\" + myProjName + "\\"; ;
                    myProjectFullName = myProjectPath + myProjName + ".mproj";
                }
                DirectoryInfo dir = new DirectoryInfo(myProjectPath);
                dir.Create();
                //bDirty = true;
                drawToolWindow.myProjectFullName = myProjectFullName;
                drawToolWindow.myProjectPath = myProjectPath;
                XmlDocument doc = new XmlDocument();
                doc.LoadXml("<MProj></MProj>");
                doc.Save(myProjectFullName);


            }
        }
        public void OpenProject()
        {
            //关闭当前工程 打开新工程 未实现 
           // int num = drawToolWindow.editWinList.Count();

            if (myProjectPath != "")
            {
                if (DialogResult.No == MessageBox.Show("工程已存在, 确实要新打开一个工程吗？",
               "Alert", MessageBoxButtons.YesNo))
                {
                    return;
                }
                CloseProject();
            }
            foreach (EditWin m_edit in drawToolWindow.editWinList)
            {
                 m_edit.Close();
            }
            drawToolWindow.editWinList.Clear();

             OpenFileDialog openFileDialog = new OpenFileDialog();
             openFileDialog.Filter = "MProj Files (*.mproj) |*.mproj";
             openFileDialog.InitialDirectory = "";
             openFileDialog.Title = "Open project file";
             openFileDialog.FileName = "";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                drawToolWindow.m_bindWin = new DrawTool.Bind();
                drawToolWindow.m_bindWin.Show();

                string projectpath = openFileDialog.FileName;
                myProjectFullName = projectpath;
                myProjectPath = new FileInfo(projectpath).DirectoryName;
                myProjectPath = myProjectPath + "\\";
                string sname = new FileInfo(projectpath).Name;
                string myProjectName = "";
                if (sname.Contains(".mproj"))
                {
                    myProjectName = sname.Substring(0, sname.Length - 6);
                }
                drawToolWindow.myProjectFullName = myProjectFullName;
                drawToolWindow.myProjectPath = myProjectPath;
                try
                {
                    String p = myProjectPath + "first.form";
                    using (FileStream fs = new FileStream(p, FileMode.Open))
                    {
                        BinaryFormatter formatter = new BinaryFormatter();
                        MainFirstForm = (string)formatter.Deserialize(fs);
                        drawToolWindow.MainFirstForm = MainFirstForm;
                        fs.Close();
                    }
                }
                catch (Exception err)
                {
                    MessageBox.Show("Exception:" + err.ToString(), "载入启动画面错误!");
                }
            }
        }
        //关闭当前工程
        public void CloseProject()
        {
            if (editWinList.Count > 0)
            {
                //close form
                foreach (EditWin Node in editWinList)
                {
                    drawToolWindow.m_editWin = Node;
                    drawToolWindow.m_editWin.Close();
                }
                editWinList.Clear();
                //close hc
                foreach (HostControl h in hcList)
                {
                    hc = h;
                    hc.Dispose();
                }
                hcList.Clear();
            }
            MainFirstForm = "";
        }

        #endregion 新建工程 打开工程

        #region draw project

        private void Save_Click(object sender, EventArgs e)
        {
            drawToolWindow.Save();
        }

        private void saveInExit_Click(object sender, EventArgs e)
        {
            drawToolWindow.saveInExit();
        }
        //新建工程
        private void NewProject_Click(object sender, EventArgs e)
        {
            NewProject();
        }

        private void Open_Click(object sender, EventArgs e)
        {
            OpenProject();
        }

        private void DeleteButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("删除(&D)");
        }

        private void copyButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("复制(&C)");
        }

        private void pasteButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("粘贴(&P)");
        }

        private void cutButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("剪切(&C)");
        }

        private void selectAllButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("全选(&S)");
        }

        private void BringForwardButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("前移一层(&U)");
        }

        private void SendBackwardButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("后移一层(&D)");
        }

        private void ArrangeButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.PerformAction("左对齐(&L)");
        }

        private void UndoButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.Undo();
        }

        private void RedoButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.Redo();
        }

        #region 上下左右移动

        //控件按像素移动方法 需改写扩充
        private void LeftButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.MoveLeft();
        }

        private void DownButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.MoveDown();

        }

        private void UpButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.MoveUp();

        }

        private void RightButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.MoveRight();

        }

        #endregion

        //旋转
        private void RotateLeftButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.RotateLeft();
        }

        private void RotateRightButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.RotateRight();
        }

        //镜像
        private void MirrorRL_Click(object sender, EventArgs e)
        {
            drawToolWindow.MirrorLR();
        }

        private void MirrorUD_Click(object sender, EventArgs e)
        {
            drawToolWindow.MirrorUpDown();
        }

        //判断当前界面是否在最前（被使用） 配合hook使用，消除bug xuehaoyuan 2016-4-8 15:38:13
        public bool ProgramInUse()
        {
            IntPtr cu = GetForegroundWindow();
            IntPtr dh = this.Handle;
            if (cu == dh)
                return true;
            else
                return false;
        }
        #endregion draw project

        #region 菜单
        private void PropertyWindowStripMenuItem_Click(object sender, EventArgs e)
        {
            drawToolWindow.m_propertyWin.Show(dockPanel1);
        }

        private void ModuleBoxStripMenuItem_Click(object sender, EventArgs e)
        {
            drawToolWindow.m_moduleWin.Show(dockPanel1);
        }


        private void ToolBoxStripMenuItem_Click(object sender, EventArgs e)
        {
            drawToolWindow.m_toolBoxWin.Show(dockPanel1);
        }
        //退出按钮
        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveButton.PerformClick();//save and exit
            this.Close();
        }
        private void dataBaseEditToolStripMenuItem_Click(object sender, EventArgs e)
        {
            dbConfigWindow = new Options.DataBase_Configure();
            dbConfigWindow.Show();
        }

        private void dBConnectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_dbConnect = new DrawTool.DBConnect();
            m_dbConnect.Show(dockPanel1);
            m_dbConnect.mainForm = this;
        }

        private void NewButton_Click(object sender, EventArgs e)
        {
            NewProject();
            //drawToolWindow.newFormClick();
        }

        private void firstFormToolStripMenuItem_Click(object sender, EventArgs e)
        {
            drawToolWindow.HomePage_Click();
        }

        private void bindWindowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            drawToolWindow.m_bindWin = new DrawTool.Bind();
            drawToolWindow.m_bindWin.Show();
        }

        private void drawToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DrawToolStrip.Show();

        }

        private void dBToolStripMenuItem_Click(object sender, EventArgs e)
        { 
            DrawToolStrip.Hide();
         //   DBToolStrip.Show();
        }
        #endregion
        
        #region runtime
        private void RunButton_Click(object sender, EventArgs e)
        {
            drawToolWindow.m_bindWin.Close();
            RunTime.RunTimeFormMng tr = new RunTime.RunTimeFormMng(this);
        }
        #endregion runtime



        #region 对自定义DLL模块的初始化
        private void DLLInit()
        {
            dllmng = new DllManager.CDllManager();
            DirectoryInfo dir = new DirectoryInfo(dllmng.DLLPATH);
            ArrayList dllList = dllmng.GetAll(dir);

            string destPath = Application.StartupPath;
            foreach (string dllname in dllList)
            {
                if (File.Exists(@destPath + "\\" + dllname))
                {
                    File.Delete(@destPath + "\\" + dllname);
                    System.IO.File.Copy(@dllmng.DLLPATH + dllname, destPath + "\\" + dllname);
                }
                else
                {
                    System.IO.File.Copy(@dllmng.DLLPATH + dllname, destPath + "\\" + dllname);
                }
            }
            //Application.StartupPath
        }
        #endregion 
        //test
        private void showToolstripToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //DrawToolStrip.Hide();
        }

        private void MainForm_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
          //  SaveButton.PerformClick();//save and exit
            this.Dispose();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            //自动对齐网格的方法  功能不完善
            drawToolWindow.ShowGrid();
        }

        //类似编译按钮，点击后打包一份运行时文件，

        public string RUNTIMEPATH = System.Environment.CurrentDirectory ;  

        private void BuildButton_Click(object sender, EventArgs e)
        {
            string target = "";
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                target = this.folderBrowserDialog1.SelectedPath;
            }

            if (myProjectPath != "" && myProjectPath != null)
                CopyDirectory(myProjectPath, RUNTIMEPATH + "\\BStar");

            CopyDirectory(RUNTIMEPATH + "\\BStar\\", target);

            MessageBox.Show("Success", "Alert", MessageBoxButtons.OK, MessageBoxIcon.Information);

        }

        private void CopyDirectory(string srcdir, string desdir)
        {
            srcdir = srcdir.Substring(0, srcdir.Length - 1);
            string folderName = srcdir.Substring(srcdir.LastIndexOf("\\") + 1);

            string desfolderdir = desdir + "\\" + folderName;

            if (desdir.LastIndexOf("\\") == (desdir.Length - 1))
            {
                desfolderdir = desdir + "\\" + folderName;
            }
            string[] filenames = Directory.GetFileSystemEntries(srcdir);

            foreach (string file in filenames)// 遍历所有的文件和目录
            {
                if (Directory.Exists(file))// 先当作目录处理如果存在这个目录就递归Copy该目录下面的文件
                {

                    string currentdir = desfolderdir + "\\" + file.Substring(file.LastIndexOf("\\") + 1);
                    if (!Directory.Exists(currentdir))
                    {
                        Directory.CreateDirectory(currentdir);
                    }
                    CopyDirectory(file + "\\", desfolderdir);
                }

                else // 否则直接copy文件
                {
                    string srcfileName = file.Substring(file.LastIndexOf("\\") + 1);

                    srcfileName = desfolderdir + "\\"  + srcfileName;


                    if (!Directory.Exists(desfolderdir))
                    {
                        Directory.CreateDirectory(desfolderdir);
                    }
                    if (File.Exists(@srcfileName))
                        File.Delete(@srcfileName);
                    File.Copy(file, srcfileName);
                }
            }
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            string PATH = System.Environment.CurrentDirectory + "\\Plugins\\";  

        }//function end 
    }
}

