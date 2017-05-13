#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myheader.h"

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
    QPushButton *butt_potw, *blokuj, *reset; //przyciski potwierdzenia trasy i resetowania
    QGridLayout *grid; //grid grupujaca przyciski
    mybutton **butt_tolock[ZWR]; //tablica wskaznikow przechowujaca zwrotnice o stanie != 0


private slots:
    void ChangeStan(int n); //n=jaki przycisk zostal wcisnjety
    void Lock();

};

#endif // MAINWINDOW_H
