#ifndef CONNECTUI_H
#define CONNECTUI_H
#include <QWidget>
#include <iostream>
namespace Ui {
class ConnectUI;
}

class ConnectUI : public QWidget
{
    Q_OBJECT

public:
    std::string mode;
    std::string url;
    std::string game;
    std::string id;
    std::string password;
    explicit ConnectUI(QWidget *parent = nullptr);
    ~ConnectUI();

private:
    Ui::ConnectUI *ui;

    void getInfo();
};

#endif // CONNECTUI_H
