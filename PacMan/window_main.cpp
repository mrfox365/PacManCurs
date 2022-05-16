#include "window_main.h"
#include "ui_window_main.h"
#include <iostream>
#include <cmath>
#include <QtDebug>
#include <QOpenGLWidget>
#include <QFile>
#include <QPainter>
#include <QTime>
#include <QTextStream>
#include <QLabel>
#include <QFont>

using namespace std;

struct POS{
    int x;
    int y;
};

struct WALL{
    POS kor[9999];
    int len{};
};

struct HOLL{
    POS kor[9999];
    int len{};
};
struct BOOST{
    POS kor;
    bool locate;
};
struct EAT{
    POS kor[9999];
    int len{};
    bool locate[9999];
};
struct POVOROT{
    POS kor[9999];
    int len{};
};

WALL pWALL;
HOLL pHOLL;
POVOROT pPOVOROT;
POS IPOV;
POS JPOV;
POS BACKRED;
POS BACKBLUE;
EAT pEAT;
BOOST TP;
BOOST ATACK;
BOOST DEF;

Window_main::Window_main(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window_main)
{
    //ui->setupUi(this);

    level = 0;
    score = 0;

    lineScore = new QLabel(this);
    QLabel *name1 = new QLabel(this);

    name1->setStyleSheet("color: rgb(255, 255, 255)");
    name1->setText("Score:");
    QFont fontname1 = name1->font();
    fontname1.setPointSize(20);
    name1->setFont(fontname1);
    name1->setGeometry(50, 720, 80, 25);

    lineScore->setStyleSheet("color: rgb(255, 255, 255)");
    lineScore->setNum(score);
    QFont font = lineScore->font();
    font.setPointSize(20);
    lineScore->setFont(font);
    lineScore->setGeometry(130, 720, 50, 25);

    lineLevel = new QLabel(this);
    QLabel *name2 = new QLabel(this);

    name2->setStyleSheet("color: rgb(255, 255, 255)");
    name2->setText("Level:");
    QFont fontname2 = name1->font();
    fontname2.setPointSize(20);
    name2->setFont(fontname2);
    name2->setGeometry(850, 720, 70, 25);

    lineLevel->setStyleSheet("color: rgb(255, 255, 255)");
    lineLevel->setNum(score);
    QFont fontl = lineLevel->font();
    fontl.setPointSize(20);
    lineLevel->setFont(fontl);
    lineLevel->setGeometry(920, 720, 50, 25);

    setStyleSheet("background-color:black;");

    resize(MAP_WIDTH, MAP_HEITH);

    //plaer
    leftDirection = false;
    rightDirection = false;
    upDirection = false;
    downDirection = false;
    //red ghost
    redLeftDirection = false;
    redRightDirection = true;
    redUpDirection = false;
    redDownDirection = false;
    //blue ghost
    blueLeftDirection = true;
    blueRightDirection = false;
    blueUpDirection = false;
    blueDownDirection = false;

    inGame = true;
    needBoost = true;
    needKol = true;
    needEat = true;
    defActive = false;
    atackActive = false;
    blueGhostLive = true;
    redGhostLive = true;

    getTex();
    initGame();

}

void Window_main::getTex(){

    wall.load("E:\\QT FILES\\PacMan\\Textures\\blue_wall.png");
    eat.load("E:\\QT FILES\\PacMan\\Textures\\aplle.png");
    pacman.load("E:\\QT FILES\\PacMan\\Textures\\pacman.png");
    rightpacman.load("E:\\QT FILES\\PacMan\\Textures\\right-pac-man.png");
    uppacman.load("E:\\QT FILES\\PacMan\\Textures\\up-pac-man.png");
    downpacman.load("E:\\QT FILES\\PacMan\\Textures\\down-pac-man.png");
    leftpacman.load("E:\\QT FILES\\PacMan\\Textures\\left-pac-man.png");
    pacmandef.load("E:\\QT FILES\\PacMan\\Textures\\pacmandef.png");
    rightpacmandef.load("E:\\QT FILES\\PacMan\\Textures\\right-pac-man-def.png");
    leftpacmandef.load("E:\\QT FILES\\PacMan\\Textures\\left-pac-man-def.png");
    uppacmandef.load("E:\\QT FILES\\PacMan\\Textures\\up-pac-man-def.png");
    downpacmandef.load("E:\\QT FILES\\PacMan\\Textures\\down-pac-man-def.png");
    redChost.load("E:\\QT FILES\\PacMan\\Textures\\redChost.png");
    blueChost.load("E:\\QT FILES\\PacMan\\Textures\\blueChost.png");
    blueBoll.load("E:\\QT FILES\\PacMan\\Textures\\blueBoll.png");
    greenBoll.load("E:\\QT FILES\\PacMan\\Textures\\greenBoll.png");
    redBoll.load("E:\\QT FILES\\PacMan\\Textures\\redBoll.png");
    horAtack.load("E:\\QT FILES\\PacMan\\Textures\\horizontalAtack.png");
    verAtack.load("E:\\QT FILES\\PacMan\\Textures\\verticalAtack.png");

    QFile mapPlain("E:\\QT FILES\\PacMan\\Textures\\map.txt");

    if(!mapPlain.open(QFile::ReadOnly | QFile::Text)){
        std::cout << "error open map_text" << endl;
        return;
    }

    QTextStream stream (&mapPlain);
    map_text = stream.readAll();
    map_text.remove(QChar('\n'));


}

