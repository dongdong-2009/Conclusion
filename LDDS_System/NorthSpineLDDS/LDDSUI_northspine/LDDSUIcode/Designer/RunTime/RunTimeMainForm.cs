//运行时主界面，待美化 xuehaoyuan 
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
    public partial class RunTimeMainForm : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        RunTimeFormMng m_rtfm;
        private XmlDocument doc = new XmlDocument();
        public RunTimeMainForm(RunTimeFormMng rtfm)
        {
            InitializeComponent();
            this.toolStripStatusLabel1.Alignment = ToolStripItemAlignment.Right;
            m_rtfm = rtfm;
        }

        private void RunTimeMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            m_rtfm.Dispose();
            this.Dispose();
            
        }

        private void ToolStripControls_Click(object sender, EventArgs e)
        {
            this.ControlsDockPanel.Show();
            for (int i = 0; i < m_rtfm.editFormList.Count; i++)
            {
                m_rtfm.editFormList[i].Show();
            }
        }

        private void ToolStripAlarms_Click(object sender, EventArgs e)
        {
            this.ControlsDockPanel.Hide();
            for (int i = 0; i < m_rtfm.editFormList.Count; i++)
            {
                m_rtfm.editFormList[i].Hide();
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
