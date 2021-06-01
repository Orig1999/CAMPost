#include "mainwindow.h"
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
    //InitModel();//初始化Model
    //InitUI();//初始化界面的控件
    //    connect(CmdBlockTable->selectionModel(),&QItemSelectionModel::selectionChanged,
    //            this,&MainWindow::slotCmdEditTableSelectionChanged);//命令的tableview的选中项发生改变
    //    connect(CmdBlockTable->selectionModel(),&QItemSelectionModel::currentRowChanged,
    //            this,&MainWindow::CmdEditTableSelectionRowChanged);//命令的tableview的选中项发生改变
    //    connect(CmdBlockTable->selectionModel(),&QItemSelectionModel::currentChanged,
    //            this,&MainWindow::slotCmdEditTableCurrentChanged);//命令的tableview的选中项发生改变
    //    connect(commandTree,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this, SLOT(onCmdsTreeClick(QTreeWidgetItem *, int )));//添加参数
    //    connect(openMenuAction,SIGNAL(triggered()),this,SLOT(onOpenFileTriggered()));//打开
    //    connect(saveMenuAction,SIGNAL(triggered()),this,SLOT(onSaveMenuActionTriggered()));//保存
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
    saveMenuAction = pFileMenu->addAction("保存");
    saveAsMenuAction = pFileMenu->addAction("另存");
    setingMenuAction = pFileMenu->addAction("设置");

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
    QTreeWidget *pCLDATAtree = new QTreeWidget (processorEditTab) ;
    //commandTree->setHeaderLabels(QStringList()<<"11"<<"22");
    pCLDATAtree->setHeaderLabels(QStringList()<<"CLDATA");
    pCLDATAtree->setStyle(QStyleFactory::create("windows"));
    QTreeWidgetItem *ptopitem = new QTreeWidgetItem (QStringList()<<"刀轨文件列表") ;
    pCLDATAtree->addTopLevelItem(ptopitem);
    //QTreeWidgetItem *pchilditem = new QTreeWidgetItem (QStringList()<<"PathStart") ;
    //ptopitem->addChild(pchilditem);
    processorEditTab->addTab(pCLDATAtree,"后处理");

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
    UpdateCmdTreeModel();
    commandTree->setModel(commandTreeModel);

    connect(commandTree->selectionModel(),&QItemSelectionModel::currentChanged,
            this,&MainWindow::slotCmdsTreeCurrentChanged);//鼠标单击命令树

    connect(cmdParamFmtScriptTreeTab,SIGNAL(currentChanged(int)),this,
            SLOT(slotCmdParamScriptTabCurrentChanged(int)));
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
    pCmdEdittab->addTab(CmdBlockTable,"");//更新tableview的标题

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
    commandTreeModel = new QStandardItemModel;//命令树
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
                content = item->Parameter.GetValue();
                standarditem = new QStandardItem(content);
                itemList << standarditem;
                standarditem->setTextAlignment(Qt::AlignCenter);//中间对齐

                standarditem->setBackground(QBrush(QColor(255,255,0)));
                //standarditem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                standarditem->setFlags(Qt::ItemIsEnabled);
                break;
            case Text://文本
                content = item->Parameter.GetValue();
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
void MainWindow::onOpenFileTriggered()
{
    //qDebug()<<"ccccc"<<endl;
    //保存成xml文件
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
}
void MainWindow::onSaveMenuActionTriggered()
{
//    //qDebug()<<"ccccc"<<endl;
//    QFileInfo file(xpost.FilePath);
//    QString filefullpath = "";
//    if(!file.isDir())
//    {
//        filefullpath = QFileDialog::getSaveFileName(this,"选择保存的文件","",
//                                                            "xpos(*.xpost)");
//        if(filefullpath.isNull())
//            return;

//        file = QFileInfo(filefullpath);
//        xpost.FileName=file.fileName();
//        xpost.FilePath=file.absolutePath();
//    }
//    //保存成xml文件
//    QFile xmlFile(filefullpath);
//    if(!xmlFile.open(QFile::WriteOnly|QFile::Truncate))
//        return;
//    QDomDocument doc;
//    QDomProcessingInstruction instruction;
//    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
//    doc.appendChild(instruction);

//    //添加根节点
//    QDomElement root = doc.createElement("Post");
//    doc.appendChild(root);
//    //添加一级节点命令
//    QDomElement cmds = doc.createElement("Commands");
//    root.appendChild(cmds);
//    //添加二级节点，具体的命令节点
//    for(map<int,postCommand>::iterator i = xpost.postData.CommandsMap.begin();
//        i!=xpost.postData.CommandsMap.end();++i)
//    {
//        //第 cmdIndex 个命令
//        QDomElement iCmd = doc.createElement("Command");
//        iCmd.setAttribute("id",i->first); //创建属性id
//        iCmd.setAttribute("id",i->second.Name); //创建属性name
//        iCmd.setAttribute("id",i->second.State); //创建属性state
//        cmds.appendChild(iCmd);

//        for(size_t cmdIndex = 0 ; cmdIndex<i->second.vBlocks.size(); ++cmdIndex)
//        {
//            QDomElement iBlock = doc.createElement("Block");
//            cmds.appendChild(iBlock);

//            for(size_t j=0;j<i->second.vBlocks[cmdIndex].vBlockItems.size();++j)
//            {
//                pCmdBlocksEdittable->setItem(
//                            0,0,new QTableWidgetItem(
//                            i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.GetValue()));
//                    switch (i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.Type) {
//                    case Text://文本
//                    {
//                        QDomElement textBlockitem = doc.createElement("Blockitem");
//                        textBlockitem.setAttribute("type","Text"); //创建属性type
//                        textBlockitem.setAttribute("value",i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.Value.s); //创建属性value
//                        textBlockitem.setAttribute("state",i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.State); //创建属性state
//                        iBlock.appendChild(textBlockitem);
//                    }
//                        break;
//                    case GeneralParameter://一般参数
//                    {
//                        QDomElement textBlockitem = doc.createElement("Blockitem");
//                        textBlockitem.setAttribute("type","Parameter"); //创建属性id
//                        textBlockitem.setAttribute("id",i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.ID); //创建属性id
//                        textBlockitem.setAttribute("state",i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.State); //创建属性state
//                        iBlock.appendChild(textBlockitem);
//                    }
//                        break;
//                    case GroupParameter://组值参数
//                    {
//                        QDomElement textBlockitem = doc.createElement("Blockitem");
//                        textBlockitem.setAttribute("type","Parameter"); //创建属性id
//                        textBlockitem.setAttribute("id",i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.ID); //创建属性id
//                        textBlockitem.setAttribute("state",i->second.vBlocks[cmdIndex].vBlockItems[j].Parameter.State); //创建属性state
//                        iBlock.appendChild(textBlockitem);
//                    }
//                        break;
//                    default:
//                        break;
//                }
//            }
//        }
//    }

//    //添加一级节点参数
//    QDomElement params = doc.createElement("Parameters");
//    root.appendChild(params);
//    //添加二级节点，具体的参数节点

//    //添加一级节点格式
//    QDomElement formats = doc.createElement("Formats");
//    root.appendChild(formats);
//    //添加二级节点，具体的格式节点

//    //输出到文件
//    QTextStream out_stream(&xmlFile);
//    doc.save(out_stream,4); //缩进4格
//    xmlFile.close();
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
    qDebug()<<"aaaa:"<<blkIterator->bloskItemList.size();
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
    qDebug()<<"c:"<<blkIterator->bloskItemList.size();
    UpdateCommandBlkModel(selCmd);//更新模型
}
void MainWindow::onAddParameter()//添加参数
{
    //通过id拿到参数对象，id号绑定在combox的itemdata中
    int paramid = pspecialParCmdCom->currentData().toInt();
    map<int,PostParameter>::iterator paramkey = xpost.postData.ParametersMap.find(paramid);
    if(paramkey==xpost.postData.ParametersMap.end())
        return;
    PostParameter parameter = xpost.postData.ParametersMap[paramid];
    addParameter(parameter);
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
    if(index==0)//后处理
    {
        UpdateWindowShowState(false);
    }
    else
        UpdateWindowShowState(true);
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
        pPropertytable->setItem(1,1,new QTableWidgetItem(parameter->GetValue()));
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

