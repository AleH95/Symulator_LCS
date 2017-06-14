#ifndef POCIAG_H
#define POCIAG_H

#include "myheaders.h"

//--Klasa reprezentujaca pociag

class Pociag: public QLabel
{
private:
    double Dlg;         //Dlugosc pociagu
    double Predkosc;    //Predkosc pociagu
    int Coords;         //Na ktorym torze sie znajduje pociag
    int Direction;      //W ktora strone jedzie pociag: 0.Lewo->Prawo, 1.Prawo->Lewo

public:
    static int Quanto;          //Ilosc pociagow w systemie
    static void increment();    //Inkrementacja zmiennej statycznej
    static void decrement();    //Dekrementacja zmiennej statycznej
    void equal(Pociag* ciuf);   //Funkcja kopiujaca zmienne
    Pociag();
    //--Nastawianie wartosci zmiennych klasy
    void setDlg(double n);
    void setPredkosc(double n);
    void setCoords(int n);
    void setDirection(int n);
    //--Pobierania wartosci zmiennych klasy
    double getDlg();
    double getPredkosc();
    int getCoords();
    int getDirection();
    static int getQuanto();
};

#endif // POCIAG_H
