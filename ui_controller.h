/********************************************************************************
** Form generated from reading UI file 'controller.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <board.h>

QT_BEGIN_NAMESPACE

class Ui_Controller
{
public:
    Board *chessboard;
    QWidget *panel;
    QPushButton *undoButton;
    QWidget *blackPanel;
    QLabel *blackImage;
    QLCDNumber *blackTimer;
    QLabel *blackLable2;
    QWidget *whitePanel;
    QLabel *whiteImage;
    QLCDNumber *whiteTimer;
    QLabel *whiteLable2;
    QPushButton *returnButton;

    void setupUi(QWidget *Controller)
    {
        if (Controller->objectName().isEmpty())
            Controller->setObjectName(QString::fromUtf8("Controller"));
        Controller->resize(1000, 750);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/blackpiece.png"), QSize(), QIcon::Normal, QIcon::Off);
        Controller->setWindowIcon(icon);
        chessboard = new Board(Controller);
        chessboard->setObjectName(QString::fromUtf8("chessboard"));
        chessboard->setGeometry(QRect(0, 0, 750, 750));
        panel = new QWidget(Controller);
        panel->setObjectName(QString::fromUtf8("panel"));
        panel->setGeometry(QRect(750, 0, 250, 750));
        undoButton = new QPushButton(panel);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));
        undoButton->setGeometry(QRect(75, 550, 100, 50));
        QFont font;
        font.setPointSize(12);
        undoButton->setFont(font);
        blackPanel = new QWidget(panel);
        blackPanel->setObjectName(QString::fromUtf8("blackPanel"));
        blackPanel->setGeometry(QRect(25, 50, 200, 250));
        blackImage = new QLabel(blackPanel);
        blackImage->setObjectName(QString::fromUtf8("blackImage"));
        blackImage->setGeometry(QRect(0, 64, 200, 50));
        blackImage->setScaledContents(false);
        blackImage->setAlignment(Qt::AlignCenter);
        blackTimer = new QLCDNumber(blackPanel);
        blackTimer->setObjectName(QString::fromUtf8("blackTimer"));
        blackTimer->setGeometry(QRect(25, 125, 150, 50));
        blackLable2 = new QLabel(blackPanel);
        blackLable2->setObjectName(QString::fromUtf8("blackLable2"));
        blackLable2->setGeometry(QRect(0, 200, 200, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(8);
        blackLable2->setFont(font1);
        blackLable2->setAlignment(Qt::AlignCenter);
        whitePanel = new QWidget(panel);
        whitePanel->setObjectName(QString::fromUtf8("whitePanel"));
        whitePanel->setGeometry(QRect(25, 250, 200, 250));
        whiteImage = new QLabel(whitePanel);
        whiteImage->setObjectName(QString::fromUtf8("whiteImage"));
        whiteImage->setGeometry(QRect(0, 64, 200, 50));
        whiteImage->setAlignment(Qt::AlignCenter);
        whiteTimer = new QLCDNumber(whitePanel);
        whiteTimer->setObjectName(QString::fromUtf8("whiteTimer"));
        whiteTimer->setGeometry(QRect(25, 125, 150, 50));
        whiteLable2 = new QLabel(whitePanel);
        whiteLable2->setObjectName(QString::fromUtf8("whiteLable2"));
        whiteLable2->setGeometry(QRect(0, 200, 200, 25));
        whiteLable2->setFont(font1);
        whiteLable2->setAlignment(Qt::AlignCenter);
        returnButton = new QPushButton(panel);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setGeometry(QRect(75, 625, 100, 50));
        returnButton->setFont(font);

        retranslateUi(Controller);

        QMetaObject::connectSlotsByName(Controller);
    } // setupUi

    void retranslateUi(QWidget *Controller)
    {
        Controller->setWindowTitle(QString());
        undoButton->setText(QCoreApplication::translate("Controller", "\346\202\224\346\243\213", nullptr));
        blackImage->setText(QCoreApplication::translate("Controller", "blackImage", nullptr));
        blackLable2->setText(QString());
        whiteImage->setText(QCoreApplication::translate("Controller", "whiteImage", nullptr));
        whiteLable2->setText(QString());
        returnButton->setText(QCoreApplication::translate("Controller", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Controller: public Ui_Controller {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLLER_H
