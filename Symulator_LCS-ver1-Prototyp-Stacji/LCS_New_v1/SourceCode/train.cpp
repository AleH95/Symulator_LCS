#include "train.h"

NEWTrain::NEWTrain()
{
    int actual_position = 10;
    int Train_length = 40;
    bool Train_direction = true;
}

NEWTrain::NEWTrain(int Tlength, bool Tdirection, int Tactual_position)
{
    int Train_length = Tlength;
    bool Train_direction = Tdirection;
    int actual_position = Tactual_position;
};

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

int NEWTrain::GetTposition()
{
    return actual_position;
}

int NEWTrain::GetTlength()
{
    return Train_length;
}