void Window_main::initGame(){

    px = 480;
    py = 420;
    rChost_x = 420;
    rGhost_x = 390;
    rChost_y = 240;
    rGhost_y = 240;
    bChost_x = 540;
    bGhost_x = 570;
    bChost_y = 240;
    bGhost_y = 240;
    redJ = true;
    blueJ = true;
    needBPoint = true;
    TPActive = false;
    inGame = true;
    needEat = true;
    defActive = false;
    atackActive = false;
    blueGhostLive = true;
    redGhostLive = true;
    TP.locate = true;
    ATACK.locate = true;
    DEF.locate = true;

    //plaer
    leftDirection = false;
    rightDirection = false;
    upDirection = false;
    downDirection = false;
    //red ghost
    redLeftDirection = false;
    redRightDirection = true;
    redUpDirection = false;
    redDownDirection = false;
    //blue ghost
    blueLeftDirection = true;
    blueRightDirection = false;
    blueUpDirection = false;
    blueDownDirection = false;

    level++;

    lineLevel->setNum(level);

    locateBoost();

    timerId = startTimer(DELAY);

}

void Window_main::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    worldPaint();
}

void Window_main::timerEvent(QTimerEvent *t){

    Q_UNUSED(t);

    if(!TPActive){
        if(inGame){
            if(needBoost){
                locateBoost();
                needBoost = false;
            }
            if(needEat){
                locateEat();
                needEat = false;
            }
            checkBoost();
            if(atackActive){
                if(atackTime > 0){
                    atackTime--;
                }else{
                    atackActive = false;
                }
            }
            if(!redGhostLive){
                if(redRespawn > 0){
                    redRespawn--;
                }else{
                    redGhostLive = true;
                    redJ = true;
                    rChost_x = 420;
                    rGhost_x = 390;
                    rChost_y = 240;
                    rGhost_y = 240;
                    redLeftDirection = false;
                    redRightDirection = true;
                    redUpDirection = false;
                    redDownDirection = false;
                }
            }
            if(!blueGhostLive){
                if(blueRespawn > 0){
                    blueRespawn--;
                }else{
                    blueGhostLive = true;
                    blueJ = true;
                    bChost_x = 540;
                    bGhost_x = 570;
                    bChost_y = 240;
                    bGhost_y = 240;
                    redLeftDirection = true;
                    redRightDirection = false;
                    redUpDirection = false;
                    redDownDirection = false;
                }
            }

            checkLevel();
            Move();
            lineScore->setNum(score);
            checkGhost();
            redMove();
            blueMove();

        }
        repaint();
    }else{
        tpActive();
    }

}

void Window_main::checkLevel(){

    int l = 0;
    for(int i = 0; i < pEAT.len; i++){

        if(pEAT.locate[i]){
            l++;
        }

    }

    if(l == 0){
        initGame();
    }

}

