#include "semafor.h"
#include <QLabel>

Semafor::Semafor(int num)
{
    myColor = num;

    SemRed = new QLabel();
    SemOrange = new QLabel();
    SemYellow = new QLabel();
    SemGreen = new QLabel();
    SemBlue = new QLabel();

    box = NULL;
    box = new QHBoxLayout(this);
    box->setSpacing(5);

    box->addWidget(SemRed);
    box->addWidget(SemOrange);
    box->addWidget(SemYellow);
    box->addWidget(SemGreen);
    box->addWidget(SemBlue);

    setColor(myColor);
}

Semafor::~Semafor()
{
    if(SemRed!=NULL)
    {
        delete SemRed;
        SemRed=NULL;
    }
    if(SemOrange!=NULL)
    {
        delete SemOrange;
        SemOrange=NULL;
    }
    if(SemYellow!=NULL)
    {
        delete SemYellow;
        SemYellow=NULL;
    }
    if(SemGreen!=NULL)
    {
        delete SemGreen;
        SemGreen=NULL;
    }
    if(SemBlue!=NULL)
    {
        delete SemBlue;
        SemBlue=NULL;
    }
    if(box!=NULL)
    {
        delete box;
        box=NULL;
    }
}

void Semafor::setColor(int numer)
{
    myColor = numer;
    if(myColor == 0)
    {
        SemRed->setStyleSheet("background-color: grey");
        SemOrange->setStyleSheet("background-color:grey");
        SemYellow->setStyleSheet("background-color:red");
        SemGreen->setStyleSheet("background-color:grey");
        SemBlue->setStyleSheet("background-color:grey");


    }
    else if(myColor == 1)
    {
        SemRed->setStyleSheet("background-color:grey");
        SemOrange->setStyleSheet("background-color:orange");
        SemYellow->setStyleSheet("background-color:grey");
        SemGreen->setStyleSheet("background-color:orange");
        SemBlue->setStyleSheet("background-color:grey");
    }

    else if(myColor == 2)
    {
        SemRed->setStyleSheet("background-color:grey");
        SemOrange->setStyleSheet("background-color:orange");
        SemYellow->setStyleSheet("background-color:grey");
        SemGreen->setStyleSheet("background-color:orange");
        SemBlue->setStyleSheet("background-color:grey");
    }
    else if(myColor == 3)
    {
        /*
        SemRed->setStyleSheet("background-color:green");
        SemOrange->setStyleSheet("background-color:grey");
        SemYellow->setStyleSheet("background-color:grey");
        SemGreen->setStyleSheet("background-color:orange");
        SemBlue->setStyleSheet("background-color:grey");
        */
        SemRed->setStyleSheet("background-color:green");
        SemOrange->setStyleSheet("background-color:white");
        SemYellow->setStyleSheet("background-color:orange");
        SemGreen->setStyleSheet("background-color:yellow");
        SemBlue->setStyleSheet("background-color:blue");
    }
    else if(myColor == 4)
    {
        SemRed->setStyleSheet("background-color:green");
        SemOrange->setStyleSheet("background-color:grey");
        SemYellow->setStyleSheet("background-color:grey");
        SemGreen->setStyleSheet("background-color:grey");
        SemBlue->setStyleSheet("background-color:grey");
    }
}

void Semafor::SemReset()
{
    myColor = 0;
}

int Semafor::getColor()
{
    return myColor;
}

QHBoxLayout* Semafor::getlayout()
{
    return box;
}
