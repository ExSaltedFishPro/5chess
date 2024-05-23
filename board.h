#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "connectui.h"

namespace Ui {
class board;
}

class board : public QWidget
{
    Q_OBJECT

public:
    explicit board(ConnectUI *connect, QWidget *parent = nullptr);
    ~board();
signals:
    void back();

private:
    Ui::board *ui;
    void paint(int **chess);
    bool waiting=true;
    int wait(std::string &url, std::string &game,std::string &mode);

    int main_loop(std::string &url, std::string &game, std::string &mode);
};


#endif // BOARD_H
