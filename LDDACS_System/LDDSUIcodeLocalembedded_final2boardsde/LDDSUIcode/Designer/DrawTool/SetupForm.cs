using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Designer.DrawTool
{
    public partial class SetupForm : Form
    {
        private string _FirstForm = "";
        private List<string> formlist = null;
        public SetupForm()
        {
            InitializeComponent();
        }
        public void SetFormList(List<string> L)
        {
            formlist = L;
            if (formlist != null)
            {
                this.comboBox1.Items.Clear();
                foreach (string s in formlist)
                {
                    this.comboBox1.Items.Add(s);
                }

            }
        }
        public string FirstForm
        {
            get
            {
                return _FirstForm;
            }
            set
            {
                _FirstForm = value;
                //this.comboBox1.SelectedText = _FirstForm;
                int n = this.comboBox1.Items.Count;
                for (int i = 0; i < n; i++)
                {
                    if (this.comboBox1.Items[i].Equals(_FirstForm))
                    {
                        this.comboBox1.SelectedItem = this.comboBox1.Items[i];
                        break;
                    }
                }
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }

        private void comboBox1_DropDownClosed(object sender, EventArgs e)
        {
            int n = this.comboBox1.SelectedIndex;
            if (n >= 0)
            {
                _FirstForm = this.comboBox1.GetItemText(this.comboBox1.SelectedItem);
            }

        }

        private void SetupForm_Load(object sender, EventArgs e)
        {

        }
    }
}
