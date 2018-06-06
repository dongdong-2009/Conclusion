//运行时管理 xuehaoyuan
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Host;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;     // io
using System.Runtime.Serialization.Formatters.Binary; // io
using System.Threading;
using System.Reflection;
using System.Collections;
using System.Xml;

namespace Designer.RunTime
{
    public partial class RunTimeFormMng : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public string myProjectPath = "";
        private string myProjectFullName = "";
        private HostSurfaceManager _hostSurfaceManager = null;
        private RunTimeForm m_RTeditWindow = null;
        private RunTimeMainForm m_RTmainWindow = null;
        public List<RunTimeForm> editFormList = new List<RunTimeForm>();
        private string MainFirstForm = "";
        private ArrayList openedForms;
        private XmlDocument mXDoc = new XmlDocument();
        private DllManager.CDllManager dllmng = new DllManager.CDllManager();
        DataBus.DataRefresh.CRealTimeDataManager rtdm;//实时数据显示相关
        private MainForm myMainform;

        private List<boardType> btDeCoilCwList;
        private List<boardType> btDeNoCoilCwList;
        private List<boardType> btDeCoilHpList;
        private List<boardType> btDeNoCoilHpList;

        private List<boardType> btReAdjHwList;
        private List<boardType> btReNoAdjHwList;
        private List<boardType> btReAdjHpList;
        private List<boardType> btReNoAdjHpList;

        public TreeExplorer m_treeExp;
        // private HostSurfaceManager m_hostSurfaceManager = null;
        // private HostControl hc = null;

        public RunTimeFormMng(MainForm mf)
        {
            InitializeComponent();
            myMainform = mf;

            btDeCoilCwList   = myMainform.btDeCoilCwList;
            btDeNoCoilCwList = myMainform.btDeNoCoilCwList;
            btDeCoilHpList   = myMainform.btDeCoilHpList;
            btDeNoCoilHpList = myMainform.btDeNoCoilHpList;
            btReAdjHwList    = myMainform.btReAdjHwList;
            btReNoAdjHwList  = myMainform.btReNoAdjHwList;
            btReAdjHpList    = myMainform.btReAdjHpList;
            btReNoAdjHpList  = myMainform.btReNoAdjHpList;


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
            rtdm = new DataBus.DataRefresh.CRealTimeDataManager();
            m_RTmainWindow = new RunTimeMainForm(this);
            _hostSurfaceManager = new HostSurfaceManager();//temp
            openedForms = new ArrayList();
            OpenSolution();
            m_RTmainWindow.FormClosed += new FormClosedEventHandler(m_RTmainWindow_Disposed);
        }

        //打开工程入口
        private void OpenSolution()
        {
            string treeExpStr = "";

            if (myMainform.myProjectPath == "")
                myProjectPath = AppDomain.CurrentDomain.BaseDirectory;
            else
                myProjectPath = myMainform.myProjectPath ;

             Splash.Splash sp = new Splash.Splash();
             sp.Show();
             sp.Refresh();
             Thread.Sleep(1500);
             sp.Close();
             m_RTmainWindow.Show();

            m_treeExp = new TreeExplorer(treeExpStr, myMainform,this);
            m_treeExp.OpenTreeSolution(this);
            m_treeExp.Show(m_RTmainWindow.ControlsDockPanel);

            foreach (boardType n in btDeCoilCwList)
            {
                OpenOneForm(n.boardNumber);
            }
            foreach (boardType n in btDeNoCoilCwList)
            {
                OpenOneForm(n.boardNumber);
            }
            foreach (boardType n in btDeCoilHpList)
            {
                OpenOneForm(n.boardNumber);
            }
            foreach (boardType n in btDeNoCoilHpList)
            {
                OpenOneForm(n.boardNumber);
            }
            foreach (boardType n in btReAdjHwList)
            {
                OpenOneForm(n.boardNumber);
            }
            foreach (boardType n in btReNoAdjHwList)
            {
                OpenOneForm(n.boardNumber);
            }
            foreach (boardType n in btReAdjHpList)
            {
                OpenOneForm(n.boardNumber);
            }
            foreach (boardType n in btReNoAdjHpList)
            {
                OpenOneForm(n.boardNumber);
            }
        }

