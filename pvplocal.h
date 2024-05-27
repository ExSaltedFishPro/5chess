#ifndef PVPLOCAL_H
#define PVPLOCAL_H

#define boardWidth 31
#include <QThread>
#include <QWidget>
#include "connectui.h"

namespace Ui {
class pvplocal;
}

class pvplocal : public QWidget
{
    Q_OBJECT

public:
    explicit pvplocal(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *event);
    int chess[boardWidth][boardWidth]={{0}};
    void paintEvent(QPaintEvent *event);
    int playerNow;
    bool isFinished;
    ~pvplocal();
signals:
    void end();
private:
    Ui::pvplocal *ui;
};


#endif
