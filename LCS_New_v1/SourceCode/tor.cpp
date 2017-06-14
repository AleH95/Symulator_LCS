#include "tor.h"

Tor::Tor(int iT, int len, int typ) :
        IsTrain(iT), Length(len), Type(typ)
{
    WhereTLook=STRAIGHT;    //<-Set to "NULL"
    From=STRAIGHT;          //<-Set to "NULL"
}

//--Automatyczne nastawianie, zmiana parametrow, zaleznie od typu zwrotnicy
void Tor::setWTL()
{
    if(Type==1 || Type==3)
    {
        if(WhereTLook==STRAIGHT)
        {
            WhereTLook=UP;
            return;
        }
    }
    else if (Type==2 || Type==4)
    {
        if(WhereTLook==STRAIGHT)
        {
            WhereTLook=DOWN;
            return;
        }
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
    if(Type==1 || Type==3)
    {
        if(From==STRAIGHT)
        {
            From=UP;
            return;
        }
    }
    else if (Type==2 || Type==4)
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
