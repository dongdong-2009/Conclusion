//====================================================================
// 文件名: DrawToolProgram.cs
//
// 文件描述:
// ------------------------------------------------------------------
// DRAWTOOL功能类，  拼图功能核心代码
// ------------------------------------------------------------------
// 
// 时间: 2015.08
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
using System.ComponentModel.Design;
using System.IO;
using WeifenLuo.WinFormsUI.Docking;
using Host;
using System.Xml;
using System.Runtime.Serialization.Formatters.Binary;
using Loader;
using System.Drawing.Design;
using System.Drawing.Drawing2D;
using System.Reflection;


namespace Designer.DrawTool
{

    public class DrawToolProgram
    {
        public ToolBoxWindow        m_toolBoxWin;
        public EditWin              m_editWin;
        public PropertyWindow       m_propertyWin;
        public ModuleBoxWindow      m_moduleWin;
        public Bind                 m_bindWin;
        public List<EditWin> editWinList = new List<EditWin>();

        private int bActiveIForm = 1;

        private HostSurfaceManager  m_hostSurfaceManager    = null;
        private HostControl         hc                      = null;
        private List<HostControl>   hcList                  = new List<HostControl>();
        private XmlDocument         mXDoc                   = new XmlDocument();

        public List<boardType> btDeCoilCwList = new List<boardType>();
        public List<boardType> btDeNoCoilCwList = new List<boardType>();
        public List<boardType> btDeCoilHpList = new List<boardType>();
        public List<boardType> btDeNoCoilHpList = new List<boardType>();

        public List<boardType> btReAdjHwList = new List<boardType>();
        public List<boardType> btReNoAdjHwList = new List<boardType>();
        public List<boardType> btReAdjHpList = new List<boardType>();
        public List<boardType> btReNoAdjHpList = new List<boardType>();


        private bool     isUseGuides = false;

        private bool     bMoreComponentSelected   = false;
        private bool     bOneComponentSelected    = true;
        public  string   myProjectPath            = "";
        public  string   myProjectFullName        = "";
        public  string   MainFirstForm            = "";

        private MainForm m_mainForm;

        private List<Hook.OverallHook> hookList = new List<Hook.OverallHook>();
        private Hook.OverallHook k_hook;

        public enum ControlChangeType
        {
            ComponentChange = 1,
            FormChange = 2,
        }

        public DrawToolProgram(MainForm mf)
        {
            m_mainForm = mf;
            btDeCoilCwList = m_mainForm.btDeCoilCwList;
            btDeNoCoilCwList = m_mainForm.btDeNoCoilCwList;
            btDeCoilHpList = m_mainForm.btDeCoilHpList;
            btDeNoCoilHpList = m_mainForm.btDeNoCoilHpList;
            btReAdjHwList = m_mainForm.btReAdjHwList;
            btReNoAdjHwList = m_mainForm.btReNoAdjHwList;
            btReAdjHpList = m_mainForm.btReAdjHpList;
            btReNoAdjHpList = m_mainForm.btReNoAdjHpList;

            m_toolBoxWin = new ToolBoxWindow();
            m_propertyWin = new PropertyWindow();
            m_propertyWin.Show(mf.dockPanel1);

         
            m_bindWin = new Bind();
            m_moduleWin = new ModuleBoxWindow(mf);
            m_moduleWin.Show(mf.dockPanel1);

            try
            {
                #if DEBUG
                    mXDoc.Load("..\\..\\DrawTool\\Components.xml");
                #else
                mXDoc.Load("DrawTool\\Components.xml");
                #endif
            }
            catch
            {
                MessageBox.Show("Load component property error!");
            }

            CustomInitialize();
        }

        #region Init
        private void CustomInitialize()
        {
            m_hostSurfaceManager = new HostSurfaceManager();
            m_hostSurfaceManager.AddService(typeof(IToolboxService), this.m_toolBoxWin.ToolBox);
            m_hostSurfaceManager.AddService(typeof(PropertyWindow), this.m_propertyWin);
        }
        #endregion Init



        #region 全局hook 键盘事件
        private void InitOverallHook()
        {
            Hook.OverallHook m_hook = new Hook.OverallHook();
            hookList.Add(m_hook);
            m_hook.KeyDownEvent += new KeyEventHandler(hook_KeyDown);//钩住键按下
            m_hook.Start();//安装键盘钩子
        }
        private void hc_LostFocus(object o, EventArgs e)
        {
            foreach (Hook.OverallHook hook in hookList)
            {
                hook.Stop();
            }
        }
        private void hook_KeyDown(object sender, KeyEventArgs e)
        {
            //判断按下的键（Alt + A）
            if (e.KeyValue == (int)Keys.A && (int)Control.ModifierKeys == (int)Keys.LShiftKey)
            {
                System.Windows.Forms.MessageBox.Show("按下了指定快捷键组合");
            }

            if (e.KeyValue == (int)Keys.Up)
            {
                MoveUp();
            }
            if (e.KeyValue == (int)Keys.Down)
            {
                MoveDown();
            }
            if (e.KeyValue == (int)Keys.Left)
            {
                MoveLeft();
            }
            if (e.KeyValue == (int)Keys.Right)
            {
                MoveRight();
            }
            if (e.KeyValue == (int)Keys.Delete)
            {
                if(m_mainForm.ProgramInUse())
                    PerformAction("删除(&D)");
            }
            if (e.KeyValue == (int)Keys.A && (int)Control.ModifierKeys == (int)Keys.Control)
            {
                PerformAction("全选(&A)");
            }
            if (e.KeyValue == (int)Keys.X && (int)Control.ModifierKeys == (int)Keys.Control)
            {
                PerformAction("剪切(&X)");
            }
            if (e.KeyValue == (int)Keys.C && (int)Control.ModifierKeys == (int)Keys.Control)
            {
                PerformAction("复制(&C)");
            }
            if (e.KeyValue == (int)Keys.V && (int)Control.ModifierKeys == (int)Keys.Control)
            {
                PerformAction("粘贴(&P)");
            }
            if (e.KeyValue == (int)Keys.Z && (int)Control.ModifierKeys == (int)Keys.Control)
            {
                Undo();
            }
        }
        #endregion 全局hook 键盘事件

