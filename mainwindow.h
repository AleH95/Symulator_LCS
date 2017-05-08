#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H
