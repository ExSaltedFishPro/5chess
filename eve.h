#ifndef EVE_H
#define EVE_H

#define boardWidth 31
#include <QThread>
#include <QWidget>
#include "connectui.h"
#define black 1
#define white 2

namespace Ui {
class eve;
}

class eve : public QWidget
{
    Q_OBJECT

public:
    explicit eve(QWidget *parent = nullptr);
    int chess[boardWidth][boardWidth]={{0}};
    int PointScore[boardWidth][boardWidth]={{0}};
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int now = black;
    ~eve();
signals:
    void end();
private:
    Ui::eve *ui;

    void Calculate(int player, int enemy);

    void AIset(int player);


};


#endif
