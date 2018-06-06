using System;
using System.Collections;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.ComponentModel.Design.Serialization;
using System.Drawing;
using System.Data;
using System.Windows.Forms;
using System.Diagnostics;
using System.Windows.Forms.Design;

namespace Host 
{
    /// <summary>
    /// Inherits from DesignSurface and hosts the RootComponent and 
    /// all other designers. It also uses loaders (BasicDesignerLoader
    /// or CodeDomDesignerLoader) when required. It also provides various
    /// services to the designers. Adds MenuCommandService which is used
    /// for Cut, Copy, Paste, etc.
    /// </summary>
	public class HostSurface : DesignSurface
	{
		private BasicDesignerLoader _loader;
		public ISelectionService _selectionService; 
        //lizheng add
        private UndoEngineExt _undoEngine = null;
        private DesignerSerializationServiceImpl _designerSerializationService = null;
        private CodeDomComponentSerializationService _codeDomComponentSerializationService = null;
        //
        IServiceContainer serviceProvider = null;
        DesignerOptionService opsService = null;

		public HostSurface() : base()
		{
            this.AddService(typeof(IMenuCommandService), new MenuCommandService(this));
		}
		public HostSurface(IServiceProvider parentProvider) : base(parentProvider)
		{
            this.AddService(typeof(IMenuCommandService), new MenuCommandService(this));
        }

		internal void Initialize()
		{

			Control control = null;
			IDesignerHost host = (IDesignerHost)this.GetService(typeof(IDesignerHost));

			if (host == null)
				return;

			try
			{
				// Set the backcolor
				Type hostType = host.RootComponent.GetType();
				if(hostType==typeof(Form))
				{
					control = this.View as Control;
					control.BackColor = Color.White;
				}
				else if (hostType == typeof(UserControl))
				{
					control = this.View as Control;
                    control.BackColor = Color.White;
                   
				}
				else if (hostType == typeof(Component))
				{
					control = this.View as Control;
					control.BackColor = Color.FloralWhite;
				}
				else
				{
					throw new Exception("Undefined Host Type: " + hostType.ToString());
				}

				// Set SelectionService - SelectionChanged event handler
				_selectionService = (ISelectionService)(this.ServiceContainer.GetService(typeof(ISelectionService)));
				//_selectionService.SelectionChanged += new EventHandler(selectionService_SelectionChanged);
			}
            catch (Exception ex)
            {
                Trace.WriteLine(ex.ToString());
            }
            //lizheng add
            //- 1. CodeDomComponentSerializationService
            _codeDomComponentSerializationService = new CodeDomComponentSerializationService(this.ServiceContainer);
            if (_codeDomComponentSerializationService != null)
            {
                //- the CodeDomComponentSerializationService is ready to be replaced
                this.ServiceContainer.RemoveService(typeof(ComponentSerializationService), false);
                this.ServiceContainer.AddService(typeof(ComponentSerializationService), _codeDomComponentSerializationService);

            }
            //- 2. IDesignerSerializationService
            _designerSerializationService = new DesignerSerializationServiceImpl(this.ServiceContainer);
            if (_designerSerializationService != null)
            {
                //- the IDesignerSerializationService is ready to be replaced
                this.ServiceContainer.RemoveService(typeof(IDesignerSerializationService), false);
                this.ServiceContainer.AddService(typeof(IDesignerSerializationService), _designerSerializationService);
            }
            //
            //- 3. UndoEngine
            _undoEngine = new UndoEngineExt(this.ServiceContainer);
            //- disable the UndoEngine
            _undoEngine.Enabled = false;
            if (_undoEngine != null)
            {
                //- the UndoEngine is ready to be replaced
                this.ServiceContainer.RemoveService(typeof(UndoEngine), false);
                this.ServiceContainer.AddService(typeof(UndoEngine), _undoEngine);
            }
            _undoEngine.Enabled = true;

            //xhy
//             serviceProvider = this.GetService(typeof(IServiceContainer)) as IServiceContainer;
//             opsService = serviceProvider.GetService(typeof(DesignerOptionService)) as DesignerOptionService;
//             if (null != opsService)
//             {
//                 serviceProvider.RemoveService(typeof(DesignerOptionService));
//             }
//             DesignerOptionService opsService2 = new DesignerOptionServiceExt4NoGuides();
//             serviceProvider.AddService(typeof(DesignerOptionService), opsService2);
        }

		public BasicDesignerLoader Loader
		{
			get
			{
				return _loader;
			}
			set
			{
				_loader = value;
			}
		}


        public void UseSnapLines()
        {
            IServiceContainer serviceProvider = this.GetService(typeof(IServiceContainer)) as IServiceContainer;
            DesignerOptionService opsService = serviceProvider.GetService(typeof(DesignerOptionService)) as DesignerOptionService;
            if (null != opsService)
            {
                serviceProvider.RemoveService(typeof(DesignerOptionService));
            }
            DesignerOptionService opsService2 = new DesignerOptionServiceExt4SnapLines();
            serviceProvider.AddService(typeof(DesignerOptionService), opsService2);
        }

