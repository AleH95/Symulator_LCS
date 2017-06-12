#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <QWidget>
#include <QLabel>


//--------UWAGA: N+M musi byc rowne AZWROTNICE*LZWROTNICE!!-------
#define UZW 2 //ilosc zwrotnic typu Up
#define DZW 1 //ilosc zwrotnicc typu Down

//Klasa do obslugi semafora :
//    0.zielone
//    1.żółte
//    2.czerwone

class Semafor: public QLabel
{
private:

    int TrainWaiting;
    int SemLightColor;
public:
    Semafor();
    Semafor(int iW);


public slots:
    //Nastawienie parametrow klasy
    void setLight();


    //Zwracanie parametrow klasy
    int getLight();


};

#endif // SEMAFOR_H
