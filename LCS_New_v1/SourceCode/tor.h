#ifndef TOR_H
#define TOR_H

#include <QWidget>
#include <QLabel>

#define LUNGHEZZA 5 //Ilosc torow w poziomie
#define ALTEZZA 5 //Ilosc torow w pionie

#define STRAIGHT "Straight"
#define UP "Up"
#define DOWN "Down"

#define LZWROTNICE 3 //Ilosc przyciskow zwrotnic w poziomie
#define AZWROTNICE 1 //Ilosc przyciskow zwrotnic w pionie

#define LSEMAFORY 2 //Ilosc przyciskow semaforow w poziomie
#define ASEMAFORY 2 //Ilosc przyciskow semaforow w pioni

#define STARTX 0 //Pozycja pozioma Pojawiania sie pociagu
#define STARTY 2 //Pozycja pionowa Pojawiania sie pociagu

#define FINISHX 4
#define FINISHY 2

#define START (STARTY*LUNGHEZZA)+STARTX //Coords 2,0 = 0*LUNGHEZZA+2
#define FINISH (FINISHY*LUNGHEZZA)+FINISHX

//--------UWAGA: N+M musi byc rowne AZWROTNICE*LZWROTNICE!!-------
#define UZW 2 //ilosc zwrotnic typu Up
#define DZW 1 //ilosc zwrotnicc typu Down

//Klasa do obslugi Torow typu:
//    0.Tor
//    1.Zwrotnica Gorna
//    2.Zwrotnica Dolna

class Tor: public QLabel
{
private:
    QString WhereTLook;
    QString From;
    //char* Direction; <- raczej do pociagu (pociag sie pojawia i w ktora strone ma jechac)
    int IsTrain;
    int Length;
    int Type; //0=Tor, 1=ZwrotnicaGorna, 2=ZwrotnicaDolna
public:
    Tor();
    Tor(int iT, int len, int typ);

public slots:
    //Nastawienie parametrow klasy
    void setWTL();
    void setITrain();
    void setLen(int num);
    void setType(int num);
    void setFrom(QString string);
    //Zwracanie parametrow klasy
    QString getWTL();
    int getITrain();
    int getLen();
    int getType();
    QString getFrom();
};

#endif // TOR_H
