#include "Mainwidget.h"
#include "ui_widget.h"
#include "thread.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //Temporary table of zwrotnice Gorne and Dolne, it'll be written to Stos
    //The table content is written as j where j = (Row*LUNGHEZZA ) + Column
   // int tmpzw[UZW+DZW] = {8,11,12};
    int tmptrain[TRAIN] = {71,106,104,139}; //34 140 69 174
    int tmpsemper[SEMPER] = {9,26,8,27,121,124,330,335,329,336,328,337,327,338};
    int tmpperony[SEMPER] = {51,51,86,86,156,156,191,191,226,226,261,261,296,296};
    //int tmpsem[SEM] = {2,3,45,89}; //<----------
    //int traincanbe[SEM] = {(5*LUNGHEZZA)+0,(6*LUNGHEZZA)+0,(5*LUNGHEZZA)+28,(6*LUNGHEZZA)+28};

    //__________________________________________________________________________________
        int tmpsem[SEM] = {35,140,69,174}; //Semafore wejsciowe-wyjsciowe
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
            //___________________________________________________________________

    ZwKol = new Color(2*(RAILLGZ+RAILLDZ)); //Pod labele, do zmieniania koloru toru
    ZwUp = new Stos(RAILLGZ,tmplgz);
    ZwDw = new Stos(RAILLDZ,tmpldz);
    SemStos = new Stos(SEM,tmpsem);         //Koordy semaforow wejsciowych - wyjsciowych
    OtherSem = new Stos(SEMPER,tmpsemper);  //Koordy semaforow peronu
    Generation = new Stos(SEM,tmptrain);    //Do ktorego bloku jest podpiety semafor
    OtherGen = new Stos(SEMPER,tmpperony);  //Na ktorym peronie znajduje sie pociagu wzgledem semaforu peronu
    TrainCan = new Stos(SEM,tmptrain);      //Gdzie sie maja pojawyc pociagi wejscie - wyjscie
    //Ciuf=NULL;
    //The size of the main window
    setFixedSize(1280,600);


    ZsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    SsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    GsignalMapper = new QSignalMapper(this);
    OSmapper = new QSignalMapper(this);

    connect(ZsignalMapper, SIGNAL(mapped(int)),this,SLOT(ZwChange(int)));
    connect(SsignalMapper, SIGNAL(mapped(int)),this,SLOT(SemaforChanged(int)));
    connect(GsignalMapper, SIGNAL(mapped(int)),this,SLOT(Train(int)));
    connect(OSmapper, SIGNAL(mapped(int)),this,SLOT(ObslugaPeronu(int)));

    for(int z=0; z<(7+4);z++)
    {
        Ciuf[z]=new Pociag();
    }

    WherePerony();
    WhereEnd();
    WhereStart();

    inizializza();

    ui->setupUi(this);
}

template <class type> void Widget::deallocate(type *ptr, int size)
{
    if(ptr!=NULL)
    {
        if(size!=0)
        {
            delete [] ptr;
        }
        else
        {
            delete ptr;
        }
        ptr = NULL;
    }
}

template <class typ> int Widget::IsIn(int num,typ *ptr, int roz)
//int Widget::IsIn(int num, int *ptr, int roz)
{
    int i;
    if(ptr!=NULL)
    {
        for(i=0;i<roz;i++)
        {
            if(num==ptr[i])
            {
                //qDebug("Num = %d , Ptr = %d , i = %d",num,ptr[i],i);
                return i;
            }
        }
    }
    return -1;
}

Widget::~Widget()
{
    /*
    deallocate(ZwKol,2*(UZW+DZW));
    deallocate(ZwUpDw,UZW+DZW);
    deallocate(SemStos,SEM);
    deallocate(Generation,TRAIN);
    deallocate(TrainCan,SEM);
    deallocate(ZsignalMapper);
    deallocate(SsignalMapper);
    deallocate(GsignalMapper);
    deallocate(MainLayout);
    deallocate(GTory);
    deallocate(HorizontalZwSemGen);
    deallocate(GBZwrotnice);
    deallocate(GBSemafory);
    */
    delete ui;
}

