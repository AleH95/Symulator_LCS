#include "train.h"

NEWTrain::NEWTrain()
{
    int actual_position = 10;
    int Train_length = 40;
    bool Train_direction = true;
}

NEWTrain::NEWTrain(int Train_length, bool Train_direction, int actual_position){};

void train_move(QTimer *timer, Tor train_route[ROZMIARTRASY], int max_train_speed)
{
    int train_speed=1000;
    train_speed = max_train_speed*200; //dodać dzielenie albo odejmowanie w zaleznosci od dlogosci toru
    timer->setInterval(train_speed);

    for(int i=0; i<ROZMIARTRASY; i++)
    {

    }

}

int NEWTrain::GetTposition()
{
    return actual_position;
}

int NEWTrain::GetTlength()
{
    return Train_length;
}
