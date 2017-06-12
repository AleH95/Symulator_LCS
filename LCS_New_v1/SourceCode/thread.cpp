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
    QList <Color*> kids;
    QString stile = "background-color: green";
    int x,y;
    sleep(time);
    window->alla[nrtor]->setITrain();
    kids = window->alla[nrtor]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
    if(!(kids.isEmpty()))
    {
        if(window->alla[nrtor]->getWTL()==UP)
        {
            x=0;
            y=1;
        }
        else if(window->alla[nrtor]->getWTL()==DOWN)
        {
            x=1;
            y=0;
        }
        else if(window->alla[nrtor]->getType()!=1)
        {
            x=0;
            y=1;
            //What when blok is straight(?)
            //from where trasa is coming: up or down??
        }
        else if(window->alla[nrtor]->getType()!=2)
        {
            x=1;
            y=0;
        }
        else
        {
            qDebug("idk");
        }
        kids.at(x)->setStyleSheet(stile);
        kids.at(y)->setStyleSheet("background-color: green");
        kids.clear();
    }
    else if(window->alla[nrtor]->getITrain()==1)
    {
        window->alla[nrtor]->setStyleSheet("background-color: green");
    }
    else
    {
        window->alla[nrtor]->setStyleSheet(stile);
    }
}
