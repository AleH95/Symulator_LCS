#ifndef COLOR_H
#define COLOR_H

#include <QLabel>

class Color: public QLabel
{
private:
    QLabel* ctab;
    int citer;
    int croz;
public:
    Color();
    Color(int num); //rozmiar tablicy
    QLabel *get();
    QLabel *getThat(int num);
    int getcroz(); //Rozmiar stosu
    int getciter(); //Pozycja iteratora we stosie
    void reset(); //Resetowanie pozycji iteratora (Iterato=Rozmiar Stosu)
};

#endif // COLOR_H
