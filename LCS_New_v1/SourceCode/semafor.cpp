#include "semafor.h"
#include <QLabel>

Semafor::Semafor(int num)
{
    myColor = num;

    mainLab = new QLabel(this);
    SemRed = new QLabel(mainLab);
    SemOrange = new QLabel(mainLab);
    SemYellow = new QLabel(mainLab);
    SemGreen = new QLabel(mainLab);
    SemBlue = new QLabel(mainLab);
    box = NULL;

    /*
    SemRed->setGeometry(QRect(0,0,15,30));
    SemOrange->setGeometry(QRect(15,0,30,15));
    SemYellow->setGeometry(QRect(30,0,30,15));
    SemGreen->setGeometry(QRect(45,0,30,15));
    SemBlue->setGeometry(QRect(60,0,30,15));
    */
    box = new QHBoxLayout(mainLab);
    box->setSpacing(0);


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
