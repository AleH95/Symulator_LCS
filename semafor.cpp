#include "semafor.h"
#include <QLabel>

Semafor::Semafor(int num)
{


    int myColor = num;

    QLabel* SemaforLab = new QLabel(this);
    QLabel* SemRed = new QLabel(SemaforLab);
    QLabel* SemOrange = new QLabel(SemaforLab);
    QLabel* SemYellow = new QLabel(SemaforLab);
    QLabel* SemGreen = new QLabel(SemaforLab);
    QLabel* SemBlue = new QLabel(SemaforLab);

    //MainLab->setStyleSheet("background-color:orange");
        SemaforLab->setGeometry(QRect(0,0,75,15));
        SemaforLab->setStyleSheet("background-color:white");
        SemRed->setGeometry(QRect(0,0,15,30));
        SemOrange->setGeometry(QRect(15,0,30,15));
        SemYellow->setGeometry(QRect(30,0,30,15));
        SemGreen->setGeometry(QRect(45,0,30,15));
        SemBlue->setGeometry(QRect(60,0,30,15));

        //ustawienie poczatkowego stanu semafora
        SemRed->setStyleSheet("background-color:red");


}

QLabel Semafor::setColor(int numer)
{
    myColor = numer;
    if(myColor == 0)
    {
        SemRed->setStyleSheet("background-color:red");
        SemOrange->setStyleSheet("background-color:white");
        SemYellow->setStyleSheet("background-color:white");
        SemGreen->setStyleSheet("background-color:white");
        SemBlue->setStyleSheet("background-color:white");


    }
    else if(myColor == 1)
    {
        SemRed->setStyleSheet("background-color:white");
        SemOrange->setStyleSheet("background-color:orange");
        SemYellow->setStyleSheet("background-color:white");
        SemGreen->setStyleSheet("background-color:white");
        SemBlue->setStyleSheet("background-color:white");
    }

    else if(myColor == 2)
    {
        SemRed->setStyleSheet("background-color:white");
        SemOrange->setStyleSheet("background-color:white");
        SemYellow->setStyleSheet("background-color:yellow");
        SemGreen->setStyleSheet("background-color:white");
        SemBlue->setStyleSheet("background-color:white");
    }
    else if(myColor == 3)
    {
        SemRed->setStyleSheet("background-color:white");
        SemOrange->setStyleSheet("background-color:white");
        SemYellow->setStyleSheet("background-color:white");
        SemGreen->setStyleSheet("background-color:green");
        SemBlue->setStyleSheet("background-color:white");
    }
    else if(myColor == 4)
    {
        SemRed->setStyleSheet("background-color:white");
        SemOrange->setStyleSheet("background-color:white");
        SemYellow->setStyleSheet("background-color:white");
        SemGreen->setStyleSheet("background-color:white");
        SemBlue->setStyleSheet("background-color:blue");
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


