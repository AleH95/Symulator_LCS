#include "stos.h"

Stos::Stos(int num, int cpy[])
{
    int i;
    iter=0;
    roz=num;
    tab = new int[roz];
    for(i=0;i<roz;i++)
    {
        tab[i]=cpy[i];
    }
}

void Stos::Append(int num)
{
    if(iter>=roz || iter<0) //Jesli przekroczono dlugosc stosu (dwustronnie)
    {
        return;
    }
    else
    {
        tab[iter]=num;
        iter++;
    }
}

int Stos::Get()
{
    if(iter>=roz || iter<0) //Jesli przekroczono dlugosc stosu (dwustronnie)
    {
        return 0;
    }
    else
    {
        iter++;
        return tab[iter];
    }
}

int Stos::GetThat(int num)
{
    if(num>=roz || num<0)
    {
        return 0;
    }
    else
    {
        return tab[num];
    }

}
/*
void Stos::operator = (const int cpy[])
{
    int i;
    for(i=0;i<roz;i++)
    {
        tab[i]=cpy[i];
    }
}
*/
int Stos::getroz()
{
    return roz;
}

int Stos::getiter()
{
    return iter;
}

void Stos::reset()
{
    iter=roz;
}
