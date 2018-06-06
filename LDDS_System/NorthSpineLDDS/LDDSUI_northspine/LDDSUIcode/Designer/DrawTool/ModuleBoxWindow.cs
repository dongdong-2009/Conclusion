using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Collections;
using System.Windows.Forms;
using Silver.UI;
using System.IO;
using System.Xml;
using System.Reflection;
using Host;

namespace Designer
{
    public partial class ModuleBoxWindow : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        private ToolBoxItem editedItem;
        private ToolBoxTab  editedTab;
        private MainForm    mfMainForm;

        private List<boardType> btDeCoilCwList;
        private List<boardType> btDeNoCoilCwList;
        private List<boardType> btDeCoilHpList;
        private List<boardType> btDeNoCoilHpList;

        private List<boardType> btReAdjHwList;
        private List<boardType> btReNoAdjHwList;
        private List<boardType> btReAdjHpList;
        private List<boardType> btReNoAdjHpList;

        private String[] moduleType = new String[]
       {
            "ChilledWater With Coil","ChilledWater Without Coil", "HeatPump With Coil","HeatPump Without Coil",
             "HotWater Adjustable","HotWater UnAdjustable", "HeatPump Adjustable","HeatPump UnAdjustable"
       };
         //tab
        private string[] CTabNameStrings = { "MainModule", "SubModule","Customize" };
        //for dll
        private DllManager.CDllManager dllmng = new DllManager.CDllManager();
        //item
        private XmlDocument mXDoc = new XmlDocument();
        private TreeView bnTreeView = new TreeView();
        private Type[] MainModuleTypes = new Type[]
        {
           typeof(Library.LDDS.Dehumidifier1),
           typeof(Library.LDDS.Dehumidifier2),
           typeof(Library.LDDS.Dehumidifier1),
           typeof(Library.LDDS.Dehumidifier2),
           typeof(Library.LDDS.Regenerator1),
           typeof(Library.LDDS.Regenerator2),
           typeof(Library.LDDS.Regenerator3),
           typeof(Library.LDDS.Regenerator2),
        };
        private Type[] SubModuleTypes = new Type[]
        {
			typeof(Library.Lable),typeof(Library.PictureBox),typeof(Library.Common.Alarm),
            typeof(Library.statusIndicator),typeof(Library.Ellipse),typeof(Library.Rectangles),
            
        };

       
        
