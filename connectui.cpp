#include "connectui.h"
#include "ui_connectui.h"
#include <cjson/cJSON.h>
#include <curl/curl.h>
#include <iostream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "board.h"
#include "pvplocal.h"
#include "pve.h"
#include "eve.h"

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
void ConnectUI::getInfo(){
    QString addr=ui->addr->text();
    std::string response;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    url = "http://" + addr.toStdString() + "/info";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
    res = curl_easy_perform(curl);
    cJSON *json = cJSON_Parse(response.c_str());
    ui->games->clear();
    for (int i = 0;i<cJSON_GetArraySize(json);i++){
        int curRow = ui->games->rowCount();
        QStringList headerlist;
        headerlist.append(QString::fromStdString("ID"));
        headerlist.append(QString::fromStdString("gamerA"));
        headerlist.append(QString::fromStdString("gamerB"));
        headerlist.append(QString::fromStdString("status"));
        ui->games->setHorizontalHeaderLabels(headerlist);
        ui->games->insertRow(curRow);
        ui->games->setItem(curRow, 0, new QTableWidgetItem(QString::fromStdString(cJSON_GetObjectItem(cJSON_GetArrayItem(json,i),"id")->valuestring)));
        ui->games->setItem(curRow, 1, new QTableWidgetItem(QString::fromStdString(cJSON_GetObjectItem(cJSON_GetArrayItem(json,i),"gamerA")->valuestring)));
        ui->games->setItem(curRow, 2, new QTableWidgetItem(QString::fromStdString(cJSON_GetObjectItem(cJSON_GetArrayItem(json,i),"gamerB")->valuestring)));
        ui->games->setItem(curRow, 3, new QTableWidgetItem(QString::fromStdString(cJSON_GetObjectItem(cJSON_GetArrayItem(json,i),"status")->valuestring)));
    }
}
ConnectUI::ConnectUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConnectUI)
{
    ui->setupUi(this);
    //设置场景标题
    setWindowTitle("5-Chess");
    ui->addr->setText(QString::fromStdString("localhost"));
    connect(ui->testconn,&QPushButton::clicked,[=](){
        QString addr=ui->addr->text();
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string url = "http://" + addr.toStdString() + "/";
        cout<<url<<endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        ui->label_5->setText("Server Type: " + QString::fromStdString(response));
        getInfo();
    });
    connect(ui->onlinepvp,&QPushButton::clicked,[=](){
        QString addr=ui->addr->text();
        QString ID=ui->username->text();
        QString pass=ui->password->text();
        if (addr.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Address!");
            return 0;
        }
        if (ID.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Username!");
            return 0;
        }
        if (pass.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Password!");
            return 0;
        }
        password = pass.toStdString();
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string baseURL = "http://" + addr.toStdString() + "/";
        string strPostData = "userId="+ID.toStdString()+"&password="+password;
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
        if (game=="nouser"){
            QMessageBox::information(NULL, "Notice", "Not Registered!");
            return 0;
        }
        if (game=="unauthorized"){
            QMessageBox::information(NULL, "Notice", "Password Wrong!");
            return 0;
        }
        ui->gameid->setText(QString::fromStdString(response));
        board *chessBoard = new board(this);
        chessBoard->show();
        return 0;
    });
    connect(ui->join,&QPushButton::clicked,[=](){
        QString addr=ui->addr->text();
        QString ID=ui->username->text();
        QString gameID=ui->gameid->text();
        QString pass=ui->password->text();
        password = pass.toStdString();
        game = gameID.toStdString();
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
        if (pass.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Password!");
            return 0;
        }
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string baseURL = "http://" + addr.toStdString() + "/";
        string strPostData = "userId="+ID.toStdString() +"&matchId="+gameID.toStdString()+"&password="+password;
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
        if (response=="unauthorized"){
            QMessageBox::information(NULL, "Notice", "Unauthorized");
            return 0;
        }
        if (QString::fromStdString(response)=="1"){
            QMessageBox::information(NULL, "Notice", "Game ID Not Exists!");
            return 0;
        }

        board *chessBoard = new board(this);
        chessBoard->show();
        return 0;
    });
    connect(ui->localpvp,&QPushButton::clicked,[=](){
        pvplocal *pvpl = new pvplocal();
        pvpl->show();
        return 0;
    });
    connect(ui->pve,&QPushButton::clicked,[=](){
        pve *pvel = new pve();
        pvel->show();
        return 0;
    });
    connect(ui->eve,&QPushButton::clicked,[=](){
        eve *evel = new eve();
        evel->show();
        return 0;
    });
    connect(ui->reg,&QPushButton::clicked,[=](){
        QString addr=ui->addr->text();
        QString ID=ui->username->text();
        QString password=ui->password->text();
        if (addr.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Address!");
            return 0;
        }
        if (ID.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Username!");
            return 0;
        }
        if (password.toStdString()==""){
            QMessageBox::information(NULL, "Notice", "Empty Password!");
            return 0;
        }
        std::string response;
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        string baseURL = "http://" + addr.toStdString() + "/";
        string strPostData = "userId="+ID.toStdString()+"&password="+password.toStdString();
        url = baseURL + "api/register";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        ui->label_5->setText("Response: " + QString::fromStdString(response));
        if (response=="registered"){
            QMessageBox::information(NULL, "Notice", "Username Exists!");
            return 0;
        }
        if (response=="OK"){
            QMessageBox::information(NULL, "Notice", "OK!");
            return 0;
        }
        return 0;
    });
}

ConnectUI::~ConnectUI()
{
    delete ui;
}
