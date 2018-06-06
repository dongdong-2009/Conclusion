using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Library.LDDS
{
    public partial class ArrowLink : Module
    {
        public ArrowLink()
        {
            InitializeComponent();
        }
        public enum dropList
        {
            WaterMixingArrow = 1,
            ThermistorArrow,
            VibTestingArrow,
            FlowtestingArrow,
            LengthArrow,
            HumidityArrow
        }
        private dropList operatorNum = dropList.WaterMixingArrow;
        /// <summary>
        /// 端口编号.
        /// </summary>
        [
            Browsable(true),
            DesignerSerializationVisibility(DesignerSerializationVisibility.Visible),
            Category("Porperty"),
            Description("Arrow Name."),
            DefaultValue(typeof(string), "0")
        ]
        public dropList ArrowName
        {
            get
            {
                return operatorNum;
            }
            set
            {
                if (value != null)
                {
                    operatorNum = value;
                    if (operatorNum.ToString() == "WaterMixingArrow")
                    {
                        this.BackgroundImage = Library.Properties.Resources.WaterMixingArrow_new;
                    }
                    else if (operatorNum.ToString() == "ThermistorArrow")
                    {
                        this.BackgroundImage = global::Library.Properties.Resources.ThermistorArrow;
                    }
                    else if (operatorNum.ToString() == "VibTestingArrow")
                    {
                        this.BackgroundImage = global::Library.Properties.Resources.VibTestingArrow;
                    }
                    else if (operatorNum.ToString() == "FlowtestingArrow")
                    {
                        this.BackgroundImage = global::Library.Properties.Resources.FlowTestingArrow_new;
                    }
                    else if (operatorNum.ToString() == "LengthArrow")
                    {
                        this.BackgroundImage = global::Library.Properties.Resources.LengthArrow;
                    }
                    else if (operatorNum.ToString() == "HumidityArrow")
                    {
                        this.BackgroundImage = global::Library.Properties.Resources.HumidityArrow;
                    }
                    this.Invalidate();
                }
            }
        }
    }
}
