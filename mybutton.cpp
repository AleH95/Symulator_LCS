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

void mybutton::setlocked(int n)
{
    this->locked=n;
}

int mybutton::getstan(void)
{
    return this->stan;
}

int mybutton::getlocked(void)
{
    return this->locked;
}
