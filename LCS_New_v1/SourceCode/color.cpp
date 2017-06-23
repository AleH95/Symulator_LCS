#include "color.h"

Color::Color()
{

}

Color::~Color()
{
    if(ctab!=NULL)
    {
        delete[] ctab;
        ctab=NULL;
    }
}

Color::Color(int num)
{
    citer=0;
    croz=num;
    ctab = new QLabel[croz];
}

QLabel* Color::get()
{
    if(citer<croz && citer>=0) //Jesli przekroczono dlugosc stosu (dwustronnie)
    {
        citer++;
        return (ctab+(citer-1));
    }
    else
    {
        return NULL;
    }
}

QLabel* Color::getThat(int num)
{
    if(num>=croz || num<0)
    {
        return NULL;
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
