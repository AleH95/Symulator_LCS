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
                           292,293,294,295,296,297,298,299,300,301,302,303}; //Straight
    /*int tmprro[RAILROADO]={43,62,120,125,145,148,149,152,153,154,155,160,
                                   161,162,163,166,167,170,183,186,187,188,189,
                                   196,197,198,199,202,219,220,221,222,223,232,
                                   233,234,235,236,255,256,257,268,269,270,291,304};
    */
    //tory ukośne
    int tmplg[RAILLG] ={160, 162, 166, 170, 196, 198, 202, 232, 234, 236, 268, 270, 304}; //lewy gorny
    int tmppg[RAILPG] = {145, 149, 153, 155, 183, 187, 189, 219, 221, 223, 255, 257, 291}; //prawy gorny
    int tmpld[RAILLD] = {62, 120, 148, 152,154, 186, 188, 220, 222, 256}; //lewa dolna
    int tmppd[RAILPD] = {43, 125, 167, 163, 161, 197, 199, 233, 235, 269}; //prawa dolna
    //zwrotnice
    int tmplgz[RAILLGZ] ={78, 107, 134, 136, 200}; //lewa gorna
    int tmppgz[RAILPGZ] = {97, 109, 111, 138, 185}; //prawa gorna
    int tmpldz[RAILLDZ] = {74, 76, 103, 110, 114, 118, 150, 184}; //lewa dolna
    int tmppdz[RAILPDZ] = {72, 99, 101, 127, 131, 135, 165, 201}; //prawa dolna

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

    PZwKol = new Color(2*(RAILPGZ+RAILPDZ)); //Pod labele, do zmieniania koloru toru
    PZwUp = new Stos(RAILPGZ,tmppgz);
    PZwDw = new Stos(RAILPDZ,tmppdz);

    SemStos = new Stos(SEM,tmpsem);         //Koordy semaforow wejsciowych - wyjsciowych
    OtherSem = new Stos(SEMPER,tmpsemper);  //Koordy semaforow peronu
    Generation = new Stos(SEM,tmptrain);    //Do ktorego bloku jest podpiety semafor
    OtherGen = new Stos(SEMPER,tmpperony);  //Na ktorym peronie znajduje sie pociagu wzgledem semaforu peronu
    TrainCan = new Stos(SEM,tmptrain);      //Gdzie sie maja pojawyc pociagi wejscie - wyjscie
    //Ciuf=NULL;
    //The size of the main window
    setFixedSize(1280,600);


    ZsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    PZsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    SsignalMapper = new QSignalMapper(this); //tworzenie signal mapper
    GsignalMapper = new QSignalMapper(this);
    OSmapper = new QSignalMapper(this);

    connect(ZsignalMapper, SIGNAL(mapped(int)),this,SLOT(ZwChange(int)));           //Obsluga zwrotnic
    connect(PZsignalMapper, SIGNAL(mapped(int)),this,SLOT(PZwChange(int)));           //Obsluga zwrotnic
    connect(SsignalMapper, SIGNAL(mapped(int)),this,SLOT(SemaforChanged(int)));     //Obsluga semaforow wejsciowych-wyjsciowych
    connect(GsignalMapper, SIGNAL(mapped(int)),this,SLOT(Train(int)));              //Obsluga generacji pociagu
    connect(OSmapper, SIGNAL(mapped(int)),this,SLOT(ObslugaPeronu(int)));           //Obsluga semaforow peronow

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
    int j,i,z,p,Pz;
    int s=0;
    MainLayout = new QVBoxLayout(this);
    GTory = new QGridLayout();
    GBZwrotnice = new QGridLayout();
    PGBZwrotnice = new QGridLayout();
    //GBSemafory = new QGridLayout();
    LLSemafory = new QVBoxLayout();
    PLSemafory = new QVBoxLayout();
    HorizontalZwSemGen = new QHBoxLayout();
    i=z=p=Pz=0;

    //--Generowanie gridu torow
    for(j=0;j<LUNGHEZZA*ALTEZZA;j++)
    {
        alla[j] = new Tor(0,100,-1);
        QString ela = "T"+QString::number(j/(LUNGHEZZA))+QString::number(i);
        //alla[j]->setText(ela);
        alla[j]->setStyleSheet("background-color: grey");
        int tempocasa=IsIn(j,Raillgz->getTab(),RAILLGZ);
        if(tempocasa!=-1)
        {
            alla[j]->setType(1);                                //Typ zwrotnica gorna
            alla[j]->setWTL();
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();                              //Pobieranie Qlabel z klasy stos
            VLay[z]->addWidget(tmpCol);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");  //Domyslne nastawienia STRAIGHT wiec koniecznosc wyswietlania dolnej czesci
            VLay[z]->addWidget(tmpCol);

            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/Tor_prosty.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);

            z++;

        }
        else if(IsIn(j,Railldz->getTab(),RAILLDZ)!=-1)
        {
            alla[j]->setType(2);                                //Typ zwrotnica dolna
            alla[j]->setWTL();
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

        //--------------zwrotnice--------------------------
        //DO OBSLUGI raprezentacja graficzna (VerticalBox, QLabel for colors)
        else if(IsIn(j,Railpgz->getTab(),RAILPGZ) !=-1)
        {
            alla[j]->setType(3);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_gora_z.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);

            PVLay[Pz] = new QVBoxLayout(alla[j]);
            PVLay[Pz]->setSpacing(0);
            PVLay[Pz]->setContentsMargins(0,0,0,0);
            tmpCol = PZwKol->get();
            PVLay[Pz]->addWidget(tmpCol);
            tmpCol = PZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");
            PVLay[Pz]->addWidget(tmpCol);
            Pz++;
        }
        else if(IsIn(j,Railpdz->getTab(),RAILPDZ) !=-1)
        {
            alla[j]->setType(4);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_dol_z.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);

            PVLay[Pz] = new QVBoxLayout(alla[j]);
            PVLay[Pz]->setSpacing(0);
            PVLay[Pz]->setContentsMargins(0,0,0,0);
            tmpCol = PZwKol->get();
            tmpCol->setStyleSheet("background-color: yellow");
            PVLay[Pz]->addWidget(tmpCol);
            tmpCol = PZwKol->get();
            PVLay[Pz]->addWidget(tmpCol);
            Pz++;
        }
        //_______________________
        //else if typ3 , else if typ 4
        //<------------------

        else if(IsIn(j,SemStos->getTab(),SEM)!=-1)
        {
            VSemaf[s]=new QVBoxLayout(alla[j]);
            sella[s] = new Semafor(0);
            VSemaf[s]->addWidget(sella[s]);
            s++;
        }

        else if(IsIn(j,OtherSem->getTab(),SEMPER)!=-1)
        {
            VOSemaf[p]=new QVBoxLayout(alla[j]);
            Osella[p] = new Semafor(0);
            VOSemaf[p]->addWidget(Osella[p]);
            p++;
        }

        //__________________________________________________________________________________
        else if(IsIn(j,RailroadS->getTab(), RAILROADS) !=-1)
        {
            alla[j]->setType(0);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/Tor_prosty.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        else if(IsIn(j,Raillg->getTab(),RAILLG) !=-1)
        {
            alla[j]->setType(5);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_gora.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        else if(IsIn(j,Railpg->getTab(),RAILPG) !=-1)
        {
            alla[j]->setType(7);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_gora.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        else if(IsIn(j,Railld->getTab(),RAILLD) !=-1)
        {
            alla[j]->setType(6);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_dol.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        else if(IsIn(j,Railpd->getTab(),RAILPD) !=-1)
        {
            alla[j]->setType(8);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_dol.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }



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

    //--Nastawianie koordow zwrotnic (Gornych PRAWYCH)
    i=0;
    for(j=0;j<RAILPGZ;j++)
    {
        PZwrotnice[j] = new QPushButton();
        QString ela = "Z"+QString::number(j/(LZWROTNICE))+QString::number(i);
        PZwrotnice[j]->setObjectName(ela);
        PZwrotnice[j]->setText(ela);
        PZwrotnice[j]->setCheckable(true);
        PGBZwrotnice->addWidget(PZwrotnice[j],j/(LZWROTNICE),i);
        connect(PZwrotnice[j], SIGNAL(toggled(bool)), PZsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
        int temp = PZwUp->GetThat(j);
        kids = alla[temp]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            kids.at(0)->setText(ela);
            kids.at(0)->setAlignment(Qt::AlignTop);
            kids.clear();
        }
        PZsignalMapper->setMapping(PZwrotnice[j], temp);                            //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (coordy torow znajdywania sie elementu)
        i++;
        if(i>=LZWROTNICE)
        {
            i=0;
        }
    }
    for(j=RAILPGZ;j<RAILPDZ+RAILPGZ;j++)
    {
        PZwrotnice[j] = new QPushButton();
        QString ela = "Z"+QString::number(j/(LZWROTNICE))+QString::number(i);
        PZwrotnice[j]->setObjectName(ela);
        PZwrotnice[j]->setText(ela);
        PZwrotnice[j]->setCheckable(true);
        PGBZwrotnice->addWidget(PZwrotnice[j],j/(LZWROTNICE),i);
        connect(PZwrotnice[j], SIGNAL(toggled(bool)), PZsignalMapper, SLOT(map())); //polaczenie signalu zwrotnicy do signalmapper
        //int m = j - RAILLGZ;
        int temp = PZwDw->GetThat(j-RAILLGZ);
        kids = alla[temp]->findChildren<Color *>(QString(), Qt::FindDirectChildrenOnly);
        if(!(kids.isEmpty()))
        {
            kids.at(1)->setText(ela);
            kids.at(1)->setAlignment(Qt::AlignBottom);
            kids.clear();
        }
        PZsignalMapper->setMapping(PZwrotnice[j], temp);                            //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (coordy torow znajdywania sie elementu)
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
        //GBSemafory->addWidget(Semafory[j],j/(LSEMAFORY),i);
        if(j%2==0) { LLSemafory->addWidget(Semafory[j]); }
        else if(j%2!=0) { PLSemafory->addWidget(Semafory[j]); }
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
        //GBSemafory->addWidget(OSemafory[j],(j+k)/(LSEMAFORY),i);
        if(j%2==0) { LLSemafory->addWidget(OSemafory[j]); }
        else if(j%2!=0) { PLSemafory->addWidget(OSemafory[j]); }
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
    GBZwrotnice->setSpacing(5);
    //HorizontalZwSemGen->addLayout(GBSemafory,2);
    //GBSemafory->setSpacing(15);
    HorizontalZwSemGen->addLayout(LLSemafory,2);
    LLSemafory->setSpacing(5);
    HorizontalZwSemGen->addLayout(PLSemafory,2);
    PLSemafory->setSpacing(5);
    HorizontalZwSemGen->addLayout(PGBZwrotnice,2);
    PGBZwrotnice->setSpacing(5);
    HorizontalZwSemGen->addLayout(VGenTrain[z],0);
    MainLayout->setSpacing(2);
    MainLayout->addLayout(GTory,2);
    MainLayout->addLayout(HorizontalZwSemGen,0);
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
            }
        }
    }
}

int Widget::ReverseTrasaPociag(int n, int pnr, QString kolor)
{

    int TimeNextTor = 0;
    int TimeLeaveTor = 0;
    if(n<(ALTEZZA*LUNGHEZZA)&&(n>0))
    {
        alla[n]->setITrain();
        clean(n,kolor);
        QCoreApplication::processEvents();
        int rap = Ciuf[pnr]->getDlg() / alla[n]->getLen();
        int y = n; //for if statement
        int x = ReverseTrasaTemp(n); //next step in order to know what to light
        if(x==-1||x==-2)
        {
            return 1;
        }
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
                    x=ReverseTrasaTemp(x);
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
                    y=ReverseTrasaTemp(y);
                    x=ReverseTrasaTemp(x);
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
                            y=ReverseTrasaTemp(y);
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
                y = ReverseTrasaTemp(x);
                if(y==-1 || y==-2)
                {
                    return 1;
                }
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
            }
        }
    }
}

