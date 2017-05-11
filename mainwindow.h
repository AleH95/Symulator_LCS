#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mybutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow* wskaznik(); //metoda klasy pozwalajaca na otrzymanie wartosci wskaznika okna (polaczenia z obiektami utworzonymi w danym oknie)

private:
    Ui::MainWindow *ui;
    mybutton *buttons[ZWR+SEM];
    QPushButton *bottone1,*bottone2;

public slots:
    void nastaw(QPushButton *elia, int n=0);
    //void resetuj();

};

#endif // MAINWINDOW_H