void Widget::inizializza()
{
    QLabel* tmpCol;
    int j,i,z,p;
    int s=0;
    MainLayout = new QVBoxLayout(this);
    GTory = new QGridLayout();
    GBZwrotnice = new QGridLayout();
    GBSemafory = new QGridLayout();
    HorizontalZwSemGen = new QHBoxLayout();
    i=z=p=0;

    //--Generowanie gridu torow
    for(j=0;j<LUNGHEZZA*ALTEZZA;j++)
    {
        alla[j] = new Tor(0,100,0);
        QString ela = "T"+QString::number(j/(LUNGHEZZA))+QString::number(i);
        //alla[j]->setText(ela);
        alla[j]->setStyleSheet("background-color: grey");
        int tempocasa=IsIn(j,Raillgz->getTab(),RAILLGZ);
        if(tempocasa!=-1)
        {
            alla[j]->setType(1);                                //Typ zwrotnica gorna
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();                              //Pobieranie Qlabel z klasy stos
            VLay[z]->addWidget(tmpCol);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");  //Domyslne nastawienia STRAIGHT wiec koniecznosc wyswietlania dolnej czesci
            VLay[z]->addWidget(tmpCol);
            z++;
        }
        else if(IsIn(j,Railldz->getTab(),RAILLDZ)!=-1)
        {
            alla[j]->setType(2);                                //Typ zwrotnica dolna
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");  //Domyslne nastawienia STRAIGHT wiec koniecznosc wyswietlania gornej czesci
            VLay[z]->addWidget(tmpCol);
            tmpCol = ZwKol->get();
            VLay[z]->addWidget(tmpCol);
            z++;
        }
        //else if typ3 , else if typ 4
        //<------------------

        else if(IsIn(j,SemStos->getTab(),SEM)!=-1)
        {
            VSemaf[s]=new QVBoxLayout(alla[j]);
            sella[s] = new Semafor(0);
            VSemaf[s]->addWidget(sella[s]);
            //sella[s]->setColor(3);
            //sella[s]->setParent(alla[j]);
            s++;
            //GTory->addWidget(sella[j],j/(LUNGHEZZA),i);
        }

        else if(IsIn(j,OtherSem->getTab(),SEMPER)!=-1)
        {
            VOSemaf[p]=new QVBoxLayout(alla[j]);
            Osella[p] = new Semafor(0);
            VOSemaf[p]->addWidget(Osella[p]);
            p++;
            //GTory->addWidget(sella[j],j/(LUNGHEZZA),i);
        }

        //__________________________________________________________________________________
                else if(IsIn(j,RailroadS->getTab(), RAILROADS) !=-1)
                        {
                            alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/Tor_prosty.png);");
                            //GTory->addWidget(alla[j],j/(LUNGHEZZA),i);
                        }
              /*  else if(IsInStos(j,RailroadO, RAILROADO) == true)
                {
                    //alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/Tor_prosty.png);");
                    alla[j]->setStyleSheet("background-color:grey");
                }*/
                else if(IsIn(j,Raillg->getTab(),RAILLG) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_gora.png);");
                }
                else if(IsIn(j,Railpg->getTab(),RAILPG) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_gora.png);");
                }
                else if(IsIn(j,Railld->getTab(),RAILLD) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_dol.png);");
                }
                else if(IsIn(j,Railpd->getTab(),RAILPD) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_dol.png);");
                }

                //--------------zwrotnice--------------------------

                else if(IsIn(j,Raillgz->getTab(),RAILLGZ) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_gora_z.png);");
                }
                else if(IsIn(j,Railpgz->getTab(),RAILPGZ) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_gora_z.png);");
                }
                else if(IsIn(j,Railldz->getTab(),RAILLDZ) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_dol_z.png);");
                }
                else if(IsIn(j,Railpdz->getTab(),RAILPDZ) !=-1)
                {
                    alla[j]->setStyleSheet("border-image:url(B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_dol_z.png);");
                }
                //_______________________

        //<-----------------
        GTory->addWidget(alla[j],j/(LUNGHEZZA),i);

        i++;                                                    //Zmienna iteracyjna konieczna dla Layaout typu grid
        if(i>=LUNGHEZZA)
        {
            i=0;
        }
    }

    //--Nastawianie koordow zwrotnic (Gornych Lewych)
    i=0;
    for(j=0;j<RAILLGZ;j++)
    {
        Zwrotnice[j] = new QPushButton();
        QString ela = "Z"+QString::number(j/(LZWROTNICE))+QString::number(i);
        Zwrotnice[j]->setObjectName(ela);
        Zwrotnice[j]->setText(ela);
        Zwrotnice[j]->setCheckable(true);
        GBZwrotnice->addWidget(Zwrotnice[j],j/(LZWROTNICE),i);
        connect(Zwrotnice[j], SIGNAL(toggled(bool)), ZsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
        int temp = ZwUp->GetThat(j);
        kids = alla[temp]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            kids.at(0)->setText(ela);
            kids.at(0)->setAlignment(Qt::AlignTop);
            kids.clear();
        }
        ZsignalMapper->setMapping(Zwrotnice[j], temp);                            //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (coordy torow znajdywania sie elementu)
        i++;
        if(i>=LZWROTNICE)
        {
            i=0;
        }
    }
        for(j=RAILLGZ;j<RAILLDZ+RAILLGZ;j++)
        {
            Zwrotnice[j] = new QPushButton();
            QString ela = "Z"+QString::number(j/(LZWROTNICE))+QString::number(i);
            Zwrotnice[j]->setObjectName(ela);
            Zwrotnice[j]->setText(ela);
            Zwrotnice[j]->setCheckable(true);
            GBZwrotnice->addWidget(Zwrotnice[j],j/(LZWROTNICE),i);
            connect(Zwrotnice[j], SIGNAL(toggled(bool)), ZsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
            //int m = j - RAILLGZ;
            int temp = ZwDw->GetThat(j-RAILLGZ);
            kids = alla[temp]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
            if(!(kids.isEmpty()))
            {
                kids.at(1)->setText(ela);
                kids.at(1)->setAlignment(Qt::AlignBottom);
                kids.clear();
            }
            ZsignalMapper->setMapping(Zwrotnice[j], temp);                            //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (coordy torow znajdywania sie elementu)
            i++;
            if(i>=LZWROTNICE)
            {
                i=0;
            }
        }

    //--Nastawianie koordow semaforow wejscia-wyjscia
    i=0;
    for(j=0;j<SEM;j++)
    {
        Semafory[j] = new QPushButton();
        QString ela = "WW"+QString::number(j/(LSEMAFORY))+QString::number(i);
        //Semafory[j]->setObjectName(ela);
        Semafory[j]->setText(ela);
        GBSemafory->addWidget(Semafory[j],j/(LSEMAFORY),i);
        connect(Semafory[j], SIGNAL(clicked()), SsignalMapper, SLOT(map()));      //polaczenie signalu zwrotnicy do signalmapper
        int temp = TrainCan->GetThat(j);
        //sella[temp]->setText(ela);                                                 //Przypisywanie do toru o koordach, nazwe elementu
        //sella[temp]->setAlignment(Qt::AlignBottom);
        SsignalMapper->setMapping(Semafory[j], temp);                             //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (koordy na ktorych moze sie znajdowac pociag)
        i++;
        if(i>=LSEMAFORY)
        {
            i=0;
        }
    }

    int k = j;
    //--Nastawianie koordow semaforow
    for(j=0;j<SEMPER;j++)
    {
        OSemafory[j] = new QPushButton();
        QString ela = "S"+QString::number(j/(LSEMAFORY))+QString::number(i);
        //OSemafory[j]->setObjectName(ela);
        OSemafory[j]->setText(ela);
        GBSemafory->addWidget(OSemafory[j],(j+k)/(LSEMAFORY),i);
        connect(OSemafory[j], SIGNAL(clicked()), OSmapper, SLOT(map()));      //polaczenie signalu zwrotnicy do signalmapper
        int temp = OtherGen->GetThat(j);
        //sella[temp]->setText(ela);                                                 //Przypisywanie do toru o koordach, nazwe elementu
        //sella[temp]->setAlignment(Qt::AlignBottom);
        OSmapper->setMapping(OSemafory[j], temp);                             //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (koordy na ktorych moze sie znajdowac pociag)
        i++;
        if(i>=LSEMAFORY)
        {
            i=0;
        }
    }

    //--Nastawienie koordow generowania pociagow (Lewa)
    i=0;
    z=0;
    VGenTrain[z] = new QVBoxLayout();                                             //Layout dla przyciskow generowaniu ruchu (Lewa strona)
    for(j=0;j<TRAIN/2;j++)
    {
        GenTrain[j] = new QPushButton();
        QString ela = "G"+QString::number(j/(LZWROTNICE))+QString::number(i);
        GenTrain[j]->setObjectName(ela);
        GenTrain[j]->setText(ela);
        GenTrain[j]->setCheckable(true);
        //VGenTrain->addWidget(GenTrain[j],j/(LZWROTNICE),i);
        VGenTrain[z]->addWidget(GenTrain[j]);
        connect(GenTrain[j], SIGNAL(toggled(bool)), GsignalMapper, SLOT(map()));    //polaczenie signalu zwrotnicy do signalmapper
        int temp = TrainCan->GetThat(j);
        alla[temp]->setText(ela);                                                 //Przypisywanie do toru o koordach, nazwe elementu
        alla[temp]->setAlignment(Qt::AlignTop);
        GsignalMapper->setMapping(GenTrain[j], temp);                               //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (kkordy generowania pociagu)
        i++;
        if(i>=TRAIN/2)
        {
            i=0;
        }
    }
    HorizontalZwSemGen->addLayout(VGenTrain[z],0);

    //--Nastawienie koordow generowania pociagow (Prawa)
    i=0;
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
        connect(GenTrain[j], SIGNAL(toggled(bool)), GsignalMapper, SLOT(map()));    //polaczenie signalu zwrotnicy do signalmapper
        int temp = TrainCan->GetThat(j);
        alla[temp]->setText(ela);                                                   //Przypisywanie do toru o koordach, nazwe elementu
        alla[temp]->setAlignment(Qt::AlignTop);
        GsignalMapper->setMapping(GenTrain[j], temp);                               //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk
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
    //deallocate(tmpCol);
}

