#include "Mainwidget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //Temporary table of zwrotnice Gorne and Dolne, it'll be written to Stos
    //The table content is written as j where j = (Row*LUNGHEZZA ) + Column
    int tmpzw[UZW+DZW] = {8,11,12};
    int tmpsem[UZW+DZW] = {2,3};
    ZwKol = new Color(2*(UZW+DZW));
    ZwUpDw = new Stos(UZW+DZW,tmpzw);
    SemStos = new Stos(UZW+DZW,tmpsem);
    //The size of the main window
    setFixedSize(1280,600);
    GenTrain = new QPushButton(this);
    TrainArrived = new QPushButton(this);
    GenTrain->setText("START");
    TrainArrived->setText("GONE");
    TrainArrived->setGeometry(GenTrain->width(),0,GenTrain->width(),GenTrain->height());

    ZsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    SsignalMapper = new QSignalMapper(this); //tworzenie signal mapper

    connect( GenTrain,SIGNAL(clicked(bool)),this,SLOT(Train()) );
    connect( TrainArrived,SIGNAL(clicked(bool)),this,SLOT(TrainGone()) );
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
    //QRect rectangle;

    QLabel* tmpCol;


    int j,i,z;
    i=z=0;
    //int h,w; //Height and Widht of a Tor
    //int x,y; //Coordinants of Tor
    MainLayout = new QVBoxLayout(this);
    GTory = new QGridLayout();
    GBZwrotnice = new QGridLayout();
    GBSemafory = new QGridLayout();

    for(j=0;j<ALTEZZA*LUNGHEZZA;j++)
    {
        alla[j] = new Tor(0,100,0);

        //variable storing the coordinants on the display of a button
        QString ela = "T"+QString::number(j/(LUNGHEZZA))+QString::number(i);
        alla[j]->setText(ela);
        //alla[j]->setStyleSheet("background-color: grey");
        if(inUp(j,ZwUpDw)==true)
        {

            alla[j]->setType(1);
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();
            VLay[z]->addWidget(tmpCol);
            //VLay[z]->setStretchFactor(tmpCol,0);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");
            VLay[z]->addWidget(tmpCol);
            //VLay[z]->setStretchFactor(tmpCol,0);
            z++;
/*
            kids = alla[j]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
            if(!(kids.isEmpty()))
            {
                kids.at(1)->setStyleSheet("background-color: red");
                kids.clear();
            }
*/


        }
        else if(inDw(j,ZwUpDw)==true)
        {
            alla[j]->setType(2);
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");
            VLay[z]->addWidget(tmpCol);
            //VLay[z]->setStretchFactor(tmpCol,0);
            tmpCol = ZwKol->get();
            VLay[z]->addWidget(tmpCol);
            //VLay[z]->setStretchFactor(tmpCol,0);
            z++;
        }
        else  if(inUp(j,SemStos)==true)
        {
            //GTory->addWidget(sella[j],j/(LUNGHEZZA),i);
            sella[j] = new Semafor(0);
            GTory->addWidget(sella[j],j/(LUNGHEZZA),i);
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

    MainLayout->setSpacing(0);
    MainLayout->addLayout(GTory);
    GBZwrotnice->setSpacing(15);
    MainLayout->addLayout(GBZwrotnice);
    GBSemafory->setSpacing(15);
    MainLayout->addLayout(GBSemafory);
/*
    h = alla[0]->height();
    w = alla[0]->width();
    x = w/LUNGHEZZA;
    y = h/ALTEZZA;
    for(j=0;j<ALTEZZA*LUNGHEZZA;j++)
    {
        rectangle = GTory->contentsRect();
        qDebug("GTORY WIDHT: %d",rectangle.width());
        qDebug("GTORY HEIGHT: %d",rectangle.height());
        qDebug("GTORY X: %d",rectangle.x());
        qDebug("GTORY Y: %d",rectangle.y());
        if(inUp(j,ZwUpDw)==true)
        {
            int nx = j/LUNGHEZZA;
            int ny = j - (LUNGHEZZA*nx);
            int widt = rectangle.width()/LUNGHEZZA;
            int heig = rectangle.height()/ALTEZZA;
            qDebug("nx: %d",nx);
            qDebug("ny: %d",ny);

            alla[j]->setType(1);
            ///----//
            tmpCol = ZwKol->get();
            tmpCol->setGeometry(nx*widt,ny*heig,widt,heig);
            tmpCol->setParent(alla[j]);

            tmpCol = ZwKol->get();
            tmpCol->setGeometry(nx*widt,(ny*heig)+heig,widt,heig);
            tmpCol->setParent(alla[j]);

            QWidget* tmpW=alla[j]->childAt(x,(int)(j/LUNGHEZZA)*y);
            tmpW->setStyleSheet("background-color: yellow");
            tmpW=alla[j]->childAt(0,0);
            tmpW->setStyleSheet("background-color: red");
            //----//
            //--//
            kids = alla[j]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
            if(!kids.empty)
            {
                kids.at(1)->setStyleSheet("background-color: yellow");
                kids.clear();
            }
            //To reimplement in order to distinguish the WhereToLook of zwrotnica
            //Distinguish between the two children of the label
            //--//
        }
        else if(inDw(j,ZwUpDw)==true)
        {
            alla[j]->setType(2);
            //--//h = alla[j]->width();
            w = alla[j]->height();

            tmpCol = ZwKol->get();
            tmpCol->setGeometry(0,0,w,h/2);
            tmpCol->setParent(alla[j]);

            tmpCol = ZwKol->get();
            tmpCol->setGeometry(0,h/2,w,h/2);
            tmpCol->setParent(alla[j]);

            QWidget* tmpW=alla[j]->childAt(0,0);
            //tmpW->setStyleSheet("background-color: yellow");//---//
        }
    }
    */
}

void Widget::Train()
{
    temptor=alla[START];
    if(temptor->getITrain()==0)
    {
        temptor->setITrain();

            temptor->setStyleSheet("background-color: blue");

        Trasa((START+1),'w',temptor->getITrain());
    }
    //----Temporary code to verify the functionality of the reverse functions
    //temptor->setITrain();
    //temptor=alla[FINISH];
    //temptor->setITrain();
    //temptor->setStyleSheet("background-color: blue");
}

void Widget::Trasa(int j, char kolor, int flg)
{
    QString tmpWTL = alla[j]->getWTL();
    QString tmpKol = "background-color: ";
    if(flg==0)
    {
        if((alla[j]->getType())!=0)
        {
            kolor='y';
        }
        else
        {
            kolor='e';
        }
    }

    if(kolor=='r'){ tmpKol.append("red"); }
    else if(kolor=='g'){ tmpKol.append("green"); }
    else if(kolor=='e'){ tmpKol.append("grey"); }
    else if(kolor=='y'){ tmpKol.append("yellow"); }
    else if(kolor=='w'){ tmpKol.append("white"); }

    if(tmpWTL==STRAIGHT)
    {
        //Verifying of the variable j isn't out of range,
        // or if the straight function isn't gone a line down the display
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0)||(j%LUNGHEZZA)==0)
        {
            //alla[j-1]->setITrain();
            return;
        }
        clean(j,tmpKol);
        j++;
        Trasa(j,kolor,flg);
    }
    else if(tmpWTL==UP)
    {
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0))
        {
            return;
        }
        clean(j,tmpKol);
        j=j-LUNGHEZZA;
        Trasa(j,kolor,flg);
    }
    else if(tmpWTL==DOWN)
    {
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0))
        {
            return;
        }
        clean(j,tmpKol);
        j=j+LUNGHEZZA;
        Trasa(j,kolor,flg);
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
    setZwStan(n);
    cleanAdjacent(n,"background-color: grey");
    //Starts where there is a train -> needed a class with a static member that return number of trains in the system
    Trasa(START+1,'w',alla[START]->getITrain());
    Zwrotnice[zwnum]->setDisabled(false);

    //Verify the label's children and change color
}