        //自定义
        private Type[] CustomModules = new Type[]
        {
        };
        public ModuleBoxWindow(MainForm mf)
        {

            mfMainForm = mf;
            InitializeComponent();
            btDeCoilCwList   = mf.btDeCoilCwList;
            btDeNoCoilCwList = mf.btDeNoCoilCwList;
            btDeCoilHpList   = mf.btDeCoilHpList;
            btDeNoCoilHpList = mf.btDeNoCoilHpList;
            btReAdjHwList    = mf.btReAdjHwList;
            btReNoAdjHwList  = mf.btReNoAdjHwList;
            btReAdjHpList    = mf.btReAdjHpList;
            btReNoAdjHpList  = mf.btReNoAdjHpList;

           
            bnTreeView.BorderStyle = BorderStyle.None;
            bnTreeView.Dock = DockStyle.Fill;
            bnTreeView.MouseDoubleClick += new MouseEventHandler(treeExplore_MouseDoubleClick);



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

            init();

        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }
        public Silver.UI.ToolBox ToolBox
        {
            get
            {
                return this.toolBoxEvo;
            }
        }



      
        public void init()
        {

   
            this.ToolBox.TabMouseUp += new TabMouseEventHandler(ToolBox_TabMouseUp);
            //组件类型

            ToolBoxTabCollection tabCollection = new ToolBoxTabCollection();
            ToolBoxItemCollection itemCollection = new ToolBoxItemCollection();

            for (int i = 0; i < CTabNameStrings.Count(); i++)
            {
                this.ToolBox.AddTab(CTabNameStrings[i], 1);
                ToolBoxTab tab = this.ToolBox[i];
                tabCollection.Add(tab);
            }
            //自定义控件处理：xuehaouan 2016-4-13 ->
            string nodeString = "Components/AddedComponent";//注意这里AddedComponent作为与原先的区别
            XmlNodeList tmpXNodeLst = mXDoc.SelectNodes(nodeString);
            XmlNode m_tmpXNode;
            IEnumerator tmpIe = tmpXNodeLst.GetEnumerator();
            List<string> dllFailList = new List<string>();
            while (tmpIe.MoveNext())
            {
                m_tmpXNode = tmpIe.Current as XmlNode;
                string ModName = m_tmpXNode.Attributes["FullName"].Value;
                string AsmStr = m_tmpXNode.Attributes["Asm"].Value;
                Assembly assembly;
                Type type = null ;
                if (AsmStr.Substring(AsmStr.Length - 3) == "dll" || AsmStr.Substring(AsmStr.Length - 3) == "DLL")
                {
                    if (File.Exists(@dllmng.DLLPATH + AsmStr))
                    {
                        assembly = Assembly.LoadFile(dllmng.DLLPATH + AsmStr);
                        type = assembly.GetType(AsmStr.Substring(0, AsmStr.Length - 3) + ModName);   //类名称 e.g.  ACMV.Controls.PIDControlPanelWithDataConn
                    }
                    else
                    {
                        if (!dllFailList.Contains("Can not find DLL: " + AsmStr + " in file " + dllmng.DLLPATH))
                            dllFailList.Add("Can not find DLL: " + AsmStr + " in file " + dllmng.DLLPATH);
                        //MessageBox.Show("Can not find" + AsmStr + " in file " + dllmng.DLLPATH, "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                else
                {
                    if (File.Exists(@dllmng.DLLPATH + AsmStr + ".dll"))
                    {
                        assembly = Assembly.LoadFile(dllmng.DLLPATH + AsmStr + ".dll");
                        type = assembly.GetType(AsmStr + "." + ModName);   //类名称 e.g.  ACMV.Controls.PIDControlPanelWithDataConn
                    }
                    else
                    {
                        if (!dllFailList.Contains("Can not find DLL: " + AsmStr + ".dll" + " in file " + dllmng.DLLPATH))
                            dllFailList.Add("Can not find DLL: " + AsmStr + ".dll" + " in file " + dllmng.DLLPATH);
                        //MessageBox.Show("Can not find" + AsmStr + ".dll " + " in file " + dllmng.DLLPATH, "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                if (type != null)
                {
                    System.Drawing.Design.ToolboxItem tbi = new System.Drawing.Design.ToolboxItem(type);
                    
                    tabCollection[tabCollection.Count-1].AddItem(tbi.DisplayName, 2, true, tbi);
                }
            }
            string infoStr = "";
            foreach(string dllFail in dllFailList)
            {
                infoStr += dllFail + "\r\n";
            }
            if(infoStr != "")
                MessageBox.Show(infoStr + "\r\n" + "Please Check!", "Custom Control(DLL) Error Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
            //<-
            if (null != tabCollection)
            {
                  for (int i = 0; i < moduleType.Count(); i++)
                    {
                        FillTreeView(bnTreeView, moduleType[i], i);
                         tabCollection[0].Control = bnTreeView;
                }

             //   }
                for (int i = 0; i < SubModuleTypes.Count(); i++)
                {
                    System.Drawing.Design.ToolboxItem tbi = new System.Drawing.Design.ToolboxItem(SubModuleTypes[i]);

                    tabCollection[1].AddItem(tbi.DisplayName,  3, true, tbi);
                }
            }
        }
        public void treeExplore_MouseDoubleClick(object sender, MouseEventArgs e)
       {
            if (e.Button == MouseButtons.Left)
            {
                Point ClickPoint = new Point(e.X, e.Y);
                TreeNode CurrentNode = bnTreeView.GetNodeAt(ClickPoint);

                if ((CurrentNode != null)&(CurrentNode.Text.Length == 8))//判断是否点到一个节点判断是boardnum
                {
                    mfMainForm.drawToolWindow.OpenOneForm(CurrentNode.Text);

                }
            }

        }
        private void FillTreeView(TreeView t, String NodeHead, int num)
        {

            t.Nodes.Add(NodeHead);
            t.ExpandAll();

            //设置显示图标

            switch (NodeHead)
            {
                case "ChilledWater With Coil":
                    for (int i = 0; i < btDeCoilCwList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btDeCoilCwList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case "ChilledWater Without Coil":
                    for (int i = 0; i < btDeNoCoilCwList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btDeNoCoilCwList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case "HeatPump With Coil":
                    for (int i = 0; i < btDeCoilHpList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btDeCoilHpList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case "HeatPump Without Coil":
                    for (int i = 0; i < btDeNoCoilHpList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btDeNoCoilHpList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case "HotWater Adjustable":
                    for (int i = 0; i < btReAdjHwList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btReAdjHwList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case "HotWater UnAdjustable":
                    for (int i = 0; i < btReNoAdjHwList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btReNoAdjHwList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case "HeatPump Adjustable":
                    for (int i = 0; i < btReAdjHpList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btReAdjHpList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case "HeatPump UnAdjustable":
                    for (int i = 0; i < btReNoAdjHpList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btReNoAdjHpList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;

                default:
                    break;

            }

        }

      //  mainfrm.drawToolWindow.OpenOneForm(no.Name);
      
        private void ToolBox_TabMouseUp(ToolBoxTab sender, MouseEventArgs e)
        {
            Point ptPos = Point.Empty;
            ContextMenu cm = null;

            if (e.Button == MouseButtons.Right)
            {
                ptPos.X = e.X;
                ptPos.Y = e.Y;
                cm = CreateContextMenu(true, sender);
                cm.Show(this.ToolBox, ptPos);
            }
        }

        private ContextMenu CreateContextMenu(bool forTab, ToolBoxItem item)
        {

            ToolBoxTab theTab = null;
            ContextMenu cm = new ContextMenu();

            cm.MenuItems.Add(forTab ? "ToolBox Tab Menu" : "ToolBox Item Menu");
            cm.MenuItems.Add(item.Caption);

            cm.MenuItems.Add("-");
            cm.MenuItems.Add("Rename " + (forTab ? "Tab" : "Item"));         //3 - Rename
            cm.MenuItems.Add("Move " + (forTab ? "Tab" : "Item") + " up"); //4 - Move up
            cm.MenuItems.Add("Move " + (forTab ? "Tab" : "Item") + " down");//5 - Move down
            cm.MenuItems.Add("Delete " + (forTab ? "Tab" : "Item"));         //6 - Delete

            cm.MenuItems[0].Enabled = false;

            if (forTab)
            {
                theTab = (ToolBoxTab)item;
            }
            else
            {
                theTab = (ToolBoxTab)item.ParentItem;
            }

            cm.MenuItems[3].Enabled = item.Renamable;
            cm.MenuItems[4].Enabled = item.CanMoveUp;
            cm.MenuItems[5].Enabled = item.CanMoveDown;
            cm.MenuItems[6].Enabled = item.Deletable;

            if (!forTab)
            {
//                 cm.MenuItems[3].Click += new EventHandler(OnItemRenameClick);
//                 cm.MenuItems[4].Click += new EventHandler(OnItemMoveUpClick);
//                 cm.MenuItems[5].Click += new EventHandler(OnItemMoveDownClick);
//                 cm.MenuItems[6].Click += new EventHandler(OnItemDeleteClick);

            }
            else
            {
//                 cm.MenuItems[3].Click += new EventHandler(OnTabRenameClick);
//                 cm.MenuItems[4].Click += new EventHandler(OnTabMoveUpClick);
//                 cm.MenuItems[5].Click += new EventHandler(OnTabMoveDownClick);
//                 cm.MenuItems[6].Click += new EventHandler(OnTabDeleteClick);
            }

            if (!forTab)
            {
                editedItem = item;
            }
            else
            {
            }

            if (null != theTab)
            {
                MenuItem[] subMenus = new MenuItem[3];

                subMenus[0] = new MenuItem("List");
                subMenus[1] = new MenuItem("Small Icons");
                subMenus[2] = new MenuItem("Large Icons");


                cm.MenuItems.Add("-");
                cm.MenuItems.Add("View", subMenus);

                switch (theTab.View)
                {
                    case ViewMode.List:
                        subMenus[0].Checked = true;
                        break;
                    case ViewMode.SmallIcons:
                        subMenus[1].Checked = true;
                        break;
                    case ViewMode.LargeIcons:
                        subMenus[2].Checked = true;
                        break;
                }

                subMenus[0].Click += new EventHandler(OnItemViewModeChange);
                subMenus[1].Click += new EventHandler(OnItemViewModeChange);
                subMenus[2].Click += new EventHandler(OnItemViewModeChange);

            }

            editedTab = theTab;

            cm.MenuItems.Add("-");

            cm.MenuItems.Add("Sample Menu Item 1");
            cm.MenuItems.Add("Sample Menu Item 2");


            return cm;
        }
        private void OnItemViewModeChange(object sender, EventArgs e)
        {
            try
            {
                switch (((MenuItem)sender).Index)
                {
                    case 0:
                        editedTab.View = ViewMode.List;
                        break;
                    case 1:
                        editedTab.View = ViewMode.SmallIcons;
                        break;
                    case 2:
                        editedTab.View = ViewMode.LargeIcons;
                        break;
                }
            }
            catch
            {
            }
        }
    }
}
