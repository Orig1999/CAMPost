﻿#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitMenuBarAndToolBar();//菜单栏和工具栏
    InitStatusBar();//状态栏
    InitLeftWindow();//左侧窗口
    InitRightWindow();//右侧窗口
    InitMidWindow();//中间窗口
    UpdateWindowShowState(false);
}

//1.各个窗口的初始化函数----------------------------------------
void MainWindow::InitMenuBarAndToolBar()//菜单栏和工具栏
{
    //1.菜单
    QMenuBar *pmenu = menuBar();
    setMenuBar(pmenu);
    pFileMenu = pmenu->addMenu("文件");

    //创建菜单项
    newMenuAction = pFileMenu->addAction("新建");

    openMenuAction = pFileMenu->addAction("打开");
    connect(openMenuAction,SIGNAL(triggered()),this,SLOT(onOpenFileTriggered()));//打开

    saveMenuAction = pFileMenu->addAction("保存");
    connect(saveMenuAction,SIGNAL(triggered()),this,SLOT(onSaveMenuActionTriggered()));//保存

    saveAsMenuAction = pFileMenu->addAction("另存");

    setingMenuAction = pFileMenu->addAction("设置");
    connect(setingMenuAction,SIGNAL(triggered()),this,SLOT(onSettingMenuActionTriggered()));//设置

    //2.工具栏
    ptoolbar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea,ptoolbar);
    //工具项
    ptoolbar->addAction(newMenuAction);
    ptoolbar->addAction(openMenuAction);
    ptoolbar->addAction(saveMenuAction);
    ptoolbar->addAction(saveAsMenuAction);
    ptoolbar->addSeparator();
    ptoolbar->addAction(setingMenuAction);
    ptoolbar->addSeparator();

    //添加【参数/命令】下拉框
    pParCmdCom = new QComboBox();
    pParCmdComAction = ptoolbar->addWidget(pParCmdCom);

    //添加【具体的参数/命令】下拉框
    pspecialParCmdCom = new QComboBox();
    pspecialParCmdComAction = ptoolbar->addWidget(pspecialParCmdCom);
    UpdateParameterCombox();//初始化参数下拉框

    //添加【添加参数】按钮
    paddParameterBnt = new QPushButton("添加参数",this);
    paddParameterBntAction = ptoolbar->addWidget(paddParameterBnt);
    connect(paddParameterBnt,SIGNAL(clicked()),this,SLOT(onAddParameter()));

    //添加分割符
    ptoolbar->addSeparator();

    //添加【添加文本】按钮
    paddTextBnt = new QPushButton("添加文本",this);
    paddTextBntAction = ptoolbar->addWidget(paddTextBnt);
    connect(paddTextBnt,SIGNAL(clicked()),this,SLOT(onAddText()));//添加文本

    //添加【添加文本】按钮
    paddnewLineBnt = new QPushButton("添加一行",this);
    paddnewlineAction = ptoolbar->addWidget(paddnewLineBnt);
    connect(paddnewLineBnt,SIGNAL(clicked()),this,SLOT(onAddNewLine()));//添加一行

    //添加【删除】按钮
    pDelBnt = new QPushButton("删除",this);
    pDelBntAction = ptoolbar->addWidget(pDelBnt);
    connect(pDelBnt,SIGNAL(clicked()),this,SLOT(onDel()));//删除
}
void MainWindow::InitStatusBar()//状态栏
{
    QStatusBar *statusBar = new QStatusBar(this);
    QLabel *statusLabl = new QLabel("准备就绪",this);
    statusBar->addWidget(statusLabl);
    setStatusBar(statusBar);
}
void MainWindow::addClsfAndProcessClicked()
{
    QFileDialog* f = new QFileDialog(this);
    f->setWindowTitle("选择catia刀位文件*.aptsource");
    f->setNameFilter("*.aptsource");
    f->setViewMode(QFileDialog::Detail);

    QString filePath;
    if(f->exec() == QDialog::Accepted)
    {
        filePath = f->selectedFiles()[0];
        postProcess process(filePath,xpost);
        process.ReadCLSFAndWriteToNC();
    }
    QTreeWidgetItem *item = CLDATAtree->topLevelItem(0);
    QFileInfo fileInfo= QFileInfo(filePath);
    item->addChild(new QTreeWidgetItem(item,QStringList()<<fileInfo.fileName()));
}
void MainWindow::showCldataTreeRightMenu(QPoint pos)
{
    Q_UNUSED(pos);
    QMenu *menuList = new QMenu(this);

    QAction *add = new QAction(QStringLiteral("添加"), this);
    //QAction *del = new QAction(QStringLiteral("删除"), this);
    //QAction *modify = new QAction(QStringLiteral("修改"), this);
    connect(add, SIGNAL(triggered()), this, SLOT(addClsfAndProcessClicked()));
    menuList->addAction(add);
    //menuList->addAction(del);
    //menuList->addAction(modify);
    menuList->exec(QCursor::pos());
}

