#include "board.h"
#include "ui_board.h"
#include <QPainter>
#include <curl/curl.h>
#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include "connectui.h"
using namespace std;
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    static int current_index = 0;
    int content_size = nmemb * size;
    std::string result = std::string((char*)contents, content_size);
    string* pStr = (string*)userp;
    if (pStr)
    {
        (*pStr).append(result);
    }
    return realsize;
}

board::board(ConnectUI *connect,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::board)
{
    ui->setupUi(this);
    if (connect->mode=="newgame"){
        wait(connect->url,connect->game,connect->mode);
    }
    if (connect->mode=="join"){
        waiting = false;
    }
}

void board::paint(int** chess){
    //画背景
    QPainter painter(this);
    for(int i=0;i<30;++i)
        for(int j=0;j<30;++j)
        {
            if(chess[i][j]==1)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/Black.png"));
            if(chess[i][j]==2)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/White.png"));
        }
    //如果游戏开始了，那么绘制棋子的提示
    //if(beginFlag){
    //    //画上次下棋子的位置 用红色标记
    //    painter.setBrush(Qt::red);
    //    painter.drawEllipse(QRect(chessX*30+212,chessY*30+42,8,8));
    //}
}
int board::main_loop(string &url,string &game,string &mode){
    connect(this,&board::back,[&](){

    });
    QTimer::singleShot(10000,this,[&](){
        //循环请求并渲染棋盘
    });
    return 0;
}

int board::wait(string &url,string &game,string &mode){
    waiting=true;
    connect(this,&board::back,[&](){
        main_loop(url,game,mode);
    });
    QTimer::singleShot(1000,this,[&](){
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string target = url + "game/" + game + "/getStatus";
        string strPostData = "";
        curl_easy_setopt(curl, CURLOPT_URL, target.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
        res = curl_easy_perform(curl);
        if (response == "Unstarted") {
            curl_easy_cleanup(curl);
            return wait(url,game,mode);
        }else if (response == "NotExist"){
            curl_easy_cleanup(curl);
            return wait(url,game,mode);
        }else{
            QMessageBox::information(NULL, "Notice", "Game Start!");
            waiting = false;
            emit back();
            return 0;
        }
    });
    return 1;
}
board::~board()
{
    delete ui;
}
