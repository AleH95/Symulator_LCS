#include "tor.h"

Tor::Tor(int iT, int len, int typ) :
        IsTrain(iT), Length(len), Type(typ)
{
    WhereTLook=NULLO;    //<-Set to "NULL"
    From=STRAIGHT;          //<-Set to "NULL"
}

//--Automatyczne nastawianie, zmiana parametrow, zaleznie od typu zwrotnicy
void Tor::setWTL()
{
    if(Type==1 || Type==3) //zwrotnica gorna lewo-prawo, prawo-lewo
    {
        if(WhereTLook==STRAIGHT)
        {
            WhereTLook=UP;
            return;
        }
    }
    else if (Type==2 || Type==4) //zwrotnica dolna lewo-prawo, prawo-lewo
    {
        if(WhereTLook==STRAIGHT)
        {
            WhereTLook=DOWN;
            return;
        }
    }
    else if(Type==5 || Type==7) //Ukosna gorna lewo-prawo, prawo-lewo
    {
        WhereTLook=UP;
        return;
    }
    else if(Type==6 || Type==8) //Ukosna dolna lewo-prawo, prawo-lewo
    {
        WhereTLook=DOWN;
        return;
    }
    else if(Type==-1) //Gdzie nie ma torow to nastawiamy NULLO
    {
        WhereTLook=NULLO;
        return;
    }
    WhereTLook=STRAIGHT;
}

//--Automatyczne nastawianie
void Tor::setITrain()
{
    if(this->getITrain()==0)
    {
        IsTrain=1;
    }
    else
    {
        IsTrain=0;
    }
}

void Tor::setLen(double num)
{
    Length = num;
}

void Tor::setType(int num)
{
    Type = num;
}

//--Automatyczne nastawianie, zaleznie od obecnych parametrow obiektu
void Tor::setFrom(QString string)
{
    if(Type==1 || Type==3) //zwrotnica gorna lewo-prawo, prawo-lewo
    {
        if(From==STRAIGHT)
        {
            From=UP;
            return;
        }
    }
    else if (Type==2 || Type==4) //zwrotnica dolna lewo-prawo, prawo-lewo
    {
        if(From==STRAIGHT)
        {
            From=DOWN;
            return;
        }
    }
    From=STRAIGHT;
}

QString Tor::getWTL()
{
    return WhereTLook;
}

int Tor::getITrain()
{
    return IsTrain;
}

double Tor::getLen()
{
    return Length;
}

int Tor::getType()
{
    return Type;
}

QString Tor::getFrom()
{
    return From;
}
