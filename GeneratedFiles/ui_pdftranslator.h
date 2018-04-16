/********************************************************************************
** Form generated from reading UI file 'pdftranslator.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFTRANSLATOR_H
#define UI_PDFTRANSLATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pdftranslatorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pdftranslatorClass)
    {
        if (pdftranslatorClass->objectName().isEmpty())
            pdftranslatorClass->setObjectName(QStringLiteral("pdftranslatorClass"));
        pdftranslatorClass->resize(600, 400);
        menuBar = new QMenuBar(pdftranslatorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        pdftranslatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pdftranslatorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        pdftranslatorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(pdftranslatorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pdftranslatorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(pdftranslatorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        pdftranslatorClass->setStatusBar(statusBar);

        retranslateUi(pdftranslatorClass);

        QMetaObject::connectSlotsByName(pdftranslatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *pdftranslatorClass)
    {
        pdftranslatorClass->setWindowTitle(QApplication::translate("pdftranslatorClass", "pdftranslator", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class pdftranslatorClass: public Ui_pdftranslatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFTRANSLATOR_H
