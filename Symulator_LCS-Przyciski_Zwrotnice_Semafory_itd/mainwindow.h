#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myheader.h"
#include <QTimer>
#include <QProgressBar>
#include <QSlider>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void NullLocked(); //inicializacia **tablicy do zera

private:
    Ui::MainWindow *ui;
    mybutton *butt_zwr[ZWR]; //tablica zwrotnic
    mybutton *butt_tory[TORY_WIDTH][TORY_HEIGHT]; //tablica torow
    QPushButton *butt_potw, *blokuj, *reset, *butt_exit; //przyciski potwierdzenia trasy i resetowania
    QGridLayout *grid; //grid grupujaca przyciski
    QGridLayout *grid_tory; //grid grupujaca przyciski
    mybutton **butt_tolock[ZWR]; //tablica wskaznikow przechowujaca zwrotnice o stanie != 0
    QProgressBar *speed_bar;
    QTimer *timer;
    QSlider *horizontalSlider;

public slots:
    void segment_on_time();
    void myfunction();


private slots:
    void ChangeStan(int n); //n=jaki przycisk zostal wcisnjety
    void Lock();
    void Exit_Application();

};

#endif // MAINWINDOW_H
