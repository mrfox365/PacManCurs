#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Window_main; }
QT_END_NAMESPACE

class Window_main : public QWidget{
    Q_OBJECT

public:
    Window_main(QWidget *parent = nullptr);
    ~Window_main();

private:
    Ui::Window_main *ui;

protected:
void paintEvent(QPaintEvent *);
void timerEvent(QTimerEvent *);
void keyPressEvent(QKeyEvent *);
void mousePressEvent(QMouseEvent *);

private:
    QLabel *lineScore;
    QLabel *lineLevel;

    QString map_text;
    QImage wall;
    QImage eat;
    QImage pacman;
    QImage leftpacman;
    QImage rightpacman;
    QImage uppacman;
    QImage downpacman;
    QImage redChost;
    QImage blueChost;
    QImage blueBoll;
    QImage greenBoll;
    QImage redBoll;
    QImage pacmandef;
    QImage leftpacmandef;
    QImage rightpacmandef;
    QImage uppacmandef;
    QImage downpacmandef;
    QImage horAtack;
    QImage verAtack;

    static const int MAP_WIDTH = 990; // 990 end
    static const int MAP_HEITH = 760; // 720 end
    static const int DOTS_SIZE = 30;
    static const int DELAY = 300;


    int timerId;
    int atackTime;
    int redRespawn;
    int blueRespawn;
    int score;
    int level;
    int px;
    int py;
    int rChost_x;
    int rGhost_x;
    int rChost_y;
    int rGhost_y;
    int bChost_x;
    int bGhost_x;
    int bChost_y;
    int bGhost_y;
    int bpoint_x;
    int bpoint_y;
    int click_x;
    int click_y;

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool redLeftDirection;
    bool redRightDirection;
    bool redUpDirection;
    bool redDownDirection;
    bool blueLeftDirection;
    bool blueRightDirection;
    bool blueUpDirection;
    bool blueDownDirection;

    bool inGame;
    bool needKol;
    bool needBoost;
    bool needBPoint;
    bool needEat;
    bool defActive;
    bool atackActive;
    bool TPActive;
    bool blueGhostLive;
    bool redGhostLive;
    bool redJ;
    bool blueJ;

    bool checkWALL(char);
    void worldPaint();
    void getTex();
    void initGame();
    void Move();
    void redMove();
    void blueMove();
    void checkGhost();
    void checkGhostKill(int ,int);
    void locateBoost();
    void locateBPoint();
    void locateEat();
    void checkEat();
    void checkBoost();
    void tpActive();
    void checkLevel();
    void onMousePress(const QPoint &pos);
    void atackPaint(QPainter &);
    void gameOver(QPainter &);




};
#endif // WINDOW_MAIN_H
