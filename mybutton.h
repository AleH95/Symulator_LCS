#ifndef MYBUTTON_H
#define MYBUTTON_H


//Tworzenie nowej klasy przyciskow ktora pozwala na przechowyanie zmiennych
//Stanu -> aktualnym stanie przycisku
//Blokuj -> w przypadku potwoierdzenia trasy

#include <QPushButton>

#define ZWR 5 //ilosc zwrotnic
#define SEM 5 //ilosc semaforow

#define LUNGHEZZA 85 //dlugosc przycisku zwrotnicy
#define ALTEZZA 45 //wysokosc przycisku zwrotnicy

#define WLUNG 1280 //dlugosc okna glownego
#define WALT 720 //wysokosc okna glownego

class mybutton : public QPushButton
{
public:
    mybutton();
    mybutton(QWidget *parent = Q_NULLPTR);
    mybutton(const QString &text, QWidget *parent = Q_NULLPTR);
    mybutton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);
    ~mybutton();

    void setstan(int n=0);
    void setlock(int n=0);
    int getstan(void);
    int getlock(void);

private:
    int stan;
    int lock;

};

#endif // MYBUTTON_H
