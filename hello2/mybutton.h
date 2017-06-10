#ifndef MYBUTTON_H
#define MYBUTTON_H


//http://doc.qt.io/qt-5/qgridlayout.html - Grid for automatic dispositions of buttons
//https://doc.qt.io/archives/qq/qq10-signalmapper.html - Mapping to connect multiple emits to one signal
//http://doc.qt.io/qt-4.8/qbuttongroup.html - ButtonGroup, groups buttons ad disables the unchecked (?)

#include "myheader.h"

class mybutton : public QPushButton
{
public:
    mybutton();
    mybutton(QWidget *parent = Q_NULLPTR);
    mybutton(const QString &text, QWidget *parent = Q_NULLPTR);
    mybutton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);
    ~mybutton();

    void setstan(); //inkrementacka stanu zwrotnicy
    void setlock(); //nastawianie blokady zwrotnicy
    int getstan(void);
    int getlock(void);
    void reset(); //inicializacia stanu i blokady zwrotnicy do zera

private:
    int stan;
    int lock;

};

#endif // MYBUTTON_H
