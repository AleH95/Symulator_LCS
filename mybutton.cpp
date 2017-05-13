#include "mybutton.h"

mybutton::mybutton(){;}

mybutton::mybutton(QWidget *parent): QPushButton(parent)
{
   ;
}

mybutton::mybutton(const QString &text, QWidget *parent): QPushButton(text,parent) {;}
mybutton::mybutton(const QIcon &icon, const QString &text, QWidget *parent): QPushButton(icon,text,parent) {;}
mybutton::~mybutton() {;}

void mybutton::setstan()
{
    if(this->stan==2)
    {
        this->stan=0;
    }
    else
    {
        this->stan=stan+1;
    }
}

void mybutton::setlock()
{
    this->lock=1;
}

int mybutton::getstan(void)
{
    return this->stan;
}

int mybutton::getlock(void)
{
    return this->lock;
}

void mybutton::reset()
{
    this->stan=0;
    this->lock=0;
}
