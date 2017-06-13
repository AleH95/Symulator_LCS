#include "color.h"

Color::Color()
{

}

Color::Color(int num)
{
    citer=0;
    croz=num;
    ctab = new QLabel[croz];
}

QLabel* Color::get()
{
    if(citer>=croz || citer<0) //Jesli przekroczono dlugosc stosu (dwustronnie)
    {
        return NULL;
    }
    else
    {
        citer++;
        return (ctab+(citer-1));
    }
}

QLabel* Color::getThat(int num)
{
    if(num>=croz || num<0)
    {
        return (ctab+0);
    }
    else
    {
        return (ctab+num);
    }
}

int Color::getcroz()
{
    return croz;
}

int Color::getciter()
{
    return citer;
}

void Color::reset()
{
    citer=0;
}