        public void UseGrid(Size gridSize)
        {
            IServiceContainer serviceProvider = this.GetService(typeof(IServiceContainer)) as IServiceContainer;
            DesignerOptionService opsService = serviceProvider.GetService(typeof(DesignerOptionService)) as DesignerOptionService;
            if (null != opsService)
            {
                serviceProvider.RemoveService(typeof(DesignerOptionService));
            }
            DesignerOptionService opsService2 = new DesignerOptionServiceExt4Grid(gridSize);
            serviceProvider.AddService(typeof(DesignerOptionService), opsService2);
        }

        public void UseGridWithoutSnapping(Size gridSize)
        {
            IServiceContainer serviceProvider = this.GetService(typeof(IServiceContainer)) as IServiceContainer;
            DesignerOptionService opsService = serviceProvider.GetService(typeof(DesignerOptionService)) as DesignerOptionService;
            if (null != opsService)
            {
                serviceProvider.RemoveService(typeof(DesignerOptionService));
            }
            DesignerOptionService opsService2 = new DesignerOptionServiceExt4GridWithoutSnapping(gridSize);
            serviceProvider.AddService(typeof(DesignerOptionService), opsService2);
        }

        public void UseNoGuides()
        {
            serviceProvider = this.GetService(typeof(IServiceContainer)) as IServiceContainer;
            opsService = serviceProvider.GetService(typeof(DesignerOptionService)) as DesignerOptionService;
            if (null != opsService)
            {
                serviceProvider.RemoveService(typeof(DesignerOptionService));
            }
            DesignerOptionService opsService2 = new DesignerOptionServiceExt4NoGuides();
            serviceProvider.AddService(typeof(DesignerOptionService), opsService2);
        }
		/// <summary>
        /// When the selection changes this sets the PropertyGrid's selected component 
		/// </summary>
        /*     private void selectionService_SelectionChanged(object sender, EventArgs e)
             {
                 if (_selectionService != null)
                 {
                     ICollection selectedComponents = _selectionService.GetSelectedComponents();
                     PropertyGrid propertyGrid = (PropertyGrid)this.GetService(typeof(PropertyGrid));


                     object[] comps = new object[selectedComponents.Count];
                     int i = 0;

                     foreach (Object o in selectedComponents)
                     {
                         comps[i] = o;
                         i++;
                     }
                     //lizheng add
                     propertyGrid.SelectedObjects = comps;
                 }
             }
             */
        public void AddService(Type type, object serviceInstance)
		{
			this.ServiceContainer.AddService(type, serviceInstance);
		}
	}// class

    //实现显示取消网格的内部类   xuehaoyuan 2015 12
    internal class DesignerOptionServiceExt4Grid : DesignerOptionService
    {
        private System.Drawing.Size _gridSize;

        public DesignerOptionServiceExt4Grid(System.Drawing.Size gridSize) : base() { _gridSize = gridSize; }

        protected override void PopulateOptionCollection(DesignerOptionCollection options)
        {
            if (null != options.Parent) return;

            DesignerOptions ops = new DesignerOptions();
            ops.GridSize = _gridSize;
            ops.SnapToGrid = true;
            ops.ShowGrid = true;
            ops.UseSnapLines = false;
            ops.UseSmartTags = true;
            DesignerOptionCollection wfd = this.CreateOptionCollection(options, "WindowsFormsDesigner", null);
            this.CreateOptionCollection(wfd, "General", ops);
        }
    }//end_class


    internal class DesignerOptionServiceExt4NoGuides : DesignerOptionService
    {
        public DesignerOptionServiceExt4NoGuides() : base() { }

        protected override void PopulateOptionCollection(DesignerOptionCollection options)
        {
            if (null != options.Parent) return;

            DesignerOptions ops = new DesignerOptions();
            ops.GridSize = new System.Drawing.Size(8, 8);
            ops.SnapToGrid = false;
            ops.ShowGrid = false;
            ops.UseSnapLines = false;
            ops.UseSmartTags = true;
            DesignerOptionCollection wfd = this.CreateOptionCollection(options, "WindowsFormsDesigner", null);
            this.CreateOptionCollection(wfd, "General", ops);
        }
    }//end_class

    internal class DesignerOptionServiceExt4SnapLines : DesignerOptionService
    {
        public DesignerOptionServiceExt4SnapLines() : base() { }

        protected override void PopulateOptionCollection(DesignerOptionCollection options)
        {
            if (null != options.Parent) return;

            DesignerOptions ops = new DesignerOptions();
            ops.UseSnapLines = true;
            ops.UseSmartTags = true;
            DesignerOptionCollection wfd = this.CreateOptionCollection(options, "WindowsFormsDesigner", null);
            this.CreateOptionCollection(wfd, "General", ops);
        }
    }//end_class


    internal class DesignerOptionServiceExt4GridWithoutSnapping : DesignerOptionService
    {
        private System.Drawing.Size _gridSize;

        public DesignerOptionServiceExt4GridWithoutSnapping(System.Drawing.Size gridSize) : base() { _gridSize = gridSize; }

        protected override void PopulateOptionCollection(DesignerOptionCollection options)
        {
            if (null != options.Parent) return;

            DesignerOptions ops = new DesignerOptions();
            ops.GridSize = _gridSize;
            ops.SnapToGrid = false;
            ops.ShowGrid = true;
            ops.UseSnapLines = false;
            ops.UseSmartTags = true;
            DesignerOptionCollection wfd = this.CreateOptionCollection(options, "WindowsFormsDesigner", null);
            this.CreateOptionCollection(wfd, "General", ops);
        }
    }//end_class

}// namespace
