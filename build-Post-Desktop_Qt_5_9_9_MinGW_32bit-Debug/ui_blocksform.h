/********************************************************************************
** Form generated from reading UI file 'blocksform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOCKSFORM_H
#define UI_BLOCKSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_blocksForm
{
public:
    QTableWidget *tableWidget;
    QDockWidget *preview_dockWidget;
    QWidget *dockWidgetContents;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *preview_tableWidget;
    QTextBrowser *preview_textBrowser;

    void setupUi(QWidget *blocksForm)
    {
        if (blocksForm->objectName().isEmpty())
            blocksForm->setObjectName(QStringLiteral("blocksForm"));
        blocksForm->resize(400, 300);
        tableWidget = new QTableWidget(blocksForm);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 401, 211));
        preview_dockWidget = new QDockWidget(blocksForm);
        preview_dockWidget->setObjectName(QStringLiteral("preview_dockWidget"));
        preview_dockWidget->setGeometry(QRect(0, 210, 401, 91));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        horizontalLayoutWidget = new QWidget(dockWidgetContents);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, -1, 411, 81));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        preview_tableWidget = new QTableWidget(horizontalLayoutWidget);
        preview_tableWidget->setObjectName(QStringLiteral("preview_tableWidget"));

        horizontalLayout->addWidget(preview_tableWidget);

        preview_textBrowser = new QTextBrowser(horizontalLayoutWidget);
        preview_textBrowser->setObjectName(QStringLiteral("preview_textBrowser"));

        horizontalLayout->addWidget(preview_textBrowser);

        preview_dockWidget->setWidget(dockWidgetContents);

        retranslateUi(blocksForm);

        QMetaObject::connectSlotsByName(blocksForm);
    } // setupUi

    void retranslateUi(QWidget *blocksForm)
    {
        blocksForm->setWindowTitle(QApplication::translate("blocksForm", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class blocksForm: public Ui_blocksForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCKSFORM_H
