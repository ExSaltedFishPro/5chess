#include "pvplocal.h"
#include "ui_pvplocal.h"
#include <QPainter>
#include <curl/curl.h>
#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include <QMouseEvent>

#define boardWidth 31
#define baseX 689
#define baseY 24
#define black 1
#define white 2

using namespace std;
//不考虑性能的话可以遍历一遍的样子
int checkWin(int x,int y,pvplocal *pvpl) {
    int flag_x = 0;
    int flag_y = 0;
    int flag_positive = 0;
    int flag_negative = 0;
    int player = pvpl->playerNow;
    // X轴正方向判断
    for (int i = x + 1; i < 31 && i < x + 5; i++) {
        if (player != pvpl->chess[y][i]) {
            break;
        }
        else if (i == x + 4) {
            return true;
        }
        else {
            flag_x++;
        }
    }
    // X轴负方向判断
    for (int i = x - 1 ; i > -1 && i > x - 5; i--) {
        if (player != pvpl->chess[y][i]) {
            break;
        }
        else if (i == x - 4) {
            return true;
        }
        else {
            flag_x++;
        }
    }
    if (flag_x >= 4) {
        return true;
    }
    // Y轴正方向判断
    for (int i = y + 1; i < 31 && i < y + 5; i++) {
        if (player != pvpl->chess[i][x]) {
            break;
        }
        else if (i == y + 4) {
            return true;
        }
        else {
            flag_y++;
        }
    }
    // Y轴负方向判断
    for (int i = y - 1; i > -1 && i > y - 5; i--) {
        if (player != pvpl->chess[i][x]) {
            break;
        }
        else if (i == y - 4) {
            return true;
        }
        else {
            flag_y++;
        }
    }
    if (flag_y >= 4) {
        return true;
    }
    // y = x 方向判断：x++ y--
    for (int i = x + 1, j = y - 1; i < 31 && i < x + 5 && j > -1 && j > y - 5; i++, j--) {
        if (player != pvpl->chess[j][i]) {
            break;
        }
        else if (i == x + 4) {
            return true;
        }
        else {
            flag_positive++;
        }
    }

    // y = x 方向判断：x-- y++
    for (int i = x - 1, j = y + 1; i > -1 && i > x - 5 && j < 31 && j < y + 5; i--, j++) {
        if (player != pvpl->chess[j][i]) {
            break;
        }
        else if (i == x - 4) {
            return true;
        }
        else {
            flag_positive++;
        }
    }
    if (flag_positive >= 4) {
        return true;
    }
    // y = -x 方向判断：x++ y++
    for (int i = x + 1, j = y + 1; i < 31 && i < x + 5 && j < 31 && j < x + 5; i++, j++) {
        if (player != pvpl->chess[j][i]) {
            break;
        }
        else if (i == x + 4) {
            return true;
        }
        else {
            flag_negative++;
        }
    }
    // y = -x 方向判断：x-- y--
    for (int i = x - 1, j = y - 1; i > -1 && i > x - 5 && j > -1 && j > x - 5; i--, j--) {
        if (player != pvpl->chess[j][i]) {
            break;
        }
        else if (i == x - 4) {
            return true;
        }
        else {
            flag_negative++;
        }
    }

    if (flag_negative >= 4) {
        return true;
    }
    return false;
}

pvplocal::pvplocal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pvplocal)
{
    setFixedSize(1512,850);
    update();
    playerNow = 1;
    isFinished = false;
}

void pvplocal::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,1512,850),QPixmap(":/images/board.png"));
    for(int j=0;j<boardWidth;++j)
        for(int i=0;i<boardWidth;++i)
        {
            if(chess[j][i]==1)
                painter.drawPixmap(QRect(baseX-8+i*22,baseY-8+j*22,16,16),QPixmap(":/images/Black.png"));
            if(chess[j][i]==2)
                painter.drawPixmap(QRect(baseX-8+i*22,baseY-8+j*22,16,16),QPixmap(":/images/White.png"));
        }
}
void DrawBoard(pvplocal *pvpl) {
    for (int i = 0; i < boardWidth; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            cout << pvpl->chess[i][j] << "  ";
        }
        cout <<' '<< i << endl;
    }
    for (int i= 0; i < boardWidth ;++i) {
        cout<<i<<" ";
        if(i<10) {
            cout<<" ";
        }
    }
    cout<<endl;
}
void pvplocal::mouseReleaseEvent(QMouseEvent *event){
    int x=event->x(),y=event->y();
    if(x < baseX||x > (baseX + 22 * boardWidth)|| y < baseY|| y > (baseY + 22 * boardWidth)) {
        return;
    }
    if (isFinished) return;
    int chessX = round((float)(x-baseX)/22);
    int chessY = round((float)(y-baseY)/22);
    if (chessX>30 || chessX<0 || chessY>30 || chessY<0){
        return;
    }
    if (chess[chessY][chessX]!=0) return;
    chess[chessY][chessX] = playerNow;
    if (checkWin(chessX, chessY, this)){
        if (playerNow==black){
            QMessageBox::information(NULL, "Notice", "BLACK WIN!");
            isFinished = true;
        }
        else{
            QMessageBox::information(NULL, "Notice", "WHITE WIN!");
            isFinished = true;
        }
    };
    if (playerNow==1){
        playerNow=2;
    }
    else{
        playerNow=1;
    }
    update();

}

pvplocal::~pvplocal()
{
    delete ui;
}
