#include "settingform.h"
#include "ui_settingform.h"

SettingForm::SettingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);
    initForm();
}

SettingForm::~SettingForm()
{
    delete ui;
}
void SettingForm::initForm()
{

//未完成，默认以五轴AC-RTCP机床结构输出

    ui->treeWidget->setHeaderHidden(true);//隐藏表头方法
    //ui->treeWidget->setHeaderLabels(QStringList()<<"设置");
    ui->treeWidget->setStyle(QStyleFactory::create("windows"));

    QTreeWidgetItem *ptopitem4 = new QTreeWidgetItem (QStringList()<<"机床设置") ;
    ui->treeWidget->addTopLevelItem(ptopitem4);
    QTreeWidgetItem *ptopitem = new QTreeWidgetItem (QStringList()<<"参数初始化") ;
    ui->treeWidget->addTopLevelItem(ptopitem);
    QTreeWidgetItem *ptopitem2 = new QTreeWidgetItem (QStringList()<<"钻孔设置") ;
    ui->treeWidget->addTopLevelItem(ptopitem2);
    QTreeWidgetItem *ptopitem3 = new QTreeWidgetItem (QStringList()<<"多轴设置") ;
    ui->treeWidget->addTopLevelItem(ptopitem3);

    QTreeWidgetItem *ptopitem5 = new QTreeWidgetItem (QStringList()<<"格式设置") ;
    ui->treeWidget->addTopLevelItem(ptopitem5);

}
