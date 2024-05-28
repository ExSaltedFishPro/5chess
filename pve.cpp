#include "pve.h"
#include "ui_pve.h"
#include <QPainter>
#include <curl/curl.h>
#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include <QMouseEvent>
#include <vector>
#define boardWidth 31
#define baseX 689
#define baseY 24
#define black 1
#define white 2

using namespace std;
//不考虑性能的话可以遍历一遍的样子
struct MaxPoints {
    int col;
    int row;
};
int checkBlockWin(int x,int y,pve *pvpl,int player) {
    int flag_x = 0;
    int flag_y = 0;
    int flag_positive = 0;
    int flag_negative = 0;
    if (pvpl->chess[y][x]!=player) return false;
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
int checkWin(pve *pvpl){
    for (int i=0;i<31;i++){
        for (int j=0;j<31;j++){
            if (checkBlockWin(i,j,pvpl,black)){
                return black;
            }
        }
    }
    for (int i=0;i<31;i++){
        for (int j=0;j<31;j++){
            if (checkBlockWin(i,j,pvpl,white)){
                return white;
            }
        }
    }
    return false;
}
void pve::Calculate(int player,int enemy) {
    int MyNum = 0;
    int EnemyNum = 0;
    int emptyNum=0;
    //清空落点价值
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardWidth; j++) {
            PointScore[i][j] = 0;
        }
    }
    for (int row= 0; row< boardWidth;row++) {
        for (int col = 0; col < boardWidth; col++) {
            if (PointScore[row][col]==0) {
                for (int y = -1; y <= 1; y++) {
                    for (int x = -1; x <= 1; x++){
                        // 重置
                        MyNum = 0;
                        EnemyNum = 0;
                        emptyNum = 0;

                        if (!(y == 0 && x == 0)) {
                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row + i * y;
                                int curCol = col + i * x;
                                if (curRow >= 0 && curRow < boardWidth &&
                                    curCol >= 0 && curCol < boardWidth &&
                                    chess[curRow][curCol] == enemy) // 真人玩家的子
                                {
                                    EnemyNum++;
                                }
                                else if (curRow >= 0 && curRow < boardWidth &&
                                         curCol >= 0 && curCol < boardWidth &&
                                         chess[curRow][curCol] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row - i * y;
                                int curCol = col - i * x;
                                if (curRow >= 0 && curRow < boardWidth &&
                                    curCol >= 0 && curCol < boardWidth &&
                                    chess[curRow][curCol] == enemy) // 真人玩家的子
                                {
                                    EnemyNum++;
                                }
                                else if (curRow >= 0 && curRow < boardWidth &&
                                         curCol >= 0 && curCol < boardWidth &&
                                         chess[curRow][curCol] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (EnemyNum == 1)                      // 杀二
                                PointScore[row][col] += 10;
                            else if (EnemyNum == 2)                 // 杀三
                            {
                                if (emptyNum == 1)
                                    PointScore[row][col] += 30;
                                else if (emptyNum == 2)
                                    PointScore[row][col] += 40;
                            }
                            else if (EnemyNum == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    PointScore[row][col] += 60;
                                else if (emptyNum == 2)
                                    PointScore[row][col] += 200;
                            }
                            else if (EnemyNum == 4)                 // 杀五
                                PointScore[row][col] += 20000;




                            // 进行一次清空
                            emptyNum = 0;




                            // MyPoint正向
                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row + i * y;
                                int curCol = col + i * x;
                                if (curRow > 0 && curRow < boardWidth &&
                                    curCol > 0 && curCol < boardWidth &&
                                    chess[curRow][curCol] == player) // 我的子
                                {
                                    MyNum++;
                                }
                                else if (curRow > 0 && curRow < boardWidth &&
                                         curCol > 0 && curCol < boardWidth &&
                                         chess[curRow][curCol] == 0) // 无落子
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }
                            // MyPoint反向
                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row - i * y;
                                int curCol = col - i * x;
                                if (curRow > 0 && curRow < boardWidth &&
                                    curCol > 0 && curCol < boardWidth &&
                                    chess[curRow][curCol] == player) // 玩家的子
                                {
                                    MyNum++;
                                }
                                else if (curRow > 0 && curRow < boardWidth &&
                                         curCol > 0 && curCol < boardWidth &&
                                         chess[curRow][curCol] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (MyNum == 0)                      // 随意落点
                                PointScore[row][col] += 5;
                            else if (MyNum == 1)                 // 活二
                                PointScore[row][col] += 10;
                            else if (MyNum == 2)
                            {
                                if (emptyNum == 1)                // 死三
                                    PointScore[row][col] += 25;
                                else if (emptyNum == 2)
                                    PointScore[row][col] += 50;  // 活三
                            }
                            else if (MyNum == 3)
                            {
                                if (emptyNum == 1)                // 死四
                                    PointScore[row][col] += 55;
                                else if (emptyNum == 2)
                                    PointScore[row][col] += 10000; // 活四
                            }
                            else if (MyNum >= 4)
                                PointScore[row][col] += 50000;// 活五，应该具有最高优先级

                        }
                    }
                }

            }
        }
    }
}
void pve::AIset(int player) {
    int MaxScore = 0;
    int MaxNum = 0;
    vector <MaxPoints> maxPoints;//创建点的数组
    MaxPoints maxPoint;//实例化的点
    for (int row = 0; row < boardWidth; row++) {
        for (int col = 0; col < boardWidth; col++)
        {
            // 前提是这个坐标是空的
            if (chess[row][col] == 0) {
                if (PointScore[row][col] > MaxScore)          // 找最大的数和坐标
                {
                    MaxNum=1;
                    MaxScore = PointScore[row][col];
                    //此时的难点在于如何存储坐标，经搜索发现可以使用vector
                    maxPoints.clear();
                    maxPoint.col=col;
                    maxPoint.row=row;

                    maxPoints.push_back(maxPoint);
                }
                else if (PointScore[row][col] == MaxScore) {// 如果有多个最大价值，都存起来
                    maxPoint.col=col;
                    maxPoint.row=row;
                    maxPoints.push_back(maxPoint);
                    MaxNum += 1;

                }
            }
        }
    }

    int i=0;
    i=rand()%(MaxNum);
    chess[maxPoints.at(i).row][maxPoints.at(i).col]=player;
}

pve::pve(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pve)
{
    setFixedSize(1512,850);
    isFinished = false;
    playerColor = QMessageBox::information(this,
                                       "Choose A Color",
                                       "Choose A Color",
                                       "Black!",
                                       "White!",
                                       "",
                                       black,
                                       white);
    playerColor++;
    if (playerColor==white){
        Calculate(black,white);
        AIset(black);
    }
    update();
}

void pve::paintEvent(QPaintEvent *event){
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

void pve::mouseReleaseEvent(QMouseEvent *event){
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
    chess[chessY][chessX] = playerColor;
    update();
    if (checkWin(this)==black) {
        QMessageBox::information(NULL, "Notice", "BLACK WIN!");
        isFinished = true;
    }
    else if (checkWin(this)==white){
        QMessageBox::information(NULL, "Notice", "WHITE WIN!");
        isFinished = true;
    }
    Calculate((playerColor==black)?white:black,playerColor);
    AIset((playerColor==black)?white:black);
    update();
    if (checkWin(this)==black) {
        QMessageBox::information(NULL, "Notice", "BLACK WIN!");
        isFinished = true;
    }
    else if (checkWin(this)==white){
        QMessageBox::information(NULL, "Notice", "WHITE WIN!");
        isFinished = true;
    }
}

pve::~pve()
{
    delete ui;
}
