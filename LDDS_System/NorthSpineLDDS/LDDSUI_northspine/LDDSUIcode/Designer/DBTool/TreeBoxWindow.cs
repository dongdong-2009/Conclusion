//====================================================================
// 文件名: TreeBoxWindow.cs
//
// 文件描述:
// ------------------------------------------------------------------
// DBTOOL左侧树状菜单栏
// ------------------------------------------------------------------
// 
// 时间: 2015.07
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
using System.IO;
using System.Reflection;
using System.Data.SqlClient;

using Silver.UI;

namespace Designer.DBTool
{
    public partial class TreeBoxWindow : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        private List<boardType> btDeCoilCwList ;
        private List<boardType> btDeNoCoilCwList ;
        private List<boardType> btDeCoilHpList ;
        private List<boardType> btDeNoCoilHpList ;

        private List<boardType> btReAdjHwList ;
        private List<boardType> btReNoAdjHwList ;
        private List<boardType> btReAdjHpList ;
        private List<boardType> btReNoAdjHpList ;

        #region 树状图变量
        private String[] TabName = new String[]
        {
            "Dehumidifer",  "Regenerator"
        };
        private String[] deType = new String[]
        {
            "ChilledWater With Coil","ChilledWater Without Coil", "HeatPump With Coil","HeatPump Without Coil"
        };
        private String[] reType = new String[]
        {
             "HotWater Adjustable","HotWater UnAdjustable", "HeatPump Adjustable","HeatPump UnAdjustable"

        };
        public TreeView treeView = null;
        public TreeView treeView1 = null;

        #endregion 树状图变量

        public TreeBoxWindow(MainForm mf)
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

            this.treeBox.SetImageList(GetImage("ToolBox_Small.bmp"), new Size(16, 16), Color.Magenta, true);
            this.treeBox.SetImageList(GetImage("ToolBox_Large.bmp"), new Size(32, 32), Color.Magenta, false);

            TreeBoxInit();

            
    }
        #region 树状图显示方法
        public void TreeBoxInit()
        {
            ToolBoxTabCollection tabCollection = new ToolBoxTabCollection();
            //增加tab

            for (int i = 0; i < TabName.Count(); i++)
            {
                this.treeBox.AddTab(TabName[i], 1);
                ToolBoxTab tab = this.treeBox[i];
                tabCollection.Add(tab);
            }

            treeView = new TreeView();
            treeView.BorderStyle = BorderStyle.None;
            treeView.Dock = DockStyle.Fill;
            treeView.ImageList = imageList1;
       
            for (int i = 0; i < deType.Count(); i++)
            {
                FillTreeView(treeView, deType[i], i);
                this.treeBox[0].Control = treeView;
            }

            treeView1 = new TreeView();
            treeView1.BorderStyle = BorderStyle.None;
            treeView1.Dock = DockStyle.Fill;

            treeView1.ImageList = imageList1;

            for (int i = 0; i < reType.Count(); i++)
            {
                FillTreeView(treeView1, reType[i], i);
                this.treeBox[1].Control = treeView1;
            }

        }

        private void FillTreeView(TreeView t, String NodeHead, int num)
        {
        
            t.Nodes.Add(NodeHead);
            t.ExpandAll();

            //设置显示图标
                       
            switch (NodeHead)
            {
                case  "ChilledWater With Coil":
                    for (int i = 0; i < btDeCoilCwList.Count(); i++)
                    {
                         t.Nodes[num].Nodes.Add(btDeCoilCwList[i].boardNumber);
                         t.Nodes[num].Nodes[i].ImageIndex = 0;
                         t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case  "ChilledWater Without Coil":
                    for (int i = 0; i < btDeNoCoilCwList.Count(); i++)
                    {
                        t.Nodes[num].Nodes.Add(btDeNoCoilCwList[i].boardNumber);
                        t.Nodes[num].Nodes[i].ImageIndex = 0;
                        t.Nodes[num].Nodes[i].SelectedImageIndex = 1;
                    }
                    break;
                case   "HeatPump With Coil":
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

        #region listicon方法
        public static Image GetImage(string resouceName)
        {
            Image image = null;
            Stream stream = null;
            try
            {
                stream = GetResource("DBtool.ListIcons." + resouceName);
                image = Image.FromStream(stream);
            }
            catch (Exception)
            {
                image = null;
            }
            return image;
        }
        public static Stream GetResource(string resourceName)
        {
            Stream stream = null;
            try
            {
                Assembly asm = Assembly.GetExecutingAssembly();
                stream = asm.GetManifestResourceStream("iDBTool.Resources." + resourceName);
            }
            catch (Exception)
            {
                stream = null;
            }
            return stream;
        }
        #endregion listicon方法
        #endregion 树状图显示方法
    }
}
