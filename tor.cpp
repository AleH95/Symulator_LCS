#include "tor.h"

Tor::Tor(int iT, int len, int typ) :
        IsTrain(iT), Length(len), Type(typ)
{
    WhereTLook=STRAIGHT;
    From=STRAIGHT;
}

void Tor::setWTL()
{
    if(Type==1)
    {
        if(WhereTLook==STRAIGHT)
        {
            WhereTLook=UP;
            return;
        }
    }
    else if (Type==2)
    {
        if(WhereTLook==STRAIGHT)
        {
            WhereTLook=DOWN;
            return;
        }
    }
    WhereTLook=STRAIGHT;
}

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

void Tor::setFrom(QString string)
{
    From = string;
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