void Window_main::worldPaint(){

    checkEat();
    checkBoost();
    QPainter qp(this);
    if(inGame){
        if(TP.locate){
            qp.drawImage(TP.kor.x, TP.kor.y, greenBoll);
        }
        if(ATACK.locate){
            qp.drawImage(ATACK.kor.x, ATACK.kor.y, redBoll);
        }
        if(DEF.locate){
            qp.drawImage(DEF.kor.x, DEF.kor.y, blueBoll);
        }

        for(int i = 0; i < pEAT.len; i++){
            if(pEAT.locate[i]){
                qp.drawImage(pEAT.kor[i].x, pEAT.kor[i].y, eat);
            }
        }

        int dl{}, lenw{}, lenh{}, lenp{};
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < 33; j++){
                int y{};
                if(i != 0){
                    y = i * DOTS_SIZE;
                }
                int x{};
                if(j != 0){
                    x = j * DOTS_SIZE;
                }
                //если W то рисуем стену и передаём эти координаты в WALL
                if(map_text[dl] == "W"){
                    qp.drawImage(x, y, wall);
                    if(needKol){
                        pWALL.kor[lenw].x = x;
                        pWALL.kor[lenw].y = y;
                        pWALL.len++;
                        lenw++;
                    }
                }
                // если нет то ничего не рисуем, но передаём эти координаты в HOLL
                else{
                    if (needKol){
                        pHOLL.kor[lenh].x = x;
                        pHOLL.kor[lenh].y = y;
                        pHOLL.len++;
                        lenh++;
                        if(map_text[dl] == "P"){
                            pPOVOROT.kor[lenp].x = x;
                            pPOVOROT.kor[lenp].y = y;
                            pPOVOROT.len++;
                            lenp++;
                        }
                        if(map_text[dl] == "I"){
                            IPOV.x = x;
                            IPOV.y = y;
                        }
                        if(map_text[dl] == "J"){
                            JPOV.x = x;
                            JPOV.y = y;
                        }
                    }
                }
                dl++;
            }//цыкл у
        }//цыкл х
        if(defActive){
            if(upDirection){
                qp.drawImage(px, py, uppacmandef);
            }
            else if(downDirection){
                qp.drawImage(px, py, downpacmandef);
            }
            else if(leftDirection){
                qp.drawImage(px, py, leftpacmandef);
            }
            else if(rightDirection){
                qp.drawImage(px, py, rightpacmandef);
            }
            else{
                qp.drawImage(px, py, pacmandef);
            }
        }else{
            if(upDirection){
                qp.drawImage(px, py, uppacman);
            }
            else if(downDirection){
                qp.drawImage(px, py, downpacman);
            }
            else if(leftDirection){
                qp.drawImage(px, py, leftpacman);
            }
            else if(rightDirection){
                qp.drawImage(px, py, rightpacman);
            }
            else{
                qp.drawImage(px, py, pacman);
            }
        }
        if(atackActive){
            atackPaint(qp);
        }
        if(redGhostLive){
        qp.drawImage(rChost_x, rChost_y, redChost);
        }
        if(blueGhostLive){
        qp.drawImage(bChost_x, bChost_y, blueChost);
        }

        needKol = false;
    }//if in game
    else{
        gameOver(qp);
    }
}//конец пейнтера

void Window_main::atackPaint(QPainter &qp){

    int lengh = pHOLL.len;
    int lengw = pWALL.len;

    if(leftDirection){

        int bufx = px;
        bool paint = true;
        while(paint){
            bufx -= DOTS_SIZE;
            for(int i = 0; i < lengh; i++){
               if( (py == pHOLL.kor[i].y) && (bufx == pHOLL.kor[i].x) ){
                   qp.drawImage(pHOLL.kor[i].x, pHOLL.kor[i].y, horAtack);
                   checkGhostKill(pHOLL.kor[i].x, pHOLL.kor[i].y);
               }else{
                   for(int i = 0; i < lengw; i++){
                      if( (py == pWALL.kor[i].y) && (bufx == pWALL.kor[i].x) ){
                          paint = false;
                          break;
                      }
                   }
               }
            }
        }
    }
    if(upDirection){

        int bufy = py;
        bool paint = true;
        while(paint){
            bufy -= DOTS_SIZE;
            for(int i = 0; i < lengh; i++){
               if( (px == pHOLL.kor[i].x) && (bufy == pHOLL.kor[i].y) ){
                   qp.drawImage(pHOLL.kor[i].x, pHOLL.kor[i].y, verAtack);
                   checkGhostKill(pHOLL.kor[i].x, pHOLL.kor[i].y);
               }else{
                   for(int i = 0; i < lengw; i++){
                      if( (px == pWALL.kor[i].x) && (bufy == pWALL.kor[i].y) ){
                          paint = false;
                          break;
                      }
                   }
               }
            }
        }

    }
    if(downDirection){

        int bufy = py;
        bool paint = true;
        while(paint){
            bufy += DOTS_SIZE;
            for(int i = 0; i < lengh; i++){
               if( (px == pHOLL.kor[i].x) && (bufy == pHOLL.kor[i].y) ){
                   qp.drawImage(pHOLL.kor[i].x, pHOLL.kor[i].y, verAtack);
                   checkGhostKill(pHOLL.kor[i].x, pHOLL.kor[i].y);
               }else{
                   for(int i = 0; i < lengw; i++){
                      if( (px == pWALL.kor[i].x) && (bufy == pWALL.kor[i].y) ){
                          paint = false;
                          break;
                      }
                   }
               }
            }
        }

    }
    if(rightDirection){

        int bufx = px;
        bool paint = true;
        while(paint){
            bufx += DOTS_SIZE;
            for(int i = 0; i < lengh; i++){
               if( (py == pHOLL.kor[i].y) && (bufx == pHOLL.kor[i].x) ){
                   qp.drawImage(pHOLL.kor[i].x, pHOLL.kor[i].y, horAtack);
                   checkGhostKill(pHOLL.kor[i].x, pHOLL.kor[i].y);
               }else{
                   for(int i = 0; i < lengw; i++){
                      if( (py == pWALL.kor[i].y) && (bufx == pWALL.kor[i].x) ){
                          paint = false;
                          break;
                      }
                   }
               }
            }
        }

    }

}

