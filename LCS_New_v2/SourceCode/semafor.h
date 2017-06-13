#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <QWidget>
#include <QLabel>


class Semafor: public QLabel
{
private:
    int rozmiar;
    QLabel *semafory;
    QLabel *SemaforLab;
    QLabel *SemRed;
    QLabel *SemOrange;
    QLabel *SemYellow;
    QLabel *SemGreen;
    QLabel *SemBlue;
    //Color *kolory;
    int myColor;

public:
    Semafor();
    Semafor(int num); //rozmiar tablicy

public slots:
    QLabel setColor(int numer);
    void SemReset();
    int getColor();

};


#endif // SEMAFOR_H