void Widget::WherePerony()
{
    int i;
    for(i=0;i<ALTEZZA;i++)
    {
        Perony[i]=(i*LUNGHEZZA)+PERON;
    }
}

void Widget::WhereEnd()
{
    int i;
    for(i=0;i<ALTEZZA;i++)
    {
        End[i]=(i*LUNGHEZZA)+LUNGHEZZA-1;
    }
}

void Widget::WhereStart()
{
    int i;
    for(i=0;i<ALTEZZA;i++)
    {
        Start[i]=(i*LUNGHEZZA)+1;
    }
}

Pociag* Widget::CreateCiuf()
{
    Pociag* tmp = new Pociag[Pociag::getQuanto()+1];
    int i;
    if(Ciuf!=NULL)
    {
        for(i=0;i<Pociag::getQuanto();i++)
        {
            tmp[i].equal(Ciuf[i]);
        }
    }
    delete [] Ciuf;
    return tmp;
}

int Widget::TrasaPociag(int n, int pnr, QString kolor)
{

    int TimeNextTor = 0;
    int TimeLeaveTor = 0;
    if(n<(ALTEZZA*LUNGHEZZA)&&(n>0))
    {
        //QString tmpWTL = alla[n]->getWTL();
        alla[n]->setITrain();
        clean(n,kolor);
        QCoreApplication::processEvents();
        int rap = Ciuf[pnr]->getDlg() / alla[n]->getLen();
        int y = n; //for if statement
        int x = TrasaTemp(n); //next step in order to know what to light
        if(x==-1||x==-2)
        {
            return 1;
        }
        /*
        else if(x==-2)
        {
            TimeLeaveTor = TrainTime(pnr);
            QThread::msleep(TimeLeaveTor*1000);
            clean(x,kolor);
            QCoreApplication::processEvents();
            return;
        }
        */
        alla[x]->setITrain();
        while(true)
        {
            if(rap>0)
            {
                for(int z=0;z<rap;z++)
                {
                    clean(x,kolor);
                    QCoreApplication::processEvents();
                    TimeNextTor = trasaTime(pnr,x);
                    QThread::msleep(TimeNextTor*1000);
                    x=TrasaTemp(x);
                }
                while(true)
                {
                    clean(x,kolor);
                    QCoreApplication::processEvents();
                    TimeLeaveTor = TrainTime(pnr);
                    QThread::msleep(TimeLeaveTor*1000);
                    //no train on y
                    alla[y]->setITrain();
                    clean(y,kolor);
                    QCoreApplication::processEvents();
                    TimeNextTor = trasaTime(pnr,x) - TimeLeaveTor;
                    QThread::msleep(TimeNextTor*1000);
                    y=TrasaTemp(y);
                    x=TrasaTemp(x);
                    if(x==-1)
                    {
                        while(y!=-1)
                        {
                            TimeLeaveTor = TrainTime(pnr);
                            QThread::msleep(TimeLeaveTor*1000);
                            //no train on y
                            alla[y]->setITrain();
                            clean(y,kolor);
                            QCoreApplication::processEvents();
                            TimeNextTor = trasaTime(pnr,y) - TimeLeaveTor;
                            QThread::msleep(TimeNextTor*1000);
                            y=TrasaTemp(y);
                        }
                        return 1;
                    }
                }
            }
            else
            {

                clean(x,kolor);
                QCoreApplication::processEvents();
                TimeNextTor = trasaTime(pnr,x);
                QThread::msleep(TimeNextTor*1000);
                Ciuf[pnr]->setCoords(y);
                y = TrasaTemp(x);
                if(y==-1 || y==-2)
                {
                    return 1;
                }
                /*
                else if(y==-2)
                {
                    TimeLeaveTor = TrainTime(pnr);
                    QThread::msleep(TimeLeaveTor*1000);
                    clean(x,kolor);
                    QCoreApplication::processEvents();
                    break;
                }
                */
                alla[y]->setITrain();
                clean(y,kolor);
                QCoreApplication::processEvents();
                TimeLeaveTor = TrainTime(pnr);
                QThread::msleep(TimeLeaveTor*1000);
                alla[x]->setITrain();
                clean(x,kolor);
                QCoreApplication::processEvents();
                x = y;
                continue;
                //clean x
                //wait time to reach new blok - diff
                //search trasa y
                //clean y
                //diww = wait to leave n
                //clean x
                //x=y
                //continue
            }
        }
    }
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

        while(j!=-1 && j!=-2)
        {
            clean(j,tmpKol);
            j=TrasaTemp(j);
        }
        //clean(j,tmpKol);
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
            if(IsIn(j,End,ALTEZZA)!=-1||IsIn(j,Perony,ALTEZZA)!=-1)
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
            if(IsIn(tmp2,End,ALTEZZA)!=-1 || IsIn(tmp2,Perony,ALTEZZA)!=-1)
            {
                clean(tmp2,stile);
                break;
            }
        }
    }
    for(tmp1=n+LUNGHEZZA;tmp1<ALTEZZA*LUNGHEZZA;tmp1=tmp1+LUNGHEZZA)
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
        if(IsIn(tmp2,End,ALTEZZA)!=-1 || IsIn(tmp2,Perony,ALTEZZA)!=-1)
        {
            clean(tmp2,stile);
            break;
        }
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
            if(IsIn(tmp2,End,ALTEZZA)!=-1)
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
            if(IsIn(tmp2,End,ALTEZZA)!=-1||IsIn(tmp2,Perony,ALTEZZA)!=-1)
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
    QString kol;
    if((n<(ALTEZZA*LUNGHEZZA))&&(n>0))
    {
        if(IsIn(n,ZwUp->getTab(),RAILLGZ)!=-1)
        {
            if(alla[n]->getWTL()==UP)
            {
                x=0;
                y=1;
            }
            else
            {
                x=1;
                y=0;
            }
        }
        if(IsIn(n,ZwDw->getTab(),RAILLDZ)!=-1)
        {
            if(alla[n]->getWTL()==DOWN)
            {
                x=1;
                y=0;
            }
            else
            {
                x=0;
                y=1;
            }
        }
        kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            if(alla[n]->getITrain()!=0)
            {
                stile = "background-color: blue";
            }
            kids.at(x)->setStyleSheet(stile);
            kids.at(y)->setStyleSheet("background-color: grey");
            kids.clear();
            return;
        }
        if(alla[n]->getITrain()!=0)
        {
            alla[n]->setStyleSheet("background-color: blue");
        }
        else
        {
            alla[n]->setStyleSheet(stile);
        }

    }
}

