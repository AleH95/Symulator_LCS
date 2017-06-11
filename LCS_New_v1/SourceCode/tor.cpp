#include "tor.h"

Tor::Tor(int iT, int len, int typ) :
        IsTrain(iT), Length(len), Type(typ)
{
    /*
    WhereTLook = new char[strlen(STRAIGHT)];
    strcpy(WhereTLook,STRAIGHT);
    */
    WhereTLook=STRAIGHT;
}

void Tor::setWTL(QString string)
{
    /*
    delete[] WhereTLook;
    WhereTLook = 0;
    WhereTLook = new char[strlen(string)];
    strcpy(WhereTLook,string);
    */
    WhereTLook = string;
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

void Tor::setLen(int num)
{
    Length = num;
}

void Tor::setType(int num)
{
    Type = num;
}

QString Tor::getWTL()
{
    return WhereTLook;
}

int Tor::getITrain()
{
    return IsTrain;
}

int Tor::getLen()
{
    return Length;
}

int Tor::getType()
{
    return Type;
}