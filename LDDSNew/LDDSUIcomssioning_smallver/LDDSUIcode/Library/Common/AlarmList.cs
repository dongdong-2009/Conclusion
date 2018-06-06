using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace Library
{
    [ToolboxBitmap(typeof(AlarmList))]
    public partial class AlarmList : UserControl
    {
        public AlarmList()
        {
            InitializeComponent();
            SetStyle(ControlStyles.UserPaint |
                    ControlStyles.DoubleBuffer |
                    ControlStyles.ResizeRedraw |
                    ControlStyles.AllPaintingInWmPaint |
                    ControlStyles.SupportsTransparentBackColor,
                    true);
           // AddToList("123", "aaa", "45678", "ttttt", "alarm", true);
           // AddToList("123", "aaa", "45678", "ttttt", "alarm", false);
        }
       // public Color _backcolor = Color.Wheat;
        public Color AlarmBackColor 
        {
            get{
                return this.listView1.BackColor;
            }
            set
            {
                this.listView1.BackColor = value;
                this.Invalidate();
            }
        }
        public Color AlarmForeColor
        {
            get
            {
                return this.listView1.ForeColor;
            }
            set
            {
                this.listView1.ForeColor = value;
                this.Invalidate();
            }
        }
        public void AddToList(string id,string name,string timestamp,string discribe,string stype,bool bAlarm)
        {
            if (bAlarm)
            {
                int count=listView1.Items.Count;
                for(int i=0;i<count;i++)
                {
                    string curid = listView1.Items[i].SubItems[0].Text;
                    if (curid.Equals(id))
                    {
                        return;
                    }
                }
                ListViewItem li = new ListViewItem();
                li.SubItems[0].Text = id;
                li.SubItems.Add(name);
                li.SubItems.Add(timestamp);
                li.SubItems.Add(discribe);
                li.SubItems.Add(stype);
                listView1.Items.Add(li);
                //listView1.Invalidate();
            }
            else
            {
                int count = listView1.Items.Count;
                for (int i = 0; i < count; i++)
                {
                    string curid = listView1.Items[i].SubItems[0].Text;
                    if (curid.Equals(id))
                    {
                        listView1.Items.Remove(listView1.Items[i]);
                        break; 
                        //listView1.Invalidate(); 
                    }
                }
            }
            
        }

        private void listView1_Resize(object sender, EventArgs e)
        {
            listView1.ClientSize = this.ClientSize;
        }
    }
}
