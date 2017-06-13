#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class Semafor: public QLabel
{
private:
    int rozmiar;
    QLabel *semafory;
    //QLabel *SemaforLab;
    QLabel *SemRed;
    QLabel *SemOrange;
    QLabel *SemYellow;
    QLabel *SemGreen;
    QLabel *SemBlue;
    QHBoxLayout *box;
    //Color *kolory;
    int myColor;

public:
    Semafor();
    Semafor(int num = 0); //numer koloru

public slots:
    void setColor(int numer);
    void SemReset();
    int getColor();

};


#endif // SEMAFOR_H
