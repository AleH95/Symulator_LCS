#ifndef POCIAG_H
#define POCIAG_H

#include <QLabel>


class Pociag: public QLabel
{
private:
    double Dlg;
    double Predkosc;
    int Coords;
    int Direction;


public:
    static int Quanto;
    Pociag();

    void setDlg(double n);
    void setPredkosc(double n);
    void setCoords(int n);
    void setDirection(int n);
    static void increment();
    static void decrement();

    void equal(Pociag* ciuf);

    double getDlg();
    double getPredkosc();
    int getCoords();
    int getDirection();
    static int getQuanto();
};

#endif // POCIAG_H
