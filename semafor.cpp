#include "semafor.h"
#include "Mainwidget.h"

Semafor::Semafor(int iW):
    myLab(myLabel)
{
   SemLightColor = 0;
}



void Semafor::setLight(int num, QLabel *semafory, Color *kolory)
{
    SemLightColor = num ;
    kolory Colors = new kolory(this);


    switch(SemLightColor)
    {
        case 1:
            // ustaw czerwony

        case 2:
            // ustaw zielony
    }

}







    QList <Color*> kids = alla[j]->findChildren<Color*>(QString(), Qt::FindDirectChildrenOnly);
                if(!(kids.isEmpty()))
                {
                    kids.at(1)->setStyleSheet("background-color: red");
                    kids.clear();
                }

             /*
                alla[j]->setType(1);
                            VLay[z] = new QVBoxLayout(alla[j]);
                            VLay[z]->setSpacing(0);
                            VLay[z]->setContentsMargins(0,0,0,0);
                            tmpCol = ZwKol->get();
                            VLay[z]->addWidget(tmpCol);
                ZwKol = new Color(2*(UZW+DZW));

                */





int Semafor::getLight()
{
    return SemLightColor;
}


