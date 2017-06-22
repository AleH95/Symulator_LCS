#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "myheaders.h"
#include "tor.h"
#include "stos.h"
#include "color.h"
#include "pociag.h"
#include "semafor.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    friend class WThread; //<- Comment this
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void inizializza();                                 //function generating the basic layout
    void WherePerony();                                 //Funkcja generujaca koordy peronow
    void WhereEnd();                                    //Funkcja generujaca koordy prawej bocznej kolumny
    void WhereStart();                                  //Funkcja generujaca koordy lewej bocznej kolumny
    Pociag *CreateCiuf();                               //Funkcja do realokacji pamieci przypisanej zmiennej przechowujacej informacje pociago w systemie (Ciuf)

    int TrasaPociag(int n, int pnr, QString kolor);    //Funkcja obslugi wisualizacji przesuwania sie pociagu w rzeczywistym czasie
    int ReverseTrasaPociag(int n, int pnr, QString kolor);    //Funkcja obslugi wisualizacji przesuwania sie pociagu w rzeczywistym czasie
    void Trasa(int j, char kolor, int flg);             //Visual rapresentation of the path the train will go on
    void ReverseTrasa(int j, char kolor, int flg);             //Visual rapresentation of the path the train will go on
    void TrasaReverse(int j, char kolor, int flg);
    void cleanAdjacent(int n, QString stile);           //Funkcja czyscaca trase
    void ReversecleanAdjacent(int n, QString stile);           //Funkcja czyscaca trase
    void cleanAdjacentReverse(int n, QString stile);    //Funkcja czyscaca trase (Prawo->Lewo)

    void clean(int n, QString stile);                   //Pomocnica funkcja nastawiajaca kolor dla odcinku (Sprawdza typ odcinku i istnienie na nim pociagu)
    int WhatTrainThere(int n);                          //Pomocnica funkcja zwracajaca indeks pociagu znajdujacego sie na danym odcinku n
    int TrasaTemp(int n);                               //Pomocnica funkcja wyznaczajaca indeks nastepnego odcineku wzgledem koordow indeksu danego odcinku
    int ReverseTrasaTemp(int n);                               //Pomocnica funkcja wyznaczajaca indeks nastepnego odcineku wzgledem koordow indeksu danego odcinku
    double kmhTOms(double vel);                         //Pomocnica funkcja konwersji predkosci z km/h na m/s
    double trasaTime(int nrciuf,int nrtor);             //Pomocnica funkcja wyliczajaca czas przejazdu odcinku o indeksie przez pociag o indeksie
    double TrainTime(int nrciuf);                       //Pomocnica funkcja wyliczajaca czas zjazdu pociagu z jakiegokolwiek odcinku

    void setCColor(int n, int flg);                              //Pomocnica funkcja obslugi nacisniecja zwrotnicy (Update wisualizacji graficznej)
    void setFromStan(int tmp, QString stan);            //Pomocnica funkcja obslugi zmiany zmiennych klasy tor

    QList<int>* IsTrainOnThere(int *tab);                      //Pomocnica funkcja sprawdzajaca czy jest jakikolwiek pociag na danej kolumnje

    int Ukosna;
    template <class type> void deallocate(type *ptr, int size = 0);
    template <class typ> int IsIn(int num,typ *ptr, int roz);

private:
    Ui::Widget *ui;
    //--Poszczegolne elementy gridu
    Tor *alla[ALTEZZA*LUNGHEZZA];                                   //Array of blocks for visual display (Tor+ZwrotnicaGorna/Dolna)
    Semafor *sella[SEM], *Osella[SEMPER];                              //Semafory stacji
    Pociag *Ciuf[(2*7)+4];                                                   //Pociagi (tablica) w stacji (nr wejsciu,wyjsciu,perony)
    int Perony[ALTEZZA], End[ALTEZZA], Start[ALTEZZA];              //Koordy peronow, i skrajnej lewej kolumny gridu

    //--Layaout do wisualizacji graficznej
    //QGridLayout *GTory,*GBZwrotnice,*GBSemafory,*PGBZwrotnice;                    //grids for window components
    QGridLayout *GTory,*GBZwrotnice,*PGBZwrotnice;                    //grids for window components
    QVBoxLayout *LLSemafory, *PLSemafory;
    QVBoxLayout *MainLayout, *VGenTrain[TRAIN/2], *VSemaf[SEM], *VOSemaf[SEMPER];                   //Main Layout that is displayed (contains the other layaouts)
    QHBoxLayout *HorizontalZwSemGen;
    QVBoxLayout *VLay[RAILLGZ+RAILLDZ];                                     //Layouty do wisualizacji QLabel kolorow zwrotnic
    QVBoxLayout *PVLay[RAILPGZ+RAILPDZ];

    //--Stosy przechowujace koordy poszczegolnych elementow
    Stos *ZwUp;                                                   //Klass Stos containing all the Coords where to find Zwrotnice on the Visualization
    Stos *ZwDw;
    Color *ZwKol;                                                   //Klasa przechowujaca tymczasowe labele dla torow (wisualizacja graficzna)
    Stos *PZwUp;
    Stos *PZwDw;
    Color *PZwKol;
    Stos *Generation;                                               //Klasa containing coords of where the trains will be generated
    Stos *SemStos;                                                  //<--------
    Stos *TrainCan;                                                 //Koordy generowania sie pociagow
    Stos *OtherGen;
    Stos *OtherSem;

    Stos *RailroadS; //<-----
    Stos *RailroadO;
    Stos *Raillg;
    Stos *Railpg;
    Stos *Railld;
    Stos *Railpd;
    Stos *Raillgz;
    Stos *Railpgz;
    Stos *Railldz;
    Stos *Railpdz; //<----

    //--Przyciski obslugujace elementy
    QPushButton *GenTrain[TRAIN];
    QPushButton *Zwrotnice[AZWROTNICE*LZWROTNICE];                  //Array of buttons Zwrotnica
    QPushButton *PZwrotnice[AZWROTNICE*LZWROTNICE];                  //Array of buttons Zwrotnica
    QPushButton *Semafory[ASEMAFORY*LSEMAFORY];                     //Array of Semafors Zwrotnica
    QPushButton *OSemafory[SEMPER];
    //Tymczasowe zmienne do tymczasowych wartosci
    Tor *temptor;                                                   //Pointer for temporary value od Tor
    QList <Color *> kids;                                           //Lista przechowujaca elementy podpiete do danego elementu

    //Mapper do szybkiego polaczenia przyciskow z jego Coords
    QSignalMapper *ZsignalMapper,*PZsignalMapper,*SsignalMapper,*GsignalMapper,*OSmapper;     //Signal mappers for Zwrotnice and Semafory

public slots:
     void ZwChange(int n);          //Obsluga wcjsniecja przycisku zwrotnicy
     void PZwChange(int n);
     void SemaforChanged(int n);    //Obsluga wcisniecja przycisku semafora
     void Train(int n);             //Obsluga wcisniecja przycisku generowania pociagu
     void ObslugaPeronu(int n);
};

#endif // MAINWIDGET_H