        //打开一个编辑画面
        public void OpenOneForm(String name)
        {
            //需新增功能： 所有form只打开一次
            for (int i = 0; i < editFormList.Count; i++)
            {
                if (editFormList[i].currentName == name)
                {
                    editFormList[i].Show();
                    return;
                }
            }
            RunTimeForm m_RTeditWindow = new RunTimeForm(this);
            try
            {
                string fileName = myProjectPath + name + ".xml";
                HostControl hc = _hostSurfaceManager.LoadNewHost(fileName);

                m_RTeditWindow.parentForm = this;
                m_RTeditWindow.currentName = name;
                m_RTeditWindow.Text = name;
                m_RTeditWindow.TabText = name;
                editFormList.Add(m_RTeditWindow);

                //填充画面
                UserControl f = new UserControl();
                UserControl user = (UserControl)_hostSurfaceManager.basicHostLoader.mComponents[0];
                f.BackColor = user.BackColor;
                f.BackgroundImage = user.BackgroundImage;
                f.BackgroundImageLayout = user.BackgroundImageLayout;
                f.BorderStyle = user.BorderStyle;
                f.Font = user.Font;
                f.ForeColor = user.ForeColor;
                f.Size = user.Size;
                f.Location = new Point(0, 0);// user.Location;
                f.Name = user.Name;
               
                #region 填充元件

                string nodeString = null;
                List<string> dllFailList = new List<string>(); //自定义控件出现错误的列表

                for (int i = 1; i < _hostSurfaceManager.basicHostLoader.mComponents.Count; i++)
                {
                    Type t = _hostSurfaceManager.basicHostLoader.mComponents[i].GetType();
                    //自定义控件的处理-->
                    nodeString = "Components/AddedComponent[@Name=\"" + t.Name + "\"]";//注意这里AddedComponent作为与原先的区别
                    XmlNode tmpXNode = mXDoc.SelectSingleNode(nodeString);
                    if (tmpXNode != null)
                    {
                        //XmlNode test = tmpXNode.SelectSingleNode("Asm");
                        string asmStr = tmpXNode.Attributes["Asm"].Value;
                        Assembly assembly = null;
                        if (asmStr.Substring(asmStr.Length - 3) == "dll" || asmStr.Substring(asmStr.Length - 3) == "DLL")
                        {
                            if (File.Exists(@dllmng.DLLPATH + asmStr))
                            {
                                assembly = Assembly.LoadFile(dllmng.DLLPATH + asmStr);
                            }
                            else
                            {
                                if (!dllFailList.Contains("Can not find DLL: " + asmStr + " in file " + dllmng.DLLPATH))
                                    dllFailList.Add("Can not find DLL: " + asmStr + " in file " + dllmng.DLLPATH);
                                continue;
                            }
                        }
                        else
                        {
                            if (File.Exists(@dllmng.DLLPATH + asmStr + ".dll"))
                            {
                                assembly = Assembly.LoadFile(dllmng.DLLPATH + asmStr + ".dll");
                            }
                            else
                            {
                                if (!dllFailList.Contains("Can not find DLL: " + asmStr + ".dll" + " in file " + dllmng.DLLPATH))
                                    dllFailList.Add("Can not find DLL: " + asmStr + ".dll" + " in file " + dllmng.DLLPATH);
                                continue;
                            }
                        }
                        Type type = assembly.GetType(t.FullName.ToString());   //类名称
                        Object obj = System.Activator.CreateInstance(type);
                        Object objInXml = _hostSurfaceManager.basicHostLoader.mComponents[i];
                        Type typeInXml = _hostSurfaceManager.basicHostLoader.mComponents[i].GetType();

                        ArrayList mObjectAttribs = new ArrayList();
                        if (tmpXNode != null)
                        {
                            try
                            {
                                XmlNodeList tmpXPropLst = tmpXNode.SelectNodes("Propertys/Property");
                                XmlNode m_tmpXNode;
                                IEnumerator tmpIe = tmpXPropLst.GetEnumerator();
                                while (tmpIe.MoveNext())
                                {
                                    m_tmpXNode = tmpIe.Current as XmlNode;
                                    mObjectAttribs.Add(m_tmpXNode.Attributes["Name"].Value);
                                }
                            }
                            catch
                            { }
                        }
                        foreach (string arr in mObjectAttribs)
                        {
                            try
                            {
                                object arrObj = typeInXml.GetProperty(arr).GetValue(objInXml, null);//get
                                type.GetProperty(arr).SetValue(obj, arrObj, null);//set
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show(ex.Message);
                            }

                        }
                        f.Controls.Add((Control)obj);
                        //<----
                    }
                    if (t.Name.Equals("PictureBox"))
                    {
                        Library.PictureBox control = (Library.PictureBox)Activator.CreateInstance(t);
                        Library.PictureBox cs = (Library.PictureBox)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.BorderStyle = cs.BorderStyle;
                        control.Image = cs.Image;
                        control.SizeMode = cs.SizeMode;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        //增加运行时标志，目的仅为可见性使用！！！
                        control.isVisible = cs.isVisible;

                        //增加退出keydown 事件
                        control.KeyDown += new KeyEventHandler(control_KeyDown);
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("Button"))
                    {
                        Library.Button control = (Library.Button)Activator.CreateInstance(t);
                        Library.Button cs = (Library.Button)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.Image = cs.Image;
                        control.ImageAlign = cs.ImageAlign;
                        control.Font = cs.Font;
                        control.ForeColor = cs.ForeColor;
                        control.FlatStyle = cs.FlatStyle;
                        control.Text = cs.Text;
                        control.TextAlign = cs.TextAlign;
                        control.TextImageRelation = cs.TextImageRelation;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;

                        control.KeyDown += new KeyEventHandler(control_KeyDown);
                        f.Controls.Add(control);

                    }
                    if (t.Name.Equals("SendButton"))
                    {
                        Library.SendButton control = (Library.SendButton)Activator.CreateInstance(t);
                        Library.SendButton cs = (Library.SendButton)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.BorderStyle = cs.BorderStyle;
                        control.Font = cs.Font;
                        control.ForeColor = cs.ForeColor;
                        control.Text = cs.Text;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        //增加运行时标志，目的仅为可见性使用！！！
                       // control.isVisible = cs.isVisible;
                        control.ID = cs.ID;
                        control.RelatedDeviceType = cs.RelatedDeviceType;
                        control.BoardNumber = cs.BoardNumber;
                        control.RelatedPort = cs.RelatedPort;
                        control.DeviceName = cs.DeviceName;
                        control.rtdm = rtdm;
                        //control.Enabled = false; //选中无光标闪烁
                        //增加退出keydown 事件
                        control.KeyDown += new KeyEventHandler(control_KeyDown);
                        f.Controls.Add(control);

                    }
                    if (t.Name.Equals("TextBox"))
                    {
                        Library.TextBox control = (Library.TextBox)Activator.CreateInstance(t);
                        Library.TextBox cs = (Library.TextBox)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.BorderStyle = cs.BorderStyle;
                        control.Font = cs.Font;
                        control.ForeColor = cs.ForeColor;
                        control.Text = cs.Text;
                        control.TextAlign = cs.TextAlign;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        //增加运行时标志，目的仅为可见性使用！！！
                        control.isVisible = cs.isVisible;

                        control.ID = cs.ID;
                        control.RelatedDeviceType = cs.RelatedDeviceType;
                        control.BoardNumber = cs.BoardNumber;
                        control.RelatedPort = cs.RelatedPort;
                        control.DeviceName = cs.DeviceName;

                        control.rtdm = rtdm;

                        //control.Enabled = false; //选中无光标闪烁
                        //增加退出keydown 事件
                        control.KeyDown += new KeyEventHandler(control_KeyDown);
                        f.Controls.Add(control);
                    }
                 
                    if (t.Name.Equals("Lable"))
                    {
                        Library.Lable control = (Library.Lable)Activator.CreateInstance(t);
                        Library.Lable cs = (Library.Lable)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.BorderStyle = cs.BorderStyle;
                        control.Font = cs.Font;
                        control.ForeColor = cs.ForeColor;
                        control.Text = cs.Text;
                        control.TextAlign = cs.TextAlign;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;

                        //增加退出keydown 事件
                        control.KeyDown += new KeyEventHandler(control_KeyDown);
                        f.Controls.Add(control);
                    }
                    if (  t.Name.Equals("LDDS") )
                    {
                        Library.LDDS.Module control = (Library.LDDS.Module)Activator.CreateInstance(t);
                        Library.LDDS.Module cs = (Library.LDDS.Module)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.InterfaceName = cs.InterfaceName;

                        control.OnDrawLineClick += new Library.LDDS.Module.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("ArrowLink"))
                    {
                        Library.LDDS.ArrowLink control = (Library.LDDS.ArrowLink)Activator.CreateInstance(t);
                        Library.LDDS.ArrowLink cs = (Library.LDDS.ArrowLink)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.InterfaceName = cs.InterfaceName;

                        control.ArrowName = cs.ArrowName;
                        if (control.ArrowName.ToString() == "WaterMixingArrow")
                        {
                            this.BackgroundImage = global::Designer.Properties.Resources.WaterMixingArrow_new;
                        }
                        else if (control.ArrowName.ToString() == "ThermistorArrow")
                        {
                            this.BackgroundImage = global::Designer.Properties.Resources.ThermistorArrow;
                        }
                        else if (control.ArrowName.ToString() == "VibTestingArrow")
                        {
                            this.BackgroundImage = global::Designer.Properties.Resources.VibTestingArrow;
                        }
                        else if (control.ArrowName.ToString() == "FlowtestingArrow")
                        {
                            this.BackgroundImage = global::Designer.Properties.Resources.FlowTestingArrow_new;
                        }
                        else if (control.ArrowName.ToString() == "LengthArrow")
                        {
                            this.BackgroundImage = global::Designer.Properties.Resources.LengthArrow;
                        }
                        else if (control.ArrowName.ToString() == "HumidityArrow")
                        {
                            this.BackgroundImage = global::Designer.Properties.Resources.HumidityArrow;
                        }
                        //control.BackgroundImage = global::Library.Properties.Resources.VibTestingArrow;

                        control.OnDrawLineClick += new Library.LDDS.Module.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }
                  

                    if (t.Name.Equals("Regenerator1"))
                    {
                        Library.LDDS.Regenerator1 control = (Library.LDDS.Regenerator1)Activator.CreateInstance(t);
                        Library.LDDS.Regenerator1 cs = (Library.LDDS.Regenerator1)_hostSurfaceManager.basicHostLoader.mComponents[i];

                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.BoardNumber = cs.BoardNumber;
                        control.InterfaceName = cs.InterfaceName;
                        control.rtdm = rtdm;
                        control.OnDrawLineClick += new Library.LDDS.Regenerator1.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("Regenerator2"))
                    {
                        Library.LDDS.Regenerator2 control = (Library.LDDS.Regenerator2)Activator.CreateInstance(t);
                        Library.LDDS.Regenerator2 cs = (Library.LDDS.Regenerator2)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.BoardNumber = cs.BoardNumber;
                        control.InterfaceName = cs.InterfaceName;
                        control.rtdm = rtdm;
                        control.OnDrawLineClick += new Library.LDDS.Regenerator2.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("Regenerator3"))
                    {
                        Library.LDDS.Regenerator3 control = (Library.LDDS.Regenerator3)Activator.CreateInstance(t);
                        Library.LDDS.Regenerator3 cs = (Library.LDDS.Regenerator3)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.BoardNumber = cs.BoardNumber;
                        control.InterfaceName = cs.InterfaceName;
                        control.rtdm = rtdm;
                        control.OnDrawLineClick += new Library.LDDS.Regenerator2.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("Regenerator4"))
                    {
                        Library.LDDS.Regenerator4 control = (Library.LDDS.Regenerator4)Activator.CreateInstance(t);
                        Library.LDDS.Regenerator4 cs = (Library.LDDS.Regenerator4)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.BoardNumber = cs.BoardNumber;
                        control.InterfaceName = cs.InterfaceName;
                        control.rtdm = rtdm;
                        control.OnDrawLineClick += new Library.LDDS.Regenerator2.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("Dehumidifier1"))
                    {
                        Library.LDDS.Dehumidifier1 control = (Library.LDDS.Dehumidifier1)Activator.CreateInstance(t);
                        Library.LDDS.Dehumidifier1 cs = (Library.LDDS.Dehumidifier1)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable(); 
                        
                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.DeviceName = control.DeviceName;
                        control.InterfaceName = cs.InterfaceName;
                        control.BoardNumber = cs.BoardNumber;
                        control.rtdm = rtdm;

                        control.OnDrawLineClick += new Library.LDDS.Dehumidifier1.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                        
                    }

                
                    if (t.Name.Equals("Dehumidifier2"))
                    {
                        Library.LDDS.Dehumidifier2 control = (Library.LDDS.Dehumidifier2)Activator.CreateInstance(t);
                        Library.LDDS.Dehumidifier2 cs = (Library.LDDS.Dehumidifier2)_hostSurfaceManager.basicHostLoader.mComponents[i];

                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.InterfaceName = cs.InterfaceName;
                        control.BoardNumber = cs.BoardNumber;
                        control.rtdm = rtdm;
                        control.OnDrawLineClick += new Library.LDDS.Dehumidifier2.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("Dehumidifier3"))
                    {
                        Library.LDDS.Dehumidifier3 control = (Library.LDDS.Dehumidifier3)Activator.CreateInstance(t);
                        Library.LDDS.Dehumidifier3 cs = (Library.LDDS.Dehumidifier3)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        DataBus.DataAccess.CData_PointTable dataPT = new DataBus.DataAccess.CData_PointTable();

                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.DeviceName = control.DeviceName;
                        control.InterfaceName = cs.InterfaceName;
                        control.BoardNumber = cs.BoardNumber;
                        control.rtdm = rtdm;

                        control.OnDrawLineClick += new Library.LDDS.Dehumidifier1.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);

                    }


                    if (t.Name.Equals("Dehumidifier4"))
                    {
                        Library.LDDS.Dehumidifier4 control = (Library.LDDS.Dehumidifier4)Activator.CreateInstance(t);
                        Library.LDDS.Dehumidifier4 cs = (Library.LDDS.Dehumidifier4)_hostSurfaceManager.basicHostLoader.mComponents[i];

                        control.BackColor = cs.BackColor;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.Name = cs.Name;
                        control.InterfaceName = cs.InterfaceName;
                        control.BoardNumber = cs.BoardNumber;
                        control.rtdm = rtdm;
                        control.OnDrawLineClick += new Library.LDDS.Dehumidifier2.OnDrawLineEventHandle(Control_OnDrawLineClick);
                        f.Controls.Add(control);
                    }

                    if (t.Name.Equals("AtoMain"))
                    {
                        //                         AutotunerFinVerOne.AtoMain control = new AutotunerFinVerOne.AtoMain();
                        //                         AutotunerFinVerOne.AtoMain cs = (AutotunerFinVerOne.AtoMain)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        //                         control.ret_val = "AHU B4_309 Supply Air Temp Control Loop";
                        //                         cs.ret_val = "AHU B4_309 Supply Air Temp Control Loop";
                        //                         control.BackColor = cs.BackColor;
                        //                         control.Size = cs.Size;
                        //                         control.Location = cs.Location;
                        //                         //control.Name = cs.Name;
                        //                         f.Controls.Add(control);
                    }
                    //if (t.Name.Equals("ButtonCheck"))
                    //{
                    //    //                         SBB_ACMV.Controls.ButtonCheck control = (SBB_ACMV.Controls.ButtonCheck)Activator.CreateInstance(t);
                    //    //                         SBB_ACMV.Controls.ButtonCheck cs = (SBB_ACMV.Controls.ButtonCheck)_hostSurfaceManager.basicHostLoader.mComponents[i];
                    //    //                         control.BoardNo = cs.BoardNo;
                    //    //                         //control.BoardNoText = cs.BoardNoText;
                    //    //                         control.loopNo = cs.loopNo;
                    //    //                         //control.loopNoText = cs.loopNoText;
                    //    //                         control.BackColor = cs.BackColor;
                    //    //                         control.Name = cs.Name;
                    //    //                         control.Size = cs.Size;
                    //    //                         control.Location = cs.Location;
                    //    //                         //control.Name = cs.Name;
                    //    //                         f.Controls.Add(control);
                    //}
              
                  
                    if (t.Name.Equals("SendButton"))
                    {
                        Library.SendButton control = (Library.SendButton)Activator.CreateInstance(t);
                        Library.SendButton cs = (Library.SendButton)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.PortData = cs.PortData;
                        control.PortBind = cs.PortBind;
                        control.RelatedPort = cs.RelatedPort;
                        control.BoardNumber = cs.BoardNumber;
                        control.DeviceName = cs.DeviceName;
                        control.BackColor = cs.BackColor;
                        control.Name = cs.Name;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        //control.Name = cs.Name;
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("statusIndicator")) 
                    {
                        Library.statusIndicator control = (Library.statusIndicator)Activator.CreateInstance(t);
                        Library.statusIndicator cs = (Library.statusIndicator)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.RelatedPort = cs.RelatedPort;
                        control.BoardNumber = cs.BoardNumber;
                        control.DeviceName = cs.DeviceName;
                        control.BackColor = cs.BackColor;
                        control.Name = cs.Name;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        //control.Name = cs.Name;
                        f.Controls.Add(control);
                        control.rtdm = rtdm;
                    }
                    if (t.Name.Equals("levelmeter"))
                    {
                        Library.Common.levelmeter control = (Library.Common.levelmeter)Activator.CreateInstance(t);
                        Library.Common.levelmeter cs = (Library.Common.levelmeter)_hostSurfaceManager.basicHostLoader.mComponents[i];

                        control.RelatedPort = cs.RelatedPort;
                        control.BoardNumber = cs.BoardNumber;
                        control.DeviceName = cs.DeviceName;
                        control.BackColor = cs.BackColor;
                        control.Value = cs.Value;
                        control.Name = cs.Name;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.rtdm = rtdm;
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("ButtonCheck"))
                    {
                        Library.Common.ButtonCheck control = (Library.Common.ButtonCheck)Activator.CreateInstance(t);
                        Library.Common.ButtonCheck cs = (Library.Common.ButtonCheck)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.PortData = cs.PortData;
                        control.PortBind = cs.PortBind;
                        control.RelatedPort = cs.RelatedPort;
                        control.BoardNumber = cs.BoardNumber;
                        control.DeviceName = cs.DeviceName;
                        control.BackColor = cs.BackColor;
                        control.Name = cs.Name;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.CheckStyleX = cs.CheckStyleX;
                        control.CheckCurrentState();
                        //control.Name = cs.Name;
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("ButtonCheckFun"))
                    {
                        Library.Common.ButtonCheckFun control = (Library.Common.ButtonCheckFun)Activator.CreateInstance(t);
                        Library.Common.ButtonCheckFun cs = (Library.Common.ButtonCheckFun)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.PortData = cs.PortData;
                        control.PortBind = cs.PortBind;
                        control.RelatedPort = cs.RelatedPort;
                        control.BoardNumber = cs.BoardNumber;
                        control.DeviceName = cs.DeviceName;
                        control.BackColor = cs.BackColor;
                        control.Name = cs.Name;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.CheckStyleX = cs.CheckStyleX;
                        control.CheckCurrentState();
                        //control.Name = cs.Name;
                        f.Controls.Add(control);
                    }
                    //if (t.Name.Equals("OnOff"))
                    //{
                    //    Library.Common.CommunicationOnOff control = (Library.Common.CommunicationOnOff)Activator.CreateInstance(t);
                    //    Library.Common.CommunicationOnOff cs = (Library.Common.CommunicationOnOff)_hostSurfaceManager.basicHostLoader.mComponents[i];
                    //    control.PortData = cs.PortData;
                    //    control.PortBind = cs.PortBind;
                    //    control.RelatedPort = cs.RelatedPort;
                    //    control.BoardNumber = cs.BoardNumber;
                    //    control.DeviceName = cs.DeviceName;
                    //    control.BackColor = cs.BackColor;
                    //    control.Name = cs.Name;
                    //    control.Size = cs.Size;
                    //    control.Location = cs.Location;
                    //    control.CheckStyleX = cs.CheckStyleX;
                    //    control.CheckCurrentState();
                    //    //control.Name = cs.Name;
                    //    f.Controls.Add(control);
                    //}
                    if (t.Name.Equals("Alarm"))
                    {
                        Library.Common.Alarm control = (Library.Common.Alarm)Activator.CreateInstance(t);
                        Library.Common.Alarm cs = (Library.Common.Alarm)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.RelatedPort = cs.RelatedPort;
                        control.BoardNumber = cs.BoardNumber;
                        control.UpLimit = cs.UpLimit;
                        control.DownLimit = cs.DownLimit;
                        control.BackColor = cs.BackColor;
                        control.Name = cs.Name;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.rtdm = rtdm;
                        //control.Name = cs.Name;
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("RunState"))
                    {
                        Library.Common.RunState control = (Library.Common.RunState)Activator.CreateInstance(t);
                        Library.Common.RunState cs = (Library.Common.RunState)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        control.RelatedPort = cs.RelatedPort;
                        control.BoardNumber = cs.BoardNumber;
                        control.BackColor = cs.BackColor;
                        control.Name = cs.Name;
                        control.Size = cs.Size;
                        control.Location = cs.Location;
                        control.rtdm = rtdm;
                        f.Controls.Add(control);
                    }
                    if (t.Name.Equals("NumericUpDownEx"))
                    {
                        //                         SBB_ACMV.Controls.NumericUpDownEx control = (SBB_ACMV.Controls.NumericUpDownEx)Activator.CreateInstance(t);
                        //                         SBB_ACMV.Controls.NumericUpDownEx cs = (SBB_ACMV.Controls.NumericUpDownEx)_hostSurfaceManager.basicHostLoader.mComponents[i];
                        //                         control.BoardNo = cs.BoardNo;
                        //                         //control.BoardNoText = cs.BoardNoText;
                        //                         control.PortNo = cs.PortNo;
                        //                         //control.PortNoText = cs.PortNoText;
                        //                         control.BackColor = cs.BackColor;
                        //                         control.Name = cs.Name;
                        //                         control.Size = cs.Size;
                        //                         control.Location = cs.Location;
                        //                         //control.Name = cs.Name;
                        //                         f.Controls.Add(control);
                    }

                }

                //自定义dll错误信息显示
                string infoStr = "";
                foreach (string dllFail in dllFailList)
                {
                    infoStr += dllFail + "\r\n";
                }
                if (infoStr != "")
                    MessageBox.Show(infoStr + "\r\n" + "Please Check!", "Custom Control(DLL) Error Information", MessageBoxButtons.OK, MessageBoxIcon.Information);


                //全屏幕form
                //                 FormState formState = new FormState();
                //                 this.SetVisibleCore(false);
                //                 formState.Maximize(m_RTeditWindow, false);
                //                 this.SetVisibleCore(true);
                //放置到主窗体 
                m_RTeditWindow.panel1.Controls.Add(f);
                m_RTeditWindow.Show(m_RTmainWindow.ControlsDockPanel);

                #endregion
                f.KeyDown += new KeyEventHandler(f_KeyDown);
            }
            catch (Exception)
            {
                MessageBox.Show("Load Error!", "Load Error Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        //画面key down 响应
        void f_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Alt && (e.KeyCode == Keys.Q || e.KeyCode == Keys.E))
            {
                if (MessageBox.Show("确定要退出监控程序吗？", "Alert", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    Application.Exit();
                }
            }
        }
        //控件获得焦点时，keydown退出事件响应
        void control_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Alt && (e.KeyCode == Keys.Q || e.KeyCode == Keys.E))
            {
                if (MessageBox.Show("确定要退出监控程序吗？", "Alert", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    Application.Exit();
                }
            }
        }

