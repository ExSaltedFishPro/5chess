#include "connectui.h"
#include "ui_connectui.h"
#include <cjson/cJSON.h>
#include <curl/curl.h>
#include <iostream>
#include <QMessageBox>
#include "board.h"
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

ConnectUI::ConnectUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConnectUI)
{
    ui->setupUi(this);
    //设置场景标题
    setWindowTitle("5-Chess");
    ui->addr->setText(QString::fromStdString("localhost:5000"));
    connect(ui->testconn,&QPushButton::clicked,[=](){
        QString addr=ui->addr->text();
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string url = "http://" + addr.toStdString() + "/";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
        res = curl_easy_perform(curl);
        ui->label_5->setText("Server Type: " + QString::fromStdString(response));
    });
    connect(ui->onlinepvp,&QPushButton::clicked,[=](){
        QString addr=ui->addr->text();
        QString ID=ui->username->text();
        if (addr.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Address!");
            return 0;
        }
        if (ID.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Username!");
            return 0;
        }
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string baseURL = "http://" + addr.toStdString() + "/";
        string strPostData = "userId="+ID.toStdString();
        url = baseURL + "api/newGame";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        ui->label_5->setText("Response: " + QString::fromStdString(response));
        id = ID.toStdString();
        mode = "newgame";
        url = "http://" + addr.toStdString() + "/";
        game = response;
        ui->gameid->setText(QString::fromStdString(response));
        board *chessBoard = new board(this);
        chessBoard->show();
        return 0;
    });
    connect(ui->join,&QPushButton::clicked,[=](){
        QString addr=ui->addr->text();
        QString ID=ui->username->text();
        QString gameID=ui->gameid->text();
        if (addr.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Address!");
            return 0;
        }
        if (ID.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Username!");
            return 0;
        }
        if (gameID.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Game ID!");
            return 0;
        }
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string baseURL = "http://" + addr.toStdString() + "/";
        string strPostData = "userId="+ID.toStdString() +"matchId="+gameID.toStdString();
        url = baseURL + "api/joinGame";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        ui->label_5->setText("Response: " + QString::fromStdString(response));
        id = ID.toStdString();
        mode = "join";
        url = "http://" + addr.toStdString() + "/";
        board *chessBoard = new board(this);
        chessBoard->show();
        return 0;
    });
}

ConnectUI::~ConnectUI()
{
    delete ui;
}
