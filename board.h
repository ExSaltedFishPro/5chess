#ifndef BOARD_H
#define BOARD_H

#define boardWidth 30

#include <QWidget>
#include "connectui.h"

namespace Ui {
class board;
}

class board : public QWidget
{
    Q_OBJECT

public:
    std::string baseURL;
    std::string gameId;
    std::string userId;
    explicit board(ConnectUI *connect, QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *event);
    int chess[boardWidth][boardWidth];
    int color; //black->1 white->2
    ~board();
signals:
    void back();

private:
    Ui::board *ui;
    void paint(std::string data);
    bool waiting=true;
    int wait(std::string &url, std::string &game,std::string &mode);

    int main_loop(std::string &url, std::string &game, std::string &mode);
};


#endif // BOARD_H