int Widget::TrasaTemp(int n)
{
    if(n<(ALTEZZA*LUNGHEZZA)&&(n>0))
    {
         QString tmpWTL = alla[n]->getWTL();

        if(tmpWTL==STRAIGHT)
        {
            //Verifying of the variable j isn't out of range,
            // or if the straight function isn't gone a line down the display
            if(IsIn(n,End,ALTEZZA)!=-1)
            {
                return -2;
            }
            else if(IsIn(n,Perony,ALTEZZA)!=-1)
            {
                return -1;
            }
            n++;
            return n;
        }
        else if(tmpWTL==UP)
        {
            n=n-LUNGHEZZA;
            return n;
        }
        else if(tmpWTL==DOWN)
        {
            n=n+LUNGHEZZA;
            return n;
        }
    }
    else
    {
        return -2;
    }
}

int Widget::WhatTrainThere(int n)
{
    int i;
    int temp;
    for(i=0;i<Pociag::Quanto;i++)
    {
        temp = (Ciuf[i]->getCoords());
        if(temp==n)
        {
            return i;
        }
    }
    return -1;
}

/*
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

int Widget::isIn(int j, int* tab)
{
    int i;
    for(i=0;i<ALTEZZA;i++)
    {
        if(j==tab[i])
        {
            return i;
        }
    }
    return 0;
}
*/
double Widget::kmhTOms(double vel)
{
    return (vel*3.6);
}

