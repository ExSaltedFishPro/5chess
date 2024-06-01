/********************************************************************************
** Form generated from reading UI file 'board.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARD_H
#define UI_BOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_board
{
public:
    QLabel *info;

    void setupUi(QWidget *board)
    {
        if (board->objectName().isEmpty())
            board->setObjectName("board");
        board->resize(1512, 850);
        info = new QLabel(board);
        info->setObjectName("info");
        info->setGeometry(QRect(60, 190, 561, 151));
        QFont font;
        font.setPointSize(20);
        info->setFont(font);

        retranslateUi(board);

        QMetaObject::connectSlotsByName(board);
    } // setupUi

    void retranslateUi(QWidget *board)
    {
        board->setWindowTitle(QCoreApplication::translate("board", "Form", nullptr));
        info->setText(QCoreApplication::translate("board", "INFO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class board: public Ui_board {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARD_H