void MainWindow::InitLeftDock()//初始化左侧的dock页面
{
    //1.创建左侧的浮动窗口
    QDockWidget *pLeftdock = new  QDockWidget("后处理/编辑",this) ;
    //2.tab页
    processorEditTab = new QTabWidget (pLeftdock) ;
    pLeftdock->setWidget(processorEditTab);
    addDockWidget(Qt::LeftDockWidgetArea,pLeftdock);

    //2.1 初始化后处理页面
    //刀轨文件树
    CLDATAtree = new QTreeWidget (processorEditTab) ;
    CLDATAtree->setHeaderHidden(true);//隐藏表头方法
    //commandTree->setHeaderLabels(QStringList()<<"11"<<"22");
    CLDATAtree->setHeaderLabels(QStringList()<<"CLDATA");
    CLDATAtree->setStyle(QStyleFactory::create("windows"));
    QTreeWidgetItem *ptopitem = new QTreeWidgetItem (QStringList()<<"刀轨文件列表",root) ;
    CLDATAtree->addTopLevelItem(ptopitem);
    //QTreeWidgetItem *pchilditem = new QTreeWidgetItem (QStringList()<<"PathStart") ;
    //ptopitem->addChild(pchilditem);
    processorEditTab->addTab(CLDATAtree,"后处理");
    CLDATAtree->setContextMenuPolicy(Qt::CustomContextMenu);
    this->connect(CLDATAtree,SIGNAL(customContextMenuRequested(QPoint)),
                     this,SLOT(showCldataTreeRightMenu(QPoint)));

    //2.2 初始化编辑页面
    cmdParamFmtScriptTreeTab = new QTabWidget (processorEditTab) ;
    //tabWidget->addTab(cmdParamFmtScriptTreeTab,"编辑");
    leftPropertytable = new QTableWidget (this) ;
    leftPropertytable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//table宽度自适应填充
    QSplitter *editsplit = new QSplitter(Qt::Vertical,this);
    editsplit->addWidget(cmdParamFmtScriptTreeTab);
    editsplit->addWidget(leftPropertytable);

    editsplit->setStretchFactor(0,70);
    editsplit->setStretchFactor(1,30);
    processorEditTab->addTab(editsplit,"编辑");
    connect(processorEditTab,SIGNAL(currentChanged(int)),this, SLOT(slotProcessorEditTabCurrentChanged(int)));
}
void MainWindow::InitLeftWindow()//左侧窗口
{
    //1.dock浮动窗口
    InitLeftDock();
    //（1）命令树
    InitCmdTree();
    //（2）参数树
    InitParameterTree();
    //（3）格式树
    InitFormatTree();
    //（4）脚本树
    InitScriptTree();
}
void MainWindow::InitRightWindow()//右侧窗口
{
    //创建右侧的浮动窗口
    pRightdock = new  QDockWidget("属性",this) ;
    pPropertytable = new QTableWidget (pRightdock) ;
    pPropertytable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//table宽度自适应填充
    pRightdock->setWidget(pPropertytable);
    addDockWidget(Qt::RightDockWidgetArea,pRightdock);
}
void MainWindow::InitCmdTree()//初始化命令树节点
{
    commandTree = new QTreeView (cmdParamFmtScriptTreeTab) ;
    commandTree->expandAll();
    cmdParamFmtScriptTreeTab->addTab(commandTree,"命令");
    commandTree->setSelectionMode(QAbstractItemView::SingleSelection);//禁止多选，只允许选中一个节点
    commandTree->setStyle(QStyleFactory::create("windows"));
    commandTree->setHeaderHidden(true);//隐藏表头方法
    //commandTree->expandAll();在这儿不起作用
    commandTreeModel = new QStandardItemModel;//命令树
    commandTree->setModel(commandTreeModel);

    connect(commandTree->selectionModel(),&QItemSelectionModel::currentChanged,
            this,&MainWindow::slotCmdsTreeCurrentChanged);//鼠标单击命令树

    connect(cmdParamFmtScriptTreeTab,SIGNAL(currentChanged(int)),this,
            SLOT(slotCmdParamScriptTabCurrentChanged(int)));

    UpdateCmdTreeModel();
}
void MainWindow::InitParameterTree()//初始化参数树
{
    parameterTree = new QTreeView (cmdParamFmtScriptTreeTab) ;
    parameterTree->expandAll();
    cmdParamFmtScriptTreeTab->addTab(parameterTree,"参数");
    parameterTree->setSelectionMode(QAbstractItemView::SingleSelection);//禁止多选，只允许选中一个节点
    parameterTree->setStyle(QStyleFactory::create("windows"));
    parameterTree->setHeaderHidden(true);//隐藏表头方法
    UpdateParameterTreeModel();
    parameterTree->setModel(ParameterTreeModel);
}
void MainWindow::InitFormatTree()//初始化格式树
{
    formatTtree = new QTreeView (cmdParamFmtScriptTreeTab) ;
    formatTtree->expandAll();
    cmdParamFmtScriptTreeTab->addTab(formatTtree,"格式");
    formatTtree->setSelectionMode(QAbstractItemView::SingleSelection);//禁止多选，只允许选中一个节点
    formatTtree->setStyle(QStyleFactory::create("windows"));
    formatTtree->setHeaderHidden(true);//隐藏表头方法
    UpdateFmtTreeModel();
    formatTtree->setModel(fmtTreeModel);
}
void MainWindow::InitScriptTree()//初始化脚本树
{
    scriptTree = new QTreeView (cmdParamFmtScriptTreeTab) ;
    scriptTree->expandAll();
    cmdParamFmtScriptTreeTab->addTab(scriptTree,"脚本");
    scriptTree->setSelectionMode(QAbstractItemView::SingleSelection);//禁止多选，只允许选中一个节点
    scriptTree->setStyle(QStyleFactory::create("windows"));
    scriptTree->setHeaderHidden(true);//隐藏表头方法
    UpdateScriptTreeModel();
    scriptTree->setModel(scriptTreeModel);
}
void MainWindow::UpdateParameterCombox()//初始化参数combox
{
    pParCmdCom->addItem("参数");
    //添加【具体的参数/命令】下拉框
    for(map<int,PostParameter>::iterator i = xpost.postData.ParametersMap.begin();
        i!=xpost.postData.ParametersMap.end();++i)
    {
        //qDebug() <<"name: "<<i->second.Name<<"  id:"<<i->first<<endl;
        pspecialParCmdCom->addItem(i->second.Name,i->first);
    }
}

