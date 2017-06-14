#ifndef COLOR_H
#define COLOR_H

#include "myheaders.h"

//--Klasa przechowujaca QLabele odpowiadajace za ustawienie zwrotnicy
//--Na glownym QLabelu sa podlozone QLabele tej klasy, zgodnie z orjentacja zwrotnicy, zmieniaja kolor

class Color: public QLabel
{
private:
    QLabel* ctab;   //Tablica QLabeli
    int citer;      //Zmienna iteracyjna tablicy
    int croz;       //Rozmiar powyzszej tablicy

public:
    Color();
    ~Color();
    Color(int num);             //num = rozmiar talicy Qlabel
    QLabel *get();
    QLabel *getThat(int num);   //Zwracanie elementu pod danym indeksie
    int getcroz();
    int getciter();
    void reset();               //Resetowanie pozycji iteratora (Iterato=Rozmiar Stosu)
};

#endif // COLOR_H
