//运行时载入组件的form，此form嵌入到运行时主界面的panel中  xuehaoyuan
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Designer.RunTime
{
    public partial class RunTimeForm : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public RunTimeFormMng m_rtfm;
        public string currentName = "";
        public RunTimeForm(RunTimeFormMng rtfm)
        {
            InitializeComponent();
            m_rtfm = rtfm;
        }
        public RunTimeFormMng parentForm = null;

        private void RunTimeEditForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            m_rtfm.editFormList.Remove(this);
            this.parentForm.FormDispose(currentName);
            this.parentForm.Close();
        }
    }
}
