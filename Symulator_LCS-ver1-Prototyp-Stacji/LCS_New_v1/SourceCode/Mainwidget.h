#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QTimer>
#include "tor.h"
#include "stos.h"
#include "train.h"



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void inizializza(); //function generating the basic layout

private:
    Ui::Widget *ui;
    QGridLayout *GTory,*GBZwrotnice,*GBSemafory; //grids for window components
    QVBoxLayout *MainLayout; //Main Layout that is displayed (contains the other layaouts)
    Tor *alla[ALTEZZA*LUNGHEZZA], *train_route[ROZMIARTRASY]; //Array of blocks for visual display (Tor+ZwrotnicaGorna/Dolna)
    QPushButton* Zwrotnice[AZWROTNICE*LZWROTNICE]; //Array of buttons Zwrotnica
    QPushButton* Semafory[ASEMAFORY*LSEMAFORY]; //Array of Semafors Zwrotnica
    Tor *temptor; //Pointer for temporary value od Tor
    QPushButton *GenTrain; //Button to generate train
    QWidget* parentLayout; //Pointer for value of parent layout (USELESS)
    QSignalMapper *ZsignalMapper,*SsignalMapper; //Signal mappers for Zwrotnice and Semafory
    Stos *ZwUpDw; //Klass Stos containing all the Coords where to find Zwrotnice on the Visualization
    NEWTrain *pociag[NUM_TRAINS];
    QTimer *timer;


public slots:
    void Train(); //Generates Train
    void Trasa(int j, char kolor); //Visual rapresentation of the path the train will go on
    bool inUp(int num,Stos* tab); //Function comparing if the Tor's j-th element is a Zwrotnica Gorna
    bool inDw(int num,Stos* tab);//Function comparing if the Tor's j-th element is a Zwrotnica Dolna
    void ZwChange(int n);

    //Needed also:
        //TrasaReset() -> seting the illumination of the position of the zwrotnica and discarding all other illumination
};

#endif // MAINWIDGET_H
