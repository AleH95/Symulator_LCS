#include "Mainwidget.h"
#include "ui_widget.h"
#include "thread.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //Temporary table of zwrotnice Gorne and Dolne, it'll be written to Stos
    //The table content is written as j where j = (Row*LUNGHEZZA ) + Column
    WherePerony();
    int tmpzw[UZW+DZW] = {8,11,12};
    int tmptrain[TRAIN] = {(5*LUNGHEZZA)+0,(6*LUNGHEZZA)+0,(5*LUNGHEZZA)+28,(6*LUNGHEZZA)+28};
    //__________________________________________________________________________________
    int tmpsem[SEM] = {35,69,140,174}; //<----------
    int tmprrs[RAILROADS]={44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,
                               70,71,73,75,77,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,98,100,102,104,
                               105,106,108,112,113,115,116,117,119,126,128,129,130,132,133,137,139,
                               146,147,151,156,157,158,159,164,168,169,
                               190,191,192,193,194,195,
                               224,225,226,227,228,229,230,231,
                               258,259,260,261,262,263,264,265,266,267,
                               292,293,294,295,296,297,298,299,300,301,302,303};
        /*int tmprro[RAILROADO]={43,62,120,125,145,148,149,152,153,154,155,160,
                               161,162,163,166,167,170,183,186,187,188,189,
                               196,197,198,199,202,219,220,221,222,223,232,
                               233,234,235,236,255,256,257,268,269,270,291,304};
*/
        //tory ukośne
        int tmplg[RAILLG] ={160, 162, 166, 170, 196, 198, 202, 232, 234, 236, 268, 270, 304};
        int tmppg[RAILPG] = {145, 149, 153, 155, 183, 187, 189, 219, 221, 223, 255, 257, 291};
        int tmpld[RAILLD] = {62, 120, 148, 152,154, 186, 188, 220, 222, 256};
        int tmppd[RAILPD] = {43, 125, 167, 163, 161, 197, 199, 233, 235, 269};
        //zwrotnice
        int tmplgz[RAILLGZ] ={78, 107, 134, 136, 200};
        int tmppgz[RAILPGZ] = {97, 109, 111, 138, 185};
        int tmpldz[RAILLDZ] = {74, 76, 103, 110, 114, 118, 150, 184};
        int tmppdz[RAILPDZ] = {72, 99, 101, 127, 131, 135, 165, 201};

        RailroadS = new Stos(RAILROADS,tmprrs);
        //RailroadO = new Stos(RAILROADO,tmprro);
        Raillg = new Stos(RAILLG,tmplg);
        Railpg = new Stos(RAILPG,tmppg);
        Railld = new Stos(RAILLD,tmpld);
        Railpd = new Stos(RAILPD,tmppd);

        Raillgz = new Stos(RAILLGZ,tmplgz);
        Railpgz = new Stos(RAILPGZ,tmppgz);
        Railldz = new Stos(RAILLDZ,tmpldz);
        Railpdz = new Stos(RAILPDZ,tmppdz);
        //__________________________________________________________________________________
    int traincanbe[SEM] = {(5*LUNGHEZZA)+0,(6*LUNGHEZZA)+0,(5*LUNGHEZZA)+28,(6*LUNGHEZZA)+28};
    ZwKol = new Color(2*(UZW+DZW)); //Pod labele, do zmieniania koloru toru
    ZwUpDw = new Stos(UZW+DZW,tmpzw);
    SemStos = new Stos(SEM,tmpsem); //<---------
    Generation = new Stos(TRAIN,tmptrain);
    TrainCan = new Stos(SEM,traincanbe);
    Ciuf=NULL;
    //The size of the main window
    setFixedSize(1280,600);


    ZsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    SsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    GsignalMapper = new QSignalMapper(this);

    connect(ZsignalMapper, SIGNAL(mapped(int)),this,SLOT(ZwChange(int)));
    //Zwrotnica signal mapper -> to implement slot handling zwrotnica's state change
    //Also the visualization of this change
    //connect(SsignalMapper, SIGNAL(mapped(int)),this,SLOT(); //Zwrotnica signal mapper -> to implement slot handling semafor's confirmation
    //Also the visualization of this confirmation
    connect(GsignalMapper, SIGNAL(mapped(int)),this,SLOT(Train(int)));
    connect(SsignalMapper, SIGNAL(mapped(int)),this,SLOT(SemaforChanged(int)));
    inizializza();

    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::inizializza()
{
    QLabel* tmpCol;
    int j,i,z;
    i=z=0;
    MainLayout = new QVBoxLayout(this);
    GTory = new QGridLayout();
    HorizontalZwSemGen = new QHBoxLayout();
    GBZwrotnice = new QGridLayout();
    GBSemafory = new QGridLayout();
//generowanie gridu
    for(j=0;j<LUNGHEZZA*ALTEZZA;j++)
    {
        alla[j] = new Tor(0,100,0);
        //variable storing the coordinants on the display of a button
        QString ela = "T"+QString::number(j/(LUNGHEZZA))+QString::number(i);
        alla[j]->setText(ela);
        //alla[j]->setStyleSheet("background-color: grey");
        if(inUp(j,ZwUpDw)==true)
        {
            //QPixmap pix("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/Materialy_Kuba/Zwrotnica_Gorna_Pusta.png");
            alla[j]->setType(1);
            //alla[j]->setPixmap(pix);
            //alla[j]->setMask(pix.mask());
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();
            VLay[z]->addWidget(tmpCol);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");
            VLay[z]->addWidget(tmpCol);
            z++;


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
            tmpCol = ZwKol->get();
            VLay[z]->addWidget(tmpCol);
            z++;
        }
        //<------------------

        else if(IsInStos(j,SemStos,SEM))
        {
            //GTory->addWidget(sella[j],j/(LUNGHEZZA),i);
            sella[j] = new Semafor(3);
            GTory->addWidget(sella[j],j/(LUNGHEZZA),i);
        }
        //__________________________________________________________________________________
        else if(IsInStos(j,RailroadS, RAILROADS) == true)
                {
                    alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/Symulator_LCS-master/LCS_New_v1/SourceCode/Tor_prosty.png);");
                    //GTory->addWidget(alla[j],j/(LUNGHEZZA),i);
                }
      /*  else if(IsInStos(j,RailroadO, RAILROADO) == true)
        {
            //alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/Symulator_LCS-master/LCS_New_v1/SourceCode/Tor_prosty.png);");
            alla[j]->setStyleSheet("background-color:grey");
        }*/
        else if(IsInStos(j,Raillg,RAILLG) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/lewy_gora.png);");
        }
        else if(IsInStos(j,Railpg,RAILPG) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/prawy_gora.png);");
        }
        else if(IsInStos(j,Railld,RAILLD) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/lewy_dol.png);");
        }
        else if(IsInStos(j,Railpd,RAILPD) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/prawy_dol.png);");
        }

        //--------------zwrotnice--------------------------

        else if(IsInStos(j,Raillgz,RAILLGZ) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/lewy_gora_z.png);");
        }
        else if(IsInStos(j,Railpgz,RAILPGZ) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/prawy_gora_z.png);");
        }
        else if(IsInStos(j,Railldz,RAILLDZ) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/lewy_dol_z.png);");
        }
        else if(IsInStos(j,Railpdz,RAILPDZ) == true)
        {
            alla[j]->setStyleSheet("border-image:url(E:/Qt/Moje_projekty/LCS_V4/Symulator_LCS-ver1-Prototyp-Stacji/LCS_New_v1/SourceCode/prawy_dol_z.png);");
        }
        //__________________________________________________________________________________
        //<-----------------
        GTory->addWidget(alla[j],j/(LUNGHEZZA),i);

        i++;
        if(i>=LUNGHEZZA)
        {
            i=0;
        }
    }