        #region   绘图管理  （new save open 及相关）
        public void NewOneForm(string FormName)
        {
            if (m_bindWin != null)
                m_bindWin.Dispose();
            m_bindWin = new Bind();

            m_bindWin.Show();
            /// Gets a new HostSurface and loads it with the appropriate type of
            /// root component. Uses the appropriate Loader to load the HostSurface.
            hc = m_hostSurfaceManager.GetNewHost(typeof(UserControl), CurrentMenuSelectionLoaderType);
            hcList.Add(hc);

            //DesignerHost提供设计器和对类型、服务和事务进行访问的主要接口
            this.m_toolBoxWin.ToolBox.DesignerHost = hc.DesignerHost;

            m_editWin = new EditWin();
            editWinList.Add(m_editWin);
            m_editWin.Tag = CurrentMenuSelectionLoaderType;

            hc.Parent = m_editWin;
            hc.Width = 10240;
            hc.Height = 800;
            hc.Dock = DockStyle.Fill;
            hc.Invalidate();//使控件的特定区域无效并向控件发送绘制消息
            m_editWin.Text = FormName;
            m_editWin.TabText = FormName;
            m_editWin.Show(m_mainForm.dockPanel1);

            m_hostSurfaceManager.ActiveDesignSurface = hc.HostSurface;
            m_propertyWin.propertyGrid.PropertyValueChanged += new PropertyValueChangedEventHandler(property_PropertyValueChanged);
            hc.HostSurface._selectionService.SelectionChanged += new EventHandler(_selectionService_SelectionChanged);//画面元件选择变化
            m_editWin.Activated += new EventHandler(EditWindow_Activated);
            InitOverallHook();
        }
        //新建窗口
        public void NewFormClick()
        {
            if (myProjectPath == "")
            {
                MessageBox.Show("Please create project first", "Alert", MessageBoxButtons.OK);
                return;
            }              
            int count = 1;   
            string text = "Form" + count.ToString();
            while (FindDocument(text) != null)
            {
                count++;
                text = "Form" + count.ToString();
            }
            NewOneForm(text);
        }

        private IDockContent FindDocument(string text)
        {
            foreach (EditWin Node in editWinList)
            {
                if (Node.Text == text)
                    return Node;
            }
            return null;
        }

        public void Save()
        {
            if (editWinList.Count == 0)
                return;

            if (myProjectPath == "")
            {
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

                    XmlDocument doc = new XmlDocument();
                    doc.LoadXml("<MProj></MProj>");
                    doc.Save(myProjectFullName);

                }
            }
                m_mainForm.myProjectPath = myProjectPath;
                foreach (boardType node in btDeCoilCwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }

                    foreach (boardType node in btDeNoCoilCwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btDeCoilHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btDeNoCoilHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReAdjHwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReNoAdjHwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReAdjHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReNoAdjHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }


                    foreach (EditWin node in editWinList)
                    {
                        m_editWin = node;
                        string s = myProjectPath + node.Text + ".xml";
                        HostControl currentHostControl = CurrentDocumentsHostControl;
                        ((BasicHostLoader)currentHostControl.HostSurface.Loader).Save(s);

                    }
                    if (m_editWin != null)
                        m_editWin.Show();
                    //save first start form
                    try
                    {
                        string p = myProjectPath + "first.form";

                        using (FileStream fs = new FileStream(p, FileMode.Create))
                        {
                            if (fs != null)
                            {
                                BinaryFormatter BinaryWrite = new BinaryFormatter();
                                if (MainFirstForm == "")
                                {
                                    MainFirstForm = m_editWin.Text;
                                }
                                BinaryWrite.Serialize(fs, MainFirstForm);
                                fs.Close();
                            }
                        }
                        MessageBox.Show("File saved!");
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show("Exception:" + err.ToString(), " 载入启动画面错误!");
                    }
                
      
        }

