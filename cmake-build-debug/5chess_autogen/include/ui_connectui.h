/********************************************************************************
** Form generated from reading UI file 'connectui.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTUI_H
#define UI_CONNECTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectUI
{
public:
    QLabel *label_2;
    QLabel *label_5;
    QLineEdit *addr;
    QLabel *label;
    QLabel *label_3;
    QPushButton *testconn;
    QLabel *label_4;
    QLineEdit *gameid;
    QLineEdit *username;
    QPushButton *onlinepvp;
    QPushButton *pve;
    QPushButton *localpvp;
    QPushButton *join;
    QPushButton *eve;
    QTableWidget *games;
    QLineEdit *password;
    QLabel *label_6;
    QPushButton *reg;

    void setupUi(QWidget *ConnectUI)
    {
        if (ConnectUI->objectName().isEmpty())
            ConnectUI->setObjectName("ConnectUI");
        ConnectUI->resize(772, 565);
        label_2 = new QLabel(ConnectUI);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 70, 131, 31));
        label_5 = new QLabel(ConnectUI);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 520, 291, 16));
        addr = new QLineEdit(ConnectUI);
        addr->setObjectName("addr");
        addr->setGeometry(QRect(180, 80, 141, 21));
        label = new QLabel(ConnectUI);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 201, 41));
        QFont font;
        font.setPointSize(25);
        label->setFont(font);
        label_3 = new QLabel(ConnectUI);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 110, 71, 31));
        testconn = new QPushButton(ConnectUI);
        testconn->setObjectName("testconn");
        testconn->setGeometry(QRect(390, 80, 131, 31));
        label_4 = new QLabel(ConnectUI);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(60, 150, 71, 31));
        gameid = new QLineEdit(ConnectUI);
        gameid->setObjectName("gameid");
        gameid->setGeometry(QRect(180, 160, 141, 21));
        username = new QLineEdit(ConnectUI);
        username->setObjectName("username");
        username->setGeometry(QRect(180, 120, 141, 21));
        onlinepvp = new QPushButton(ConnectUI);
        onlinepvp->setObjectName("onlinepvp");
        onlinepvp->setGeometry(QRect(40, 250, 81, 31));
        pve = new QPushButton(ConnectUI);
        pve->setObjectName("pve");
        pve->setGeometry(QRect(260, 250, 81, 31));
        localpvp = new QPushButton(ConnectUI);
        localpvp->setObjectName("localpvp");
        localpvp->setGeometry(QRect(370, 250, 81, 31));
        join = new QPushButton(ConnectUI);
        join->setObjectName("join");
        join->setGeometry(QRect(150, 250, 81, 31));
        eve = new QPushButton(ConnectUI);
        eve->setObjectName("eve");
        eve->setGeometry(QRect(480, 250, 81, 31));
        games = new QTableWidget(ConnectUI);
        if (games->columnCount() < 4)
            games->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        games->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        games->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        games->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        games->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        games->setObjectName("games");
        games->setGeometry(QRect(30, 310, 571, 181));
        password = new QLineEdit(ConnectUI);
        password->setObjectName("password");
        password->setGeometry(QRect(180, 200, 141, 21));
        label_6 = new QLabel(ConnectUI);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(60, 190, 71, 31));
        reg = new QPushButton(ConnectUI);
        reg->setObjectName("reg");
        reg->setGeometry(QRect(390, 130, 131, 31));

        retranslateUi(ConnectUI);

        QMetaObject::connectSlotsByName(ConnectUI);
    } // setupUi

    void retranslateUi(QWidget *ConnectUI)
    {
        ConnectUI->setWindowTitle(QCoreApplication::translate("ConnectUI", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectUI", "Server Address", nullptr));
        label_5->setText(QCoreApplication::translate("ConnectUI", "Server Type:", nullptr));
        label->setText(QCoreApplication::translate("ConnectUI", "5-Chess!!!!!", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectUI", "Username", nullptr));
        testconn->setText(QCoreApplication::translate("ConnectUI", "Test Connnection", nullptr));
        label_4->setText(QCoreApplication::translate("ConnectUI", "Game ID", nullptr));
        onlinepvp->setText(QCoreApplication::translate("ConnectUI", "Online PVP", nullptr));
        pve->setText(QCoreApplication::translate("ConnectUI", "PVE", nullptr));
        localpvp->setText(QCoreApplication::translate("ConnectUI", "Local PVP", nullptr));
        join->setText(QCoreApplication::translate("ConnectUI", "Join PVP", nullptr));
        eve->setText(QCoreApplication::translate("ConnectUI", "EVE", nullptr));
        QTableWidgetItem *___qtablewidgetitem = games->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ConnectUI", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = games->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ConnectUI", "gamerA", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = games->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ConnectUI", "gamerB", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = games->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ConnectUI", "Status", nullptr));
        password->setText(QString());
        label_6->setText(QCoreApplication::translate("ConnectUI", "Password", nullptr));
        reg->setText(QCoreApplication::translate("ConnectUI", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectUI: public Ui_ConnectUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTUI_H