//nastawianie koordow zwrotnic
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
//nastawianie koordow semaforow
    for(j=0;j<ASEMAFORY*LSEMAFORY;j++)
    {
        Semafory[j] = new QPushButton();
        QString ela = "S"+QString::number(j/(LSEMAFORY))+QString::number(i);
        Semafory[j]->setObjectName(ela);
        Semafory[j]->setText(ela);
        GBSemafory->addWidget(Semafory[j],j/(LSEMAFORY),i);
        connect(Semafory[j], SIGNAL(clicked()), SsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
        int temp = TrainCan->GetThat(j);
        //Needed to pass the value in order to distingush the coords at which the TRAIN CAN BE in the visualization
        SsignalMapper->setMapping(Semafory[j], temp); //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
        i++;
        if(i>=LSEMAFORY)
        {
            i=0;
        }
    }
z=0;
VGenTrain[z] = new QVBoxLayout();
 //nastawienie koordow generowania pociagow
    for(j=0;j<TRAIN/2;j++)
    {
        GenTrain[j] = new QPushButton();
        QString ela = "G"+QString::number(j/(LZWROTNICE))+QString::number(i);
        GenTrain[j]->setObjectName(ela);
        GenTrain[j]->setText(ela);
        GenTrain[j]->setCheckable(true);
        //VGenTrain->addWidget(GenTrain[j],j/(LZWROTNICE),i);
        VGenTrain[z]->addWidget(GenTrain[j]);
        connect(GenTrain[j], SIGNAL(toggled(bool)), GsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
        int temp = Generation->GetThat(j);
        GsignalMapper->setMapping(GenTrain[j], temp); //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
        //passing j that stores the coords of where to find the zwrotnica
        i++;
        if(i>=LZWROTNICE)
        {
            i=0;
        }
    }
    HorizontalZwSemGen->addLayout(VGenTrain[z],0);
z++;
VGenTrain[z] = new QVBoxLayout();
for(j=TRAIN/2;j<TRAIN;j++)
{
    GenTrain[j] = new QPushButton();
    QString ela = "G"+QString::number(j/(LZWROTNICE))+QString::number(i);
    GenTrain[j]->setObjectName(ela);
    GenTrain[j]->setText(ela);
    GenTrain[j]->setCheckable(true);
    VGenTrain[z]->addWidget(GenTrain[j]);
    connect(GenTrain[j], SIGNAL(toggled(bool)), GsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
    int temp = Generation->GetThat(j);
    GsignalMapper->setMapping(GenTrain[j], temp); //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
    //passing j that stores the coords of where to find the zwrotnica
    i++;
    if(i>=TRAIN/2)
    {
        i=0;
    }
}

    HorizontalZwSemGen->addLayout(GBZwrotnice,2);
    GBZwrotnice->setSpacing(15);
    HorizontalZwSemGen->addLayout(GBSemafory,2);
    GBSemafory->setSpacing(15);
    HorizontalZwSemGen->addLayout(VGenTrain[z],0);
    MainLayout->setSpacing(0);
    MainLayout->addLayout(GTory);
    MainLayout->addLayout(HorizontalZwSemGen);
    }

void Widget::Train(int n)
{
    int WhatTrain = Generation->getpos(n); //na ktorym indeksie powynien znajdywac sie pociag
    //generation (tablicy koordow generacji pociagow) podpiete do gentrain (przyciski)
    temptor=alla[n];
    if(temptor->getITrain()==0)
    {
        Pociag::increment();
        Ciuf = CreateCiuf();
        temptor->setITrain();
        Ciuf[WhatTrain].setCoords(n);
        temptor->setStyleSheet("background-color: blue");
        if(WhatTrain<TRAIN/2)
        {
            Ciuf[WhatTrain].setDirection(0);
            Trasa((n+1),'w',temptor->getITrain());
        }
        else
        {
            Ciuf[WhatTrain].setDirection(1);
            TrasaReverse((n-1),'w',temptor->getITrain());
        }
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
    if(j<(ALTEZZA*LUNGHEZZA)&&(j>0))
    {
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
            if((j%LUNGHEZZA)==0)
            {
                return;
            }
            else if(isIn(j,Perony))
            {
                clean(j,tmpKol);
                return;
            }
            clean(j,tmpKol);
            j++;
            Trasa(j,kolor,flg);
        }
        else if(tmpWTL==UP)
        {
            clean(j,tmpKol);
            j=j-LUNGHEZZA;
            Trasa(j,kolor,flg);
        }
        else if(tmpWTL==DOWN)
        {
            clean(j,tmpKol);
            j=j+LUNGHEZZA;
            Trasa(j,kolor,flg);
        }
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
            if((tmp2%LUNGHEZZA)==0 || isIn(tmp2,Perony))
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
            if((tmp2%LUNGHEZZA)==0)
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
    if((n<(ALTEZZA*LUNGHEZZA))&&(n>0))
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
    if(j<(ALTEZZA*LUNGHEZZA)&&(j>0))
    {
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
            if(((j%LUNGHEZZA)==0)||isIn(j,Perony))
            {
                clean(j,tmpKol);
                return;
            }
            clean(j,tmpKol);
            j--;
            TrasaReverse(j,kolor,flg);
        }
        else if(tmpWTL==UP)
        {
            clean(j,tmpKol);
            j=j+LUNGHEZZA;
            TrasaReverse(j,kolor,flg);
        }
        else if(tmpWTL==DOWN)
        {
            clean(j,tmpKol);
            j=j-LUNGHEZZA;
            TrasaReverse(j,kolor,flg);
        }
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
            if((tmp2%LUNGHEZZA)==0)
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
            if((tmp2%LUNGHEZZA==0)||isIn(tmp2,Perony))
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
        cleanAdjacentReverse(FINISH,"background-color: grey");
        TrasaReverse((FINISH-1),'w',alla[START]->getITrain());
        temptor->setStyleSheet("background-color: blue");
    }
}

//przekazac tor c+1, gdzie c to blok na ktory wyjezdza pociag
void Widget::TrasaPociag(int n, QString kolor)
{
    WThread* aspetta = new WThread;
    QString tmpWTL = alla[n]->getWTL();
    int TimeNextTor;
    int TimeLeaveTor;
    if(n>(ALTEZZA*LUNGHEZZA)||(n<0))
    {
        return;
    }
    if(tmpWTL==STRAIGHT)
    {
        //Verifying of the variable n isn't out of range,
        // or if the straight function isn't gone a line down the display
        if((n%LUNGHEZZA)==0)
        {
            return;
        }
        if(isIn(n,Perony))
        {
            alla[n]->setITrain();
            //aspetta->terminate();
            return;
        }
        TimeNextTor = trasaTime(1,n);
        TimeLeaveTor = TrainTime(1,n);
        clean(n,kolor);
        QThread::sleep(TimeNextTor);
        aspetta->start(n,TimeLeaveTor,this);
        n++;
        TrasaPociag(n,kolor);
        //aspetta->terminate();
    }
    else if(tmpWTL==UP)
    {
        TimeNextTor = trasaTime(1,n);
        TimeLeaveTor = TrainTime(1,n);
        clean(n,kolor);
        QThread::sleep(TimeNextTor);
        aspetta->start(n,TimeLeaveTor,this);
        n=n-LUNGHEZZA;
        TrasaPociag(n,kolor);
        //aspetta->terminate();
    }
    else if(tmpWTL==DOWN)
    {
        TimeNextTor = trasaTime(1,n);
        TimeLeaveTor = TrainTime(1,n);
        clean(n,kolor);
        QThread::sleep(TimeNextTor);
        aspetta->start(n,TimeLeaveTor,this);
        n=n+LUNGHEZZA;
        TrasaPociag(n,kolor);
        //aspetta->terminate();
    }

}

double Widget::trasaTime(int nrciuf,int nrtor)
{
    double Tdlg=alla[nrtor]->getLen();
    double Pvel=Ciuf[nrciuf].getPredkosc();

    double wynik = Tdlg/Pvel;
    return wynik;
}

double Widget::TrainTime(int nrciuf,int nrtor)
{
    double Pdlg=Ciuf[nrciuf].getDlg();
    double Pvel=Ciuf[nrciuf].getPredkosc();

    double wynik = Pdlg/Pvel;
    return wynik;
}

double Widget::kmhTOms(double vel)
{
    return (vel*3.6);
}
/*
double secTOms(double sec)
{
    return (sec*1000);
}
*/
 Pociag* Widget::CreateCiuf()
 {
     Pociag* tmp = new Pociag[Pociag::getQuanto()];
     int i;
     if(Ciuf!=NULL)
     {
         for(i=0;i<Pociag::getQuanto();i++)
         {
             tmp[i].equal((Ciuf+i));
         }
     }
     return tmp;
 }

 void Widget::WherePerony()
 {
     int i;
     for(i=0;i<ALTEZZA;i++)
     {
         Perony[i]=(i*LUNGHEZZA)+PERON;
     }
 }

 bool Widget::isIn(int j, int* tab)
 {
     int i;
     for(i=0;i<ALTEZZA;i++)
     {
         if(j==tab[i])
         {
             return true;
         }
     }
     return false;
 }

 bool Widget::IsInStos(int j, Stos* pile, int roz)
 {
     int i;
     for(i=0;i<roz;i++)
     {
         if(j==pile->GetThat(i))
         {
             return true;
         }
     }
     return false;
 }

 void Widget::SemaforChanged(int n)
 {
     if(alla[n]->getITrain())
     {
         int trainnr = WhatTrainThere(n);
         if(!(Ciuf[trainnr].getDirection()))
         {
             //TrasaPociag(n+1,"background color: green");
         }
         else
         {
             qDebug("Reverse Trasa");
             //trasa
         }
     }
     else
     {
         qDebug("Nie ma pociagu");
     }
 }

 int Widget::WhatTrainThere(int n)
 {
     int i;
     for(i=0;i<Pociag::Quanto;i++)
     {
         if((Ciuf[i].getCoords())==n)
         {
             return i;
         }
     }
 }
