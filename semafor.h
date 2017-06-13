#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <QWidget>
#include <QLabel>


class Semafor: public QLabel
{
private:
    int rozmiar;
    QLabel *semafory;
    QLabel *MainLab;
    QLabel *Lab2;
    QLabel *Lab3;
    //Color *kolory;
    int myColor;

public:
    Semafor();
    Semafor(int num); //rozmiar tablicy

public slots:
    QLabel setColor(int numer);

    int getColor();

};


#endif // SEMAFOR_H