void Widget::cleanAdjacent(int n, QString stile)
{
    int tmp1, tmp2;
    QString stilo = "background-color: yellow";
    for(tmp1=n;tmp1>0;tmp1=tmp1-LUNGHEZZA)
    {
        tmp2=tmp1;
        while(true)
        {
                if((alla[tmp2]->getType())!=0)
                {
                    clean(tmp2,stilo);
                }
                else
                {
                   clean(tmp2,stile);
                }
            tmp2++;
            if(tmp2%LUNGHEZZA==0)
            {
                break;
            }
        }
    }
    for(tmp1=n+LUNGHEZZA;tmp1<ALTEZZA*LUNGHEZZA;tmp1=tmp1+LUNGHEZZA)
    {
        tmp2=tmp1;
        while(true)
        {
            clean(tmp2,stile);
            tmp2++;
            if(tmp2%LUNGHEZZA==0)
            {
                break;
            }
        }
    }
}

void Widget::clean(int n, QString stile)
{
    int x,y,z;
    x=y=z=0;
    if(n<(ALTEZZA*LUNGHEZZA)&&(n>0))
    {
        kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            if(alla[n]->getWTL()==UP)
            {
                x=0;
                y=1;
            }
            else if(alla[n]->getWTL()==DOWN)
            {
                x=1;
                y=0;
            }
            else if(alla[n]->getType()!=1)
            {
                x=0;
                y=1;
                //What when blok is straight(?)
                //from where trasa is coming: up or down??
            }
            else if(alla[n]->getType()!=2)
            {
                x=1;
                y=0;
            }
            else
            {
                qDebug("idk");
            }
            kids.at(x)->setStyleSheet(stile);
            kids.at(y)->setStyleSheet("background-color: grey");
            kids.clear();
        }
        else if(alla[n]->getITrain()==1)
        {
            alla[n]->setStyleSheet("background-color: blue");
        }
        else
        {
            alla[n]->setStyleSheet(stile);
        }
    }
}

