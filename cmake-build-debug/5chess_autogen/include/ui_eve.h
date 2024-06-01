/********************************************************************************
** Form generated from reading UI file 'eve.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVE_H
#define UI_EVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_eve
{
public:

    void setupUi(QWidget *eve)
    {
        if (eve->objectName().isEmpty())
            eve->setObjectName("eve");
        eve->resize(1512, 850);

        retranslateUi(eve);

        QMetaObject::connectSlotsByName(eve);
    } // setupUi

    void retranslateUi(QWidget *eve)
    {
        eve->setWindowTitle(QCoreApplication::translate("eve", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class eve: public Ui_eve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVE_H
