#ifndef TRAIN_H
#define TRAIN_H

#include <QTimer>
#include "tor.h"

#define NUM_TRAINS 10
#define ROZMIARTRASY 10
#define TIMER_SPEED 1000

class NEWTrain
{
private:
    int Train_length;
    bool Train_direction;
    int actual_position;

public:
    NEWTrain();
    NEWTrain(int Train_length, bool Train_direction, int actual_position);

//wejście tablica torów do zatrzymania, prędość z jaką może poruszać się pociąg, dlugosc toru
    void train_move(QTimer *timer, Tor train_route[ROZMIARTRASY], int max_train_speed);

//Zwracanie parametrów
    int GetTposition();
    int GetTlength();

};




#endif // TRAIN_H