void Window_main::gameOver(QPainter &qp) {

    QString message = "Game over";
    message += "\n  Score:";
    message += QString::number(score);
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void Window_main::locateBoost() {

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int RAND_POS = pHOLL.len - 1;

    int r = qrand() % RAND_POS;
    TP.kor.x = pHOLL.kor[r].x;
    TP.kor.y = pHOLL.kor[r].y;
    TP.locate = true;

    r = qrand() % RAND_POS;
    ATACK.kor.x = pHOLL.kor[r].x;
    ATACK.kor.y = pHOLL.kor[r].y;
    ATACK.locate = true;

    r = qrand() % RAND_POS;
    DEF.kor.x = pHOLL.kor[r].x;
    DEF.kor.y = pHOLL.kor[r].y;
    DEF.locate = true;
}

void Window_main::locateEat(){

    int len{};
    for(int i = 0; i < pHOLL.len; i++){
        if( (pHOLL.kor[i].x != px) || (pHOLL.kor[i].y != py) ){
            if( (pHOLL.kor[i].x != TP.kor.x) || (pHOLL.kor[i].y != TP.kor.y) ){
                if( (pHOLL.kor[i].x != ATACK.kor.x) || (pHOLL.kor[i].y != ATACK.kor.y) ){
                    if( (pHOLL.kor[i].x != DEF.kor.x) || (pHOLL.kor[i].y != DEF.kor.y) ){
                        pEAT.kor[len].x = pHOLL.kor[i].x;
                        pEAT.kor[len].y = pHOLL.kor[i].y;
                        pEAT.len++;
                        pEAT.locate[len] = true;
                        len++;
                    }
                }
            }
        }
    }// конец цыкла

}

void Window_main::checkEat(){

    for(int i = 0; i < pEAT.len; i++){
        if(pEAT.locate[i]){
            if( (px == pEAT.kor[i].x) && (py == pEAT.kor[i].y) ){
                pEAT.locate[i] = false;
                score++;
            }
        }
    }

}

void Window_main::checkBoost(){

    if(DEF.locate){
        if( (px == DEF.kor.x) && (py == DEF.kor.y) ){
            defActive = true;
            DEF.locate = false;
        }
    }
    if(ATACK.locate){
        if( (px == ATACK.kor.x) && (py == ATACK.kor.y) ){
            atackActive = true;
            atackTime = 100;
            ATACK.locate = false;
        }
    }
    if(TP.locate){
        if( (px == TP.kor.x) && (py == TP.kor.y) ){
            TPActive = true;
            tpActive();
            TP.locate = false;
        }
    }

}

void Window_main::tpActive(){

    //cout << click_x << "    " << click_y << endl;

int len = pHOLL.len;
for(int i = 0; i < len; i++){
    if ((pHOLL.kor[i].x <= click_x) && ( click_x <= (pHOLL.kor[i].x + DOTS_SIZE))) {
        if ((pHOLL.kor[i].y <= click_y) && (click_y <= (pHOLL.kor[i].y + DOTS_SIZE))) {
            px = pHOLL.kor[i].x;
            py = pHOLL.kor[i].y;
            TPActive = false;
        }
    }
}

click_x = 0;
click_y = 0;
}

void Window_main::checkGhost(){

    if(defActive){
        if((px == rChost_x) && (py == rChost_y)){
            px = 480;
            py = 420;
            defActive = false;
        }
        if((px == bChost_x) && (py == bChost_y)){
            px = 480;
            py = 420;
            defActive = false;
        }
    }else{
        if(redGhostLive){
            if((px == rChost_x) && (py == rChost_y)){
                inGame = false;
            }
        }
        if(blueGhostLive){
            if((px == bChost_x) && (py == bChost_y)){
                inGame = false;
            }
        }
    }
}

void Window_main::checkGhostKill(int x, int y){

    if( (x == rChost_x) && (y == rChost_y) ){
        redGhostLive = false;
        redRespawn = 35;
    }
    if( (x == bChost_x) && (y == bChost_y) ){
        blueGhostLive = false;
        blueRespawn = 35;
    }

}

void Window_main::Move() {

    if ((leftDirection) && (checkWALL('l'))) {
        px -= DOTS_SIZE;
    }

    if ((rightDirection) && (checkWALL('r'))) {
        px += DOTS_SIZE;
    }

    if ((upDirection) && (checkWALL('u'))) {
        py -= DOTS_SIZE;
    }

    if ((downDirection) && (checkWALL('d'))) {
        py += DOTS_SIZE;
    }
}

void Window_main::redMove(){

    POS RUP;
    POS RDOWN;
    POS RLEFT;
    POS RRIGHT;

    double bufL{}, bufR{}, bufU{}, bufD{};
    double leftD{}, rightD{}, upD{}, downD{};

    if ( (rChost_x == IPOV.x) && (rChost_y == IPOV.y) ){
        redLeftDirection = false;
        redRightDirection = false;
        redUpDirection = true;
        redDownDirection = false;
    }
    if (redJ){
        if ( (rChost_x == JPOV.x) && (rChost_y == JPOV.y) ){
            RLEFT.x = JPOV.x - DOTS_SIZE;
            RLEFT.y = JPOV.y;
            RRIGHT.x = JPOV.x + DOTS_SIZE;
            RRIGHT.y = JPOV.y;

            bufL = pow(px-RLEFT.x, 2.0) + pow(py - RLEFT.y, 2.0);
            leftD = sqrt(bufL);
            bufR = pow(px-RRIGHT.x, 2.0) + pow(py - RRIGHT.y, 2.0);
            rightD = sqrt(bufR);

            if(leftD > rightD){
                redLeftDirection = false;
                redRightDirection = true;
                redUpDirection = false;
                redDownDirection = false;
            }
            else if(leftD < rightD){
                redLeftDirection = true;
                redRightDirection = false;
                redUpDirection = false;
                redDownDirection = false;
            }else{
                redLeftDirection = false;
                redRightDirection = true;
                redUpDirection = false;
                redDownDirection = false;
            }
            redJ = false;
        }
    }

    for(int i = 0; i < pPOVOROT.len; i++){

        if( (rChost_x == pPOVOROT.kor[i].x) && (rChost_y == pPOVOROT.kor[i].y) ){

            bool bufright = true;
            bool bufleft = true;
            bool bufup = true;
            bool bufdown = true;

            // проверка на повороты
            for(int j = 0; j < pWALL.len ; j++){
                if( ((pPOVOROT.kor[i].x - DOTS_SIZE) == pWALL.kor[j].x) && (pPOVOROT.kor[i].y == pWALL.kor[j].y) ){
                    bufleft = false;
                    break;
                }
            }
            for(int j = 0; j < pWALL.len ; j++){
                if( ((pPOVOROT.kor[i].x + DOTS_SIZE) == pWALL.kor[j].x) && (pPOVOROT.kor[i].y == pWALL.kor[j].y) ){
                    bufright = false;
                    break;;
                }
            }
            for(int j = 0; j < pWALL.len ; j++){
                if( (pPOVOROT.kor[i].x == pWALL.kor[j].x) && ((pPOVOROT.kor[i].y - DOTS_SIZE) == pWALL.kor[j].y) ){
                    bufup = false;
                    break;
                }
            }
            for(int j = 0; j < pWALL.len ; j++){
                if( (pPOVOROT.kor[i].x == pWALL.kor[j].x) && ((pPOVOROT.kor[i].y + DOTS_SIZE) == pWALL.kor[j].y) ){
                    bufdown = false;
                    break;
                }
            }
            if( ((pPOVOROT.kor[i].x - DOTS_SIZE) == rGhost_x) && (pPOVOROT.kor[i].y == rGhost_y) ){
                bufleft = false;
            }
            if( ((pPOVOROT.kor[i].x + DOTS_SIZE) == rGhost_x) && (pPOVOROT.kor[i].y == rGhost_y) ){
                bufright = false;
            }
            if( (pPOVOROT.kor[i].x == rGhost_x) && ((pPOVOROT.kor[i].y - DOTS_SIZE) == rGhost_y) ){
                bufup = false;
            }
            if( (pPOVOROT.kor[i].x == rGhost_x) && ((pPOVOROT.kor[i].y + DOTS_SIZE) == rGhost_y) ){
                bufdown = false;
            }

            //если там поворот то передаём координаты
            if(bufleft){
                RLEFT.x = pPOVOROT.kor[i].x - DOTS_SIZE;
                RLEFT.y = pPOVOROT.kor[i].y;
                bufL = pow(px-RLEFT.x, 2.0) + pow(py - RLEFT.y, 2.0);
                leftD = sqrt(bufL);
            }
            else{
                leftD = 99999;
            }

            if(bufright){
                RRIGHT.x = pPOVOROT.kor[i].x + DOTS_SIZE;
                RRIGHT.y = pPOVOROT.kor[i].y;
                bufR = pow(px-RRIGHT.x, 2.0) + pow(py - RRIGHT.y, 2.0);
                rightD = sqrt(bufR);
            }
            else{
                rightD = 99999;
            }

            if(bufup){
                RUP.x = pPOVOROT.kor[i].x;
                RUP.y = pPOVOROT.kor[i].y - DOTS_SIZE;
                bufU = pow(px-RUP.x, 2.0) + pow(py - RUP.y, 2.0);
                upD = sqrt(bufU);
            }
            else{
                upD = 99999;
            }

            if(bufdown){
                RDOWN.x = pPOVOROT.kor[i].x;
                RDOWN.y = pPOVOROT.kor[i].y + DOTS_SIZE;
                bufD = pow(px-RDOWN.x, 2.0) + pow(py - RDOWN.y, 2.0);
                downD = sqrt(bufD);
            }
            else{
                downD = 99999;
            }

            if( (leftD < rightD) && (leftD < upD) && (leftD < downD) ){
                redLeftDirection = true;
                redRightDirection = false;
                redUpDirection = false;
                redDownDirection = false;
            }
            else if( (rightD < leftD) && (rightD < upD) && (rightD < downD) ){
                redLeftDirection = false;
                redRightDirection = true;
                redUpDirection = false;
                redDownDirection = false;
            }
            else if( (upD < rightD) && (upD < leftD) && (upD < downD) ){
                redLeftDirection = false;
                redRightDirection = false;
                redUpDirection = true;
                redDownDirection = false;
            }
            else if( (downD < rightD) && (downD < upD) && (downD < leftD) ){
                redLeftDirection = false;
                redRightDirection = false;
                redUpDirection = false;
                redDownDirection = true;
            }
            else{
                redLeftDirection = false;
                redRightDirection = false;
                redUpDirection = false;
                redDownDirection = false;

            }


        break;
        }//end check
    }

    rGhost_x = rChost_x;
    rGhost_y = rChost_y;
    if (redLeftDirection) {
        rChost_x -= DOTS_SIZE;
    }

    if (redRightDirection) {
        rChost_x += DOTS_SIZE;
    }

    if (redUpDirection) {
        rChost_y -= DOTS_SIZE;
    }

    if (redDownDirection) {
        rChost_y += DOTS_SIZE;
    }

}

void Window_main::locateBPoint(){

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int RAND_POS = pHOLL.len - 1;

    int r = qrand() % RAND_POS;
    bpoint_x = pHOLL.kor[r].x;
    bpoint_y = pHOLL.kor[r].y;


}

void Window_main::blueMove(){

    POS BUP;
    POS BDOWN;
    POS BLEFT;
    POS BRIGHT;

    double bufL{}, bufR{}, bufU{}, bufD{};
    double leftD{}, rightD{}, upD{}, downD{};

    if(needBPoint){
        locateBPoint();
        needBPoint = false;
    }

    if( (bChost_x == bpoint_x) && (bChost_y == bpoint_y) ){
        locateBPoint();
    }

    if ( (bChost_x == IPOV.x) && (bChost_y == IPOV.y) ){
        blueLeftDirection = false;
        blueRightDirection = false;
        blueUpDirection = true;
        blueDownDirection = false;
    }
    if (blueJ){
        if ( (bChost_x == JPOV.x) && (bChost_y == JPOV.y) ){
            BLEFT.x = JPOV.x - DOTS_SIZE;
            BLEFT.y = JPOV.y;
            BRIGHT.x = JPOV.x + DOTS_SIZE;
            BRIGHT.y = JPOV.y;

            bufL = pow(bpoint_x-BLEFT.x, 2.0) + pow(bpoint_y - BLEFT.y, 2.0);
            leftD = sqrt(bufL);
            bufR = pow(bpoint_x-BRIGHT.x, 2.0) + pow(bpoint_y - BRIGHT.y, 2.0);
            rightD = sqrt(bufR);

            if(leftD > rightD){
                blueLeftDirection = false;
                blueRightDirection = true;
                blueUpDirection = false;
                blueDownDirection = false;
            }
            else if(leftD < rightD){
                blueLeftDirection = true;
                blueRightDirection = false;
                blueUpDirection = false;
                blueDownDirection = false;
            }else{
                blueLeftDirection = false;
                blueRightDirection = true;
                blueUpDirection = false;
                blueDownDirection = false;
            }
            blueJ = false;
        }
    }

    for(int i = 0; i < pPOVOROT.len; i++){

        if( (bChost_x == pPOVOROT.kor[i].x) && (bChost_y == pPOVOROT.kor[i].y) ){

            bool bufright = true;
            bool bufleft = true;
            bool bufup = true;
            bool bufdown = true;

            // проверка на повороты
            for(int j = 0; j < pWALL.len ; j++){
                if( ((pPOVOROT.kor[i].x - DOTS_SIZE) == pWALL.kor[j].x) && (pPOVOROT.kor[i].y == pWALL.kor[j].y) ){
                    bufleft = false;
                    break;
                }
            }
            for(int j = 0; j < pWALL.len ; j++){
                if( ((pPOVOROT.kor[i].x + DOTS_SIZE) == pWALL.kor[j].x) && (pPOVOROT.kor[i].y == pWALL.kor[j].y) ){
                    bufright = false;
                    break;;
                }
            }
            for(int j = 0; j < pWALL.len ; j++){
                if( (pPOVOROT.kor[i].x == pWALL.kor[j].x) && ((pPOVOROT.kor[i].y - DOTS_SIZE) == pWALL.kor[j].y) ){
                    bufup = false;
                    break;
                }
            }
            for(int j = 0; j < pWALL.len ; j++){
                if( (pPOVOROT.kor[i].x == pWALL.kor[j].x) && ((pPOVOROT.kor[i].y + DOTS_SIZE) == pWALL.kor[j].y) ){
                    bufdown = false;
                    break;
                }
            }
            if( ((pPOVOROT.kor[i].x - DOTS_SIZE) == bGhost_x) && (pPOVOROT.kor[i].y == bGhost_y) ){
                bufleft = false;
            }
            if( ((pPOVOROT.kor[i].x + DOTS_SIZE) == bGhost_x) && (pPOVOROT.kor[i].y == bGhost_y) ){
                bufright = false;
            }
            if( (pPOVOROT.kor[i].x == bGhost_x) && ((pPOVOROT.kor[i].y - DOTS_SIZE) == bGhost_y) ){
                bufup = false;
            }
            if( (pPOVOROT.kor[i].x == bGhost_x) && ((pPOVOROT.kor[i].y + DOTS_SIZE) == bGhost_y) ){
                bufdown = false;
            }

            //если там поворот то передаём координаты
            if(bufleft){
                BLEFT.x = pPOVOROT.kor[i].x - DOTS_SIZE;
                BLEFT.y = pPOVOROT.kor[i].y;
                bufL = pow(bpoint_x-BLEFT.x, 2.0) + pow(bpoint_y - BLEFT.y, 2.0);
                leftD = sqrt(bufL);
            }
            else{
                leftD = 99999;
            }

            if(bufright){
                BRIGHT.x = pPOVOROT.kor[i].x + DOTS_SIZE;
                BRIGHT.y = pPOVOROT.kor[i].y;
                bufR = pow(bpoint_x-BRIGHT.x, 2.0) + pow(bpoint_y - BRIGHT.y, 2.0);
                rightD = sqrt(bufR);
            }
            else{
                rightD = 99999;
            }

            if(bufup){
                BUP.x = pPOVOROT.kor[i].x;
                BUP.y = pPOVOROT.kor[i].y - DOTS_SIZE;
                bufU = pow(bpoint_x-BUP.x, 2.0) + pow(bpoint_y - BUP.y, 2.0);
                upD = sqrt(bufU);
            }
            else{
                upD = 99999;
            }

            if(bufdown){
                BDOWN.x = pPOVOROT.kor[i].x;
                BDOWN.y = pPOVOROT.kor[i].y + DOTS_SIZE;
                bufD = pow(bpoint_x-BDOWN.x, 2.0) + pow(bpoint_y - BDOWN.y, 2.0);
                downD = sqrt(bufD);
            }
            else{
                downD = 99999;
            }

            if( (leftD < rightD) && (leftD < upD) && (leftD < downD) ){
                blueLeftDirection = true;
                blueRightDirection = false;
                blueUpDirection = false;
                blueDownDirection = false;
            }
            else if( (rightD < leftD) && (rightD < upD) && (rightD < downD) ){
                blueLeftDirection = false;
                blueRightDirection = true;
                blueUpDirection = false;
                blueDownDirection = false;
            }
            else if( (upD < rightD) && (upD < leftD) && (upD < downD) ){
                blueLeftDirection = false;
                blueRightDirection = false;
                blueUpDirection = true;
                blueDownDirection = false;
            }
            else if( (downD < rightD) && (downD < upD) && (downD < leftD) ){
                blueLeftDirection = false;
                blueRightDirection = false;
                blueUpDirection = false;
                blueDownDirection = true;
            }
            else{

                if(bufleft){
                    blueLeftDirection = true;
                    blueRightDirection = false;
                    blueUpDirection = false;
                    blueDownDirection = false;
                }
                else if(bufright){
                    blueLeftDirection = false;
                    blueRightDirection = true;
                    blueUpDirection = false;
                    blueDownDirection = false;
                }
                else if(bufup){
                    blueLeftDirection = false;
                    blueRightDirection = false;
                    blueUpDirection = true;
                    blueDownDirection = false;
                }
                else if(bufdown){
                    blueLeftDirection = false;
                    blueRightDirection = false;
                    blueUpDirection = false;
                    blueDownDirection = true;
                }

            }


        break;
        }//end check
    }

    bGhost_x = bChost_x;
    bGhost_y = bChost_y;
    if (blueLeftDirection) {
        bChost_x -= DOTS_SIZE;
    }

    if (blueRightDirection) {
        bChost_x += DOTS_SIZE;
    }

    if (blueUpDirection) {
        bChost_y -= DOTS_SIZE;
    }

    if (blueDownDirection) {
        bChost_y += DOTS_SIZE;
    }

}

bool Window_main::checkWALL(char p){

    int len = pWALL.len;
    if(p == 'l'){// check left
        for(int i = 0; i < len; i++){
            int buflx = px - DOTS_SIZE;
            if((py == pWALL.kor[i].y) && (buflx == pWALL.kor[i].x)){
                return false;
            }
        }
    }//end
    if(p == 'r'){// check right
        for(int i = 0; i < len; i++){
            int bufrx = px + DOTS_SIZE;
            if((py == pWALL.kor[i].y) && (bufrx == pWALL.kor[i].x)){
                return false;
            }
        }
    }//end
    if(p == 'u'){// check up
        for(int i = 0; i < len; i++){
            int bufuy = py - DOTS_SIZE;
            if((px == pWALL.kor[i].x) && (bufuy == pWALL.kor[i].y)){
                return false;
            }
        }
    }//end
    if(p == 'd'){// check down
        for(int i = 0; i < len; i++){
            int bufdy = py + DOTS_SIZE;
            if((px == pWALL.kor[i].x) && (bufdy == pWALL.kor[i].y)){
                return false;
            }
        }
    }//end


    return true;

}

void Window_main::keyPressEvent(QKeyEvent *e) {

    int key = e->key();
    //int r = 0;

    if (key == Qt::Key_Left){
        leftDirection = true;
        upDirection = false;
        downDirection = false;
        rightDirection = false;
    }

    if (key == Qt::Key_Right){
        rightDirection = true;
        upDirection = false;
        downDirection = false;
        leftDirection = false;
    }

    if (key == Qt::Key_Up){
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
        downDirection = false;
    }

    if (key == Qt::Key_Down){
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
        upDirection = false;
    }

    QWidget::keyPressEvent(e);
}

void Window_main::mousePressEvent(QMouseEvent *event){

    onMousePress(event->pos());

}

void Window_main::onMousePress(const QPoint &pos){

    click_x = pos.x();
    click_y = pos.y();

}

Window_main::~Window_main()
{
    delete ui;

}


