#ifndef TRAIN_H
#define TRAIN_H

#include <QTimer>
#include <QDebug>



#define NUM_TRAINS 10
#define ROZMIARTRASY 10
#define TIMER_SPEED 1000

class TTrain
{
private:
    int Train_length;
    bool Train_direction;
    int actual_position;

public:
    TTrain();
    TTrain(int Tlength, bool Tdirection, int Tactual_position);

//wejście tablica torów do zatrzymania, prędość z jaką może poruszać się pociąg, dlugosc toru
   // void train_move(Tor *train_route);

//Zwracanie parametrów
    int GetTposition();
    int GetTlength();

};




#endif // TRAIN_H