void Widget::Trasa(int j, char kolor, int flg)
{
    QString tmpWTL = alla[j]->getWTL();
    QString tmpKol = "background-color: ";
    int typeblok;
    if(j<(ALTEZZA*LUNGHEZZA)&&(j>0))
    {
        typeblok = alla[j]->getType();
        if(flg==0)
        {
            if(typeblok==1 || typeblok==2 || typeblok==3 || typeblok==4)
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
    }
}

void Widget::ReverseTrasa(int j, char kolor, int flg)
{
    QString tmpWTL = alla[j]->getWTL();
    QString tmpKol = "background-color: ";
    int typeblok;
    if(j<(ALTEZZA*LUNGHEZZA)&&(j>0))
    {
        typeblok = alla[j]->getType();
        if(flg==0)
        {
            if(typeblok==1 || typeblok==2 || typeblok==3 || typeblok==4)
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
            j=ReverseTrasaTemp(j);
        }
    }
}

void Widget::cleanAdjacent(int n, QString stile)
{
    int tmp1, tmp2;
    QString stilo = "background-color: yellow";
    QString canIgo;
    int typeblok;
    for(tmp1=n;tmp1>0;tmp1=tmp1-LUNGHEZZA)
    {
        tmp2=tmp1;
        while(true)
        {
            typeblok = alla[tmp2]->getType();
            canIgo = alla[tmp2]->getWTL();
            if(canIgo!=NULLO)
            {
                if(typeblok==1 || typeblok==2 || typeblok==3 || typeblok==4)
                {
                    clean(tmp2,stilo);
                }
                else
                {
                    clean(tmp2,stile);
                }
            }
            tmp2++;
            if(IsIn(tmp2,End,ALTEZZA)!=-1 || IsIn(tmp2,Perony,ALTEZZA)!=-1)
            {
                canIgo = alla[tmp2]->getWTL();
                if(canIgo!=NULLO)
                {
                clean(tmp2,stile);
                }
                break;
            }
        }
    }
    for(tmp1=n+LUNGHEZZA;tmp1<ALTEZZA*LUNGHEZZA;tmp1=tmp1+LUNGHEZZA)
    {
        tmp2=tmp1;
        while(true)
        {
            typeblok = alla[tmp2]->getType();
            canIgo = alla[tmp2]->getWTL();
            if(canIgo!=NULLO)
            {
                if(typeblok==1 || typeblok==2 || typeblok==3 || typeblok==4)
                {
                    clean(tmp2,stilo);
                }
                else
                {
                    clean(tmp2,stile);
                }
            }
            tmp2++;
            if(IsIn(tmp2,End,ALTEZZA)!=-1 || IsIn(tmp2,Perony,ALTEZZA)!=-1)
            {
                canIgo = alla[tmp2]->getWTL();
                if(canIgo!=NULLO)
                {
                clean(tmp2,stile);
                }
                break;
            }
        }
    }
}

void Widget::ReversecleanAdjacent(int n, QString stile)
{
    int tmp1, tmp2;
    QString stilo = "background-color: yellow";
    QString canIgo;
    int typeblok;
    for(tmp1=n;tmp1>0;tmp1=tmp1-LUNGHEZZA)
    {
        tmp2=tmp1;
        while(true)
        {
            typeblok = alla[tmp2]->getType();
            canIgo = alla[tmp2]->getWTL();
            if(canIgo!=NULLO)
            {
                if(typeblok==1 || typeblok==2 || typeblok==3 || typeblok==4)
                {
                    clean(tmp2,stilo);
                }
                else
                {
                    clean(tmp2,stile);
                }
            }
            tmp2--;
            if(IsIn(tmp2,Start,ALTEZZA)!=-1 || IsIn(tmp2,Perony,ALTEZZA)!=-1)
            {
                canIgo = alla[tmp2]->getWTL();
                if(canIgo!=NULLO)
                {
                clean(tmp2,stile);
                }
                break;
            }
        }
    }
    for(tmp1=n+LUNGHEZZA;tmp1<ALTEZZA*LUNGHEZZA;tmp1=tmp1+LUNGHEZZA)
    {
        tmp2=tmp1;
        while(true)
        {
            typeblok = alla[tmp2]->getType();
            canIgo = alla[tmp2]->getWTL();
            if(canIgo!=NULLO)
            {
                if(typeblok==1 || typeblok==2 || typeblok==3 || typeblok==4)
                {
                    clean(tmp2,stilo);
                }
                else
                {
                    clean(tmp2,stile);
                }
            }
            tmp2--;
            if(IsIn(tmp2,Start,ALTEZZA)!=-1 || IsIn(tmp2,Perony,ALTEZZA)!=-1)
            {
                canIgo = alla[tmp2]->getWTL();
                if(canIgo!=NULLO)
                {
                clean(tmp2,stile);
                }
                break;
            }
        }
    }
}

//----------------Dodac zwrotnice z prawej strony-------// --> Zweryfikowac dzialanie!!!
void Widget::clean(int n, QString stile)
{
    int x,y,z;
    x=y=z=0;
    QString kol;
    if((n<(ALTEZZA*LUNGHEZZA))&&(n>0))
    {
        if(IsIn(n,ZwUp->getTab(),RAILLGZ)!=-1 || IsIn(n,Railpgz->getTab(),RAILPGZ)!=-1)
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
        if(IsIn(n,ZwDw->getTab(),RAILLDZ)!=-1 || IsIn(n,Railpdz->getTab(),RAILPDZ)!=-1)
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
    else
    {
        qDebug("Przekroczono tablice");
    }
}

int Widget::TrasaTemp(int n)
{
    if(n<(ALTEZZA*LUNGHEZZA)&&(n>0))
    {
        QString tmpWTL = alla[n]->getWTL();
        QString canIgo;
        int bloktype = alla[n]->getType();

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
        else if(bloktype==8) //blok ukosny dol od prawej strony
        {
            canIgo = alla[n-LUNGHEZZA]->getWTL();
            if(canIgo==NULLO || canIgo==STRAIGHT) //dla blokow ukosnych, ide zgodnie z wtl ale jak null do w prawo
            {
                n++;
            }
            else
            {
                n=n-LUNGHEZZA;
            }
            return n;
        }
        else if(bloktype==7) //blok ukosny gora od prawej strony
        {
            canIgo = alla[n+LUNGHEZZA]->getWTL();
            if(canIgo==NULLO || canIgo==STRAIGHT)
            {
                n++;
            }
            else
            {
                n=n+LUNGHEZZA;
            }
            return n;
        }
        else if (tmpWTL==UP)
        {
            if(bloktype==3)
            {
                n++;
                return n;
            }
            n=n-LUNGHEZZA;
            return n;
        }
        else if(tmpWTL==DOWN)
        {
            if(bloktype==4)
            {
                n++;
                return n;
            }
            n=n+LUNGHEZZA;
            return n;
        }
    }
    else
    {
        return -2;
    }
}

int Widget::ReverseTrasaTemp(int n)
{
    if(n<(ALTEZZA*LUNGHEZZA)&&(n>0))
    {
        QString tmpWTL = alla[n]->getWTL();
        QString canIgo;
        int bloktype = alla[n]->getType();

        if(tmpWTL==STRAIGHT)
        {
            //Verifying of the variable j isn't out of range,
            // or if the straight function isn't gone a line down the display
            if(IsIn(n,Start,ALTEZZA)!=-1)
            {
                return -2;
            }
            else if(IsIn(n,Perony,ALTEZZA)!=-1)
            {
                return -1;
            }
            n--;
            return n;
        }
        else if(bloktype==6) //blok ukosny dol od lewej strony
        {
            canIgo = alla[n-LUNGHEZZA]->getWTL();
            if(canIgo==NULLO || canIgo==STRAIGHT) //dla blokow ukosnych, ide zgodnie z wtl ale jak null do w lewo
            {
                n--;
            }
            else
            {
                n=n+LUNGHEZZA;
            }
            return n;
        }
        else if(bloktype==5) //blok ukosny gora od lewej strony
        {
            canIgo = alla[n+LUNGHEZZA]->getWTL();
            if(canIgo==NULLO || canIgo==STRAIGHT)
            {
                n--;
            }
            else
            {
                n=n-LUNGHEZZA;
            }
            return n;
        }
        else if (tmpWTL==UP)
        {
            if(bloktype==1)
            {
                n--;
                return n;
            }
            n=n+LUNGHEZZA;
            return n;
        }
        else if(tmpWTL==DOWN)
        {
            if(bloktype==2)
            {
                n--;
                return n;
            }
            n=n-LUNGHEZZA;
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

void Widget::setCColor(int n, int flg)
{
    if(flg==0)
    {
        clean(n,"background-color: yellow");
    }
    else
    {
        clean(n,"background-color: grey");
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
    setCColor(n,0);

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
        ReversecleanAdjacent(gridTrain->at(0),"background-color: grey");
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
                    ReverseTrasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
                }
            }
        }

    }
    else if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
    {
        ReversecleanAdjacent(gridTrain->at(0),"background-color: grey");
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
            nrCiuf = WhatTrainThere(gridTrain->at(nn));
            if(nrCiuf!=-1)
            {
                if(Ciuf[nrCiuf]->getDirection()==2)
                {
                    qDebug("TRASA W LEWO");

                    ReverseTrasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
                }
            }
        }
    }
    Zwrotnice[zwnum]->setDisabled(false);
}

void Widget::PZwChange(int n)
{
    int zwnum = PZwUp->getpos(n);
    int nrCiuf;
    QList<int>* gridTrain;
    bool check=PZwrotnice[zwnum]->isChecked();
    if(zwnum==-1)
    {
        zwnum = (PZwDw->getpos(n))+RAILPGZ;
        if(zwnum==-1)
        {
            return;
        }
    }
    PZwrotnice[zwnum]->setDisabled(true);
    if(check==true)
    {
        PZwrotnice[zwnum]->setDown(true);
    }
    else
    {
        PZwrotnice[zwnum]->setDown(false);
    }
    //QThread::msleep(500);
    setCColor(n,0);

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
        ReversecleanAdjacent(gridTrain->at(0),"background-color: grey");
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
                    ReverseTrasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
                }
            }
        }

    }
    else if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
    {
        ReversecleanAdjacent(gridTrain->at(0),"background-color: grey");
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
            nrCiuf = WhatTrainThere(gridTrain->at(nn));
            if(nrCiuf!=-1)
            {
                if(Ciuf[nrCiuf]->getDirection()==2)
                {
                    qDebug("TRASA W LEWO");

                    ReverseTrasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
                }
            }
        }
    }
    PZwrotnice[zwnum]->setDisabled(false);
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
                        ReversecleanAdjacent(Perony[peron],"background kolor : grey");
                        Trasa(Perony[peron],'w',alla[Perony[peron]]->getITrain());
                    }
                    else if((peron=IsIn(Ciuf[z]->getCoords(),End,ALTEZZA))!=-1)
                    {
                        Pociag::decrement();
                        //Ciuf = CreateCiuf();
                        clean(End[peron],"background kolor : grey");
                    }
                }

            }
        }
        else if((Ciuf[trainnr]->getDirection())==2)
        {
            if(ReverseTrasaPociag(n,trainnr,"background color: grey"))
            {
            qDebug("Reverse Trasa");
            for(z=0;z<Pociag::getQuanto();z++)
            {
                if((peron=IsIn(Ciuf[z]->getCoords(),Perony,ALTEZZA))!=-1)
                {
                    int numbers = Perony[peron];
                    cleanAdjacent(numbers,"background kolor : grey");
                    qDebug("Reverse Trasa");
                    //ReverseTrasa(Perony[peron],'w',alla[Perony[peron]]->getITrain());
                }
                else if((peron=IsIn(Ciuf[z]->getCoords(),Start,ALTEZZA))!=-1)
                {
                    Pociag::decrement();
                    clean(Start[peron],"background kolor : grey");
                }

            }
            }
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

    //Starts where there is a train -> needed a class with a static member that return number of trains in the system
    if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
    {
        cleanAdjacent(n,"background-color: grey");
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
        ReversecleanAdjacent(n,"background-color: grey");
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
            nrCiuf = WhatTrainThere(gridTrain->at(nn));
            if(nrCiuf!=-1)
            {
                if(Ciuf[nrCiuf]->getDirection()==2)
                {
                    qDebug("TRASA W LEWO");
                    ReverseTrasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
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
    //---//
    int zwnum = OtherGen->getpos(n);
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
        else if((Ciuf[trainnr]->getDirection())==2)
        {
            qDebug("Reverse Trasa");
            if(ReverseTrasaPociag(n+1,trainnr,"background color: grey"))
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