        //点击AHU
        public void Control_OnDrawLineClick(object sender, EventArgs e)
        {
            Library.LDDS.Module_DoubleClickEventArgs arg = (Library.LDDS.Module_DoubleClickEventArgs)e;
            string fn = arg.FormName;
            if (!openedForms.Contains(fn))
            {
                openedForms.Add(fn);
                OpenOneForm(fn);
            }
            else
            {
                MessageBox.Show("Form opened already", "Alert", MessageBoxButtons.OK);
            }

        }
        #region Class used to preserve / restore state of the form
        //Class used to preserve / restore state of the form
        public class FormState
        {
            private FormWindowState winState;
            private FormBorderStyle brdStyle;
            private bool topMost;
            private Rectangle bounds;
            private bool IsMaximized = false;
            public void Maximize(Form targetForm, bool tpmost)
            {
                if (!IsMaximized)
                {
                    IsMaximized = true;
                    // Save(targetForm);
                    targetForm.WindowState = FormWindowState.Maximized;
                    targetForm.FormBorderStyle = FormBorderStyle.None;
                    targetForm.TopMost = tpmost;
                    WinApi.SetWinFullScreen(targetForm.Handle);
                }
            }
            public void Save(Form targetForm)
            {
                winState = targetForm.WindowState;
                brdStyle = targetForm.FormBorderStyle;
                topMost = targetForm.TopMost;
                bounds = targetForm.Bounds;
            }
            public void Restore(Form targetForm)
            {
                targetForm.WindowState = winState;
                targetForm.FormBorderStyle = brdStyle;
                targetForm.TopMost = topMost;
                targetForm.Bounds = bounds;
                IsMaximized = false;
            }
        }
        public class WinApi
        {
            [DllImport("user32.dll", EntryPoint = "GetSystemMetrics")]
            public static extern int GetSystemMetrics(int which);

