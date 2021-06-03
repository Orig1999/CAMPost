#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTabWidget>
#include <QString>
#include <QStyleFactory>
#include <QDebug>
#include <QComboBox>
#include <QGridLayout>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTextBrowser>
#include <QStatusBar>
#include "XPost.h"
#include <QLineEdit>
#include <map>
#include <Qtxml>
#include <QFileDialog>
#include <QDomElement>
#include <QItemDelegate>
//----------
#include <QStandardItemModel>
//----------

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
 //----------------
    QStandardItemModel* commandTreeModel;//命令树数据
    QStandardItemModel* commandBlkModel;//命令的block数据
    QStandardItemModel* ParameterTreeModel;//参数树模型数据
    QStandardItemModel* fmtTreeModel;//格式树模型数据
    QStandardItemModel* scriptTreeModel;//脚本树模型数据

    XPost xpost;//后处理文件数据
    void UpdateCommandBlkModel(postCommand *selCmd);//更新命令的block数据
    void UpdateCmdTreeModel();//更新命令树的model
    void UpdateParameterTreeModel();//更新参数树的model
    void UpdateFmtTreeModel();//更新格式树的model
    void UpdateScriptTreeModel();//更新脚本树的model

    void InitMenuBarAndToolBar();//菜单栏和工具栏
    void InitStatusBar();//状态栏
    void InitLeftWindow();//左侧窗口
    void InitLeftDock();//左侧的dock
    void InitRightWindow();//右侧窗口
    void InitMidWindow();//中间窗口
    void updateLeftPropertytable();//刷新左侧的命令属性窗口
    QTableView *CmdBlockTable;

 //-------------
    Ui::MainWindow *ui;
    //1.菜单
    QMenu *pFileMenu;//菜单
    //2.工具
    QToolBar *ptoolbar;//工具栏
    QAction * newMenuAction ;
    QAction * openMenuAction ;
    QAction * saveMenuAction ;
    QAction * saveAsMenuAction;
    QAction * setingMenuAction;

    QComboBox *pParCmdCom;
    QComboBox *pspecialParCmdCom;
    QPushButton *paddParameterBnt;
    QPushButton *paddTextBnt;
    QPushButton *pDelBnt;
    QPushButton *paddnewLineBnt;

    QAction * pParCmdComAction ;
    QAction * pspecialParCmdComAction ;
    QAction * paddParameterBntAction ;
    QAction * paddTextBntAction;
    QAction * pDelBntAction;
    QAction * paddnewlineAction;


    //3.编辑器
    QTabWidget *processorEditTab;// 左侧[后处理/编辑]tab页
    QTabWidget *cmdParamFmtScriptTreeTab;//  左侧[命令/参数/格式/脚本]tab页
    QTreeView *commandTree;//命令树
    QTreeView *parameterTree;//参数树
    QTreeView *scriptTree;//脚本树
    QTreeView *formatTtree;//格式树
    QTableWidget *leftPropertytable;//左侧属性窗口


    //4.预览窗口
    QDockWidget *ppreviewdock;     //底部浮动窗口
    QTextBrowser *textBrowser;
    QTableWidget *pPreviewtable;

    //5.右侧的属性窗口
    QDockWidget *pRightdock;
    QTableWidget *pPropertytable;
    QComboBox *formatCombox;
    //6.中心窗口
    QTabWidget *pCmdEdittab;//tab页面
    //QTableWidget *pCmdBlocksEdittable;//表格

    //7.后处理对象

    void UpdateParameterCombox();
    void InitCmdTree();
    void InitParameterTree();
    void InitScriptTree();
    void InitFormatTree();
    void UpdateWindowShowState(bool show);
    void UpdateRightPropertytable(PostParameter * parameter);//更新右侧blockitem的属性窗口
    postCommand *GetSelCommand();//获取被选中的命令
protected slots:
    //----------新改的
    //void onCmdsTreeClick(const QModelIndex &index);//鼠标点击命令树事件
    void slotCmdsTreeCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void slotCmdEditTableCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void slotProcessorEditTabCurrentChanged(int index);//[后处理/编辑]tab页面发生切换
    void slotCmdParamScriptTabCurrentChanged(int index);//[命令/参数/格式/脚本]tab页面发生切换
    //void slotCmdEditTableSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    //void CmdEditTableSelectionRowChanged(const QModelIndex &current, const QModelIndex &previous);
    // void
    //----------





    //void onBlocksEdittableCellChanged(QTableWidgetItem *item);//编辑结束
    //void onTabCurrentChanged(int index);

    void clickCommandStateCombobox(int index);
    void clickFormatCombobox(int index);
    //工具栏按钮响应函数

    void addParameter(PostParameter &parameter);//添加参数

    void onAddParameter();//添加参数
    void onAddText();//添加文本
    void onDel();//删除对象
    void onAddNewLine();//添加一行
    void onSaveMenuActionTriggered();
    void writeInCommands(QDomDocument &doc,QDomElement &root);
    void writeInParameters(QDomDocument &doc,QDomElement &root);
    void writeInFormats(QDomDocument &doc,QDomElement &root);

    void onOpenFileTriggered();
    void initFormats(QDomElement formatsElem);
    void initParameters(QDomElement formatsElem);
    void initCommands(QDomElement formatsElem);


    //当QStandardModel中的数据被更改的时候，会发射出dataChanged信号:
    /*[signal] void QAbstractItemModel::dataChanged(const QModelIndex &topLeft,
    const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int> ());

    topLeft bottomRight这两索引指的是表格中被更改数据的区域，
    如果只有一个数据被更改，那么topLeft等于bottomRight
    */
    //blockitem的值发生改变
    void cmdBlkItemdataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    //void cmdTreedataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
};

#endif // MAINWINDOW_H
