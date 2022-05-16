#include "window_main.h"

#include <QApplication>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window_main w;
    w.show();
    return a.exec();
}
