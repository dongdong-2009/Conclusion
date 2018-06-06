//临时载入的方法， 不用可删 xuehaoyuan
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Designer.DAQ
{
    public partial class DAQ :   WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public DAQ()
        {
            InitializeComponent();
            InitTree();
            this.treeExplore.MouseDoubleClick += new MouseEventHandler(treeExplore_MouseDoubleClick);
        
        }

        public void InitTree()
        {
            treeExplore.Nodes.Clear();
            TreeNode newnode1 = new TreeNode("DAQ configuration");
            treeExplore.Nodes.Add(newnode1);
            TreeNode newnode2 = new TreeNode("OPC configuration");
            treeExplore.Nodes.Add(newnode2);
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
                        case "DAQ configuration":
                            System.Diagnostics.Process.Start("..\\..\\..\\DAQ\\DAQ.exe"); 
                            break;
                    }
                }
            }

        }
    }
}
