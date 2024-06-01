/********************************************************************************
** Form generated from reading UI file 'pvplocal.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVPLOCAL_H
#define UI_PVPLOCAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pvplocal
{
public:
    QLabel *status;

    void setupUi(QWidget *pvplocal)
    {
        if (pvplocal->objectName().isEmpty())
            pvplocal->setObjectName("pvplocal");
        pvplocal->resize(1512, 850);
        status = new QLabel(pvplocal);
        status->setObjectName("status");
        status->setGeometry(QRect(60, 50, 491, 41));

        retranslateUi(pvplocal);

        QMetaObject::connectSlotsByName(pvplocal);
    } // setupUi

    void retranslateUi(QWidget *pvplocal)
    {
        pvplocal->setWindowTitle(QCoreApplication::translate("pvplocal", "Form", nullptr));
        status->setText(QCoreApplication::translate("pvplocal", "Status:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pvplocal: public Ui_pvplocal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVPLOCAL_H
