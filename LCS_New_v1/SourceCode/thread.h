#ifndef THREAD_H
#define THREAD_H

#include <QThread>
//#include "color.h"
//#include "tor.h"
#include "Mainwidget.h"
//#include "Mainwidget.h"


class WThread : public QThread
{
public:
    WThread();
    void start(int nr, int tm, Widget *main);
    void run() override;
private:

    int nrtor;
    int time;
    Widget* window;

};

#endif // THREAD_H
