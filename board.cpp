#include "board.h"
#include "ui_board.h"
#include <QPainter>
#include <curl/curl.h>
#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include "connectui.h"
#include <QMouseEvent>

#define boardWidth 31
#define baseX 689
#define baseY 24
#define black 1
#define white 2

using namespace std;
//CURL回调函数
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
    setFixedSize(1512,850);
    baseURL = connect->url;
    gameId = connect->game;
    userId = connect->id;
    ui->setupUi(this);
    color = 0;
    if (connect->mode=="newgame"){
        waiting = true;
        wait(connect->url,connect->game,connect->id);
    }
    if (connect->mode=="join"){
        waiting = false;
        int requestColor = QMessageBox::information(this,
                                                    "Choose A Color",
                                                    "Choose A Color",
                                                    "Black!",
                                                    "White!",
                                                    "",
                                                    black,
                                                    white);
        string tmpColor = requestColor?"white":"black";
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string target = baseURL + "api/chooseColor";
        string strPostData = "userId="+userId+"&matchId="+gameId+"&color="+tmpColor;
        curl_easy_setopt(curl, CURLOPT_URL, target.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
        res = curl_easy_perform(curl);
        if (response=="black"){
            wait_another = false;
            color = black;
        }
        else{
            wait_another = true;
            color = white;
        }
        main_loop(baseURL,gameId,userId);
    }
}

void board::paintEvent(QPaintEvent *event){
    for(int i=0;i<boardWidth;i++){
        for(int j=0;j<boardWidth;j++){
            this->chess[i][j]=(int)this->boardRaw[i*boardWidth+j]-48;
        }
    }
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
    //如果游戏开始了，那么绘制棋子的提示
    //if(beginFlag){
    //    //画上次下棋子的位置 用红色标记
    //    painter.setBrush(Qt::red);
    //    painter.drawEllipse(QRect(chessX*30+212,chessY*30+42,8,8));
    //}


void board::mouseReleaseEvent(QMouseEvent *event){
    int x=event->x(),y=event->y();
    if(x < baseX||x > (baseX + 22 * boardWidth)|| y < baseY|| y > (baseY + 22 * boardWidth)) {
        return;
    }
    int chessX = round((float)(x-baseX)/22);
    int chessY = round((float)(y-baseY)/22);
    if (chessX>30 || chessX<0 || chessY>30 || chessY<0){
        return;
    }
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
    tempGetBoard();
    update();
    wait_another = true;
}

void board::tempGetBoard(){
    string target = baseURL + "game/" + gameId + "/getBoard";
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
    curl_easy_cleanup(curl);
}
string board::getPlayerNow(string &url,string &game,string &id){
    string target = url + "game/" + game + "/getPlayerNow";
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
    curl_easy_cleanup(curl);
    return response;
}

int board::main_loop(string &url,string &game,string &id){
    connect(this,&board::set,[&](){
        wait_another = true;
    });
    QTimer::singleShot(3000,this,[&](){
        //循环请求并渲染棋盘
        if (wait_another){
            string a = getPlayerNow(url,game,id);
            if (a == id){
                wait_another = false;
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
                if (response=="white"){
                    QMessageBox::information(NULL, "Notice", "WHITE WIN!");
                    return 0;
                } else if (response=="black"){
                    QMessageBox::information(NULL, "Notice", "BLACK WIN!");
                    return 0;
                }
                curl_easy_cleanup(curl);
            }
        } else {
            update();
        }
        return main_loop(url,game,id);
    });
    return 0;
}

int board::wait(string &url,string &game,string &id){
    waiting=true;
    connect(this,&board::back,[&](){
        if (!color){
            int requestColor = QMessageBox::information(this,
                                                        "Choose A Color",
                                                        "Choose A Color",
                                                        "Black!",
                                                        "White!",
                                                        "",
                                                        black,
                                                        white);
            string tmpColor = requestColor?"white":"black";
            std::string response;
            CURL *curl;
            CURLcode res;
            curl = curl_easy_init();
            string target = url + "api/chooseColor";
            string strPostData = "userId="+userId+"&matchId="+gameId+"&color="+tmpColor;
            curl_easy_setopt(curl, CURLOPT_URL, target.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
            res = curl_easy_perform(curl);
            if (response=="black"){
                wait_another = false;
                color = black;
            }
            else{
                wait_another = true;
                color = white;
            }
        }
        main_loop(url,game,id);
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
            return wait(url,game,id);
        }else if (response == "NotExist"){
            curl_easy_cleanup(curl);
            return wait(url,game,id);
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
