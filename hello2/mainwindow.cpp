#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
    int timer_flag=0;
    int flag=0;
    int road_flag=0;
    int basic_speed =1000;
    int timer_speed=basic_speed;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->progressBar,SLOT(setValue(int)) );
    timer = new QTimer(this);
    timer->start(timer_speed);
    connect(timer, SIGNAL(timeout()),this, SLOT(myfunction()));


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{

    timer_speed=basic_speed-ui->progressBar->value();
    timer->setInterval(timer_speed);
   // qDebug() << road_flag;
    if(timer_speed<basic_speed)
    {
        timer_flag++;
        segment_on_time();

    }
}

void MainWindow::segment_on_time()
{

    if(timer_flag==1)
    {
        ui->segment_7->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==2)
    {
        ui->segment_8->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==3)
    {
        ui->segment_7->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==4)
    {
        ui->segment_9->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==5)
    {
        ui->segment_8->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==6)
    {
        ui->segment_10->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==7)
    {
        ui->segment_9->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==8)
    {
        ui->segment_11->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==9)
    {
        ui->segment_10->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==10)
    {
        ui->segment_12->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==11)
    {
        ui->segment_11->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==12)
    {
        if(road_flag) timer_flag=25;
        else ui->segment_13->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==13)
    {
        ui->segment_12->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==14)
    {
        ui->segment_14->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==15)
    {
        ui->segment_13->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==16)
    {
        ui->segment_15->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==17)
    {
        ui->segment_14->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==18)
    {
        ui->segment_16->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==19)
    {
        ui->segment_15->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==20)
    {
        ui->segment_17->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==21)
    {
        ui->segment_16->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==22)
    {
        ui->segment_18->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==23)
    {
        ui->segment_17->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==24)
    {
        ui->segment_18->setStyleSheet("background-color:rgb(210,210,210)");
        timer_flag=0;
    }

   //-----------------------------------------------------------------------
    else if(timer_flag==25)
    {
        ui->segment_12->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==26)
    {
        ui->segment_30->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==27)
    {
        ui->segment_12->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==28)
    {
        ui->segment_29->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==29)
    {
        ui->segment_30->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==30)
    {
        ui->segment_28->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==31)
    {
        ui->segment_29->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==32)
    {
        ui->segment_27->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==33)
    {
        ui->segment_28->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==34)
    {
        ui->segment_26->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==35)
    {
        ui->segment_27->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==36)
    {
        ui->segment_25->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==37)
    {
        ui->segment_26->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==38)
    {
        ui->segment_24->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==39)
    {
        ui->segment_25->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==40)
    {
        ui->segment_23->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==41)
    {
        ui->segment_24->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==42)
    {
        ui->segment_22->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==43)
    {
        ui->segment_23->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==44)
    {
        ui->segment_21->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==45)
    {
        ui->segment_22->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==46)
    {
        ui->segment_20->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==47)
    {
        ui->segment_21->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==48)
    {
        ui->segment_19->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==49)
    {
        ui->segment_20->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==50)
    {
        ui->segment_31->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==51)
    {
        ui->segment_19->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==52)
    {
       ui->segment_18->setStyleSheet("background-color:rgb(255,255,125)");
    }
    else if(timer_flag==53)
    {
       ui->segment_31->setStyleSheet("background-color:rgb(210,210,210)");
    }
    else if(timer_flag==54)
    {
        ui->segment_18->setStyleSheet("background-color:rgb(210,210,210)");
        timer_flag=0;
    }


}

void MainWindow::on_pushButton_clicked()
{
    QPushButton *current_element=ui->segment_1;
    QPushButton *previous_element=ui->segment_1;

    if(flag==0)
    {
        current_element=ui->segment_1;
        previous_element=ui->segment_1;
    }
    else if(flag==1)
    {
        current_element=ui->segment_2;
        previous_element=ui->segment_1;
    }
    else if(flag==2)
    {
        current_element=ui->segment_3;
        previous_element=ui->segment_2;
    }
    else if(flag==3)
    {
        current_element=ui->segment_4;
        previous_element=ui->segment_3;
    }
    else if(flag==4)
    {
        current_element=ui->segment_5;
        previous_element=ui->segment_4;
    }
    else if(flag==5)
    {
        current_element=ui->segment_6;
        previous_element=ui->segment_5;

    }
    else if(flag==6)
    {
        current_element=ui->segment_1;
        previous_element=ui->segment_6;
        flag=0;

    }
        previous_element->setStyleSheet("background-color:rgb(210,210,210)");
        current_element->setStyleSheet("background-color:rgb(255,255,125)");


    flag++;

}

void MainWindow::on_pushButton_2_clicked()
{
    if(!road_flag)road_flag=1;
            else road_flag=0;
}
