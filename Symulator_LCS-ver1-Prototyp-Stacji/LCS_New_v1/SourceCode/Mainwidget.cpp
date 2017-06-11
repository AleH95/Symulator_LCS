#include "Mainwidget.h"
#include "ui_widget.h"
#include "stos.h"
#include <QString>
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //Temporary table of zwrotnice Gorne and Dolne, it'll be written to Stos
    //The table content is written as j where j = (Row*LUNGHEZZA ) + Column
    int tmpzw[UZW+DZW] = {8,11,12};
    ZwUpDw = new Stos(UZW+DZW,tmpzw);
    //The size of the main window
    setFixedSize(1280,720);
    GenTrain = new QPushButton(this);
    GenTrain->setText("START");

    ZsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    SsignalMapper = new QSignalMapper(this); //tworzenie signal mapper

    connect( GenTrain,SIGNAL(clicked(bool)),this,SLOT(Train()) );
    connect(ZsignalMapper, SIGNAL(mapped(int)),this,SLOT(ZwChange(int))); //Zwrotnica signal mapper -> to implement slot handling zwrotnica's state change
                                                              //Also the visualization of this change
    //connect(SsignalMapper, SIGNAL(mapped(int)),this,SLOT(); //Zwrotnica signal mapper -> to implement slot handling semafor's confirmation
                                                               //Also the visualization of this confirmation
    inizializza();

    ui->setupUi(this);



}

Widget::~Widget()
{
    delete ui;
}

