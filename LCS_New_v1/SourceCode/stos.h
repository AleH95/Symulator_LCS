#ifndef STOS_H
#define STOS_H

#include "myheaders.h"

//Specjalna klasa Stos (w rzeczywistosci KOLEJKA), zwracajaca rowniez rzadana wartosc
//    Sluzy do obslugi Koordynantow Zwrotnic i Semaforow
class Stos
{
private:
    int *tab;
    int iter;
    int roz;
public:
    Stos();
    ~Stos();
    Stos(int num, int cpy[]);   //Konstruktor inicjujace tablice stosu, dana tablica
    void Append(int num);       //Dodanie wartosci na poczatek stosu (NIEUZYWANA)
    int Get();                  //Zwracanie wartosci ze stosu (Startujac od indeksa 0)
    int GetThat(int num);       //Zwracanie wartosci o rzadanym indeksie ze stosu
    int getroz();               //Rozmiar stosu
    int getiter();              //Pozycja iteratora we stosie
    int getpos(int num);        //Indeks pod ktorym sie znajduje wartosc num
    void reset();               //Resetowanie pozycji iteratora (Iterato=Rozmiar Stosu)
};

#endif // STOS_H