void Widget::setZwStan(int n)
{
    int tmp;
    alla[n]->setWTL();
    if(alla[n]->getWTL()==UP)
    {
        kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            kids.at(0)->setStyleSheet("background-color: yellow");
            kids.at(1)->setStyleSheet("background-color: grey");
            kids.clear();
        }
        tmp=n-LUNGHEZZA;
        setFromStan(tmp,DOWN);
    }
    else if(alla[n]->getWTL()==DOWN)
    {
        kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            kids.at(0)->setStyleSheet("background-color: grey");
            kids.at(1)->setStyleSheet("background-color: yellow");
            kids.clear();
        }
        tmp=n+LUNGHEZZA;
        setFromStan(tmp,UP);
    }
    else
    {
        if(alla[n]->getType()==1)
        {
            kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
            if(!(kids.isEmpty()))
            {
                kids.at(1)->setStyleSheet("background-color: yellow");
                kids.at(0)->setStyleSheet("background-color: grey");
                kids.clear();
            }
        }
        if(alla[n]->getType()==2)
        {
            kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
            if(!(kids.isEmpty()))
            {
                kids.at(0)->setStyleSheet("background-color: yellow");
                kids.at(1)->setStyleSheet("background-color: grey");
                kids.clear();
            }
        }
        tmp=n-1;
        setFromStan(tmp,STRAIGHT);
        tmp=n+1;
        setFromStan(tmp,STRAIGHT);
    }
}

void Widget::setFromStan(int tmp, QString stan)
{
    if(tmp<(ALTEZZA*LUNGHEZZA)&&(tmp>0))
    {
        alla[tmp]->setFrom(stan);
    }
}

void Widget::TrasaReverse(int j, char kolor, int flg)
{
    QString tmpWTL = alla[j]->getWTL();
    QString tmpKol = "background-color: ";
    if(flg==0)
    {
        if((alla[j]->getType())!=0)
        {
            kolor='y';
        }
        else
        {
            kolor='e';
        }
    }
    if(kolor=='r'){ tmpKol.append("red"); }
    else if(kolor=='g'){ tmpKol.append("green"); }
    else if(kolor=='e'){ tmpKol.append("grey"); }
    else if(kolor=='y'){ tmpKol.append("yellow"); }
    else if(kolor=='w'){ tmpKol.append("white"); }

    if(tmpWTL==STRAIGHT)
    {
        //Verifying of the variable j isn't out of range,
        // or if the straight function isn't gone a line down the display
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0)||(j%LUNGHEZZA)==0)
        {
            alla[j]->setITrain();
            clean(j,"background-color: grey");
            return;
        }
        clean(j,tmpKol);
        j--;
        TrasaReverse(j,kolor,flg);
    }
    else if(tmpWTL==UP)
    {
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0))
        {
            return;
        }
        clean(j,tmpKol);
        j=j+LUNGHEZZA;
        TrasaReverse(j,kolor,flg);
    }
    else if(tmpWTL==DOWN)
    {
        if(j>(ALTEZZA*LUNGHEZZA)||(j<0))
        {
            return;
        }
        clean(j,tmpKol);
        j=j-LUNGHEZZA;
        TrasaReverse(j,kolor,flg);
    }

}

void Widget::cleanAdjacentReverse(int n, QString stile)
{
    int tmp1, tmp2;
    QString stilo = "background-color: yellow";
    for(tmp1=n;tmp1>0;tmp1=tmp1-LUNGHEZZA)
    {
        tmp2=tmp1+1;
        while(true)
        {
            tmp2--;
            if((alla[tmp2]->getType())!=0)
            {
                clean(tmp2,stilo);
            }
            else
            {
                clean(tmp2,stile);
            }
            if(tmp2%LUNGHEZZA==0)
            {
                break;
            }
        }
    }
    for(tmp1=n+LUNGHEZZA;tmp1<ALTEZZA*LUNGHEZZA;tmp1=tmp1+LUNGHEZZA)
    {
        tmp2=tmp1+1;
        while(true)
        {
            tmp2--;
            if((alla[tmp2]->getType())!=0)
            {
                clean(tmp2,stilo);
            }
            else
            {
                clean(tmp2,stile);
            }
            if(tmp2%LUNGHEZZA==0)
            {
                break;
            }
        }
    }
}

void Widget::TrainGone()
{
    temptor=alla[FINISH];
    if(temptor->getITrain()==1)
    {
        //temptor->setITrain();
        /*
        {
            temptor->setStyleSheet("background-color: blue");
        }
        */
        //alla[START]->setITrain();
        cleanAdjacentReverse(FINISH,"background-color: grey");
        TrasaReverse((FINISH-1),'w',alla[START]->getITrain());
        temptor->setStyleSheet("background-color: blue");
    }
}
