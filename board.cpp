#include "board.h"
#include "ui_board.h"
#include <QPainter>
#include <curl/curl.h>
#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include "connectui.h"
#include <QMouseEvent>
#define boardWidth 30
#define baseX 517
#define baseY 17
#define black 1
#define white 2
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
    baseURL = connect->url;
    gameId = connect->game;
    userId = connect->id;
    ui->setupUi(this);
    if (connect->mode=="newgame"){
        wait(connect->url,connect->game,connect->mode);
        color = black;
    }
    if (connect->mode=="join"){
        waiting = false;
        color = white;
        main_loop(connect->url,connect->game,connect->mode);
    }
}

void board::paintEvent(QPaintEvent *event){
    for(int i=0;i<boardWidth;i++){
        for(int j=0;j<boardWidth;j++){
            this->chess[i][j]=(int)this->boardRaw[i*boardWidth+j]-48;
        }
    }
    //for(int i=0;i<boardWidth;i++){
    //    for(int j=0;j<boardWidth;j++){
    //        cout<<chess[i][j];
    //     }
    //    cout<<endl;
    //}
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,1134,638),QPixmap(":/images/board.png"));
    painter.drawPixmap(QRect(baseX,baseY,15,15),QPixmap(":/images/Black.png"));
    for(int j=0;j<30;++j)
        for(int i=0;i<30;++i)
        {
            if(chess[i][j]==1)
                painter.drawPixmap(QRect(baseX+i*17,baseY+j*17,15,15),QPixmap(":/images/Black.png"));
            if(chess[i][j]==2)
                painter.drawPixmap(QRect(baseX+i*17,baseY+j*17,15,15),QPixmap(":/images/Black.png"));
        }
    //如果游戏开始了，那么绘制棋子的提示
    //if(beginFlag){
    //    //画上次下棋子的位置 用红色标记
    //    painter.setBrush(Qt::red);
    //    painter.drawEllipse(QRect(chessX*30+212,chessY*30+42,8,8));
    //}
}
void board::mouseReleaseEvent(QMouseEvent *event){
    if(waiting) return;
    int x=event->x(),y=event->y();
    if(x<baseX||x>(baseX+17*boardWidth)||y<baseY||y>(baseY+17*boardWidth)) return;
    int chessX = (x-baseX)/17;
    int chessY = (y-baseY)/17;
    if (chess[chessY][chessX]!=0) return;
    chess[chessY][chessX] = color;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    string response;
    string location = to_string(chessX) + "," + to_string(chessY);
    string url = baseURL + "game/" + gameId + "/setChess";
    string strPostData = "location="+location+"&userId="+userId;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}
int board::main_loop(string &url,string &game,string &mode){
    connect(this,&board::end,[&](){

    });
    QTimer::singleShot(3000,this,[&](){
        //循环请求并渲染棋盘
        string target = url + "game/" + game + "/getBoard";
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string strPostData = "";
        string response;
        curl_easy_setopt(curl, CURLOPT_URL, target.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
        res = curl_easy_perform(curl);
        boardRaw = response;
        update();
        return main_loop(url,game,url);
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