double Widget::trasaTime(int nrciuf,int nrtor)
{
    double Tdlg=alla[nrtor]->getLen();
    double Pvel=Ciuf[nrciuf]->getPredkosc();

    double wynik = Tdlg/Pvel;
    return wynik;
}

double Widget::TrainTime(int nrciuf)
{
    double Pdlg=Ciuf[nrciuf]->getDlg();
    double Pvel=Ciuf[nrciuf]->getPredkosc();

    double wynik = Pdlg/Pvel;
    return wynik;
}

void Widget::setZwStan(int n, int flg)
{
    int tmp;
    alla[n]->setWTL();
    if(flg==0)
    {
        clean(n,"background-color: yellow");
    }
    else
    {
        clean(n,"background-color: grey");
    }
    if(alla[n]->getWTL()==UP)
    {
        /*
        kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            kids.at(0)->setStyleSheet("background-color: yellow");
            kids.at(1)->setStyleSheet("background-color: grey");
            kids.clear();
        }
        */
        //clean(n,"background-color: grey");
        tmp=n-LUNGHEZZA;
        setFromStan(tmp,DOWN);
    }
    else if(alla[n]->getWTL()==DOWN)
    {
        /*
        kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            kids.at(0)->setStyleSheet("background-color: grey");
            kids.at(1)->setStyleSheet("background-color: yellow");
            kids.clear();
        }
        */
        //clean(n,"background-color: grey");
        tmp=n+LUNGHEZZA;
        setFromStan(tmp,UP);
    }
    else
    {
        if(alla[n]->getType()==1)
        {
            /*
            kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
            if(!(kids.isEmpty()))
            {
                kids.at(1)->setStyleSheet("background-color: yellow");
                kids.at(0)->setStyleSheet("background-color: grey");
                kids.clear();
            }
            */
            //clean(n,"background-color: grey");
        }
        if(alla[n]->getType()==2)
        {
            /*
            kids = alla[n]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
            if(!(kids.isEmpty()))
            {
                kids.at(0)->setStyleSheet("background-color: yellow");
                kids.at(1)->setStyleSheet("background-color: grey");
                kids.clear();
            }
            */
            //clean(n,"background-color: grey");
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

void Widget::ZwChange(int n)
{
    int zwnum = ZwUp->getpos(n);
    int nrCiuf;
    QList<int>* gridTrain;
    bool check=Zwrotnice[zwnum]->isChecked();
    if(zwnum==-1)
    {
        zwnum = (ZwDw->getpos(n))+RAILLGZ;
        if(zwnum==-1)
        {
            return;
        }
    }
    Zwrotnice[zwnum]->setDisabled(true);
    if(check==true)
    {
        Zwrotnice[zwnum]->setDown(true);
    }
    else
    {
        Zwrotnice[zwnum]->setDown(false);
    }
    //QThread::msleep(500);
    setZwStan(n,0);

    //Starts where there is a train -> needed a class with a static member that return number of trains in the system
    if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
    {
        cleanAdjacent(gridTrain->at(0),"background-color: grey");
        for(int nn=0; nn<gridTrain->count(); nn++)
        {


        nrCiuf = WhatTrainThere(gridTrain->at(nn));
        if(nrCiuf!=-1)
        {
            if(Ciuf[nrCiuf]->getDirection()==1)
            {

                qDebug("TRASA W PRAWO"); //wzgledem gridTrain
                Trasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
            }
        }
        }
    }
    else if((gridTrain=IsTrainOnThere(Perony))->isEmpty()==false)
    {
        cleanAdjacent(gridTrain->at(0),"background-color: grey");
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
        nrCiuf = WhatTrainThere(gridTrain->at(nn));
        if(nrCiuf!=-1)
        {
            if(Ciuf[nrCiuf]->getDirection()==1)
            {

                qDebug("TRASA W PRAWO");
                Trasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
            }
            else if(Ciuf[nrCiuf]->getDirection()==2)
            {
                qDebug("TRASA W LEWO");
            }
        }
        }

    }
    else if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
    {
        cleanAdjacent(gridTrain->at(0),"background-color: grey");
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
        nrCiuf = WhatTrainThere(gridTrain->at(nn));
        if(nrCiuf!=-1)
        {
            if(Ciuf[nrCiuf]->getDirection()==2)
            {
                qDebug("TRASA W LEWO");

                Trasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
            }
        }
        }

    }
    Zwrotnice[zwnum]->setDisabled(false);
}

 void Widget::SemaforChanged(int n)
 {
     int num = TrainCan->getpos(n);
     int z, peron;
     if(alla[n]->getITrain())
     {
         int trainnr = WhatTrainThere(n);
         if(IsTrainOnThere(Perony))
         {
             Ciuf[trainnr]->setPredkosc(40);
             sella[num]->setColor(3);
         }
         else
         {
             Ciuf[trainnr]->setPredkosc(100);
             sella[num]->setColor(4);
         }
         if((Ciuf[trainnr]->getDirection())==1)
         {

             //Podajemy z aktualnym bloczku znajdywania sie pociagu!!
             if(TrasaPociag(n,trainnr,"background color: grey"))
             {
                 for(z=0;z<Pociag::getQuanto();z++)
                 {
                     if((peron=IsIn(Ciuf[z]->getCoords(),Perony,ALTEZZA))!=-1)
                     {
                         Trasa(peron,'w',alla[peron]->getITrain());
                     }
                     else if((peron=IsIn(Ciuf[z]->getCoords(),End,ALTEZZA))!=-1)
                     {
                         Pociag::decrement();
                         //Ciuf = CreateCiuf();
                         clean(peron,"background kolor : grey");
                     }
                 }

             }
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

 void Widget::Train(int n)
 {
     int zwnum = TrainCan->getpos(n);
     int nrCiuf;
     QList<int>* gridTrain;
     bool check=GenTrain[zwnum]->isChecked();
     if(zwnum==-1)
     {
         return;
     }
     GenTrain[zwnum]->setDisabled(true);
     if(check==true)
     {
         GenTrain[zwnum]->setDown(true);
     }
     else
     {
         GenTrain[zwnum]->setDown(false);
     }
     //QThread::msleep(500);
     //setZwStan(n);
     if(alla[n]->getITrain()==0)
     {
         Pociag::increment();
         //Ciuf = CreateCiuf();
         Ciuf[(Pociag::getQuanto())-1]->setCoords(n);
         if(zwnum<TRAIN/2)
         {
             Ciuf[(Pociag::getQuanto())-1]->setDirection(1);
         }
         else
         {
              Ciuf[(Pociag::getQuanto())-1]->setDirection(2);
         }
         alla[n]->setITrain();
     }
     cleanAdjacent(n,"background-color: grey");
     //Starts where there is a train -> needed a class with a static member that return number of trains in the system
     if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
     {
         for(int nn=0; nn<gridTrain->count(); nn++)
         {
         nrCiuf = WhatTrainThere(gridTrain->at(nn));
         if(nrCiuf!=-1)
         {
             if(Ciuf[nrCiuf]->getDirection()==1)
             {
                 qDebug("TRASA W PRAWO"); //wzgledem gridTrain
                 Trasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
             }
         }
         }
     }
     else if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
     {
         for(int nn=0; nn<gridTrain->count(); nn++)
         {
         nrCiuf = WhatTrainThere(gridTrain->at(nn));
         if(nrCiuf!=-1)
         {
             if(Ciuf[nrCiuf]->getDirection()==2)
             {
                 qDebug("TRASA W LEWO");
             }
         }
         }

     }
     GenTrain[zwnum]->setDisabled(false);
 }

 void Widget::ObslugaPeronu(int n)
 {
     //TYMCZASOWA GENERACJA POCIAGU DO DEBAGOWANIA//
     Pociag::increment();
     alla[n]->setITrain();
     Ciuf[Pociag::getQuanto()-1]->setDirection(1);
     Ciuf[Pociag::getQuanto()-1]->setCoords(n);
     clean(n,"background color: grey");
     //QThread::msleep(1000);
     //---//
     int zwnum = OtherGen->getpos(n);
     //int z, peron;
     int peron;
     if(alla[n]->getITrain())
     {
             int trainnr = WhatTrainThere(n);
             Ciuf[trainnr]->setPredkosc(100);
             sella[zwnum]->setColor(4);
             alla[n]->setITrain();
             QThread::msleep(trasaTime(trainnr,n)*1000);
             alla[n+1]->setITrain();
             clean(n,"background color: grey");
             QCoreApplication::processEvents();
             QThread::msleep(TrainTime(trainnr)*1000);
             alla[n]->setITrain();
             clean(n+1,"background color: grey");
             QCoreApplication::processEvents();
             QThread::msleep(trasaTime(trainnr,n+1)*1000);
         if((Ciuf[trainnr]->getDirection())==1) //==1 w prawo, ==2 w lewo
         {

             //Podajemy z aktualnym bloczku znajdywania sie pociagu!!
             if(TrasaPociag(n+1,trainnr,"background color: grey"))
             {
                 if((peron=IsIn(Ciuf[trainnr]->getCoords(),End,ALTEZZA))!=-1)
                 {
                     Pociag::decrement();
                     //Ciuf = CreateCiuf();
                     alla[End[peron]]->setITrain();
                     clean(End[peron],"background kolor : grey");
                 }
                 else if((peron=IsIn(Ciuf[trainnr]->getCoords(),Start,ALTEZZA))!=-1)
                 {
                     Pociag::decrement();
                     //Ciuf = CreateCiuf();
                     alla[Start[peron]]->setITrain();
                     clean(Start[peron],"background kolor : grey");
                 }
             }

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

QList<int>* Widget::IsTrainOnThere(int *tab)
{
    int i;
    int index;
    QList<int>* tmplista = new QList<int>();
    for(i=0;i<ALTEZZA;i++)
    {
        index = tab[i];
        if(alla[index]->getITrain())
        {
            tmplista->append(index);
        }
    }
    return tmplista;
}

 //przekazac tor c+1, gdzie c to blok na ktory wyjezdza pociag

 //pass the real position n (not n+1)
/*
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

 int Widget::WyznaczTrasaJedzie(int n, QString string)
 {
     alla[n]->setITrain();
     clean(n,string);
 }

*/


 /*
 double secTOms(double sec)
 {
     return (sec*1000);
 }
 */
