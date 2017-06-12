#include "pociag.h"

int Pociag::Quanto=0;

Pociag::Pociag()
{
    Dlg = 50;
    Predkosc=0;
    Coords=0;
    Direction=0;
}

void Pociag::setDlg(double n)
{
    Dlg = n;
}

void Pociag::setPredkosc(double n)
{
    Predkosc = n;
}

void Pociag::setCoords(int n)
{
    Coords = n;
}

void Pociag::setDirection(int n)
{
    Direction = n;
}

void Pociag::increment()
{
    Quanto++;
    if(Quanto<0)
    {
        Quanto = 0;
    }
}

void Pociag::decrement()
{
    Quanto--;
    if(Quanto<0)
    {
        Quanto = 0;
    }
}

void Pociag::equal(Pociag* ciuf)
{
    Dlg = ciuf->Dlg;
    Predkosc = ciuf->Predkosc;
    Coords = ciuf->Coords;
    Direction = ciuf->Direction;
}

double Pociag::getDlg()
{
    return Dlg;
}

double Pociag::getPredkosc()
{
    return Predkosc;
}

int Pociag::getCoords()
{
    return Coords;
}

int Pociag::getDirection()
{
    return Direction;
}

int Pociag::getQuanto()
{
    return Quanto;
}