        public void saveInExit()
        {
            if (editWinList.Count == 0)
                return;

            MessageBoxButtons buttons=MessageBoxButtons.YesNoCancel;
            DialogResult result = MessageBox.Show("Do you want to save this project?", "Confirmation", buttons);

            if (result == DialogResult.Yes)
            {
                if (myProjectPath == "")
                {
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

                        XmlDocument doc = new XmlDocument();
                        doc.LoadXml("<MProj></MProj>");
                        doc.Save(myProjectFullName);

                    }
                    foreach (boardType node in btDeCoilCwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }

                    foreach (boardType node in btDeNoCoilCwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btDeCoilHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btDeNoCoilHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReAdjHwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReNoAdjHwList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReAdjHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }
                    foreach (boardType node in btReNoAdjHpList)
                    {
                        string s = myProjectPath + node.boardNumber + ".xml";
                        string s_org = AppDomain.CurrentDomain.BaseDirectory + node.boardNumber + ".xml";
                        XmlDocument file_sample = new XmlDocument();
                        file_sample.Load(s_org);
                        file_sample.Save(s);
                    }


                    foreach (EditWin node in editWinList)
                    {
                        m_editWin = node;
                        string s = myProjectPath + node.Text + ".xml";
                        HostControl currentHostControl = CurrentDocumentsHostControl;
                        ((BasicHostLoader)currentHostControl.HostSurface.Loader).Save(s);

                    }
                    if (m_editWin != null)
                        m_editWin.Show();
                    //save first start form
                    try
                    {
                        string p = myProjectPath + "first.form";

                        using (FileStream fs = new FileStream(p, FileMode.Create))
                        {
                            if (fs != null)
                            {
                                BinaryFormatter BinaryWrite = new BinaryFormatter();
                                if (MainFirstForm == "")
                                {
                                    MainFirstForm = m_editWin.Text;
                                }
                                BinaryWrite.Serialize(fs, MainFirstForm);
                                fs.Close();
                            }
                        }
                        MessageBox.Show("File saved!");
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show("Exception:" + err.ToString(), " 载入启动画面错误!");
                    }
                }
                else
                    return;
            }

            
        }
        

        public void OpenOneForm(String name)
        {
            //重新刷新

            int existed = 0;
            object objWithNname = name;

            try
            {
                // string curPath = AppDomain.CurrentDomain.BaseDirectory + "configdoc.xml";//获取基目录，它由程序集冲突解决程序用来探测程序集。 
                string fileName = myProjectPath + name + ".xml";
                //加入判断代码，如果没有xml文件，退出
                if (!File.Exists(fileName))
                    return;

                hc = m_hostSurfaceManager.GetNewHost(fileName);
                this.m_toolBoxWin.ToolBox.DesignerHost = hc.DesignerHost;
                hcList.Add(hc);
                //m_editWin = new EditWin();
   
                for (int i = 0; i < editWinList.Count; i++)
                {
                    if (editWinList[i].Text == name)
                    {
                        editWinList[i].Show();
                        return;
                    }
                }



                if (editWinList.Any(p => p.Text == name) == false)
                {
                    m_editWin = new EditWin();
                    editWinList.Add(m_editWin);
                    m_editWin.Tag = CurrentMenuSelectionLoaderType;
                    hc.Parent = m_editWin;
                    hc.Width = 1024;
                    hc.Height = 768;
                    hc.Dock = DockStyle.Fill;
                    hc.Refresh();
                    //m_editWin.LostFocus += new EventHandler(hc_LostFocus);
                    m_editWin.Text = name;
                    m_editWin.TabText = name;
                    m_editWin.Show(m_mainForm.dockPanel1);

                    m_hostSurfaceManager.ActiveDesignSurface = hc.HostSurface;
                    //add every form select actionwindow and eventwindow!!
                    hc.HostSurface._selectionService.SelectionChanged += new EventHandler(_selectionService_SelectionChanged);
                    m_editWin.Activated += new EventHandler(EditWindow_Activated);
                    //选择第一个当前的form  
                    XmlNode tmpXNode = mXDoc.SelectSingleNode("Components/Component[@Name=\"UserControl\"]");
                    XmlNodeList tmpXPropLst = tmpXNode.SelectNodes("Propertys/Property");
                    CustomProperty comps = new CustomProperty(hc.HostSurface.ComponentContainer.Components[0], tmpXPropLst);
                    m_propertyWin.propertyGrid.SelectedObject = comps;// hc.HostSurface.ComponentContainer.Components[0];
                    m_propertyWin.Invalidate();
                    m_propertyWin.propertyGrid.PropertyValueChanged += new PropertyValueChangedEventHandler(property_PropertyValueChanged);
                    //this.OutputWindow.RichTextBox.Text += "Opened new host.\n";

                    InitOverallHook();
                }
                   
               
              
            }
            catch
            {
                MessageBox.Show("创建画面实例错误", "APMC Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public string CreateFormName(string name)
        {
            if (name.Contains("GraphicsEdition"))
            {
                int count = 1;
                string text = "Form" + count.ToString();
                while (FindDocument(text) != null)
                {
                    count++;
                    text = "Form" + count.ToString();
                }
                return text;
            }
            return "error";
        }

        //public void LoadUserForm()
        //{
        //    OpenFileDialog openFileDialog1 = new OpenFileDialog();
        //    openFileDialog1.Filter = "APMC Files (*.xml)|*.xml";
        //    openFileDialog1.InitialDirectory = "";
        //    openFileDialog1.Title = "打开画面文件";
        //    openFileDialog1.FileName = "";
        //    if (openFileDialog1.ShowDialog() == DialogResult.OK)
        //    {
        //        string projectpath = openFileDialog1.FileName;
        //        string name = new FileInfo(projectpath).Name;
        //        if (name.Contains(".xml"))
        //        {
        //            name = name.Substring(0, name.Length - 4);
        //        }
        //        foreach (TreeNode tree in m_soluWindow.solutionwindow.SelectedNode.Nodes)
        //        {
        //            if (tree.Text == name)
        //            {
        //                MessageBox.Show("Already exist in project.", "System Alert", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        //                return;
        //            }
        //        }
        //        try
        //        {
        //            string fileName = projectpath;
        //            hc = m_hostSurfaceManager.GetNewHost(fileName);
        //            //this.m_toolWindow.ToolBox.DesignerHost = hc.DesignerHost;
        //            hcList.Add(hc);
        //            m_editWin = new EditWin() ;
        //            editWinList.Add(m_editWin);
        //            m_editWin.Tag = CurrentMenuSelectionLoaderType;
        //            hc.Parent = m_editWin;
        //            hc.Width = 1024;
        //            hc.Height = 768;
        //            hc.Dock = DockStyle.Fill;
        //            hc.Refresh();

        //            m_editWin.Text = name;
        //            m_editWin.TabText = name;
        //            m_editWin.Show(m_mainForm.dockPanel1);
        //            m_hostSurfaceManager.ActiveDesignSurface = hc.HostSurface;
        //            //add every form select actionwindow and eventwindow!!
        //            hc.HostSurface._selectionService.SelectionChanged += new EventHandler(_selectionService_SelectionChanged);
        //            m_editWin.Activated += new EventHandler(EditWindow_Activated);
        //            //选择第一个当前的form  
        //            XmlNode tmpXNode = mXDoc.SelectSingleNode("Components/Component[@Name=\"UserControl\"]");
        //            XmlNodeList tmpXPropLst = tmpXNode.SelectNodes("Propertys/Property");
        //            CustomProperty comps = new CustomProperty(hc.HostSurface.ComponentContainer.Components[0], tmpXPropLst);
        //            m_propertyWin.propertyGrid.SelectedObject = comps;// hc.HostSurface.ComponentContainer.Components[0];
        //            m_propertyWin.Invalidate();
        //            //向工程树中添加节点名
        //            TreeNode tn = new TreeNode(name);
        //            tn.ImageIndex = 2;
        //            tn.SelectedImageIndex = 3;

        //        }
        //        catch
        //        {
        //            MessageBox.Show("载入画面实例错误", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        //        }
        //    }
        //}
        //工具栏设置启动画面主页
        public void HomePage_Click()
        {
            if (editWinList.Count > 0)
            {
                List<string> list = new List<string>();
                foreach (EditWin ef in editWinList)
                {
                    list.Add(ef.Text);
                }
                SetupForm f = new SetupForm();
                f.SetFormList(list);
                f.FirstForm = MainFirstForm;
                if (f.ShowDialog() == DialogResult.OK)
                {
                    MainFirstForm = f.FirstForm;
                }
            }
        }
        #endregion 绘图管理  （new save open 及相关）

        #region        事件响应 （图元选择变化 form选择变化等）
        //得到当前hostcontrol
        private HostControl CurrentDocumentsHostControl
        {
            get
            {
                if (m_editWin != null)
                {
                    return (HostControl)m_editWin.Controls[0];
                }
                else
                {
                    return null;
                }
            }
        }
        void _selectionService_SelectionChanged(object sender, EventArgs e)
        {
            ControlChangeShow((int)ControlChangeType.ComponentChange);
        }
        void EditWindow_Activated(object sender, EventArgs e)
        {
            EditWin edw = (EditWin)sender;
            foreach (EditWin win in editWinList)
            {
                if (edw.Text.Equals(win.Text))
                {
                    m_editWin = win;
                    hc = (HostControl)m_editWin.Controls[0];
                    ControlChangeShow((int)ControlChangeType.FormChange);
                    bActiveIForm = 1;
                    break;
                }
            }
        }
        //属性视图值变化时事件处理
        private void property_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            //if (e.ChangedItem.Label.ToString() == "FormName")
            //{
            //    foreach (EditWin form in editWinList)
            //    {
            //        if (form.Text.Equals(m_soluWindow.solutionwindow.SelectedNode.Text))
            //        {
            //            string sf = myProjectPath + form.Text + ".xml";
            //            FileInfo file = new FileInfo(@sf);
            //            if (file.Exists)
            //            {
            //                file.Delete();//删除原来的画面文件
            //            }
            //            form.Text = e.ChangedItem.Value.ToString();
            //            form.TabText = e.ChangedItem.Value.ToString();
            //            form.Tag = e.ChangedItem.Value.ToString();
            //        //    m_soluWindow.solutionwindow.SelectedNode.Text = form.Text;
            //            Save();
            //            break;
            //        }
            //    }
            // }

            if (hc.HostSurface._selectionService != null)
            {
                ICollection selectedComponents = hc.HostSurface._selectionService.GetSelectedComponents();
                int count = selectedComponents.Count;
                if (count != 1)
                    return;
                int i = 0;
                object[] comps = new object[count];
                foreach (object o in selectedComponents)
                {
                    comps[i] = o;
                    i++;
                }
             //   int aa = 0;
                Type t = comps[0].GetType();
                string Boardcode="";
                if (t.Name.Equals("TextBox"))
                {  
                    Library.TextBox tb = (Library.TextBox)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                  
                    string RelatedPort = "";
                    string RelatedDeviceType ="";

                    dataPT.GetBoardPortByNameBdnum(tb.DeviceName, tb.BoardNumber,ref RelatedPort, ref RelatedDeviceType,ref Boardcode);

                    PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                    PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                  
                    m_DeviceType.SetValue(tb, RelatedDeviceType, null);
                    m_RelatedPort.SetValue(tb, RelatedPort, null);
                }
                if (t.Name.Equals("levelmeter"))
                {
                    Library.Common.levelmeter tb = (Library.Common.levelmeter)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string RelatedPort = "";
                    string RelatedDeviceType = "";

                    dataPT.GetBoardPortByNameBdnum(tb.DeviceName, tb.BoardNumber, ref RelatedPort, ref RelatedDeviceType,ref Boardcode);

                    PropertyInfo m_DeviceType = t.GetProperty("RelatedDeviceType");
                    PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");

                    m_DeviceType.SetValue(tb, RelatedDeviceType, null);
                    m_RelatedPort.SetValue(tb, RelatedPort, null);
                }
               
                if (t.Name.Equals("statusIndicator"))
                {
                    Library.statusIndicator tb = (Library.statusIndicator)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                    string BoardNumber = "";
                    string RelatedPort = "";
                    string PortData = "";
                    string PortBind = "";
                    dataPT.GetBoardSendPortByPointID(dataPT.GetPointID(tb.RelatedDeviceType, tb.ID), ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                    //需要改掉
                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                    PropertyInfo m_PortData = t.GetProperty("PortData");
                    PropertyInfo m_PortBind = t.GetProperty("PortBind");

                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    m_RelatedPort.SetValue(tb, RelatedPort, null);
                    m_PortData.SetValue(tb, PortData, null);
                    m_PortBind.SetValue(tb, PortBind, null);
                }
                if (t.Name.Equals("Led"))
                {
                    Library.Led tb = (Library.Led)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                    string BoardNumber = "";
                    string RelatedPort = "";
                    string PortData = "";
                    string PortBind = "";
              //      dataPT.GetBoardSendPortByPointID(dataPT.GetPointID(tb.RelatedDeviceType, tb.ID), ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                    //需要改掉
                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                    PropertyInfo m_PortData = t.GetProperty("PortData");
                    PropertyInfo m_PortBind = t.GetProperty("PortBind");

                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    m_RelatedPort.SetValue(tb, RelatedPort, null);
                    m_PortData.SetValue(tb, PortData, null);
                    m_PortBind.SetValue(tb, PortBind, null);
                }
                if (t.Name.Equals("SendButton"))
                {
                    Library.SendButton tb = (Library.SendButton)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                    string BoardNumber = "";
                    string RelatedPort = "";
                    string PortData = "";
                    string PortBind = "";
                    dataPT.GetBoardSendPortByPointID(dataPT.GetPointID(tb.RelatedDeviceType, tb.ID), ref BoardNumber, ref RelatedPort, ref PortData, ref PortBind);
                    //需要改掉
                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                    PropertyInfo m_PortData = t.GetProperty("PortData");
                    PropertyInfo m_PortBind = t.GetProperty("PortBind");
                    
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    m_RelatedPort.SetValue(tb, RelatedPort, null);
                    m_PortData.SetValue(tb, PortData, null);
                    m_PortBind.SetValue(tb, PortBind, null);
                }
                if (t.Name.Equals("Alarm"))
                {
                    Library.Common.Alarm tb = (Library.Common.Alarm)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                    string BoardNumber = "";
                    string RelatedPort = "";
                    //string UpLimit = "";
                    //string DownLimit = "";
                    dataPT.GetBoardPortByPointID(dataPT.GetPointID(tb.RelatedDeviceType, tb.ID), ref BoardNumber, ref RelatedPort);
                    
                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    PropertyInfo m_RelatedPort = t.GetProperty("RelatedPort");
                    PropertyInfo m_UpLimit = t.GetProperty("UpLimit");
                    PropertyInfo m_DownLimit = t.GetProperty("DownLimit");

                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    m_RelatedPort.SetValue(tb, RelatedPort, null);
                    //m_UpLimit.SetValue(tb, UpLimit, null);
                    //m_DownLimit.SetValue(tb, DownLimit, null);
                }
                if (t.Name.Equals("OnOff"))
                {
                    Library.Common.CommunicationOnOff tb = (Library.Common.CommunicationOnOff)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();
                    string BoardNumber = "";
                    dataPT.GetBoardSendByPointID(dataPT.GetPointID(tb.RelatedDeviceType, tb.ID), ref BoardNumber);
                    
                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                }
                if (t.Name.Equals("Dehumidifier1"))
                {
                    Library.LDDS.Dehumidifier1 tb = (Library.LDDS.Dehumidifier1)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int  a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                      PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                      m_BoardNumber.SetValue(tb, BoardNumber, null);
                      a = tb.Controls.Count;
                      foreach (object o in tb.Controls)
                      {
                          Type compldds = o.GetType();
                          if (compldds.Name.Equals("TextBox"))
                          {
                              Library.TextBox otextbox = (Library.TextBox)o;
                              otextbox.BoardNumber = BoardNumber;
                              PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                              m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                          }

                      }
                }
                if (t.Name.Equals("Dehumidifier3"))
                {
                    Library.LDDS.Dehumidifier3 tb = (Library.LDDS.Dehumidifier3)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }
                if (t.Name.Equals("Dehumidifier4"))
                {
                    Library.LDDS.Dehumidifier4 tb = (Library.LDDS.Dehumidifier4)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }
                if (t.Name.Equals("Dehumidifier2"))
                {
                    Library.LDDS.Dehumidifier2 tb = (Library.LDDS.Dehumidifier2)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    //int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    //a = tb.Controls.Count;
                    //foreach (object o in tb.Controls)
                    //{
                    //    Type compldds = o.GetType();
                    //    if (compldds.Name.Equals("TextBox"))
                    //    {
                    //        Library.TextBox otextbox = (Library.TextBox)o;
                    //        otextbox.BoardNumber = BoardNumber;
                    //        PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                    //        m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                    //    }

                    //}
                }
                if (t.Name.Equals("Regenerator1"))
                {
                    Library.LDDS.Regenerator1 tb = (Library.LDDS.Regenerator1)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }
                if (t.Name.Equals("Regenerator3"))
                {
                    Library.LDDS.Regenerator3 tb = (Library.LDDS.Regenerator3)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }
                if (t.Name.Equals("Regenerator4"))
                {
                    Library.LDDS.Regenerator4 tb = (Library.LDDS.Regenerator4)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }
                if (t.Name.Equals("Regenerator2"))
                {
                    Library.LDDS.Regenerator2 tb = (Library.LDDS.Regenerator2)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }
                if (t.Name.Equals("Tank"))
                {
                    Library.LDDS.Tank tb = (Library.LDDS.Tank)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }

                if (t.Name.Equals("Heatpump"))
                {
                    Library.LDDS.Heatpump tb = (Library.LDDS.Heatpump)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }

                if (t.Name.Equals("HotWaterHeater"))
                {
                    Library.LDDS.HotWaterHeater tb = (Library.LDDS.HotWaterHeater)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }
                if (t.Name.Equals("HeatExchangers"))
                {
                    Library.LDDS.HeatExchangers tb = (Library.LDDS.HeatExchangers)comps[0];
                    DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                    string BoardNumber = "";
                    string RelatedDeviceType = "";
                    int a = 0;
                    dataPT.GetBoardinfoByName(tb.DeviceName, ref BoardNumber, ref  RelatedDeviceType);

                    PropertyInfo m_BoardNumber = t.GetProperty("BoardNumber");
                    m_BoardNumber.SetValue(tb, BoardNumber, null);
                    a = tb.Controls.Count;
                    foreach (object o in tb.Controls)
                    {
                        Type compldds = o.GetType();
                        if (compldds.Name.Equals("TextBox"))
                        {
                            Library.TextBox otextbox = (Library.TextBox)o;
                            otextbox.BoardNumber = BoardNumber;
                            PropertyInfo m_comBoardNumber = compldds.GetProperty("BoardNumber");
                            m_comBoardNumber.SetValue(otextbox, BoardNumber, null);

                        }

                    }
                }

            }
        }
        /*===================================================================
        * 功能描述: type:1 画面元件选择发生变化
         *         type:2 editWindow选择发生变化
        ===================================================================*/
        private void ControlChangeShow(int type)
        {
            if (hc.HostSurface._selectionService == null)
                return;
            ICollection selectedComponents;
            PropertyGrid propertyGrid = (PropertyGrid)hc.HostSurface.GetService(typeof(PropertyGrid));
            object[] selectedcomps = null;
            object[] comps = null;
            int selectedCompCount = 0;
            if (type == 1)
            {
                selectedComponents = hc.HostSurface._selectionService.GetSelectedComponents();
                selectedCompCount = selectedComponents.Count;
                if (selectedCompCount == 1)
                {
                    bOneComponentSelected = true;
                    bMoreComponentSelected = false;
                }
                else if (selectedCompCount > 1)
                {
                    bOneComponentSelected = false;
                    bMoreComponentSelected = true;
                }

                comps = new object[selectedCompCount];//?
                selectedcomps = new object[selectedCompCount];

                int j = 0;
                foreach (object o in selectedComponents)
                {
                    selectedcomps[j] = o;
                    j++;
                }
            }
            else if (type == 2)
            {
                selectedCompCount = 1;
                comps = new object[selectedCompCount];
                selectedcomps = new object[selectedCompCount];
                selectedcomps[0] = hc.HostSurface._selectionService.PrimarySelection;
            }

            int ComponentIndex = 0;
            for (int m = 0; m < selectedCompCount; m++)
            {
                object o = selectedcomps[m];
                Type t = o.GetType();
                string nodeString = null;

                nodeString = "Components/Component[@Name=\"" + t.Name + "\"]";//Components/Component[@Name=\"UserControl\
                XmlNode tmpXNode = mXDoc.SelectSingleNode(nodeString);
                if (tmpXNode == null)
                {
                    nodeString = "Components/AddedComponent[@Name=\"" + t.Name + "\"]";//Components/Component[@Name=\"UserControl\
                    tmpXNode = mXDoc.SelectSingleNode(nodeString);
                }
                try
                {
                    XmlNodeList tmpXPropLst = tmpXNode.SelectNodes("Propertys/Property");
                    comps[ComponentIndex] = new CustomProperty(o, tmpXPropLst);
                    m_propertyWin.propertyGrid.SelectedObject = comps[ComponentIndex];// hc.HostSurface.ComponentContainer.Components[0];
                    ComponentIndex++;
                }
                catch
                {

                }

                if (t.Name.Equals("TextBox"))
                {
                    Library.TextBox tb = (Library.TextBox)selectedcomps[m];
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentBindName = tb.DeviceName;
                    m_bindWin.currentID = tb.ID;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType!= null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
           
                else if (t.Name.Equals("SendButton"))
                {
                    Library.SendButton tb = (Library.SendButton)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentBindName = tb.DeviceName;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("ButtonCheck"))
                {
                    Library.Common.ButtonCheck tb = (Library.Common.ButtonCheck)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentBindName = tb.DeviceName;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("ButtonCheckFun"))
                {
                    Library.Common.ButtonCheck tb = (Library.Common.ButtonCheck)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentBindName = tb.DeviceName;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("CommunicationOnOff"))
                {
                    Library.Common.CommunicationOnOff tb = (Library.Common.CommunicationOnOff)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentID = tb.ID;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("RunState"))
                {
                    Library.Common.RunState tb = (Library.Common.RunState)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("Alarm"))
                {
                    Library.Common.Alarm tb = (Library.Common.Alarm)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("Dehumidifier1"))
                {
                    Library.LDDS.Dehumidifier1 tb = (Library.LDDS.Dehumidifier1)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("levelmeter"))
                {
                    Library.Common.levelmeter tb = (Library.Common.levelmeter)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("Regenerator1"))
                {
                    Library.LDDS.Regenerator1 tb = (Library.LDDS.Regenerator1)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("statusIndicator"))
                {
                    Library.statusIndicator tb = (Library.statusIndicator)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else if (t.Name.Equals("Led"))
                {
                    Library.Led tb = (Library.Led)o;
                    m_bindWin.currentObj = o;
                    m_bindWin.couldBeBind = true;
                    m_bindWin.currentType = tb.RelatedDeviceType;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                    if (tb.RelatedDeviceType != null)
                        m_bindWin.TypeComboBox.SelectedValue = tb.RelatedDeviceType;
                }
                else
                {
                    m_bindWin.couldBeBind = false;
                    m_bindWin.TypeComboBox.SelectedIndex = -1;
                }
            }

            if (comps != null || comps[0] != null)
            {
                //propertyGrid.SelectedObjects = comps;
            }
        }

        //事件视图窗口鼠标响应
        private object CustomEventItem_OnClick(object sender, EventArgs e)
        {
            return null;
        }
        private LoaderType CurrentMenuSelectionLoaderType
        {
            get
            {
                return LoaderType.BasicDesignerLoader;
            }
        }

        public object getCurrentSelectedObj()
        {
            if (hc == null)
                return null;
            object o = hc.HostSurface._selectionService.PrimarySelection;
            return o;
        }

        private object[] getSelectedComponents()
        {
            if (hc == null)
                return null;
            ICollection selectedComponents = hc.HostSurface._selectionService.GetSelectedComponents();
            int c = selectedComponents.Count;
            int i = 0;
            object[] comps = new object[c];
            foreach (object o in selectedComponents)
            {
                comps[i] = o;
                i++;
            }
            return comps;
        }

        //查找或者创建画面
        public bool LookOrCreateForm(string sFormname)
        {
            bool bfind = false;
            foreach (EditWin Node in editWinList)
            {
                if (Node.Text.Equals(sFormname))
                {
                    m_editWin = Node;
                    m_editWin.Show();
                    bfind = true;
                    break;
                }
            }
            if (!bfind)
            {
                NewOneForm(sFormname);
                return false;
            }
            return true;
        }
        //画面右键删除菜单
        //public void FormDelMenu()
        //{
        //    if (m_soluWindow.solutionwindow.SelectedNode.Parent != null)
        //    {
        //        string formname = m_soluWindow.solutionwindow.SelectedNode.Text;
        //        if (m_soluWindow.solutionwindow.SelectedNode.Parent.Text == "GraphicsEdition")
        //        {
        //            if (formname != "")
        //            {
        //                if (DialogResult.No == MessageBox.Show("Are you sure to delete the form？",
        //              "Alert", MessageBoxButtons.YesNo))
        //                {
        //                    return;
        //                }
        //                //删除画面
        //                DeleteForm(formname);
        //                //delete tree
        //                m_soluWindow.solutionwindow.SelectedNode.Remove();
        //            }
        //        }
        //    }
        //}

        private bool DeleteForm(string name)
        {
            bool bfind = false;
            foreach (EditWin Node in editWinList)
            {
                if (Node.Text.Equals(name))
                {
                    m_editWin = Node;
                    m_editWin.Close();
                    editWinList.Remove(Node);//clear list
                    //delete the file form project
                    string s = myProjectPath + name + ".xml";
                    FileInfo file = new FileInfo(@s);
                    if (file.Exists)
                    {
                        bfind = true;
                        file.Delete(); //删除                       
                    }
                    break;
                }
            }
            if (!bfind)
            {
                //MessageBox.Show("没有发现该画面!");
                return false;
            }
            return true;
        }
        #endregion 事件响应 （图元选择变化 form选择变化等）

        #region 添加图片图元

        public void InserPic(string name)
        {
            if (hc == null)
            {
                return;
            }
            if (hc.HostSurface._selectionService != null)
            {
                ICollection selectedComponents;
                PropertyGrid propertyGrid = (PropertyGrid)hc.HostSurface.GetService(typeof(PropertyGrid));
                object[] selectedcomp = null;
                object[] comps = null;
                int n = 0, i = 0;
                selectedComponents = hc.HostSurface._selectionService.GetSelectedComponents();
                n = selectedComponents.Count;
                if (n != 1)
                {
                    return;
                }
                selectedcomp = new object[n];
                comps = new object[n];
                foreach (object o in selectedComponents)
                {
                    selectedcomp[i] = o;
                    i++;
                }
                for (int m = 0; m < n; m++)
                {
                    object o = selectedcomp[m];
                    Type t = o.GetType();
                    if (t.Name.Equals("Button"))
                    {
                        Library.Button button = (Library.Button)o;
                        button.Image = Image.FromFile(name);
                    }
                    else if (t.Name.Equals("PictureBox"))
                    {
                        Library.PictureBox picBox = (Library.PictureBox)o;
                        picBox.Image = Image.FromFile(name);
                        picBox.SizeMode = PictureBoxSizeMode.StretchImage;
                    }
                    else
                    {
                        comps[0] = null;
                    }
                }
                if (comps[0] != null)
                {
                    propertyGrid.SelectedObjects = comps;
                }

            }
        }

        public void addPicBox(Library.PictureBox pb, Size s)
        {
            if (hc == null)
                return;
            IDesignerHost idh = hc.DesignerHost;
            Library.PictureBox b = (Library.PictureBox)idh.CreateComponent(typeof(Library.PictureBox));
            b.Size = s;
            b.BorderStyle = 0;
            b.SizeMode = PictureBoxSizeMode.StretchImage;
            b.BorderStyle = BorderStyle.None;
            b.BackColor = Color.Transparent;
            b.Image = pb.Image;
            // Set the Parent of this Button to the RootComponent (the Form)
            b.Parent = (UserControl)idh.RootComponent;
            // Use ComponentChangeService to announce changing of the 
            // Form's Controls collection */
            //IComponentChangeService icc = (IComponentChangeService) idh.GetService(typeof(IComponentChangeService));
            //icc.OnComponentChanging(idh.RootComponent, TypeDescriptor.GetProperties(idh.RootComponent)["Controls"]); 
        }
        #endregion

        #region 工具栏方法

        //执行编辑菜单命令函数
        public void PerformAction(string text)
        {
            if (this.CurrentDocumentsHostControl == null)
            {
                MessageBox.Show("当前画面实例为空!");
                return;
            }
            IMenuCommandService ims = this.CurrentDocumentsHostControl.HostSurface.GetService(typeof(IMenuCommandService)) as IMenuCommandService;
            try
            {
                switch (text)
                {
                    case "剪切(&X)":
                        ims.GlobalInvoke(StandardCommands.Cut);
                        break;
                    case "复制(&C)":
                        ims.GlobalInvoke(StandardCommands.Copy);
                        break;
                    case "粘贴(&P)":
                        ims.GlobalInvoke(StandardCommands.Paste);
                        break;
                    case "删除(&D)":
                        ims.GlobalInvoke(StandardCommands.Delete);
                        break;
                    case "全选(&A)":
                        ims.GlobalInvoke(StandardCommands.SelectAll);
                        break;
                    case "左对齐(&L)":
                        ims.GlobalInvoke(StandardCommands.AlignLeft);
                        break;
                    case "居中对齐(&C)":
                        ims.GlobalInvoke(StandardCommands.AlignHorizontalCenters);
                        break;
                    case "右对齐(&R)":
                        ims.GlobalInvoke(StandardCommands.AlignRight);
                        break;
                    case "顶端对齐(&S)":
                        ims.GlobalInvoke(StandardCommands.AlignTop);
                        break;
                    case "中间对齐(&M)":
                        ims.GlobalInvoke(StandardCommands.AlignVerticalCenters);
                        break;
                    case "底部对齐(&B)":
                        ims.GlobalInvoke(StandardCommands.AlignBottom);
                        break;
                    case "置于顶层(&B)":
                        ims.GlobalInvoke(StandardCommands.BringToFront);
                        break;
                    case "置于底层(&S)":
                        ims.GlobalInvoke(StandardCommands.SendToBack);
                        break;
                    case "前移一层(&U)":
                        bool b = ims.GlobalInvoke(StandardCommands.BringToFront);
                        break;
                    case "后移一层(&D)":
                        bool c = ims.GlobalInvoke(StandardCommands.SendToBack);
                        break;
                    default:
                        break;
                }
            }
            catch
            {
                //this.OutputWindow.RichTextBox.Text += "Error in performing the action: " + text.Replace("&", "");
            }
        }

        public void Undo()
        {
            if (this.CurrentDocumentsHostControl == null)
            {
                MessageBox.Show("当前画面实例为空!");
                return;
            }
            UndoEngineExt ims = this.CurrentDocumentsHostControl.HostSurface.GetService(typeof(UndoEngine)) as UndoEngineExt;
            ims.Undo();
        }

        public void Redo()
        {
            if (this.CurrentDocumentsHostControl == null)
            {
                MessageBox.Show("当前画面实例为空!");
                return;
            }
            UndoEngineExt ims = this.CurrentDocumentsHostControl.HostSurface.GetService(typeof(UndoEngine)) as UndoEngineExt;
            ims.Redo();
        }

        //新增组件后更新此处代码
        private void ComponentMove(object o, string direction)
        {
            Type a = o.GetType();
            if (a.Name.Equals("PictureBox"))
            {
                Library.PictureBox n = (Library.PictureBox)o;
                switch (direction)
                {
                    case "Left":
                        n.Left -= 1;
                        break;
                    case "Right":
                        n.Left += 1;
                        break;
                    case "Up":
                        n.Top -= 1;
                        break;
                    case "Down":
                        n.Top += 1;
                        break;
                }
            }
            else if(a.Name.Equals("TextBox"))
            {
                TextBox comp = new TextBox();
                try
                {
                    comp = (TextBox)o;
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                switch (direction)
                {
                    case "Left":
                        comp.Left -= 1;
                        break;
                    case "Right":
                        comp.Left += 1;
                        break;
                    case "Up":
                        comp.Top -= 1;
                        break;
                    case "Down":
                        comp.Top += 1;
                        break;
                }
            }
            else if (a.Name.Equals("SendButton"))
            {
                Library.SendButton comp = new Library.SendButton();
                try
                {
                    comp = (Library.SendButton)o;
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                switch (direction)
                {
                    case "Left":
                        comp.Left -= 1;
                        break;
                    case "Right":
                        comp.Left += 1;
                        break;
                    case "Up":
                        comp.Top -= 1;
                        break;
                    case "Down":
                        comp.Top += 1;
                        break;
                }
            }
            else if (a.Name.Equals("statusIndicator"))
            {
                Library.statusIndicator comp = new Library.statusIndicator();
                try
                {
                    comp = (Library.statusIndicator)o;
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                switch (direction)
                {
                    case "Left":
                        comp.Left -= 1;
                        break;
                    case "Right":
                        comp.Left += 1;
                        break;
                    case "Up":
                        comp.Top -= 1;
                        break;
                    case "Down":
                        comp.Top += 1;
                        break;
                }
            }
            else if (a.Name.Equals("Label"))
            {
                Label comp = new Label();
                try
                {
                    comp = (Label)o;
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                switch (direction)
                {
                    case "Left":
                        comp.Left -= 1;
                        break;
                    case "Right":
                        comp.Left += 1;
                        break;
                    case "Up":
                        comp.Top -= 1;
                        break;
                    case "Down":
                        comp.Top += 1;
                        break;
                }
            }
            else if (a.Name.Equals("ButtonCheck"))
            {
                Library.Common.ButtonCheck comp = new Library.Common.ButtonCheck();
                try
                {
                    comp = (Library.Common.ButtonCheck)o;
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                switch (direction)
                {
                    case "Left":
                        comp.Left -= 1;
                        break;
                    case "Right":
                        comp.Left += 1;
                        break;
                    case "Up":
                        comp.Top -= 1;
                        break;
                    case "Down":
                        comp.Top += 1;
                        break;
                }
            }
            else if (a.Name.Equals("RunState"))
            {
                Library.Common.RunState comp = new Library.Common.RunState();
                try
                {
                    comp = (Library.Common.RunState)o;
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                switch (direction)
                {
                    case "Left":
                        comp.Left -= 1;
                        break;
                    case "Right":
                        comp.Left += 1;
                        break;
                    case "Up":
                        comp.Top -= 1;
                        break;
                    case "Down":
                        comp.Top += 1;
                        break;
                }
            }
        }

        //控件按像素移动方法 需改写扩充
        public void MoveLeft()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            ComponentMove(comps[0], "Left");
        }

        public void MoveDown()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            ComponentMove(comps[0], "Down");
        }

        public void MoveUp()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            ComponentMove(comps[0], "Up");
        }

        public void MoveRight()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            ComponentMove(comps[0], "Right");
        }

        public void Arrange()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            //ComponentMove(comps[0], "Right");
        }

        public void ShowGrid()
        {
            //if (isUseGuides == true)
            {
                foreach (HostControl m_hc in hcList)
                {
                    m_hc.HostSurface.UseNoGuides();
                }
                isUseGuides = false;
            }
//             else if (isUseGuides == false)
//             {
//                 foreach (HostControl m_hc in hcList)
//                 {
//                     m_hc.HostSurface.UseSnapLines();
//                 }
//                 isUseGuides = true;
//             }
            
        }
        #endregion 工具栏方法

        #region 组件旋转代码 新增组件后需要更新此处代码
        public void RotateLeft()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            foreach (object o in comps)
            {
                Type a = o.GetType();
                if (a.Name.Equals("PictureBox"))
                {
                    Library.PictureBox n = (Library.PictureBox)o;
                    n.Image.RotateFlip(RotateFlipType.Rotate270FlipXY);
                    n.Refresh();
                }
                else if (a.Name.Equals("Lable"))
                {
                    //Library.Lable n = (Library.Lable)o;
                    //n.RotateFlip(RotateFlipType.Rotate270FlipXY);
                    //n.Refresh();
                }
                else
                {
                    UserControl comp = new UserControl();
                    try
                    {
                        comp = (UserControl)comps[0];
                    }
                    catch (Exception ex)
                    {
                        ex.ToString();
                    }
                    if (comp.BackgroundImage == null)
                        return;
                    comp.BackgroundImage.RotateFlip(RotateFlipType.Rotate270FlipXY);
                    comp.Refresh();
                }
            }
        }

        public void RotateRight()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            Type a = comps[0].GetType();
            if (a.Name.Equals("PictureBox"))
            {
                Library.PictureBox n = (Library.PictureBox)comps[0];
                n.Image.RotateFlip(RotateFlipType.Rotate90FlipXY);
                //n.Image = RotateImage(n.Image, 20);
                n.Refresh();
            }
            // else if (a.Name.Equals("dehumidifier1"))
            //            else if (a.Name.Equals("Wall_Co2_Sensor_01"))
            //            {
            //                 Library.Chillers.Wall_Co2_Sensor_01 n = (Library.Chillers.Wall_Co2_Sensor_01)comps[0];
            //                 n.BackgroundImage.RotateFlip(RotateFlipType.Rotate90FlipXY);
            //                 n.Refresh();                
            //            }
            else
            {
                UserControl comp = new UserControl();
                try
                {
                    comp = (UserControl)comps[0];
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                if (comp.BackgroundImage == null)
                    return;
                comp.BackgroundImage.RotateFlip(RotateFlipType.Rotate90FlipXY);
                comp.Refresh();
            }
        }
        public static Image RotateImage(Image img, float a)
        {
            Bitmap b = new Bitmap(img.Width, img.Height);
            Graphics g = Graphics.FromImage(b);
            g.TranslateTransform((float)b.Width / 2, (float)b.Height / 2);
            g.RotateTransform(a);
            g.TranslateTransform(-(float)b.Width / 2, -(float)b.Height / 2);
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;
            g.DrawImage(img, new Point(0, 0));
            g.Dispose();
            return b;
        }

        public void MirrorUpDown()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            Type a = comps[0].GetType();
            if (a.Name.Equals("PictureBox"))
            {
                Library.PictureBox n = (Library.PictureBox)comps[0];
                n.Image.RotateFlip(RotateFlipType.RotateNoneFlipY);
                n.Refresh();
            }
            else
            {
                UserControl comp = new UserControl();
                try
                {
                    comp = (UserControl)comps[0];
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                if (comp.BackgroundImage == null)
                    return;
                comp.BackgroundImage.RotateFlip(RotateFlipType.RotateNoneFlipY);
                comp.Refresh();
            }
        }
        public void MirrorLR()
        {
            object[] comps = getSelectedComponents();
            if (comps == null)
                return;
            Type a = comps[0].GetType();
            if (a.Name.Equals("PictureBox"))
            {
                Library.PictureBox n = (Library.PictureBox)comps[0];
                n.Image.RotateFlip(RotateFlipType.RotateNoneFlipX);
                n.Refresh();
            }
            else
            {
                UserControl comp = new UserControl();
                try
                {
                    comp = (UserControl)comps[0];
                }
                catch (Exception ex)
                {
                    ex.ToString();
                }
                if (comp.BackgroundImage == null)
                    return;
                comp.BackgroundImage.RotateFlip(RotateFlipType.RotateNoneFlipX);
                comp.Refresh();
            }
        }
        #endregion 旋转

        #region 模块显示隐藏方法
        public void HideModule()
        {
            m_propertyWin.Hide();

        }
        public void ShowModule()
        {
            m_propertyWin.Show();

        }
        #endregion 
    }
}
