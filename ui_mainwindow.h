/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *localGameButton;
    QLabel *label;
    QPushButton *aiGameButton;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/blackpiece.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        localGameButton = new QPushButton(centralwidget);
        localGameButton->setObjectName(QString::fromUtf8("localGameButton"));
        localGameButton->setGeometry(QRect(175, 250, 150, 70));
        QFont font;
        font.setPointSize(12);
        localGameButton->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 125, 500, 100));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(18);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        aiGameButton = new QPushButton(centralwidget);
        aiGameButton->setObjectName(QString::fromUtf8("aiGameButton"));
        aiGameButton->setGeometry(QRect(175, 350, 150, 70));
        aiGameButton->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 100, 500, 50));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AI  \344\272\224\345\255\220\346\243\213", nullptr));
        localGameButton->setText(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260\346\270\270\346\210\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Gobang AI", nullptr));
        aiGameButton->setText(QCoreApplication::translate("MainWindow", "\344\272\272\346\234\272\346\270\270\346\210\217", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
