#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set size of the window
    setFixedSize(1280, 720);

    QSignalMapper *signalMapper = new QSignalMapper(this); //tworzenie signal mapper
    QWidget *widget = new QWidget(this);
    butt_potw = new QPushButton("Potwierdz", this);     // Create and position the button, make "this" the parent
    grid = new QGridLayout;

    for (int i = 0; i < ZWR; i++)
    {
        QString text = QString::number(i); //tworzeniu tekstu dla przycisku
        butt_zwr[i] = new mybutton(text); //nastawianie liczby dla tekstu na dany przycisk
        butt_zwr[i]->reset(); //inicjalizowanie parametrow zwrotnic
        grid->addWidget(butt_zwr[i],0,i); //dodanie zwrotnicy do grid na dany wiersz i kolumne
        connect(butt_zwr[i], SIGNAL(clicked()), signalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
        signalMapper->setMapping(butt_zwr[i], i); //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
    }
    butt_potw->setGeometry(100,100,200,50);
    grid->addWidget(butt_potw,1,0); //dodanie przycisku potwierdzenia do grid
    grid->setSpacing(15); //nastawianie minimalnej odleglosci (horizontal and vertical) dla elementow grid
    NullLocked(); //zerowanie tablicy zwrotnic to lock
    /*MainWindow to poszczegolny przypadek dla ktorego konieczne jest przypisanie grid do widget*/
    widget->setLayout(grid); //nastawianie layoutu
    widget->setGeometry(0,350,720,300); //umieszczanie layoutu w glownym oknie

/*
 * SIGNAL AND SLOTS:
 * SIGNAL variables can't be fewer than SLOTS variables!!!
 *
*/
    connect(signalMapper, SIGNAL(mapped(int)),this,SLOT(ChangeStan(int)));
    connect(butt_potw,SIGNAL(clicked(bool)),this,SLOT(Lock()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ChangeStan(int n)
{
    butt_zwr[n]->setstan();
    if(butt_zwr[n]->getstan()!=0)
    {
        butt_tolock[n]=&butt_zwr[n];
    }
}

void MainWindow::NullLocked()
{
    int i;
    for(i=0;i<ZWR;i++)
    {
        butt_tolock[i]=0;
    }
}

void MainWindow::Lock()
{
    int i;
    for(i=0;i<ZWR;i++)
    {
        if(butt_tolock[i]!=0)
        {
            (*butt_tolock[i])->setlock();
            (*butt_tolock[i])->setDisabled(true);
        }
    }
}