void Widget::inizializza()
{
    int j,i=0;
    MainLayout = new QVBoxLayout(this);
    GTory = new QGridLayout();
    GBZwrotnice = new QGridLayout();
    GBSemafory = new QGridLayout();

    MainLayout->addLayout(GTory);
    MainLayout->addLayout(GBZwrotnice);
    MainLayout->addLayout(GBSemafory);


    for(j=0;j<ALTEZZA*LUNGHEZZA;j++)
    {
            alla[j] = new Tor(0,100,0);
            //variable storing the coordinants on the display of a button
            QString ela = "T"+QString::number(j/(LUNGHEZZA))+QString::number(i);
            alla[j]->setText(ela);
            alla[j]->setStyleSheet("background-color: grey");
            if(inUp(j,ZwUpDw)==true)
            {
                alla[j]->setType(1);
                //To reimplement in order to distinguish the WhereToLook of zwrotnica
                //Distinguish between the two children of the label
                alla[j]->setStyleSheet("background-color: yellow");
            }
            else if(inDw(j,ZwUpDw)==true)
            {
                alla[j]->setType(2);
                alla[j]->setStyleSheet("background-color: yellow");
            }
            GTory->addWidget(alla[j],j/(LUNGHEZZA),i);
            i++;
            if(i>=LUNGHEZZA)
            {
                i=0;
            }
    }

    for(j=0;j<AZWROTNICE*LZWROTNICE;j++)
    {
            Zwrotnice[j] = new QPushButton();
            QString ela = "Z"+QString::number(j/(LZWROTNICE))+QString::number(i);
            Zwrotnice[j]->setObjectName(ela);
            Zwrotnice[j]->setText(ela);
            Zwrotnice[j]->setCheckable(true);
            GBZwrotnice->addWidget(Zwrotnice[j],j/(LZWROTNICE),i);
            connect(Zwrotnice[j], SIGNAL(toggled(bool)), ZsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
            int temp = ZwUpDw->GetThat(j);
            ZsignalMapper->setMapping(Zwrotnice[j], temp); //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
                                                        //passing j that stores the coords of where to find the zwrotnica
            i++;
            if(i>=LZWROTNICE)
            {
                i=0;
            }
    }

    for(j=0;j<ASEMAFORY*LSEMAFORY;j++)
    {
            Semafory[j] = new QPushButton();
            QString ela = "S"+QString::number(j/(LSEMAFORY))+QString::number(i);
            Semafory[j]->setObjectName(ela);
            Semafory[j]->setText(ela);
            GBSemafory->addWidget(Semafory[j],j/(LSEMAFORY),i);
            connect(Semafory[j], SIGNAL(clicked()), SsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
            //Needed to pass the value in order to distingush the coords at which the semafor is in the visualization
            SsignalMapper->setMapping(Semafory[j], j); //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
            i++;
            if(i>=LSEMAFORY)
            {
                i=0;
            }
    }
}

void Widget::Train()
{
   // Tor *train_route = alla[10];
    temptor=alla[START];
    if(temptor->getITrain()==0)
    {
        temptor->setITrain();
        {
            temptor->setStyleSheet("background-color: blue");
        }
        Trasa((START+1),'w');


    }
    timer = new QTimer(this);
    timer->start(TIMER_SPEED);
    pociag[1] = new NEWTrain();
    int max_train_speed = 5000; //predkosc pociagu w km/h

    connect(timer, SIGNAL(timeout()),this, SLOT(pociag[1]->train_move(alla[10])));



}

void Widget::Trasa(int j, char kolor)
{
    QString tmpWTL = alla[j]->getWTL();
    QString tmpKol = "background-color: ";
    switch(kolor)
    {
    case 'r':
        tmpKol.append("red");
    case 'g':
        tmpKol.append("green");
    case 'w':
        tmpKol.append("white");
    }

    if(tmpWTL==STRAIGHT)
    {
        //Verifying of the variable j isn't out of range,
        // or if the straight function isn't gone a line down the display
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0)||(j%LUNGHEZZA)==0)
        {
            return;
        }
        alla[j]->setStyleSheet(tmpKol);
        j++;
        Trasa(j,kolor);
        //stylesheet mtor[j]
        //move right j++
        //if(j>ALTEZZA*LUNGHEZZA or j<0){ return }
        //Trasa(mtor[j],j,kolor)
    }
    else if(tmpWTL==UP)
    {
        //verify children
        //select children 1( the first is the upper)
        //change kolor of children 1
        //move up j=j-(j*LUNGHEZZA)
         //Trasa(mtor[j],j,kolor)
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0))
        {
            return;
        }
        alla[j]->setStyleSheet(tmpKol);
        //j=j-(int(j/LUNGHEZZA)*LUNGHEZZA);
        j=j-LUNGHEZZA;
        Trasa(j,kolor);
    }
    else if(tmpWTL==DOWN)
    {
         //move down j=j+(j*LUNGHEZZA)
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0))
        {
            return;
        }
        alla[j]->setStyleSheet(tmpKol);
        //j=j+(int(j/LUNGHEZZA)*LUNGHEZZA);
        j=j+LUNGHEZZA;
        Trasa(j,kolor);
    }

}

bool Widget::inUp(int num,Stos* tab)
{
    int i;
    for(i=0;i<=UZW-1;i++)
    {
        if(num==tab->GetThat(i))
        {
            tab->reset();
            return true;
        }
    }
    tab->reset();
    return false;
}

bool Widget::inDw(int num,Stos* tab)
{
    int i;
    for(i=UZW;i<UZW+DZW;i++)
    {
        if(num==tab->GetThat(i))
        {
            tab->reset();
            return true;
        }
    }
    tab->reset();
    return false;
}

void Widget::ZwChange(int n)
{
    int zwnum = ZwUpDw->getpos(n);
    bool check=Zwrotnice[zwnum]->isChecked();
    Zwrotnice[zwnum]->setDisabled(true);
    if(check==true)
    {
        Zwrotnice[zwnum]->setDown(true);
    }
    else
    {
        Zwrotnice[zwnum]->setDown(false);
    }
    QThread::msleep(500);
    alla[n]->setWTL();
    Zwrotnice[zwnum]->setDisabled(false);

    //Verify the label's children and change color
}
