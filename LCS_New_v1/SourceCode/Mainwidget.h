#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QThread>
#include <QLabel>
#include <QtCore>
#include "tor.h"
#include "stos.h"
#include "color.h"
#include "pociag.h"
//#include "thread.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    friend class WThread;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void inizializza(); //function generating the basic layout

private:
    Ui::Widget *ui;
    QGridLayout *GTory,*GBZwrotnice,*GBSemafory; //grids for window components
    QVBoxLayout *MainLayout, *VGenTrain[TRAIN/2]; //Main Layout that is displayed (contains the other layaouts)
    QHBoxLayout *HorizontalZwSemGen;
    Tor *alla[ALTEZZA*LUNGHEZZA]; //Array of blocks for visual display (Tor+ZwrotnicaGorna/Dolna)
    QPushButton* Zwrotnice[AZWROTNICE*LZWROTNICE]; //Array of buttons Zwrotnica
    QPushButton* Semafory[ASEMAFORY*LSEMAFORY]; //Array of Semafors Zwrotnica
    Tor *temptor; //Pointer for temporary value od Tor
    //QPushButton *GenTrain; //Button to generate train
    QPushButton *GenTrain[TRAIN];
    //QPushButton *TrainArrived; //Button to clear the path where the train arrived
    QWidget* parentLayout; //Pointer for value of parent layout (USELESS)
    QSignalMapper *ZsignalMapper,*SsignalMapper,*GsignalMapper; //Signal mappers for Zwrotnice and Semafory
    Stos *ZwUpDw; //Klass Stos containing all the Coords where to find Zwrotnice on the Visualization
    Stos *Generation; //Klasa containing coords of where the trains will be generated
    Color *ZwKol;
    QVBoxLayout* VLay[UZW+DZW];
    QList <Color *> kids;
    Pociag *Ciuf;


public slots:
    void Train(); //Generates Train
    void Trasa(int j, char kolor, int flg); //Visual rapresentation of the path the train will go on
    void TrasaReverse(int j, char kolor, int flg);
    bool inUp(int num,Stos* tab); //Function comparing if the Tor's j-th element is a Zwrotnica Gorna
    bool inDw(int num,Stos* tab);//Function comparing if the Tor's j-th element is a Zwrotnica Dolna
    void ZwChange(int n);
    void cleanAdjacent(int n, QString stile);
    void cleanAdjacentReverse(int n, QString stile);
    void setZwStan(int n);
    void clean(int n, QString stile);
    void setFromStan(int tmp, QString stan);
    void TrainGone();
    void TrasaPociag(int n, QString kolor);
    double trasaTime(int nrciuf,int nrtor);
    double TrainTime(int nrciuf,int nrtor);
    double kmhTOms(double vel);
    //double secTOms(double sec);
    //Needed also:
        //TrasaReset() -> seting the illumination of the position of the zwrotnica and discarding all other illumination
};

#endif // MAINWIDGET_H
