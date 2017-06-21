#ifndef THREAD_H
#define THREAD_H

#include "Mainwidget.h"


class WThread : public QThread
{
    //Q_OBJECT
//signals:
  //  void counterReached(int n, QString stile);
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
