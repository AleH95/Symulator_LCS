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
    void Trasa(int j, char kolor, int flg);             //Visual rapresentation of the path the train will go on
    void TrasaReverse(int j, char kolor, int flg);
    void cleanAdjacent(int n, QString stile);           //Funkcja czyscaca trase
    void cleanAdjacentReverse(int n, QString stile);    //Funkcja czyscaca trase (Prawo->Lewo)

    void clean(int n, QString stile);                   //Pomocnica funkcja nastawiajaca kolor dla odcinku (Sprawdza typ odcinku i istnienie na nim pociagu)
    int WhatTrainThere(int n);                          //Pomocnica funkcja zwracajaca indeks pociagu znajdujacego sie na danym odcinku n
    int TrasaTemp(int n);                               //Pomocnica funkcja wyznaczajaca indeks nastepnego odcineku wzgledem koordow indeksu danego odcinku
    bool inUp(int num,Stos* tab);                       //Function comparing if the Tor's j-th element is a Zwrotnica Gorna
    bool inDw(int num,Stos* tab);                       //Function comparing if the Tor's j-th element is a Zwrotnica Dolna
    int isIn(int j, int* tab);                         //Pomocnica funkcja sprawdzajaca czy wartosc j wystepuje w wartosciach tablicy tab
    bool IsInStos(int j, Stos* pile, int roz);          //Pomocnica funkcja sprawdzajaca czy wartosc j wystepuje w wartosciach stosu o danym rozmiarze
    double kmhTOms(double vel);                         //Pomocnica funkcja konwersji predkosci z km/h na m/s
    double trasaTime(int nrciuf,int nrtor);             //Pomocnica funkcja wyliczajaca czas przejazdu odcinku o indeksie przez pociag o indeksie
    double TrainTime(int nrciuf);                       //Pomocnica funkcja wyliczajaca czas zjazdu pociagu z jakiegokolwiek odcinku

    void setZwStan(int n);                              //Pomocnica funkcja obslugi nacisniecja zwrotnicy (Update wisualizacji graficznej)
    void setFromStan(int tmp, QString stan);            //Pomocnica funkcja obslugi zmiany zmiennych klasy tor

    bool IsTrainOnThere(int *tab);                      //Pomocnica funkcja sprawdzajaca czy jest jakikolwiek pociag na danej kolumnje

    template <class type> void deallocate(type *ptr, int size = 0);

private:
    Ui::Widget *ui;
    //--Poszczegolne elementy gridu
    Tor *alla[ALTEZZA*LUNGHEZZA];                                   //Array of blocks for visual display (Tor+ZwrotnicaGorna/Dolna)
    Semafor *sella[SEM], *Osella[SEMPER];                              //Semafory stacji
    Pociag *Ciuf;                                                   //Pociagi (tablica) w stacji
    int Perony[ALTEZZA], End[ALTEZZA], Start[ALTEZZA];              //Koordy peronow, i skrajnej lewej kolumny gridu

    //--Layaout do wisualizacji graficznej
    QGridLayout *GTory,*GBZwrotnice,*GBSemafory;                    //grids for window components
    QVBoxLayout *MainLayout, *VGenTrain[TRAIN/2], *VSemaf[SEM], *VOSemaf[SEMPER];                   //Main Layout that is displayed (contains the other layaouts)
    QHBoxLayout *HorizontalZwSemGen;
    QVBoxLayout *VLay[RAILLG+RAILLD];                                     //Layouty do wisualizacji QLabel kolorow zwrotnic

    //--Stosy przechowujace koordy poszczegolnych elementow
    Stos *ZwUp;                                                   //Klass Stos containing all the Coords where to find Zwrotnice on the Visualization
    Stos *ZwDw;
    Stos *Generation;                                               //Klasa containing coords of where the trains will be generated
    Stos *SemStos;                                                  //<--------
    Color *ZwKol;                                                   //Klasa przechowujaca tymczasowe labele dla torow (wisualizacja graficzna)
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
    QPushButton *Semafory[ASEMAFORY*LSEMAFORY];                     //Array of Semafors Zwrotnica
    QPushButton *OSemafory[SEMPER];
    //Tymczasowe zmienne do tymczasowych wartosci
    Tor *temptor;                                                   //Pointer for temporary value od Tor
    QList <Color *> kids;                                           //Lista przechowujaca elementy podpiete do danego elementu

    //Mapper do szybkiego polaczenia przyciskow z jego Coords
    QSignalMapper *ZsignalMapper,*SsignalMapper,*GsignalMapper,*OSmapper;     //Signal mappers for Zwrotnice and Semafory

public slots:
    void TrainGone(); //OLD FUNCTION
    int WyznaczTrasaJedzie(int n, QString string); //??

     void ZwChange(int n);          //Obsluga wcjsniecja przycisku zwrotnicy
     void SemaforChanged(int n);    //Obsluga wcisniecja przycisku semafora
     void Train(int n);             //Obsluga wcisniecja przycisku generowania pociagu
     //double secTOms(double sec);
    //Needed also:
        //TrasaReset() -> seting the illumination of the position of the zwrotnica and discarding all other illumination
};

#endif // MAINWIDGET_H
