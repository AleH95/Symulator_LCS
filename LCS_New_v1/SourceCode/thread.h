#ifndef THREAD_H
#define THREAD_H

#include <QtCore>
#include "color.h"
#include "tor.h"
#include "Mainwidget.h"
//#include "Mainwidget.h"


class WThread : public QThread
{
public:
    WThread();
private:

    int nrtor;
    int time;
    Widget* window;
    void start(int nr, int tm, Widget *main);
    void run();
};

#endif // THREAD_H
