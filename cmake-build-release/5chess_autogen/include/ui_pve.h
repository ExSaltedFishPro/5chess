/********************************************************************************
** Form generated from reading UI file 'pve.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVE_H
#define UI_PVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pve
{
public:
    QLabel *status;

    void setupUi(QWidget *pve)
    {
        if (pve->objectName().isEmpty())
            pve->setObjectName("pve");
        pve->resize(1512, 850);
        status = new QLabel(pve);
        status->setObjectName("status");
        status->setGeometry(QRect(60, 50, 491, 41));

        retranslateUi(pve);

        QMetaObject::connectSlotsByName(pve);
    } // setupUi

    void retranslateUi(QWidget *pve)
    {
        pve->setWindowTitle(QCoreApplication::translate("pve", "Form", nullptr));
        status->setText(QCoreApplication::translate("pve", "Status:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pve: public Ui_pve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVE_H
