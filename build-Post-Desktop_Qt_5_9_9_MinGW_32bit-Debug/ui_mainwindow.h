/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionnewFile;
    QAction *actionopenFile;
    QAction *actionsaveFile;
    QAction *actionsaveAsFile;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionnewFile = new QAction(MainWindow);
        actionnewFile->setObjectName(QStringLiteral("actionnewFile"));
        actionopenFile = new QAction(MainWindow);
        actionopenFile->setObjectName(QStringLiteral("actionopenFile"));
        actionsaveFile = new QAction(MainWindow);
        actionsaveFile->setObjectName(QStringLiteral("actionsaveFile"));
        actionsaveAsFile = new QAction(MainWindow);
        actionsaveAsFile->setObjectName(QStringLiteral("actionsaveAsFile"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionnewFile->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", Q_NULLPTR));
        actionopenFile->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        actionsaveFile->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        actionsaveAsFile->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
