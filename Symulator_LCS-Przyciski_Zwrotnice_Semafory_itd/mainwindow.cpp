#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>

int timer_flag=0;
int road_flag=0;
int basic_speed =1000;
int timer_speed=basic_speed;
int x=0,y=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set size of the window
    setFixedSize(1280, 720);

    QSignalMapper *signalMapper = new QSignalMapper(this); //tworzenie signal mapper
    QWidget *widget = new QWidget(this);
    QWidget *widget_tory = new QWidget(this);
    timer = new QTimer(this);
    QProgressBar *speed_bar = new QProgressBar(this);

    QSlider *horizontalSlider = new QSlider(this);

    butt_potw = new QPushButton("Potwierdz", this);     // Create and position the button, make "this" the parent
    butt_exit = new QPushButton("Wyjdź", this);
    grid = new QGridLayout;
    grid_tory = new QGridLayout;


    for (int j = 0; j < TORY_HEIGHT; j++){

        for (int i = 0; i < TORY_WIDTH; i++)
        {
            QString text = QString::number(i)+"/"+QString::number(j); //tworzeniu tekstu dla przycisku
            butt_tory[j][i] = new mybutton(text); //nastawianie tekstu na dany przycisk
            butt_tory[j][i]->setEnabled(false); //disable buttons
            butt_tory[j][i]->setFixedSize(86,41);
            grid_tory->addWidget(butt_tory[j][i],j,i); //dodanie zwrotnicy do grid na dany wiersz i kolumne
            // connect(butt_zwr[i], SIGNAL(clicked()), signalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
            // signalMapper->setMapping(butt_zwr[i], i); //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
        }
    }
    grid_tory->setHorizontalSpacing(0);
    grid_tory->setVerticalSpacing(0);
    widget_tory->setLayout(grid_tory); //nastawianie layoutu
    widget_tory->setGeometry(0,5,1280,600); //umieszczanie layoutu w glownym oknie

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
    grid->addWidget(butt_exit,1,1);
    grid->setSpacing(15); //nastawianie minimalnej odleglosci (horizontal and vertical) dla elementow grid
    NullLocked(); //zerowanie tablicy zwrotnic to lock
    /*MainWindow to poszczegolny przypadek dla ktorego konieczne jest przypisanie grid do widget*/

/*
 * SIGNAL AND SLOTS:
 * SIGNAL variables can't be fewer than SLOTS variables!!!
 *
*/
    speed_bar->setMaximum(100);
    speed_bar->setMinimum(0);
    speed_bar->setValue(0);
    speed_bar->setFormat(" %v km/h");
    horizontalSlider->setMaximum(100);
    horizontalSlider->setMinimum(0);

    grid->addWidget(speed_bar,0,11);
    grid->addWidget(horizontalSlider,0,12);
    widget->setLayout(grid); //nastawianie layoutu
    widget->setGeometry(0,600,1280,120); //umieszczanie layoutu w glownym oknie

    connect(signalMapper, SIGNAL(mapped(int)),this,SLOT(ChangeStan(int)));
    connect(butt_potw,SIGNAL(clicked(bool)),this,SLOT(Lock()));
    connect(butt_exit,SIGNAL(clicked(bool)),this,SLOT(Exit_Application()));
    connect(horizontalSlider,SIGNAL(valueChanged(int)),speed_bar,SLOT(setValue(int)) );
    timer->start(timer_speed);
    connect(timer, SIGNAL(timeout()),this, SLOT(myfunction()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{

   //timer_speed=basic_speed-speed_bar->value();
   //timer->setInterval(timer_speed);
   // qDebug() << speed_bar->value();
    timer_speed=basic_speed-500;
    if(timer_speed<basic_speed)
    {
        timer_flag++;
        segment_on_time();

    }
}

void MainWindow::segment_on_time()
{



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
void MainWindow::Exit_Application()
{
    this->close();
}
