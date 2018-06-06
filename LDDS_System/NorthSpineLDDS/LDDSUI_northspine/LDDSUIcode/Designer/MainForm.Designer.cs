namespace Designer
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.MainMenu = new System.Windows.Forms.MenuStrip();
            this.文件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新建ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.视图ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ModuleBoxStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PropertyWindowStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dBConnectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dataBaseWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bindWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.编辑ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dataBaseEditToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.firstFormToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dBToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.drawToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolBoxStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ImageFormStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.showToolstripToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DrawToolStrip = new System.Windows.Forms.ToolStrip();
            this.NewButton = new System.Windows.Forms.ToolStripButton();
            this.OpenButton = new System.Windows.Forms.ToolStripButton();
            this.SaveButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.UndoButton = new System.Windows.Forms.ToolStripButton();
            this.RedoButton = new System.Windows.Forms.ToolStripButton();
            this.DeleteButton = new System.Windows.Forms.ToolStripButton();
            this.selectAllButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.BringForwardButton = new System.Windows.Forms.ToolStripButton();
            this.SendBackwardButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.LeftButton = new System.Windows.Forms.ToolStripButton();
            this.RightButton = new System.Windows.Forms.ToolStripButton();
            this.UpButton = new System.Windows.Forms.ToolStripButton();
            this.DownButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.MirrorRL = new System.Windows.Forms.ToolStripButton();
            this.MirrorUD = new System.Windows.Forms.ToolStripButton();
            this.ArrangeButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.tunButton = new System.Windows.Forms.ToolStripButton();
            this.BuildButton = new System.Windows.Forms.ToolStripButton();
            this.dockPanel1 = new WeifenLuo.WinFormsUI.Docking.DockPanel();
            this.ContextMenuStripNew = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.MenuItemNew = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItemLoad = new System.Windows.Forms.ToolStripMenuItem();
            this.ContextMenuLook = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.MenuItemLookUp = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItemDelete = new System.Windows.Forms.ToolStripMenuItem();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.MainMenu.SuspendLayout();
            this.DrawToolStrip.SuspendLayout();
            this.ContextMenuStripNew.SuspendLayout();
            this.ContextMenuLook.SuspendLayout();
            this.SuspendLayout();
            // 
            // MainMenu
            // 
            this.MainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件ToolStripMenuItem,
            this.视图ToolStripMenuItem,
            this.编辑ToolStripMenuItem,
            this.toolsToolStripMenuItem,
            this.windowToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.MainMenu.Location = new System.Drawing.Point(0, 0);
            this.MainMenu.Name = "MainMenu";
            this.MainMenu.Size = new System.Drawing.Size(784, 24);
            this.MainMenu.TabIndex = 0;
            this.MainMenu.Text = "menuStrip1";
            // 
            // 文件ToolStripMenuItem
            // 
            this.文件ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建ToolStripMenuItem,
            this.打开ToolStripMenuItem,
            this.保存ToolStripMenuItem,
            this.退出ToolStripMenuItem});
            this.文件ToolStripMenuItem.Name = "文件ToolStripMenuItem";
            this.文件ToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.文件ToolStripMenuItem.Text = "File";
            // 
            // 新建ToolStripMenuItem
            // 
            this.新建ToolStripMenuItem.Image = global::Designer.Properties.Resources.folder_new_5;
            this.新建ToolStripMenuItem.Name = "新建ToolStripMenuItem";
            this.新建ToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.新建ToolStripMenuItem.Text = "New Project";
            this.新建ToolStripMenuItem.Click += new System.EventHandler(this.NewProject_Click);
            // 
            // 打开ToolStripMenuItem
            // 
            this.打开ToolStripMenuItem.Image = global::Designer.Properties.Resources.folder_open_3;
            this.打开ToolStripMenuItem.Name = "打开ToolStripMenuItem";
            this.打开ToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.打开ToolStripMenuItem.Text = "Open Project";
            this.打开ToolStripMenuItem.Click += new System.EventHandler(this.Open_Click);
            // 
            // 保存ToolStripMenuItem
            // 
            this.保存ToolStripMenuItem.Image = global::Designer.Properties.Resources.document_save_5;
            this.保存ToolStripMenuItem.Name = "保存ToolStripMenuItem";
            this.保存ToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.保存ToolStripMenuItem.Text = "Save";
            // 
            // 退出ToolStripMenuItem
            // 
            this.退出ToolStripMenuItem.Image = global::Designer.Properties.Resources.application_exit;
            this.退出ToolStripMenuItem.Name = "退出ToolStripMenuItem";
            this.退出ToolStripMenuItem.Size = new System.Drawing.Size(143, 22);
            this.退出ToolStripMenuItem.Text = "Exit";
            this.退出ToolStripMenuItem.Click += new System.EventHandler(this.退出ToolStripMenuItem_Click);
            // 
            // 视图ToolStripMenuItem
            // 
            this.视图ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ModuleBoxStripMenuItem,
            this.PropertyWindowStripMenuItem,
            this.dBConnectToolStripMenuItem,
            this.dataBaseWindowToolStripMenuItem,
            this.bindWindowToolStripMenuItem});
            this.视图ToolStripMenuItem.Name = "视图ToolStripMenuItem";
            this.视图ToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.视图ToolStripMenuItem.Text = "View";
            // 
            // ModuleBoxStripMenuItem
            // 
            this.ModuleBoxStripMenuItem.Name = "ModuleBoxStripMenuItem";
            this.ModuleBoxStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.ModuleBoxStripMenuItem.Text = "ModuleBox";
            this.ModuleBoxStripMenuItem.Click += new System.EventHandler(this.ModuleBoxStripMenuItem_Click);
            // 
            // PropertyWindowStripMenuItem
            // 
            this.PropertyWindowStripMenuItem.Name = "PropertyWindowStripMenuItem";
            this.PropertyWindowStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.PropertyWindowStripMenuItem.Text = "PropertyWindow";
            this.PropertyWindowStripMenuItem.Click += new System.EventHandler(this.PropertyWindowStripMenuItem_Click);
            // 
            // dBConnectToolStripMenuItem
            // 
            this.dBConnectToolStripMenuItem.Name = "dBConnectToolStripMenuItem";
            this.dBConnectToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.dBConnectToolStripMenuItem.Text = "DBConnect";
            this.dBConnectToolStripMenuItem.Click += new System.EventHandler(this.dBConnectToolStripMenuItem_Click);
            // 
            // dataBaseWindowToolStripMenuItem
            // 
            this.dataBaseWindowToolStripMenuItem.Name = "dataBaseWindowToolStripMenuItem";
            this.dataBaseWindowToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.dataBaseWindowToolStripMenuItem.Text = "DataBaseWindow";
            // 
            // bindWindowToolStripMenuItem
            // 
            this.bindWindowToolStripMenuItem.Name = "bindWindowToolStripMenuItem";
            this.bindWindowToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.bindWindowToolStripMenuItem.Text = "BindWindow";
            this.bindWindowToolStripMenuItem.Click += new System.EventHandler(this.bindWindowToolStripMenuItem_Click);
            // 
            // 编辑ToolStripMenuItem
            // 
            this.编辑ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dataBaseEditToolStripMenuItem,
            this.firstFormToolStripMenuItem});
            this.编辑ToolStripMenuItem.Name = "编辑ToolStripMenuItem";
            this.编辑ToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.编辑ToolStripMenuItem.Text = "Edit";
            // 
            // dataBaseEditToolStripMenuItem
            // 
            this.dataBaseEditToolStripMenuItem.Name = "dataBaseEditToolStripMenuItem";
            this.dataBaseEditToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.dataBaseEditToolStripMenuItem.Text = "DataBaseEdit";
            this.dataBaseEditToolStripMenuItem.Click += new System.EventHandler(this.dataBaseEditToolStripMenuItem_Click);
            // 
            // firstFormToolStripMenuItem
            // 
            this.firstFormToolStripMenuItem.Name = "firstFormToolStripMenuItem";
            this.firstFormToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.firstFormToolStripMenuItem.Text = "FirstForm";
            this.firstFormToolStripMenuItem.Click += new System.EventHandler(this.firstFormToolStripMenuItem_Click);
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
            this.toolsToolStripMenuItem.Text = "Tools";
            // 
            // windowToolStripMenuItem
            // 
            this.windowToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dBToolStripMenuItem,
            this.drawToolStripMenuItem});
            this.windowToolStripMenuItem.Name = "windowToolStripMenuItem";
            this.windowToolStripMenuItem.Size = new System.Drawing.Size(63, 20);
            this.windowToolStripMenuItem.Text = "Window";
            // 
            // dBToolStripMenuItem
            // 
            this.dBToolStripMenuItem.Name = "dBToolStripMenuItem";
            this.dBToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.dBToolStripMenuItem.Text = "DataBaseEdit";
            this.dBToolStripMenuItem.Click += new System.EventHandler(this.dBToolStripMenuItem_Click);
            // 
            // drawToolStripMenuItem
            // 
            this.drawToolStripMenuItem.Name = "drawToolStripMenuItem";
            this.drawToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.drawToolStripMenuItem.Text = "Draw";
            this.drawToolStripMenuItem.Click += new System.EventHandler(this.drawToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // ToolBoxStripMenuItem
            // 
            this.ToolBoxStripMenuItem.Name = "ToolBoxStripMenuItem";
            this.ToolBoxStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.ToolBoxStripMenuItem.Text = "ToolBox";
            this.ToolBoxStripMenuItem.Click += new System.EventHandler(this.ToolBoxStripMenuItem_Click);
            // 
            // ImageFormStripMenuItem
            // 
            this.ImageFormStripMenuItem.Name = "ImageFormStripMenuItem";
            this.ImageFormStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // showToolstripToolStripMenuItem
            // 
            this.showToolstripToolStripMenuItem.Name = "showToolstripToolStripMenuItem";
            this.showToolstripToolStripMenuItem.Size = new System.Drawing.Size(178, 22);
            this.showToolstripToolStripMenuItem.Text = "ShowToolstrip";
            this.showToolstripToolStripMenuItem.Click += new System.EventHandler(this.showToolstripToolStripMenuItem_Click);
            // 
            // DrawToolStrip
            // 
            this.DrawToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NewButton,
            this.OpenButton,
            this.SaveButton,
            this.toolStripSeparator1,
            this.UndoButton,
            this.RedoButton,
            this.DeleteButton,
            this.selectAllButton,
            this.toolStripSeparator2,
            this.BringForwardButton,
            this.SendBackwardButton,
            this.toolStripSeparator3,
            this.LeftButton,
            this.RightButton,
            this.UpButton,
            this.DownButton,
            this.toolStripSeparator4,
            this.MirrorRL,
            this.MirrorUD,
            this.ArrangeButton,
            this.toolStripSeparator5,
            this.tunButton,
            this.BuildButton});
            this.DrawToolStrip.Location = new System.Drawing.Point(0, 24);
            this.DrawToolStrip.Name = "DrawToolStrip";
            this.DrawToolStrip.Size = new System.Drawing.Size(784, 25);
            this.DrawToolStrip.TabIndex = 1;
            this.DrawToolStrip.Text = "toolStrip1";
            // 
            // NewButton
            // 
            this.NewButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.NewButton.Image = global::Designer.Properties.Resources.folder_new_5;
            this.NewButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.NewButton.Name = "NewButton";
            this.NewButton.Size = new System.Drawing.Size(23, 22);
            this.NewButton.Text = "New";
            this.NewButton.Click += new System.EventHandler(this.NewButton_Click);
            // 
            // OpenButton
            // 
            this.OpenButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.OpenButton.Image = global::Designer.Properties.Resources.folder_open_3;
            this.OpenButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.OpenButton.Name = "OpenButton";
            this.OpenButton.Size = new System.Drawing.Size(23, 22);
            this.OpenButton.Text = "Open";
            this.OpenButton.Click += new System.EventHandler(this.Open_Click);
            // 
            // SaveButton
            // 
            this.SaveButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.SaveButton.Image = global::Designer.Properties.Resources.document_save_5;
            this.SaveButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(23, 22);
            this.SaveButton.Text = "Save";
            this.SaveButton.Click += new System.EventHandler(this.Save_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // UndoButton
            // 
            this.UndoButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.UndoButton.Image = global::Designer.Properties.Resources.edit_undo_8;
            this.UndoButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.UndoButton.Name = "UndoButton";
            this.UndoButton.Size = new System.Drawing.Size(23, 22);
            this.UndoButton.Text = "Undo";
            this.UndoButton.Click += new System.EventHandler(this.UndoButton_Click);
            // 
            // RedoButton
            // 
            this.RedoButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.RedoButton.Image = global::Designer.Properties.Resources.edit_redo_8;
            this.RedoButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.RedoButton.Name = "RedoButton";
            this.RedoButton.Size = new System.Drawing.Size(23, 22);
            this.RedoButton.Text = "Redo";
            this.RedoButton.Click += new System.EventHandler(this.RedoButton_Click);
            // 
            // DeleteButton
            // 
            this.DeleteButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.DeleteButton.Image = global::Designer.Properties.Resources.edit_delete_6;
            this.DeleteButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.DeleteButton.Name = "DeleteButton";
            this.DeleteButton.Size = new System.Drawing.Size(23, 22);
            this.DeleteButton.Text = "Delete";
            this.DeleteButton.Click += new System.EventHandler(this.DeleteButton_Click);
            // 
            // selectAllButton
            // 
            this.selectAllButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.selectAllButton.Image = global::Designer.Properties.Resources.select_rectangular;
            this.selectAllButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.selectAllButton.Name = "selectAllButton";
            this.selectAllButton.Size = new System.Drawing.Size(23, 22);
            this.selectAllButton.Text = "SelectAll";
            this.selectAllButton.Click += new System.EventHandler(this.selectAllButton_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // BringForwardButton
            // 
            this.BringForwardButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BringForwardButton.Image = global::Designer.Properties.Resources.layer_forward;
            this.BringForwardButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BringForwardButton.Name = "BringForwardButton";
            this.BringForwardButton.Size = new System.Drawing.Size(23, 22);
            this.BringForwardButton.Text = "BringForward";
            this.BringForwardButton.Click += new System.EventHandler(this.BringForwardButton_Click);
            // 
            // SendBackwardButton
            // 
            this.SendBackwardButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.SendBackwardButton.Image = global::Designer.Properties.Resources.layer_backward;
            this.SendBackwardButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.SendBackwardButton.Name = "SendBackwardButton";
            this.SendBackwardButton.Size = new System.Drawing.Size(23, 22);
            this.SendBackwardButton.Text = "SendBackward";
            this.SendBackwardButton.Click += new System.EventHandler(this.SendBackwardButton_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // LeftButton
            // 
            this.LeftButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.LeftButton.Image = global::Designer.Properties.Resources.distribute_horizontal_left;
            this.LeftButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.LeftButton.Name = "LeftButton";
            this.LeftButton.Size = new System.Drawing.Size(23, 22);
            this.LeftButton.Text = "Left";
            this.LeftButton.Click += new System.EventHandler(this.LeftButton_Click);
            // 
            // RightButton
            // 
            this.RightButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.RightButton.Image = global::Designer.Properties.Resources.distribute_horizontal_right;
            this.RightButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.RightButton.Name = "RightButton";
            this.RightButton.Size = new System.Drawing.Size(23, 22);
            this.RightButton.Text = "Right";
            this.RightButton.Click += new System.EventHandler(this.RightButton_Click);
            // 
            // UpButton
            // 
            this.UpButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.UpButton.Image = global::Designer.Properties.Resources.distribute_vertical_top;
            this.UpButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.UpButton.Name = "UpButton";
            this.UpButton.Size = new System.Drawing.Size(23, 22);
            this.UpButton.Text = "Up";
            this.UpButton.Click += new System.EventHandler(this.UpButton_Click);
            // 
            // DownButton
            // 
            this.DownButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.DownButton.Image = global::Designer.Properties.Resources.distribute_vertical_bottom;
            this.DownButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.DownButton.Name = "DownButton";
            this.DownButton.Size = new System.Drawing.Size(23, 22);
            this.DownButton.Text = "Down";
            this.DownButton.Click += new System.EventHandler(this.DownButton_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // MirrorRL
            // 
            this.MirrorRL.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.MirrorRL.Image = global::Designer.Properties.Resources.object_flip_horizontal_2;
            this.MirrorRL.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.MirrorRL.Name = "MirrorRL";
            this.MirrorRL.Size = new System.Drawing.Size(23, 22);
            this.MirrorRL.Text = "MirrorRL";
            this.MirrorRL.Click += new System.EventHandler(this.MirrorRL_Click);
            // 
            // MirrorUD
            // 
            this.MirrorUD.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.MirrorUD.Image = global::Designer.Properties.Resources.object_flip_vertical_2;
            this.MirrorUD.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.MirrorUD.Name = "MirrorUD";
            this.MirrorUD.Size = new System.Drawing.Size(23, 22);
            this.MirrorUD.Text = "MirrorUD";
            this.MirrorUD.Click += new System.EventHandler(this.MirrorUD_Click);
            // 
            // ArrangeButton
            // 
            this.ArrangeButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ArrangeButton.Image = global::Designer.Properties.Resources.arrange;
            this.ArrangeButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ArrangeButton.Name = "ArrangeButton";
            this.ArrangeButton.Size = new System.Drawing.Size(23, 22);
            this.ArrangeButton.Text = "Arrange";
            this.ArrangeButton.Click += new System.EventHandler(this.ArrangeButton_Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // tunButton
            // 
            this.tunButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tunButton.Image = global::Designer.Properties.Resources.go_next_5;
            this.tunButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tunButton.Name = "tunButton";
            this.tunButton.Size = new System.Drawing.Size(23, 22);
            this.tunButton.Text = "Run";
            this.tunButton.Click += new System.EventHandler(this.RunButton_Click);
            // 
            // BuildButton
            // 
            this.BuildButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.BuildButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.BuildButton.Image = global::Designer.Properties.Resources.run_build_file;
            this.BuildButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BuildButton.Name = "BuildButton";
            this.BuildButton.Size = new System.Drawing.Size(23, 22);
            this.BuildButton.Tag = "Build";
            this.BuildButton.Text = "BuildButton";
            this.BuildButton.Click += new System.EventHandler(this.BuildButton_Click);
            // 
            // dockPanel1
            // 
            this.dockPanel1.ActiveAutoHideContent = null;
            this.dockPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dockPanel1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.World);
            this.dockPanel1.Location = new System.Drawing.Point(0, 49);
            this.dockPanel1.Name = "dockPanel1";
            this.dockPanel1.Size = new System.Drawing.Size(784, 513);
            this.dockPanel1.TabIndex = 2;
            // 
            // ContextMenuStripNew
            // 
            this.ContextMenuStripNew.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItemNew,
            this.MenuItemLoad});
            this.ContextMenuStripNew.Name = "contextMenuStripNew";
            this.ContextMenuStripNew.Size = new System.Drawing.Size(68, 48);
            // 
            // MenuItemNew
            // 
            this.MenuItemNew.Name = "MenuItemNew";
            this.MenuItemNew.Size = new System.Drawing.Size(67, 22);
            // 
            // MenuItemLoad
            // 
            this.MenuItemLoad.Name = "MenuItemLoad";
            this.MenuItemLoad.Size = new System.Drawing.Size(67, 22);
            // 
            // ContextMenuLook
            // 
            this.ContextMenuLook.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItemLookUp,
            this.MenuItemDelete});
            this.ContextMenuLook.Name = "ContextMenuLook";
            this.ContextMenuLook.Size = new System.Drawing.Size(68, 48);
            // 
            // MenuItemLookUp
            // 
            this.MenuItemLookUp.Name = "MenuItemLookUp";
            this.MenuItemLookUp.Size = new System.Drawing.Size(67, 22);
            // 
            // MenuItemDelete
            // 
            this.MenuItemDelete.Name = "MenuItemDelete";
            this.MenuItemDelete.Size = new System.Drawing.Size(67, 22);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 562);
            this.Controls.Add(this.dockPanel1);
            this.Controls.Add(this.DrawToolStrip);
            this.Controls.Add(this.MainMenu);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.MainMenu;
            this.Name = "MainForm";
            this.Text = "Designer";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.MainMenu.ResumeLayout(false);
            this.MainMenu.PerformLayout();
            this.DrawToolStrip.ResumeLayout(false);
            this.DrawToolStrip.PerformLayout();
            this.ContextMenuStripNew.ResumeLayout(false);
            this.ContextMenuLook.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip MainMenu;
        private System.Windows.Forms.ToolStripMenuItem 视图ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 文件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 新建ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出ToolStripMenuItem;
        private System.Windows.Forms.ToolStrip DrawToolStrip;
        private System.Windows.Forms.ToolStripButton NewButton;
        private System.Windows.Forms.ToolStripButton OpenButton;
        private System.Windows.Forms.ToolStripButton BringForwardButton;
        private System.Windows.Forms.ToolStripButton SendBackwardButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton DeleteButton;
        private System.Windows.Forms.ToolStripButton selectAllButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton UndoButton;
        private System.Windows.Forms.ToolStripButton RedoButton;
        private System.Windows.Forms.ToolStripButton LeftButton;
        private System.Windows.Forms.ToolStripButton RightButton;
        private System.Windows.Forms.ToolStripButton UpButton;
        private System.Windows.Forms.ToolStripButton DownButton;
        private System.Windows.Forms.ToolStripMenuItem ToolBoxStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ModuleBoxStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ImageFormStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem PropertyWindowStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        //private System.Windows.Forms.ToolStripButton RotateRightButton;
        //private System.Windows.Forms.ToolStripButton RotateLeftButton;
        private System.Windows.Forms.ToolStripButton ArrangeButton;
        public WeifenLuo.WinFormsUI.Docking.DockPanel dockPanel1;
        public System.Windows.Forms.ToolStripButton SaveButton;
        private System.Windows.Forms.ToolStripMenuItem showToolstripToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 编辑ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dataBaseEditToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dBConnectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dBToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dataBaseWindowToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripButton tunButton;
        private System.Windows.Forms.ToolStripMenuItem MenuItemNew;
        private System.Windows.Forms.ToolStripMenuItem MenuItemLoad;
        public System.Windows.Forms.ContextMenuStrip ContextMenuStripNew;
        private System.Windows.Forms.ToolStripMenuItem MenuItemDelete;
        public System.Windows.Forms.ContextMenuStrip ContextMenuLook;
        private System.Windows.Forms.ToolStripMenuItem firstFormToolStripMenuItem;
        private System.Windows.Forms.ToolStripButton MirrorRL;
        private System.Windows.Forms.ToolStripButton MirrorUD;
        public System.Windows.Forms.ToolStripMenuItem MenuItemLookUp;
        private System.Windows.Forms.ToolStripMenuItem bindWindowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem drawToolStripMenuItem;
        private System.Windows.Forms.ToolStripButton BuildButton;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
    }
}

