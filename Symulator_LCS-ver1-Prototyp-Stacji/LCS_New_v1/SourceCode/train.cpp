#include "train.h"

TTrain::TTrain()
{
     //actual_position = 10;
    // Train_length = 40;
    // Train_direction = true;
}

TTrain::TTrain(int Tlength, bool Tdirection, int Tactual_position)
{
     Train_length = Tlength;
     Train_direction = Tdirection;
     actual_position = Tactual_position;
}

/*
void train_move(Tor *train_route)
{
     //dodać dzielenie albo odejmowanie w zaleznosci od dlogosci toru
    QString tmpKol = "background-color: yellow";

        //train_speed = max_train_speed/train_route[i].getLen();
        //timer->setInterval(max_train_speed/train_route[i].getLen());
        //qDebug() << max_train_speed/train_route[i].getLen();
     train_route->setITrain();
     train_route->setStyleSheet(tmpKol);


}
*/
int TTrain::GetTposition()
{
    return actual_position;
}

int TTrain::GetTlength()
{
    return Train_length;
}