            [DllImport("user32.dll")]
            public static extern void
                SetWindowPos(IntPtr hwnd, IntPtr hwndInsertAfter,
                             int X, int Y, int width, int height, uint flags);
            private const int SM_CXSCREEN = 0;
            private const int SM_CYSCREEN = 1;
            private static IntPtr HWND_TOP = IntPtr.Zero;
            private const int SWP_SHOWWINDOW = 64; // 0x0040
            public static int ScreenX
            {
                get { return GetSystemMetrics(SM_CXSCREEN); }
            }
            public static int ScreenY
            {
                get { return GetSystemMetrics(SM_CYSCREEN); }
            }
            public static void SetWinFullScreen(IntPtr hwnd)
            {
                SetWindowPos(hwnd, HWND_TOP, 0, 0, ScreenX, ScreenY, SWP_SHOWWINDOW);
            }
        }
        #endregion Class used to preserve / restore state of the form#region Class used to preserve / restore state of the form

        public void FormDispose(string name)
        {
            rtdm.stop();
            if (name != "")
            {
                openedForms.Remove(name);
                for (int i = 0; i < editFormList.Count; i++)
                {
                    if (editFormList[i].currentName == name)
                    {
                        for (int j = 0; j < editFormList[i].Controls.Count; j++)
                            editFormList[i].Controls.RemoveAt(j);
                    }
                }
            }
        }

        private void m_RTmainWindow_Disposed(object sender, FormClosedEventArgs e)
        {
            rtdm.stop();
        }
    }
}
