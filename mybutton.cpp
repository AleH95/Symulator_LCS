#include "mybutton.h"

mybutton::mybutton(){;}

mybutton::mybutton(QWidget *parent): QPushButton(parent) {;}
mybutton::mybutton(const QString &text, QWidget *parent): QPushButton(text,parent) {;}
mybutton::mybutton(const QIcon &icon, const QString &text, QWidget *parent): QPushButton(icon,text,parent) {;}
mybutton::~mybutton() {;}

void mybutton::setstan(int n)
{
    this->stan=n;
}

void mybutton::setlock(int n)
{
    this->lock=n;
}

int mybutton::getstan(void)
{
    return this->stan;
}

int mybutton::getlock(void)
{
    return this->lock;
}
