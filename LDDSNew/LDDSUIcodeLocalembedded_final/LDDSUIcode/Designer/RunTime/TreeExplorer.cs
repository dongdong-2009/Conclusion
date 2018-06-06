//运行时界面主界面的属性目录， 目前实现的功能只是根据xml文件解析出的内容，显示各个页面的名称，双击名称，打开界面xuehaoyuan
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace Designer.RunTime
{
    public partial class TreeExplorer : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        private string spath;
        private RunTimeFormMng m_rfm;
        private XmlDocument doc = new XmlDocument();
        public TreeNode newnode1;
        private List<boardType> btDeCoilCwList;
        private List<boardType> btDeNoCoilCwList;
        private List<boardType> btDeCoilHpList;
        private List<boardType> btDeNoCoilHpList;

        private List<boardType> btReAdjHwList;
        private List<boardType> btReNoAdjHwList;
        private List<boardType> btReAdjHpList;
        private List<boardType> btReNoAdjHpList;

        private String[] deType = new String[]
        {
            "ChilledWater With Coil","ChilledWater Without Coil", "HeatPump With Coil","HeatPump Without Coil"
        };
        private String[] reType = new String[]
        {
             "HotWater Adjustable","HotWater UnAdjustable", "HeatPump Adjustable","HeatPump UnAdjustable"
        };

        public TreeExplorer(string path,MainForm mf, RunTimeFormMng mrtf)
        {

            InitializeComponent();

            btDeCoilCwList = mf.btDeCoilCwList;
            btDeNoCoilCwList = mf.btDeNoCoilCwList;
            btDeCoilHpList = mf.btDeCoilHpList;
            btDeNoCoilHpList = mf.btDeNoCoilHpList;
            btReAdjHwList = mf.btReAdjHwList;
            btReNoAdjHwList = mf.btReNoAdjHwList;
            btReAdjHpList = mf.btReAdjHpList;
            btReNoAdjHpList = mf.btReNoAdjHpList;

            InitTree();
            m_rfm = mrtf;
            spath = path;
         //   m_rfm = mf;
            this.solutionwindow.MouseClick += new MouseEventHandler(Solutionwindow_MouseClick);
            this.solutionwindow.MouseDoubleClick += new MouseEventHandler(Solutionwindow_MouseDoubleClick);
        }

        public void InitTree()
        {
            int cnt=0;
            treeExploreView.Nodes.Clear();

            treeExploreView.BorderStyle = BorderStyle.None;
            treeExploreView.Dock = DockStyle.Fill;
          

            for ( int i = 0; i < deType.Count(); i++)
            {

                FillTreeView(treeExploreView, deType[i], i);
                cnt++;
           
            }

            for (int i = 0; i < reType.Count(); i++)
            {
           
                FillTreeView(treeExploreView, reType[i], cnt);
                cnt++;
            }

        }
        public void CloseTree()
        {
            foreach (TreeNode tn in treeExploreView.Nodes)
            {
                if (tn == null)
                    continue;
                else
                    tn.Remove();
            }
        }
        public TreeView solutionwindow
        {
            get
            {
                return this.treeExploreView;
            }
        }

        public void OpenTreeSolution(RunTimeFormMng rfm)
        {

            treeExploreView.ExpandAll();
        }

        private void ChildNodes(XmlNode ParentNode, TreeNode tvNode)
        {
            foreach (XmlNode no in ParentNode.ChildNodes)
            {
                TreeNode tn = tvNode.Nodes.Add(no.Name);
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
        #region 工程树事件
        //工程树鼠标点击事件处理
        public void Solutionwindow_MouseClick(object sender, MouseEventArgs e)
        {
            if (spath == "")
                return;
            if (e.Button == MouseButtons.Right)//判断你点的是不是右键
            {
                Point ClickPoint = new Point(e.X, e.Y);
                TreeNode CurrentNode = this.solutionwindow.GetNodeAt(ClickPoint);
            }
            if (MouseButtons.Left == e.Button)
            {
                Point ClickPoint = new Point(e.X, e.Y);
                TreeNode CurrentNode = this.solutionwindow.GetNodeAt(ClickPoint);
                if (CurrentNode != null)//判断你点的是不是一个节点
                {
                    this.solutionwindow.SelectedNode = CurrentNode;
                }
            }
        }

        public void Solutionwindow_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)//判断你点的是left键
            {
                Point ClickPoint = new Point(e.X, e.Y);
                TreeNode CurrentNode = this.solutionwindow.GetNodeAt(ClickPoint);
                if (CurrentNode != null)//判断你点的是不是一个节点
                {
                    this.solutionwindow.SelectedNode = CurrentNode;//选中这个节点
                    TreeItemLookUp_Click();
                }
            }
        }
        private void TreeItemLookUp_Click()
        {
            string formname = this.solutionwindow.SelectedNode.Text;
            if (this.solutionwindow.SelectedNode== null)
                return;
            if (this.solutionwindow.SelectedNode.Text.Length == 8)
            {
                m_rfm.OpenOneForm(formname);
                
            }
        }
        #endregion
    }
}
