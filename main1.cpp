// 预研期的参考代码

#include <cjson/cJSON.h>
#include <curl/curl.h>
#include <iostream>
#include <windows.h>
using namespace std;

#define boardWidth 10
#define white 2
#define black 1

string baseURL = "http://localhost:5000/";

int board[boardWidth][boardWidth] = { {0} };
int playerNow = black;
int checkBlockWin(int x,int y,int player) {
    int flag_x = 0;
    int flag_y = 0;
    int flag_positive1 = 0;
    int flag_positive2 = 0;
    int flag_negative1 = 0;
    int flag_negative2 = 0;
    // X轴正方向判断
    for (int i = x + 1; i < boardWidth && i < x + 5; i++) {
        if (player != board[y][i]) {
            break;
        }
        else if (i == x + 4) {
            return player;
        }
        else {
            flag_x++;
        }
    }
    // X轴负方向判断
    for (int i = x - 1 ; i > -1 && i > x - 5; i--) {
        if (player != board[y][i]) {
            break;
        }
        else if (i == x - 4) {
            return player;
        }
        else {
            flag_x++;
        }
    }
    if (flag_x > 4) {
        return player;
    }
    // Y轴正方向判断
    for (int i = y + 1; i < boardWidth && i < y + 5; i++) {
        if (player != board[i][x]) {
            break;
        }
        else if (i == y + 4) {
            return player;
        }
        else {
            flag_y++;
        }
    }
    // Y轴负方向判断
    for (int i = y - 1; i > -1 && i > y - 5; i--) {
        if (player != board[i][x]) {
            break;
        }
        else if (i == y - 4) {
            return player;
        }
        else {
            flag_y++;
        }
    }
    if (flag_y > 4) {
        return player;
    }
    // y = x 方向判断：x++ y--
    for (int i = x + 1, j = y - 1; i < boardWidth && i < x + 5 && j > -1 && j > y - 5; i++, j--) {
        if (player != board[j][i]) {
            break;
        }
        else if (i == x + 4) {
            return player;
        }
        else {
            flag_positive1++;
        }
    }
    if (flag_positive1 > 4) {
        return player;
    }
    // y = x 方向判断：x-- y++
    for (int i = x - 1, j = y + 1; i > -1 && i > x - 5 && j < boardWidth && j < y + 5; i--, j++) {
        if (player != board[j][i]) {
            break;
        }
        else if (i == x - 4) {
            return player;
        }
        else {
            flag_positive2++;
        }
    }
    if (flag_positive2 > 4) {
        return player;
    }
    // y = -x 方向判断：x++ y++
    for (int i = x + 1, j = y + 1; i < boardWidth && i < x + 5 && j < boardWidth && j < x + 5; i++, j++) {
        if (player != board[j][i]) {
            break;
        }
        else if (i == x + 4) {
            return player;
        }
        else {
            flag_negative1++;
        }
    }
    if (flag_negative1 > 4) {
        return player;
    }
    // y = -x 方向判断：x-- y--
    for (int i = x - 1, j = y - 1; i > -1 && i > x - 5 && j > -1 && j > x - 5; i--, j--) {
        if (player != board[j][i]) {
            break;
        }
        else if (i == x - 4) {
            return player;
        }
        else {
            flag_negative2++;
        }
    }
    if (flag_negative2 > 4) {
        return player;
    }
    return false;
}

string ID = "white";

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
string newGame(){
    std::string response;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    string strPostData = "userId="+ID;
    string url = baseURL + "api/newGame";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);
    return response;
}
boolean isStarted(string gameID){
    std::string response;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    string url = baseURL + "game/" + gameID +"/getStatus";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
    res = curl_easy_perform(curl);
    cout<<response<<endl;
    curl_easy_cleanup(curl);
    if (response == "Unstarted"){
        return false;
    }
    else{
        return true;
    }
}
string getBoard(string gameID){
    std::string response;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    string url = baseURL + "game/" + gameID+ "/getBoard";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return response;
}
string setChess(string gameID,string location){
    std::string response;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    string url = baseURL + "game/" + gameID + "/setChess";
    string strPostData = "location="+location+"&userId="+ID;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return response;
}
void joinGame(string matchId){
    std::string response;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    string strPostData = "userId="+ID+"&matchId="+matchId;
    string url = baseURL + "api/joinGame";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L );
    res = curl_easy_perform(curl);
}
void print_board(string data) {
    for(int i=0;i<boardWidth;i++){
        for(int j=0;j<boardWidth;j++){
            board[i][j]=(int)data[i*boardWidth+j]-48;
        }
    }
    cout << "B X  ";
    for (int i = 0; i < boardWidth; i++) {
        cout << i;
        if (i < 10) {
            cout << "  ";
        }
        else {
            cout << " ";
        }
    }
    cout << endl << "Y" << endl;
    for (int i = 0; i < boardWidth; i++) {
        cout << i << "   ";
        if (i < 10 ) {
            cout << " ";
        }
        for (int j = 0; j < boardWidth; j++) {
            if (board[i][j]) {
                cout << ((board[i][j] == white) ? "W" : "B") << "  ";
            }
            else {
                cout << 0 << "  ";
            }
        }
        cout << endl;
    }
    cout << "Player Now:" << " " << ((playerNow == black) ? "Black" : "White");
    cout << endl;
}

int main(int argc,char* argv[]) {
    string stringInput;
    string boardStr;
    getline(cin, stringInput);
    string gameID = stringInput;
    joinGame(gameID);
    //string gameID = newGame();
    while (1){
        print_board(getBoard(gameID));
        getline(cin, stringInput);
        setChess(gameID,stringInput);
    }
    //QApplication a(argc, argv);
    //QPushButton button("Hello world!", nullptr);
    //button.resize(800, 500);
    //button.show();
    //return QApplication::exec();
}
