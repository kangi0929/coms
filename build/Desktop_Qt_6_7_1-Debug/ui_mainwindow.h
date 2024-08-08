/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonU;
    QPushButton *pushButtonD;
    QPushButton *pushButtonL;
    QPushButton *pushButtonR;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 362);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButtonU = new QPushButton(centralwidget);
        pushButtonU->setObjectName("pushButtonU");
        pushButtonU->setGeometry(QRect(190, 70, 89, 25));
        pushButtonD = new QPushButton(centralwidget);
        pushButtonD->setObjectName("pushButtonD");
        pushButtonD->setGeometry(QRect(190, 170, 89, 25));
        pushButtonL = new QPushButton(centralwidget);
        pushButtonL->setObjectName("pushButtonL");
        pushButtonL->setGeometry(QRect(70, 120, 89, 25));
        pushButtonR = new QPushButton(centralwidget);
        pushButtonR->setObjectName("pushButtonR");
        pushButtonR->setGeometry(QRect(300, 120, 89, 25));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(480, 60, 89, 25));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(620, 60, 89, 25));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(620, 120, 89, 25));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(480, 120, 89, 25));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(620, 180, 89, 25));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(480, 180, 89, 25));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(620, 240, 89, 25));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(458, 240, 111, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonU->setText(QCoreApplication::translate("MainWindow", "\344\270\212", nullptr));
        pushButtonD->setText(QCoreApplication::translate("MainWindow", "\344\270\213", nullptr));
        pushButtonL->setText(QCoreApplication::translate("MainWindow", "\345\267\246", nullptr));
        pushButtonR->setText(QCoreApplication::translate("MainWindow", "\345\217\263", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\217\230\345\200\215\347\237\255", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\217\230\345\200\215\351\225\277", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\350\201\232\347\204\246\350\277\234", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\350\201\232\347\204\246\350\277\221", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\346\277\200\345\205\211\345\260\217", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\346\277\200\345\205\211\345\244\247", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\344\272\221\345\217\260\345\275\222\351\233\266", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\344\272\221\345\217\260\345\275\222\351\233\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
