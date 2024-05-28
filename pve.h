#ifndef PVE_H
#define PVE_H

#define boardWidth 31
#include <QThread>
#include <QWidget>
#include "connectui.h"

namespace Ui {
class pve;
}

class pve : public QWidget
{
    Q_OBJECT

public:
    explicit pve(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *event);
    int chess[boardWidth][boardWidth]={{0}};
    int PointScore[boardWidth][boardWidth]={{0}};
    void paintEvent(QPaintEvent *event);
    int playerNow;
    int playerColor;
    bool isFinished;
    ~pve();
signals:
    void end();
private:
    Ui::pve *ui;

    void Calculate(int player, int enemy);

    void AIset(int player);
};


#endif
