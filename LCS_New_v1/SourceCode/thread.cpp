#include "thread.h"

WThread::WThread()
{

}

void WThread::start(int nr, int tm, Widget *main)
{
    nrtor=nr;
    time=tm;
    window=main;
    QThread::start();
}

void WThread::run()
{
    QString stile = "background-color: green";
    sleep(time);
    window->alla[nrtor]->setITrain();
    window->clean(nrtor,stile);
    //emit counterReached(nrtor,stile);
    exec();
    //quit();
}