void MainWindow::InitMidWindow()//初始化block页面
{
    //1.中间的命令编辑子窗口
    pCmdEdittab = new QTabWidget (ui->centralWidget) ;
    CmdBlockTable = new QTableView (pCmdEdittab) ;
    CmdBlockTable->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                           "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    CmdBlockTable->verticalHeader()->setStyleSheet("QHeaderView::section {"
                                                             "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    pCmdEdittab->addTab(CmdBlockTable,"UNLL");//更新tableview的标题
    //CmdBlockTable->setVisible(false);

    //2.底部浮动预览子窗口
    ppreviewdock = new  QDockWidget("预览",this) ;
    QSplitter *split = new QSplitter(Qt::Vertical,this);

    //3.将1和2添加入中间窗口（分裂）
    split->addWidget(pCmdEdittab);
    split->addWidget(ppreviewdock);
    split->setStretchFactor(0,80);
    split->setStretchFactor(1,20);
    //预览子窗口再次分裂
    QSplitter *subsplit = new QSplitter(Qt::Horizontal,this);
    textBrowser = new QTextBrowser(this);
    pPreviewtable = new QTableWidget (this) ;
    subsplit->addWidget(textBrowser);
    subsplit->addWidget(pPreviewtable);
    ppreviewdock->setWidget(subsplit);
    setCentralWidget(split);

    commandBlkModel = new QStandardItemModel;
    CmdBlockTable->setModel(commandBlkModel);

    //数据发生改变事件（即文本参数编辑结束）
    connect(commandBlkModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(cmdBlkItemdataChanged(QModelIndex,QModelIndex)));
    //鼠标单击blockItem
    connect(CmdBlockTable->selectionModel(),&QItemSelectionModel::currentChanged,
            this,&MainWindow::slotCmdEditTableCurrentChanged);
}

//各个窗口的初始化函数----------------------------------------

//2.模型数据的更新-------------------------------------
void MainWindow::UpdateCmdTreeModel()//更新命令树的模型
{
    commandTreeModel->clear();
    //commandTreeModel = new QStandardItemModel;//命令树
    for(map<int,postCommand>::iterator i = xpost.postData.CommandsMap.begin();
        i!=xpost.postData.CommandsMap.end();++i)
    {
        //qDebug()<<"name:"<<i->second.Name<<" id:"<<i->first<<" GroupName:"<<i->second.GroupName;

        QStandardItem *itemChild =  new  QStandardItem(i->second.Name);
        itemChild->setData(i->first,Qt::UserRole);//绑定id
        if(i->second.GroupName=="")//无需组节点，具体的命令直接挂在跟节点下
        {
            commandTreeModel->appendRow(itemChild);
            //setChild效果同上 itemProject->setChild(0,itemChild);
        }
        else//需要组节点 groupItem
        {
            QModelIndexList list = commandTreeModel->match(commandTreeModel->index(0, 0),
                                                    Qt::UserRole + 1, QVariant::fromValue(i->second.GroupName),
                                                    1,Qt::MatchContains | Qt::MatchRecursive);
            if (!list.empty())//在根节下有名称为i->second.GroupName的组节点
            {
              //model->removeRow(list .first().row());
              QModelIndex currentIndex = list .at(0);
              QStandardItem *currentItem = commandTreeModel->itemFromIndex(currentIndex);
              currentItem->appendRow(itemChild);
            }
            else
            {
                //创建一个组节点
                QStandardItem *groupItem =  new  QStandardItem(i->second.GroupName);
                groupItem->setData(-1,Qt::UserRole);//标记是group
                groupItem->setData(i->second.GroupName,Qt::UserRole+1);//绑定GroupName
                commandTreeModel->appendRow(groupItem);//二级节点
                groupItem->appendRow(itemChild);
            }
        }
    }
}
void MainWindow::UpdateParameterTreeModel()//更新参数树的模型
{
    ParameterTreeModel = new QStandardItemModel;

    for(map<int, PostParameter >::iterator i = xpost.postData.ParametersMap.begin();
        i!=xpost.postData.ParametersMap.end();++i)
    {
        QStandardItem *itemChild =  new  QStandardItem(i->second.Name);
        itemChild->setData(i->first,Qt::UserRole);//绑定id

        QModelIndexList list = ParameterTreeModel->match(ParameterTreeModel->index(0, 0),
                                                       Qt::UserRole + 1, QVariant::fromValue(i->second.GroupName),
                                                       1,Qt::MatchContains | Qt::MatchRecursive);
        if (!list.empty())//在根节下有名称为i->second.GroupName的组节点
        {
            //model->removeRow(list .first().row());
            QModelIndex currentIndex = list .at(0);
            QStandardItem *currentItem = ParameterTreeModel->itemFromIndex(currentIndex);
            currentItem->appendRow(itemChild);
        }
        else
        {
            //创建一个组节点
            QStandardItem *groupItem =  new  QStandardItem(i->second.GroupName);
            groupItem->setData(-1,Qt::UserRole);//标记是group
            groupItem->setData(i->second.GroupName,Qt::UserRole+1);//绑定GroupName
            ParameterTreeModel->appendRow(groupItem);//二级节点
            groupItem->appendRow(itemChild);
        }
    }
}
void MainWindow::UpdateCommandBlkModel(postCommand *selCmd)//更新命令编辑视图的模型
{
    //最长的一行
    list<postBlock>::size_type columnMax = 0;
    for(list<postBlock>::iterator i = selCmd->blocklist.begin();
        i!=selCmd->blocklist.end();++i)
    {
        if(columnMax < i->bloskItemList.size())
        {
           columnMax = i->bloskItemList.size();
        }
    }
    columnMax = columnMax+1 ;
    commandBlkModel->clear();//清空
    qDebug()<<selCmd->blocklist.size();

    for(list<postBlock>::iterator r = selCmd->blocklist.begin();
        r!=selCmd->blocklist.end();++r)
    {

        QList<QStandardItem*> itemList;//一行
        for(list<postBlockItem>::iterator item = r->bloskItemList.begin();
            item!=r->bloskItemList.end();++item)
        {
            qDebug()<<r->bloskItemList.size();

            QString content = "";
            QStandardItem* standarditem = NULL;
            switch (item->Parameter.Type) {
            case UnknownParameter://未知，白色
                //content = item->Parameter.GetValue();
                standarditem = new QStandardItem(content);
                itemList << standarditem;
                standarditem->setTextAlignment(Qt::AlignCenter);//中间对齐

                standarditem->setBackground(QBrush(QColor(255,255,0)));
                //standarditem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                standarditem->setFlags(Qt::ItemIsEnabled);
                break;
            case Text://文本
                item->Parameter.GetOutPutString(content,true);
                standarditem = new QStandardItem(content);
                itemList << standarditem;
                standarditem->setTextAlignment(Qt::AlignCenter);//中间对齐

                standarditem->setBackground(QBrush(QColor(155,234,156)));
                standarditem->setFlags(Qt::ItemIsEnabled |Qt::ItemIsEditable);
                break;
            case GeneralParameter://一般参数
                content = item->Parameter.Name;
                standarditem = new QStandardItem(content);
                itemList << standarditem;
                standarditem->setTextAlignment(Qt::AlignCenter);//中间对齐

                standarditem->setBackground(QBrush(QColor(232,232,255)));
                standarditem->setFlags(Qt::ItemIsEnabled);
                break;
            case GroupParameter://组值参数
                content = item->Parameter.Name;
                standarditem = new QStandardItem(content);
                itemList << standarditem;
                standarditem->setTextAlignment(Qt::AlignCenter);//中间对齐

                standarditem->setBackground(QBrush(QColor(232,232,255)));
                standarditem->setFlags(Qt::ItemIsEnabled);
                break;
            default:
                //content = item->Parameter.Name;
                standarditem = new QStandardItem(content);
                itemList << standarditem;

                standarditem->setBackground(QBrush(QColor(255,255,0)));
                standarditem->setFlags(Qt::ItemIsEnabled);
                break;
            }
        }
         //qDebug()<<"A"<<endl;
        //补全空格
        size_t blockCount = columnMax - r->bloskItemList.size();
        for(size_t index = 0; index<blockCount; ++index)
        {
            QString content = "";
            QStandardItem* standarditem = NULL;
            standarditem = new QStandardItem(content);
            itemList << standarditem;
            standarditem->setTextAlignment(Qt::AlignCenter);//中间对齐

            standarditem->setBackground(QBrush(QColor(255,255,0)));
            //standarditem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            standarditem->setFlags(Qt::ItemIsEnabled);
        }
         commandBlkModel->appendRow(itemList);
    }
}
void MainWindow::UpdateFmtTreeModel()
{
    fmtTreeModel = new QStandardItemModel;
    for(map<int, ParameterFormat >::iterator i = xpost.postData.FormatsMap.begin();
        i!=xpost.postData.FormatsMap.end();++i)
    {
        QStandardItem *itemChild =  new  QStandardItem(i->second.Name);
        itemChild->setData(i->first,Qt::UserRole);//绑定id
        fmtTreeModel->appendRow(itemChild);
    }

}
void MainWindow::UpdateScriptTreeModel()
{
    scriptTreeModel = new QStandardItemModel;
    //未完成..
    QStandardItem *itemChild =  new  QStandardItem("testScript");
    scriptTreeModel->appendRow(itemChild);
}
//模型数据的更新----------------------------------------

//3.工具栏的响应事件-------------------------------------
void MainWindow::initFormats(QDomElement formatsElem)
{
  for(int i=0;i<formatsElem.childNodes().count();++i)
  {
      QDomElement elem = formatsElem.childNodes().at(i).toElement();
      int id = elem.attribute("id").toInt();
      QString name = elem.attribute("name");
      QString prefix = elem.attribute("prefix");
      QString postfix = elem.attribute("postfix");
      QString decimalCount = elem.attribute("decimalCount");
      ParameterFormat format = ParameterFormat(name,prefix,postfix,decimalCount.toInt(),id);
      xpost.postData.FormatsMap.insert(map<int,ParameterFormat>::value_type(format.ID,format));
  }
}
void MainWindow::initParameters(QDomElement parametersElem)
{
    for(int i=0;i<parametersElem.childNodes().count();++i)
    {
        QDomElement elem = parametersElem.childNodes().at(i).toElement();
        QString id = elem.attribute("id");
        QString name = elem.attribute("name");
        //qDebug()<<name<<endl;
        int formatID = elem.attribute("formatID").toInt();
        int type = elem.attribute("type").toInt();
        QString groupName = elem.attribute("groupName");
        ParameterType paramtype = (ParameterType)type;
        ParameterFormat format = xpost.postData.FormatsMap.at(formatID);
        PostParameter parameter = PostParameter(groupName,name,paramtype,format,id.toInt());
        xpost.postData.ParametersMap.insert(map<int,PostParameter>::value_type(parameter.ID,parameter));
    }
}
void MainWindow::createCommandFromNode(QDomElement elem,postCommand *cmd)
{
    QString id = elem.attribute("id");
    QString name = elem.attribute("name");
    QString groupName = elem.attribute("groupName");
    int state = elem.attribute("state").toInt();
    CommandState cmdstate = (CommandState)state;
    *cmd = postCommand(name,groupName,id.toInt(),cmdstate,false);
}
void MainWindow::createBlockFromNode(QDomElement cmdElem,postBlock *blk)
{
    postBlock block = postBlock();
    QDomNodeList itemNodelist = cmdElem.childNodes();
    for(int i=0;i<itemNodelist.count();++i)
    {
      QDomElement itemElem = itemNodelist.at(i).toElement();//blockitem
      postBlockItem blkitem;
      createBlockItemFromNode(itemElem,&blkitem);

      blk->bloskItemList.push_back(blkitem);// 将blockitem添加入bloskItemList
    }
}

void MainWindow::createBlockItemFromNode(QDomElement itemElem,postBlockItem *blkitem)
{
    QString itemType = itemElem.attribute("type");//parameter text
    blkitem->State = (ItemState)itemElem.attribute("state").toInt();
    if(itemType=="text")//文本
    {
        QString text = itemElem.attribute("text");
        blkitem->Parameter = PostParameter(text);
    }
    else if(itemType=="parameter")//文本 <param formatID="53" id="24"/>
    {
        int fmtid = itemElem.attribute("formatID").toInt();
        int id = itemElem.attribute("id").toInt();
        PostParameter parameter(id);
        parameter.Format = xpost.postData.FormatsMap.at(fmtid);
        blkitem->Parameter = parameter;
    }
}
void MainWindow::initCommands(QDomElement cmdElem)
{
    for(int i=0;i<cmdElem.childNodes().count();++i)
    {
        QDomElement elem = cmdElem.childNodes().at(i).toElement();//command
        postCommand cmd(false);
        createCommandFromNode(elem,&cmd);//创建命令

        QDomNodeList blockNodelist = elem.childNodes();//blocklist

        qDebug()<<blockNodelist.count();
        qDebug()<<cmd.blocklist.size();
        for(int i=0;i<blockNodelist.count();++i)
        {
          QDomElement blocksElem = blockNodelist.at(i).toElement();//block
          postBlock block;
          createBlockFromNode(blocksElem,&block);//创建 block
          cmd.blocklist.push_back(block);//block添加入command中
        }
        qDebug()<<cmd.blocklist.size();
        //将命令插入xpost
        xpost.postData.CommandsMap.insert(map<int,postCommand>::value_type(cmd.ID,cmd));
    }
}
void MainWindow::onOpenFileTriggered()
{
    QFileDialog* f = new QFileDialog(this);
    f->setWindowTitle("选择后处理文件*.xpost");
    f->setNameFilter("*.xpost");
    f->setViewMode(QFileDialog::Detail);

    QString filePath;
    if(f->exec() == QDialog::Accepted)
    {
        xpost.FileName = f->selectedFiles()[0];

        QFile xmlFile(xpost.FileName);
        if(!xmlFile.open(QFile::ReadOnly))
            return;
        QDomDocument doc;
        if(!doc.setContent(&xmlFile))
        {
            xmlFile.close();
            return;
        }
        //获取根节点
        QDomElement root = doc.documentElement();
        qDebug()<<root.tagName()<<endl;
        QDomNodeList nodeList = root.childNodes();
        QDomElement commandsElem ;
        QDomElement parametersElem ;
        QDomElement formatsElem ;

        qDebug()<<nodeList.count()<<endl;

        for(int i=0;i<nodeList.count();++i)
        {
          QDomElement elem = nodeList.at(i).toElement();

          qDebug()<<elem.tagName()<<endl;

          if(elem.tagName()=="commands")
          {
            commandsElem = elem;
          }
          else if(elem.tagName()=="parameters")
          {
            parametersElem = elem;
          }
          else if(elem.tagName()=="formats")
          {
            formatsElem = elem;
          }
        }
      xpost.postData.CommandsMap.clear();
      xpost.postData.ParametersMap.clear();
      xpost.postData.FormatsMap.clear();
      initFormats(formatsElem);
      initParameters(parametersElem);
      initCommands(commandsElem);
      UpdateCmdTreeModel();
    }
}
void MainWindow::onSettingMenuActionTriggered()
{
  settingFrm =new  SettingForm() ;
  settingFrm->show();
}
void MainWindow::onSaveMenuActionTriggered()
{
   //qDebug()<<"ccccc"<<endl;
    QFileInfo file(xpost.FilePath);
    QString filefullpath = "";
    if(!file.isDir())
    {
        filefullpath = QFileDialog::getSaveFileName(this,"选择保存的文件","","xpos(*.xpost)");
        if(filefullpath.isNull())
            return;
        file = QFileInfo(filefullpath);
        xpost.FileName=file.fileName();
        xpost.FilePath=file.absolutePath();
    }
    //保存成xml文件
    QFile xmlFile(filefullpath);
    if(!xmlFile.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root = doc.createElement("Post");
    doc.appendChild(root);
    writeInCommands(doc,root);
    writeInParameters(doc,root);
    writeInFormats(doc,root);
    //输出到文件
    QTextStream out_stream(&xmlFile);
    doc.save(out_stream,4); //缩进4格
    xmlFile.close();
}
void MainWindow::writeInCommands(QDomDocument &doc,QDomElement &root)
{
    //添加一级节点命令
    QDomElement cmds = doc.createElement("commands");
    root.appendChild(cmds);
    //添加二级节点，具体的命令节点
    for(map<int,postCommand>::iterator i = xpost.postData.CommandsMap.begin();
        i!=xpost.postData.CommandsMap.end();++i)
    {
        //第 cmdIndex 个命令
        QDomElement iCmd = doc.createElement("command");
        iCmd.setAttribute("id",i->first); //创建属性id
        iCmd.setAttribute("name",i->second.Name); //创建属性name
        iCmd.setAttribute("state",i->second.State); //创建属性state
        iCmd.setAttribute("groupName",i->second.GroupName); //GroupName
        cmds.appendChild(iCmd);
        //block
        for(list<postBlock>::iterator block = i->second.blocklist.begin();
            block!=i->second.blocklist.end();++block)
        {
            QDomElement iBlock = doc.createElement("block");
            iCmd.appendChild(iBlock);

            //blockitem
            for(list<postBlockItem>::iterator blockitem = block->bloskItemList.begin();
                blockitem!=block->bloskItemList.end();++blockitem)
            {
                QDomElement iBlockitem = doc.createElement("blockItem");
                iBlock.appendChild(iBlockitem);
                switch (blockitem->Parameter.Type) {
                case Text://文本
                {
                    iBlockitem.setAttribute("type","text"); //创建属性type
                    iBlockitem.setAttribute("state",blockitem->State); //创建属性state
                    QDomElement itextparam = doc.createElement("param");
                    QString str="";
                    blockitem->Parameter.GetOutPutString(str,true);
                    itextparam.setAttribute("text",str); //创建属性state
                    iBlockitem.appendChild(itextparam);
                }
                    break;
                case GeneralParameter://一般参数
                {
                    iBlockitem.setAttribute("type","parameter"); //创建属性type
                    iBlockitem.setAttribute("state",blockitem->State); //创建属性state
                    QDomElement iparam = doc.createElement("param");
                    iparam.setAttribute("id",blockitem->Parameter.ID); //创建属性id
                    iparam.setAttribute("formatID",blockitem->Parameter.Format.ID); //创建格式id
                    iBlockitem.appendChild(iparam);
                }
                    break;
                case GroupParameter://组值参数
                {
                    iBlockitem.setAttribute("type","parameter"); //创建属性type
                    iBlockitem.setAttribute("state",blockitem->State); //创建属性state
                    QDomElement iparam = doc.createElement("param");
                    iparam.setAttribute("id",blockitem->Parameter.ID); //创建属性id
                    iparam.setAttribute("formatID",blockitem->Parameter.Format.ID); //创建格式id
                    iBlockitem.appendChild(iparam);
                }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
void MainWindow::writeInParameters(QDomDocument &doc,QDomElement &root)
{
    //添加一级节点命令
    QDomElement paramers = doc.createElement("parameters");
    root.appendChild(paramers);
    //添加二级节点，具体的参数
    for(map<int,PostParameter>::iterator i = xpost.postData.ParametersMap.begin();
        i!=xpost.postData.ParametersMap.end();++i)
    {
        //第 i 个参数
        QDomElement iParameter = doc.createElement("parameter");
        iParameter.setAttribute("id",i->first); //创建属性id
        iParameter.setAttribute("name",i->second.Name); //创建属性name
        iParameter.setAttribute("formatID",i->second.Format.ID); //创建属性格式ID
        iParameter.setAttribute("groupName",i->second.GroupName); //创建属性参数所属的组
        iParameter.setAttribute("type",i->second.Type); //类型
        paramers.appendChild(iParameter);
    }
}
void MainWindow::writeInFormats(QDomDocument &doc,QDomElement &root)
{
    //添加一级节点命令
    QDomElement formats = doc.createElement("formats");
    root.appendChild(formats);
    //添加二级节点，具体的格式
    for(map<int,ParameterFormat>::iterator i = xpost.postData.FormatsMap.begin();
        i!=xpost.postData.FormatsMap.end();++i)
    {
        //第 i 个格式
        QDomElement iFmt = doc.createElement("format");
        iFmt.setAttribute("id",i->first); //创建属性id
        iFmt.setAttribute("name",i->second.Name); //创建属性name
        iFmt.setAttribute("prefix",i->second.Prefix); //前缀
        iFmt.setAttribute("postfix",i->second.Postfix); //后缀
        iFmt.setAttribute("decimalCount",i->second.DecimalNum); //小数位数
        formats.appendChild(iFmt);
    }
}
void MainWindow::onAddNewLine()//添加一行
{
    //1.获取被选中的表格item
    QModelIndex blkIndex = CmdBlockTable->currentIndex();
    size_t row = blkIndex.row();
    size_t colum = blkIndex.column();
    postCommand * selCmd = GetSelCommand();
    if(selCmd==NULL)
      return;

    //3.找到对应的block
    if(row>selCmd->blocklist.size()-1)
        return;
    list<postBlock>::iterator blkIterator = selCmd->blocklist.begin();
    advance(blkIterator,row);//将迭代器向后移动row个位置
    //如果colum是该行的最后的一个blockitem，则在他的下面添加一行，否则在他上面添加一行
    postBlock newBlok;
    qDebug()<<blkIterator->bloskItemList.size();
    if(colum>blkIterator->bloskItemList.size()-1)
    {
        ++blkIterator;
    }
    selCmd->blocklist.insert(blkIterator,newBlok);
    //更新模型
    UpdateCommandBlkModel(selCmd);
}
void MainWindow::onDel()//删除
{
    //1.获取被选中的表格item
    QModelIndex blkIndex = CmdBlockTable->currentIndex();
    size_t row = blkIndex.row();
    size_t colum = blkIndex.column();
    //qDebug()<<blkIndex.row();
    //qDebug()<<blkIndex.column();
    //2.获取命令
    postCommand * selCmd = GetSelCommand();
    if(selCmd==NULL)
      return;

    //3.找到对应的block
    if(row>selCmd->blocklist.size()-1)
        return;

    list<postBlock>::iterator blkIterator = selCmd->blocklist.begin();
    advance(blkIterator,row);//将迭代器向后移动row个位置
    if(colum>blkIterator->bloskItemList.size()-1)//超出本行的最大值
        return;

    list<postBlockItem>::iterator blkItemIterator = blkIterator->bloskItemList.begin();
    advance(blkItemIterator,colum);//将迭代器向后移动colum个位置
    blkIterator->bloskItemList.erase(blkItemIterator);
    //更新模型
    UpdateCommandBlkModel(selCmd);
}
void MainWindow::addParameter(PostParameter &parameter)//添加参数
{
    //1.获取被选中的表格item
    QModelIndex blkIndex = CmdBlockTable->currentIndex();
    size_t newRow = blkIndex.row();
    size_t newColum = blkIndex.column();
    //qDebug()<<blkIndex.row();
    //qDebug()<<blkIndex.column();

    //2.获取命令
    postCommand * selCmd = GetSelCommand();
    if(selCmd==NULL)
      return;
    //3.找到对应的block
    //qDebug()<<"xx:"<<selCmd->blocklist.size();
    if(newRow>selCmd->blocklist.size()-1)
        return;

    list<postBlock>::iterator blkIterator = selCmd->blocklist.begin();
    //qDebug()<<"aaaa:"<<blkIterator->bloskItemList.size();
    advance(blkIterator,newRow);//将迭代器向后移动row个位置
    //qDebug()<<"bw:"<<blkIterator->GetNotEmptySize();

    postBlockItem newBlkItem(parameter);
    list<postBlockItem>::iterator blkItem;
    if(newColum >= blkIterator->bloskItemList.size()-1)//添加在末尾
    {
        blkItem = blkIterator->bloskItemList.end();
    }
    else
    {
        blkItem = blkIterator->bloskItemList.begin();
        advance(blkItem,newColum);//将迭代器向后移动newColum个位置
    }
    blkIterator->bloskItemList.insert(blkItem,newBlkItem);
    //qDebug()<<"c:"<<blkIterator->bloskItemList.size();
    UpdateCommandBlkModel(selCmd);//更新模型
}
void MainWindow::onAddParameter()//添加参数
{
    //通过id拿到参数对象，id号绑定在combox的itemdata中
    int paramid = pspecialParCmdCom->currentData().toInt();
    map<int,PostParameter>::iterator paramkey = xpost.postData.ParametersMap.find(paramid);
    if(paramkey==xpost.postData.ParametersMap.end())
        return;
    //PostParameter parameter = xpost.postData.ParametersMap[paramid];
    addParameter(xpost.postData.ParametersMap[paramid]);
}
void MainWindow::onAddText()//添加文本
{ 
    PostParameter parameter("");
    addParameter(parameter);
}
//工具栏的响应事件-------------------------------------

//4.左侧窗口事件--------------------------------------
void MainWindow::slotCmdParamScriptTabCurrentChanged(int index)
{
  qDebug()<<index;
}
void MainWindow::slotProcessorEditTabCurrentChanged(int index)
{
    QModelIndex currentIndex = commandTree->currentIndex(); //选中的行
    QStandardItem *currentItem = commandTreeModel->itemFromIndex(currentIndex);
    if(currentItem==NULL)
    {
        UpdateWindowShowState(false);
        return;
    }
    //获取命令的ID
    int cmdId  = currentItem->data(Qt::UserRole).value<int>();
    if(cmdId==-1)
    {
        UpdateWindowShowState(false);
        return;
    }

    if(index==0)//后处理
    {
        UpdateWindowShowState(false);
    }
    else
    {
        UpdateWindowShowState(true);
    }
}
void MainWindow::slotCmdsTreeCurrentChanged(const QModelIndex &current,const QModelIndex &previous)//鼠标点击命令树
{
  QStandardItem *currentItem = commandTreeModel->itemFromIndex(current);
  //获取命令的ID
  int cmdId  = currentItem->data(Qt::UserRole).value<int>();
  if(cmdId==-1)
  {
      UpdateWindowShowState(false);
      return;
  }
  map<int,postCommand>::iterator key = xpost.postData.CommandsMap.find(cmdId);
  if(key==xpost.postData.CommandsMap.end())
  {
      UpdateWindowShowState(false);
      return;
  }
  postCommand *selCmd = &(xpost.postData.CommandsMap[cmdId]);//当前被选中的命令command
  if(selCmd==NULL)
  {
      UpdateWindowShowState(false);
      return;
  }
  UpdateCommandBlkModel(selCmd);//更新模型
  updateLeftPropertytable();//更新左侧的命令属性窗口
  pCmdEdittab->setTabText(0,selCmd->Name);//更新tableview的标题
  UpdateWindowShowState(true);
}
void MainWindow::clickCommandStateCombobox(int index)//切换命令状态(active,inactive)的下拉框
{
    //获取命令的ID
    postCommand * selCmd = GetSelCommand();
    if(selCmd==NULL)
        return;

    selCmd->State = (CommandState)index;
}
void MainWindow::updateLeftPropertytable()//刷新左侧的命令的属性框
{
    //1.获取命令
    postCommand * selCmd = GetSelCommand();
    if(selCmd==NULL)
        return;
   leftPropertytable->setColumnCount(2);
   leftPropertytable->setRowCount(3);
   leftPropertytable->verticalHeader()->hide();//隐藏列头
   leftPropertytable->horizontalHeader()->hide();//隐藏行头
   leftPropertytable->setItem(0,0,new QTableWidgetItem("Name"));
   leftPropertytable->setItem(0,1,new QTableWidgetItem(selCmd->Name));
   //状态下拉框
   leftPropertytable->setItem(1,0,new QTableWidgetItem("State"));
   QComboBox *stateCombox = new QComboBox (leftPropertytable) ;
   stateCombox->addItem("Active");
   stateCombox->addItem("Inactive");
   stateCombox->setCurrentIndex(selCmd->State);
   leftPropertytable->setCellWidget(1,1,stateCombox);
   //脚本下拉框
   leftPropertytable->setItem(2,0,new QTableWidgetItem("Script"));
   leftPropertytable->setItem(2,1,new QTableWidgetItem("None"));
   //设置每行行高
   for(int i=0;i<leftPropertytable->rowCount();++i)
   {
        leftPropertytable->setRowHeight(i,20);
   }
   //设置第一列列宽
   //leftPropertytable->setColumnWidth(0,30);不起作用
   //禁止修改
   leftPropertytable->setEditTriggers(QAbstractItemView::NoEditTriggers);
   connect(stateCombox, SIGNAL(currentIndexChanged(int)), this,SLOT(clickCommandStateCombobox(int)));
}
//左侧窗口事件--------------------------------------

//5.中间窗口的事件--------------------------------------
//鼠标点击blockitem,或者键盘移动导致被选中的blockitem发生改变
void MainWindow::slotCmdEditTableCurrentChanged(const QModelIndex &currentIndex, const QModelIndex &previous)
{
    //qDebug()<<"222222";
    //1.获取命令
    postCommand * selCmd = GetSelCommand();
    if(selCmd==NULL)
      return;
    PostParameter *parameter = NULL;
    QStandardItem *currentItem = commandBlkModel->itemFromIndex(currentIndex);
    bool isNotEmpty = true;
    //初步筛选：如果所在的行>该命令的blocks的数目，
    if(currentItem->row() > selCmd->blocklist.size()-1 ||
            selCmd->blocklist.size()==0)
    {
        isNotEmpty = false;
    }
    else
    {
        list<postBlock>::iterator blkIterator = selCmd->blocklist.begin();
        advance(blkIterator,currentItem->row());//将迭代器向后移动destRow个位置,行
        //列大于所在block的blockitem的数目则禁止编辑
        if(currentItem->column() > blkIterator->bloskItemList.size()-1 ||
                blkIterator->bloskItemList.size()==0)
        {
            isNotEmpty = false;
        }
        else
        {
            qDebug()<<blkIterator->bloskItemList.size();
            list<postBlockItem>::iterator itemIterator = blkIterator->bloskItemList.begin();
            advance(itemIterator,currentItem->column());//将迭代器向后移动destColumn个位置，列
            if(itemIterator->IsEmpty())//空的
                isNotEmpty = false;
            else
            {
                parameter = &(itemIterator->Parameter);
                isNotEmpty = true;
            }
        }
    }
    //如果是空的参数，则禁止删除,右侧属性窗口隐藏
    if(!isNotEmpty)
    {
        pDelBnt->setEnabled(false);
    }
    else//可以删除，刷新右侧属性窗口
    {
        pDelBnt->setEnabled(true);
    }
    //更新右侧blockitem的属性窗口
    UpdateRightPropertytable(parameter);
}
//blockitem编辑结束事件(文本参数编辑结束)
void MainWindow::cmdBlkItemdataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    //1.获取命令
    postCommand * selCmd = GetSelCommand();
    if(selCmd==NULL)
        return;
    //2.行和列
    size_t destRow = topLeft.row();
    size_t destColumn = topLeft.column();
    //3.修改 destRow行destColumn列的值
    list<postBlock>::iterator blkIterator = selCmd->blocklist.begin();
    advance(blkIterator,destRow);//将迭代器向后移动destRow个位置,行
    list<postBlockItem>::iterator itemIterator = blkIterator->bloskItemList.begin();
    advance(itemIterator,destColumn);//将迭代器向后移动destColumn个位置，列
    QStandardItem *currentItem = commandBlkModel->itemFromIndex(topLeft);
    PostParameter parameter = PostParameter(currentItem->text());
    itemIterator->Parameter = parameter;
    //4.更新模型
    UpdateCommandBlkModel(selCmd);
}
//中间窗口的事件--------------------------------------

//6.右侧窗口的事件--------------------------------------
void MainWindow::UpdateRightPropertytable(PostParameter *parameter)//更新右侧blockitem的属性窗口
{
    if(parameter==NULL)
    {
        pRightdock->setVisible(false);
        //pPropertytable->setVisible(false);
        return;
    }

    pRightdock->setVisible(true);

    if(parameter->Type== Text )//文本参数
    {
        pPropertytable->setColumnCount(2);
        pPropertytable->setRowCount(2);
        pPropertytable->verticalHeader()->hide();//隐藏列头
        pPropertytable->horizontalHeader()->hide();//隐藏行头
        //1.type
        pPropertytable->setItem(0,0,new QTableWidgetItem("Type"));
        pPropertytable->setItem(0,1,new QTableWidgetItem("Text"));
        //2.value
        pPropertytable->setItem(1,0,new QTableWidgetItem("Value"));
        QString str = "";
        parameter->GetOutPutString(str,true);
        pPropertytable->setItem(1,1,new QTableWidgetItem(str));
    }
    else if( parameter->Type== GeneralParameter || parameter->Type== GroupParameter )//一般参数和组参数
    {
        //1.刷新pPropertytable
        pPropertytable->setColumnCount(2);
        pPropertytable->setRowCount(3);
        pPropertytable->verticalHeader()->hide();//隐藏列头
        pPropertytable->horizontalHeader()->hide();//隐藏行头

        //1.type
        QString type = "UNKnown";
        pPropertytable->setItem(0,0,new QTableWidgetItem("Type"));
        if(parameter->Type==GeneralParameter)//一般参数
        {
            type = "GeneralParameter";
        }
        else if(parameter->Type==GroupParameter)//组值参数
        {
            type = "GroupParameter";
        }
        pPropertytable->setItem(0,1,new QTableWidgetItem(type));

        //2.name
        pPropertytable->setItem(1,0,new QTableWidgetItem("Name"));
        pPropertytable->setItem(1,1,new QTableWidgetItem(parameter->Name));

        //3.format
        pPropertytable->setItem(2,0,new QTableWidgetItem("Format"));
        formatCombox = new QComboBox (pPropertytable) ;

        for(map<int,ParameterFormat>::iterator i = xpost.postData.FormatsMap.begin();
            i!=xpost.postData.FormatsMap.end();++i)
        {
            formatCombox->addItem(i->second.Name,i->first);
            //qDebug()<<i->second.Name<<i->first;
        }
        formatCombox->setCurrentText(parameter->Format.Name);
        pPropertytable->setCellWidget(2,1,formatCombox);

        connect(formatCombox, SIGNAL(currentIndexChanged(int)), this,SLOT(clickFormatCombobox(int)));

        //设置每行行高
        for(int i=0;i<pPropertytable->rowCount();++i)
        {
            pPropertytable->setRowHeight(i,20);
        }
        //禁止修改
        pPropertytable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }
}
void MainWindow::clickFormatCombobox(int index)//blockitem对应的参数的格式下拉框
{
    //1.找到对应的命令
     postCommand * selCmd = GetSelCommand();
     if(selCmd==NULL)
         return;
    //2.找到表格的位置
    QModelIndex currentIndex = CmdBlockTable->selectionModel()->currentIndex();
    QStandardItem *currentItem = commandBlkModel->itemFromIndex(currentIndex);
    //初步筛选：如果所在的行>该命令的blocks的数目，
    if(currentItem->row() > selCmd->blocklist.size()-1 ||
            selCmd->blocklist.size()==0)
    {
        return;
    }
    else
    {
        list<postBlock>::iterator blkIterator = selCmd->blocklist.begin();
        advance(blkIterator,currentItem->row());//将迭代器向后移动destRow个位置,行
        //列大于所在block的blockitem的数目则禁止编辑
        if(currentItem->column() > blkIterator->bloskItemList.size()-1 ||
                blkIterator->bloskItemList.size()==0)
        {
            return;
        }
        else
        {
            qDebug()<<blkIterator->bloskItemList.size();
            list<postBlockItem>::iterator itemIterator = blkIterator->bloskItemList.begin();
            advance(itemIterator,currentItem->column());//将迭代器向后移动destColumn个位置，列
            if(itemIterator->IsEmpty())//空的
                return;
            else
            {
                if(itemIterator->Parameter.Type== Text )//文本参数
                    return;
                else
                {
                    int formatId = formatCombox->currentData().toInt();
                    map<int,ParameterFormat>::iterator formatkey = xpost.postData.FormatsMap.find(formatId);
                    if(formatkey==xpost.postData.FormatsMap.end())
                        return;
                    ParameterFormat fmt = xpost.postData.FormatsMap.at(formatId);
                    itemIterator->Parameter.Format=fmt;
                }
            }
        }
    }
}
//右侧窗口的事件--------------------------------------

//7.其他函数--------------------------------------
void MainWindow::UpdateWindowShowState(bool state)//控制各个窗口的显示和隐藏状态
{
    pParCmdComAction->setVisible(state);
    pspecialParCmdComAction->setVisible(state);
    paddParameterBntAction->setVisible(state);
    paddTextBntAction->setVisible(state);
    paddnewlineAction->setVisible(state);
    pDelBntAction->setVisible(state);
    ppreviewdock->setVisible(state);
    pRightdock->setVisible(state);
    pCmdEdittab->setVisible(state);
    leftPropertytable->setVisible(state);
}
postCommand *MainWindow::GetSelCommand()//获取当前选中的命令
{
    //1.找到对应的命令
    QModelIndex CmdIndex = commandTree->currentIndex();
    QStandardItem *currentCmdItem = commandTreeModel->itemFromIndex(CmdIndex);
    //获取命令的ID
    if(!(currentCmdItem->data(Qt::UserRole).canConvert<int>()))
        return NULL;
    int cmdId  = currentCmdItem->data(Qt::UserRole).value<int>();
    map<int,postCommand>::iterator key = xpost.postData.CommandsMap.find(cmdId);
    if(key==xpost.postData.CommandsMap.end())
        return NULL;

    return &(xpost.postData.CommandsMap[cmdId]);
}
//其他函数--------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

