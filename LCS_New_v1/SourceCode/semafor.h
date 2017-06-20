#ifndef SEMAFOR_H
#define SEMAFOR_H

#include "myheaders.h"

//--Klasa reprezentujaca pociag

class Semafor: public QLabel
{
private:
    int rozmiar;
    int myColor;        //Kod Semafora -> jakie kolory beda wyswietlane
    //--QLabele do obslugi kolorow
    QLabel *mainLab;
    QLabel *semafory;
    QLabel *SemRed;
    QLabel *SemOrange;
    QLabel *SemYellow;
    QLabel *SemGreen;
    QLabel *SemBlue;
    //--Layout do graficznej implementacji powyzszych kolorow
    QHBoxLayout *box;


public:
    Semafor();
    ~Semafor();
    Semafor(int num = 0); //num = numer kodu koloru

public slots:
    void setColor(int numer); //Nastawianie danego kodu i wyswietlanie kombinacji kolorow
    void SemReset();
    int getColor();
    QHBoxLayout* getlayout();

};


#endif // SEMAFOR_H
