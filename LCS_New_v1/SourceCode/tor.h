#ifndef TOR_H
#define TOR_H

#include "myheaders.h"

//--Klasa reprezentujaca Tor, i zaleznie od typu rowniez Zwrotnice

class Tor: public QLabel
{
private:
    QString WhereTLook;     //Jak jest dany tor, lub zwrotnica nastawiony (gdzie jest nastepny element)
    QString From;           //Z ktorego elementu sie dostalismy do danego innego elementu
    int IsTrain;            //Czy jest Pociag na danym odcinku
    double Length;          //Dlugosc odcinka
    int Type;               //Tup odcinku -> 0=Tor, 1=ZwrotnicaGorna(Lewo->Prawo), 2=ZwrotnicaDolna(Lewo->Prawo)
                            //                      3=ZwrotnicaGorna(Prawo->Lewo), 4=ZwrotnicaDolna(Prawo->Lewo)

public:
    Tor();
    Tor(int iT, int len, int typ);
    //Nastawienie parametrow klasy
    void setWTL();                  //Automatyczne nastawianie
    void setITrain();               //Automatyczne nastawianie
    void setFrom(QString string);   //Automatyczne nastawianie
    void setLen(double num);
    void setType(int num);
    //Zwracanie parametrow klasy
    QString getWTL();
    int getType();
    int getITrain();
    double getLen();
    QString getFrom();
};

#endif // TOR_H
