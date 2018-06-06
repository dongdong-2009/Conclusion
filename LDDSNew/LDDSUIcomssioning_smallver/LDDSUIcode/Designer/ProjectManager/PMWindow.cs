using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
namespace Designer.ProjectManager
{
    public partial class PMWindow : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        private string      spath ;
        private Settingcontrol mainfrm;
        private XmlDocument doc = new XmlDocument();
        public  string      currentProjectPath = null ;
        private ProjectManagerWindow pmw = null;

//         private bstarConfigurationLyh.SystemSetting st;
//         private bstarConfigurationLyh.DBManager dbmanager;
//         private bstarConfigurationLyh.HardwareConfig hardwareConfig;
//         private bstarConfigurationLyh.LoopConfig loopConfig;
        public PMWindow()
        {
            InitializeComponent();
            InitTree();
            mainfrm = null;
            pmw = new ProjectManagerWindow();
//             st = new bstarConfigurationLyh.SystemSetting();
//             dbmanager = new bstarConfigurationLyh.DBManager();
//             hardwareConfig = new bstarConfigurationLyh.HardwareConfig();
//             loopConfig = new bstarConfigurationLyh.LoopConfig();
            //fddSetting = new bstarFddClassLibLyh.SelectFDDFunction();
            this.treeExplore.MouseDoubleClick += new MouseEventHandler(treeExplore_MouseDoubleClick);
        }
        public void InitParamEvent(string propath, Settingcontrol mf)
        {
            mainfrm = mf;
            currentProjectPath = propath;
            this.treeExplore.MouseClick += new MouseEventHandler(treeExplore_MouseClick);
        }
        public void treeExplore_MouseClick(object sender, MouseEventArgs e)
        {
            if (currentProjectPath == null)
                return;
            if (e.Button == MouseButtons.Right)
            {
                Point ClickPoint = new Point(e.X, e.Y);
                TreeNode CurrentNode = treeExplore.GetNodeAt(ClickPoint);
                if (CurrentNode != null)//判断是否点到一个节点
                {
                    switch (CurrentNode.Text)//根据不同节点显示不同的右键菜单，当然你可以让它显示一样的菜单
                    {
                        case "FormDesigner":
                            //LoadUserForm.Visible = true;
                            CurrentNode.ContextMenuStrip = RightMenuStrip;
                            break;
                    }
                }
            }

        }
        public void treeExplore_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Point ClickPoint = new Point(e.X, e.Y);
                TreeNode CurrentNode = treeExplore.GetNodeAt(ClickPoint);
                if (CurrentNode != null)//判断是否点到一个节点
                {
                    switch (CurrentNode.Text)//根据不同节点显示不同的右键菜单，当然你可以让它显示一样的菜单
                    {
                        case "ProjectManager":
                            pmw = new ProjectManagerWindow();
                            pmw.Show();
                            break;
                        case "Loop Configuration":
                            //loopConfig.Show();
                            break;
                        case "Hardware Configuration":
                            //hardwareConfig.Show();
                            break;
                        case "Database Configuration":
                            //dbmanager.Show();
                            break;
                        case "System Setting":
                            //st.Show();
                            break;
                        case "FDD Setting":
                            //fddSetting.Show();
                            break;
                        case "EMS":
                            System.Diagnostics.Process.Start("..\\..\\..\\EMS\\Release\\HVACSchedulerCS.exe"); 
                            break;
                    }
                }
            }
        }
        public void InitTree()
        {
            treeExplore.Nodes.Clear();

            TreeNode newnode1 = new TreeNode("ProjectManager");
            treeExplore.Nodes.Add(newnode1);
            TreeNode newnode2 = new TreeNode("FormDesigner");
            treeExplore.Nodes.Add(newnode2);
            TreeNode newnode3 = new TreeNode("DataBaseManager");
            treeExplore.Nodes.Add(newnode3);
            TreeNode DBMchildNode1 = new TreeNode("Loop Configuration");
            TreeNode DBMchildNode2 = new TreeNode("Hardware Configuration");
            TreeNode DBMchildNode3 = new TreeNode("Database Configuration");
            TreeNode DBMchildNode4 = new TreeNode("System Setting");
            newnode3.Nodes.Add(DBMchildNode1);
            newnode3.Nodes.Add(DBMchildNode2);
            newnode3.Nodes.Add(DBMchildNode3);
            newnode3.Nodes.Add(DBMchildNode4);
            TreeNode newnode4 = new TreeNode("FDD Setting");
            treeExplore.Nodes.Add(newnode4);
            TreeNode newnode5 = new TreeNode("EMS");
            treeExplore.Nodes.Add(newnode5);
        }
        public void closeTree()
        {         
            foreach (TreeNode tn in treeExplore.Nodes)
            {
                tn.Remove();
            }
        }
//         public TreeView solutionwindow   无用
//         {
//             get
//             {
//                 return this.treeExplore;
//             }
//         }
        public void saveTreeSolution(string path)
        {
            spath = path;

            doc.LoadXml("<APMCPrj></APMCPrj>");
            XmlNode root = doc.SelectSingleNode("APMCPrj");
            foreach (TreeNode tn in treeExplore.Nodes)
            {
                XmlElement Test = doc.CreateElement(tn.Text);
                root.AppendChild(Test);
                if (tn.Nodes != null)
                {
                    ChildNods(tn, Test);
                }
            }
            doc.Save(path);           
        }
         private void ChildNods(TreeNode ParentNode, XmlElement Test)
        {
            foreach (TreeNode tn in ParentNode.Nodes)
            {
                try
                {
                    XmlElement Ts = doc.CreateElement(tn.Text);
                    Test.AppendChild(Ts);
                    if (tn.Nodes != null)
                    {
                        ChildNods(tn, Ts);
                    }
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
              
            }
        }

         public void openTreeSolution(string path, Settingcontrol frm)
         {
             mainfrm = frm;
             treeExplore.Nodes.Clear();
             XmlDocument document = new XmlDataDocument();
             document.Load(path);
             foreach (XmlNode node in document.ChildNodes[0].ChildNodes)
             {
                 TreeNode tn = treeExplore.Nodes.Add(node.Name);
                 if (node.ChildNodes != null)
                 {
                     ChildNodes(node, tn);
                 }
             }
             treeExplore.ExpandAll();
         }
        private void ChildNodes(XmlNode ParentNode, TreeNode tvNode)
        {
            foreach (XmlNode no in ParentNode.ChildNodes)
            {
                TreeNode tn = tvNode.Nodes.Add(no.Name);
                //for form
                if (tn.Parent.Text.Equals("GraphicsEdition"))
                {
                    tn.ImageIndex = 0;
                    tn.SelectedImageIndex = 1;
                    if (mainfrm != null)
                    {
                        //mainfrm.OpenOneForm(no.Name);
                    }
                }
                //for control
                if (tn.Parent.Text.Equals("ControlStrategy"))
                {
                    tn.ImageIndex = 9;
                    tn.SelectedImageIndex = 3;
                    if (mainfrm != null)
                    {
                        //mainfrm.openControlForm(no.Name);
                    }
                }
                if (tn.Parent.Text.Equals("虚拟驱动"))
                {
                    tn.Parent.ImageIndex = 4;
                    tn.Parent.SelectedImageIndex = 4;
                    tn.ImageIndex = 5;
                    tn.SelectedImageIndex = 5;
                    //open device form
                    if (mainfrm != null)
                    {
                        //mainfrm.OpenDevForm(no.Name);
                    }
                }
                if (no.ChildNodes != null)
                {
                    ChildNodes(no, tn);
                }
            }
        }
    }
}
