#ifndef MYBUTTON_H
#define MYBUTTON_H


//Tworzenie nowej klasy przyciskow ktora pozwala na przechowyanie zmiennych
//Stanu -> aktualnym stanie przycisku
//Blokuj -> w przypadku potwoierdzenia trasy

#include <QPushButton>

class mybutton : public QPushButton
{
public:
    mybutton();
    mybutton(QWidget *parent = Q_NULLPTR);
    mybutton(const QString &text, QWidget *parent = Q_NULLPTR);
    mybutton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);
    ~mybutton();

    void setstan(int n=0);
    void setlocked(int n=0);
    int getstan(void);
    int getlocked(void);

private:
    int stan;
    int locked;

};

#endif // MYBUTTON_H
