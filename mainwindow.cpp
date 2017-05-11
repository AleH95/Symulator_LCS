#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myheader.h"


/* dan
void blokuj(MainWindow* elia); //funkcja ktora powinna nastawic stan blokuj dlaych przyciskow
void resetuj(MainWindow* elia); //funkcja ktora powinna odblokowac stan blokowany przyciskow
*/
/*void blokuj(MainWindow* elia)
{
    Ui::MainWindow *ala = elia->wskaznik(); //wyglada na to ze dostajemy sie do wskaznika
    //ala->progressBar->reset();
    ala->progressBar->setValue(88); //lecz wywolanie akcji na progress bar nic nie powoduje
}*/
/*
void resetuj(MainWindow* elia)
{
    //MainWindow::ui->progressBar->reset();
    ;
}
*/
Ui::MainWindow* MainWindow::wskaznik()
{
    return this->ui;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(WLUNG,WALT);
    ui->setupUi(this);
    /*
    QPushButton *lvl = new QPushButton(this);
    lvl->setText("ala");
    lvl->setToolTip("elo");
    lvl->setGeometry(100,100,100,50);
    */
    int i,lspacing,wspacing;
    //mybutton *buttons[ZWR+SEM];
    lspacing=wspacing=15;

    //QPushButton *bottone1,*bottone2;
    bottone1 = new QPushButton("Potwierdz",this);
    bottone2 = new QPushButton("Resetuj",this);
    bottone1->setGeometry(150,150,100,100);
    bottone2->setGeometry(350,150,100,100);
    //bottone1->setDefault(true); //wcisniecie enter w okienku powoduje ze wciska sie ten przycisk
    //bottone2->setAutoDefault(false); //??
     ui->progressBar->setValue(89);

     QObject::connect(ui->Premimi,SIGNAL(QPushButton::pressed()),SLOT(MainWindow::nastaw(QPushButton*,int)));
    //connect(bottone2,SIGNAL(released()),resetuj(this));


    for(i=0;i<(ZWR+SEM);i++)
    {
        buttons[i]=new mybutton(this);
        buttons[i]->setGeometry(lspacing,wspacing,LUNGHEZZA,ALTEZZA);
        buttons[i]->setToolTip("Odcinek 1-2");
        buttons[i]->setText("Zwrotnica1");
        //buttons[i].setstan(0);
        lspacing=lspacing+LUNGHEZZA + 15;
        if(lspacing>WLUNG)
        {
            lspacing=0;
            wspacing=wspacing+ALTEZZA+15;
        }
        if(wspacing>WALT)
        {
            wspacing=0;
        }

        mybutton *elia;
        elia = buttons[i];
        elia->setText("ala");
        elia->setstan(5);
        //elia->setEnabled(false);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nastaw(QPushButton *elia, int n)
{
    QPushButton *butt = new QPushButton(this);
    butt->setGeometry(200,200,50,50);
    elia->setText("ela");
    //elia->setstan(n);
    elia->setEnabled(false);
}
