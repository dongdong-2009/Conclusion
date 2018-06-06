using System;
using System.Xml;
using System.Windows.Forms;
using Library;
using System.Collections.Generic;
using System.Drawing.Imaging;
using System.Drawing;

namespace ToolboxLibrary
{
	/// <summary>
	/// ToolboxXmlManager - Reads an XML file and populates the toolbox.
	/// </summary>
	public class ToolboxXmlManager
	{
		Toolbox m_toolbox = null;
        //basic
		private Type[] windowsFormsToolTypes = new Type[] {
			//typeof(Library.Lines),typeof(Library.Bezier),typeof(Library.Arc),typeof(Library.Polygon),typeof(Library.Ellipse),typeof(Library.Rectangles),typeof(Library.Pie),typeof(Library.RotaryImage)
		};
        //component
        private Type[] componentsToolTypes = new Type[] {typeof(Library.PictureBox), typeof(Library.TextBox), typeof(Library.Lable),typeof(Library.Lines)
			//typeof(Library.Button),typeof(Library.Lable),typeof(Library.PictureBox),typeof(Library.PictureBoxModel),typeof(Library.RadioButton),typeof(Library.RichTextBox),typeof(Library.TextBox)
		};
        //advanced
		private Type[] dataToolTypes = new Type[] {
			typeof(Library.AlarmList),typeof(Library.Date),typeof(Library.Led),typeof(Library.Scale),typeof(Library.Curve),typeof(Library.Switch),
		};
        private Type[] dataToolTypes1 = new Type[] {
			typeof(Library.Button)
		};

		public ToolboxXmlManager(Toolbox toolbox)
		{
			m_toolbox = toolbox;
		}

		public ToolboxTabCollection PopulateToolboxInfo()
		{
            
			try
			{
				if (Toolbox.FilePath == null || Toolbox.FilePath == "" || Toolbox.FilePath == String.Empty)
					return PopulateToolboxTabs();

				XmlDocument xmlDocument = new XmlDocument();
				xmlDocument.Load(Toolbox.FilePath);
				return PopulateToolboxTabs(xmlDocument);
			}
			catch(Exception ex)
			{
				MessageBox.Show("读取XML文件时发生错误.\n" + ex.ToString());
				return null;
			}
		}

		private Toolbox Toolbox
		{
			get
			{
				return m_toolbox;
			}
		}

		private ToolboxTabCollection PopulateToolboxTabs()
		{
			ToolboxTabCollection toolboxTabs = new ToolboxTabCollection();
			string[] tabNames = { Strings.WindowsForms, Strings.Components, Strings.Data, Strings.Data1};

			for (int i = 0; i < tabNames.Length; i++)
			{
				ToolboxTab toolboxTab = new ToolboxTab();
				toolboxTab.Name = tabNames[i];
				PopulateToolboxItems(toolboxTab);
				toolboxTabs.Add(toolboxTab);
			}

			return toolboxTabs;
		}
        
		private void PopulateToolboxItems(ToolboxTab toolboxTab)
		{
			if (toolboxTab == null)
				return;

			Type[] typeArray = null;

			switch (toolboxTab.Name)
			{
				case Strings.WindowsForms:
					typeArray = windowsFormsToolTypes;
					break;
				case Strings.Components:
					typeArray = componentsToolTypes;
					break;
                case Strings.Data:
                    typeArray = dataToolTypes;
                    break;
                case Strings.Data1:
                    typeArray = dataToolTypes1;
                    break;
				default:
					break;
			}

			ToolboxItemCollection toolboxItems = new ToolboxItemCollection();

			for (int i = 0; i < typeArray.Length; i++)
			{

                
				ToolboxItem toolboxItem = new ToolboxItem();
                
                toolboxItem.Type = typeArray[i];
                //toolboxItem.Type = typeList[0];
                toolboxItem.Name = typeArray[i].Name;
                //toolboxItem.Name = typeList[0].Name;
                toolboxItems.Add(toolboxItem);

			}

			toolboxTab.ToolboxItems = toolboxItems;
		}

		private ToolboxTabCollection PopulateToolboxTabs(XmlDocument xmlDocument)
		{
			if(xmlDocument==null)
				return null;

			XmlNode toolboxNode = xmlDocument.FirstChild;
			if(toolboxNode==null)
				return null;

			XmlNode tabCollectionNode = toolboxNode.FirstChild;
			if(tabCollectionNode==null)
				return null;

			XmlNodeList tabsNodeList = tabCollectionNode.ChildNodes;
			if(tabsNodeList==null)
				return null;

			ToolboxTabCollection toolboxTabs = new ToolboxTabCollection();

			foreach(XmlNode tabNode in tabsNodeList)
			{
				if(tabNode==null)
					continue;

				XmlNode propertiesNode = tabNode.FirstChild;
				if(propertiesNode==null)
					continue;

				XmlNode nameNode = propertiesNode[Strings.Name];
				if(nameNode==null)
					continue;

				ToolboxTab toolboxTab = new ToolboxTab();
				toolboxTab.Name = nameNode.InnerXml.ToString();
				PopulateToolboxItems(tabNode, toolboxTab);
				toolboxTabs.Add(toolboxTab);
			}
			if(toolboxTabs.Count==0)
				return null;

			return toolboxTabs;
		}

		private void PopulateToolboxItems(XmlNode tabNode, ToolboxTab toolboxTab)
		{
			if(tabNode==null)
				return;

			XmlNode toolboxItemCollectionNode = tabNode[Strings.ToolboxItemCollection];
			if(toolboxItemCollectionNode==null)
				return;

			XmlNodeList toolboxItemNodeList = toolboxItemCollectionNode.ChildNodes;
			if(toolboxItemNodeList==null)
				return;

			ToolboxItemCollection toolboxItems = new ToolboxItemCollection();

			foreach(XmlNode toolboxItemNode in toolboxItemNodeList)
			{
				if(toolboxItemNode==null)
					continue;

				XmlNode typeNode = toolboxItemNode[Strings.Type];
				if(typeNode==null)
					continue;

				bool found = false;
				System.Reflection.Assembly[] loadedAssemblies = System.AppDomain.CurrentDomain.GetAssemblies();
				for(int i=0; i<loadedAssemblies.Length && !found;i++)
				{
					System.Reflection.Assembly assembly = loadedAssemblies[i];
					System.Type[] types = assembly.GetTypes();
					for(int j=0;j<types.Length && !found;j++)
					{
						System.Type type = types[j];
						if(type.FullName == typeNode.InnerXml.ToString()) 
						{
							ToolboxItem toolboxItem = new ToolboxItem();
							toolboxItem.Type = type;
							toolboxItems.Add(toolboxItem);
							found = true;
						}
					}
				}
			}
			toolboxTab.ToolboxItems = toolboxItems;
			return;
		}

		private class Strings
		{
			public const string Toolbox = "Toolbox";
			public const string TabCollection = "TabCollection";
			public const string Tab = "Tab";
			public const string Properties = "Properties";
			public const string Name = "Name";
			public const string ToolboxItemCollection = "ToolboxItemCollection";
			public const string ToolboxItem = "ToolboxItem";
			public const string Type = "Type";
			public const string WindowsForms = "Sensors";
            public const string Components = "Chillers";
            public const string Data = "Heaters";
            public const string Data1 = "mHeaters";
			
		}

	}// class
}// namespace
