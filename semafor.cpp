#include "semafor.h"
#include <QLabel>

Semafor::Semafor(int num)
{


    int myColor = num;

    QLabel* MainLab = new QLabel(this);
    QLabel* Lab2 = new QLabel(MainLab);
    QLabel* Lab3 = new QLabel(MainLab);

    //MainLab->setStyleSheet("background-color:orange");
        MainLab->setGeometry(QRect(0,0,30,15));
        //Lab2->setStyleSheet("background-color:red");
        Lab2->setGeometry(QRect(0,0,15,30));
        //Lab3->setStyleSheet("background-color:orange");
        Lab3->setGeometry(QRect(15,0,30,15));

        //ustawienie poczatkowego stanu semafora
        Lab2->setStyleSheet("background-color:red");
        Lab3->setStyleSheet("background-color:white");


}

QLabel Semafor::setColor(int numer)
{
    myColor = numer;
    if(myColor == 0)
    {
        Lab2->setStyleSheet("background-color:red");
        Lab3->setStyleSheet("background-color:white");
    }
    else if(myColor == 1)
    {
        Lab2->setStyleSheet("background-color:white");
        Lab3->setStyleSheet("background-color:green");
    }
}



int Semafor::getColor()
{
    return myColor;
}


