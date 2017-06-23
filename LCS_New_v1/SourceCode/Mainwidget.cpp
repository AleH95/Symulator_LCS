#include "Mainwidget.h"
#include "ui_widget.h"
#include "thread.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setFixedSize(1280,600);
    this->setWindowTitle("Stacja PKP");
    //Temporary table of zwrotnice Gorne and Dolne, it'll be written to Stos
    //The table content is written as j where j = (Row*LUNGHEZZA ) + Column
    //__________________________________________________________________________________
    int tmptrain[TRAIN] = {71,106,104,139}; //Pozycja przybywajacych pociagow
    int tmpsemper[SEMPER] = {9,26,8,27,121,124,330,335,329,336,328,337,327,338};
    int tmpperony[SEMPER] = {51,51,86,86,156,156,191,191,226,226,261,261,296,296};
    int tmpsem[SEM] = {36,141,69,174}; //Semafore wejsciowe-wyjsciowe
    int tmprrs[RAILROADS]={44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,
                           70,71,73,75,77,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,98,100,102,104,
                           105,106,108,112,113,115,116,117,119,126,128,129,130,132,133,137,139,
                           146,147,151,156,157,158,159,164,168,169,
                           190,191,192,193,194,195,
                           224,225,226,227,228,229,230,231,
                           258,259,260,261,262,263,264,265,266,267,
                           292,293,294,295,296,297,298,299,300,301,302,303}; //Straight
    //---------tory ukośne
    int tmplg[RAILLG] ={160, 162, 166, 170, 196, 198, 202, 232, 234, 236, 268, 270, 304}; //lewy gorny
    int tmppg[RAILPG] = {145, 149, 153, 155, 183, 187, 189, 219, 221, 223, 255, 257, 291}; //prawy gorny
    int tmpld[RAILLD] = {62, 120, 148, 152,154, 186, 188, 220, 222, 256}; //lewa dolna
    int tmppd[RAILPD] = {43, 125, 167, 163, 161, 197, 199, 233, 235, 269}; //prawa dolna
    //------------zwrotnice
    int tmplgz[RAILLGZ] ={78, 107, 134, 136, 200}; //lewa gorna
    int tmppgz[RAILPGZ] = {97, 109, 111, 138, 185}; //prawa gorna
    int tmpldz[RAILLDZ] = {74, 76, 103, 110, 114, 118, 150, 184}; //lewa dolna
    int tmppdz[RAILPDZ] = {72, 99, 101, 127, 131, 135, 165, 201}; //prawa dolna
    //----------------------------------------------------------------------------------
    RailroadS = new Stos(RAILROADS,tmprrs);
    Raillg = new Stos(RAILLG,tmplg);
    Railpg = new Stos(RAILPG,tmppg);
    Railld = new Stos(RAILLD,tmpld);
    Railpd = new Stos(RAILPD,tmppd);

    Raillgz = new Stos(RAILLGZ,tmplgz);
    Railpgz = new Stos(RAILPGZ,tmppgz);
    Railldz = new Stos(RAILLDZ,tmpldz);
    Railpdz = new Stos(RAILPDZ,tmppdz);
    //___________________________________________________________________
    //--Stosy powyzszych tablic
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
    //The size of the main window

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

    Ukosna=0;
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
    LLSemafory = new QVBoxLayout();
    PLSemafory = new QVBoxLayout();
    HorizontalZwSemGen = new QHBoxLayout();
    i=z=p=Pz=0;

    for(j=0;j<LUNGHEZZA*ALTEZZA;j++)
    {
    alla[j] = new Tor(0,100,-1);
    QString ela = "T"+QString::number(j/(LUNGHEZZA))+QString::number(i);
    //alla[j]->setText(ela);
    alla[j]->setStyleSheet(GREY);
    }

    //----------Generowanie gridu torow
    for(j=0;j<LUNGHEZZA*ALTEZZA;j++)
    {
        //--------------zwrotnice--------------------------
        //--ZWROTNICA GORNA (LEWA)
        if(IsIn(j,Raillgz->getTab(),RAILLGZ)!=-1)
        {
            alla[j]->setType(1);                                //Typ zwrotnica gorna
            alla[j]->setWTL();
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();                              //Pobieranie Qlabel z klasy stos
            VLay[z]->addWidget(tmpCol);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet(YELLOW);  //Domyslne nastawienia STRAIGHT wiec koniecznosc wyswietlania dolnej czesci
            VLay[z]->addWidget(tmpCol);

            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/Tor_prosty.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);

            z++;

        }
        //--ZWROTNICA DOLNA (LEWA)
        else if(IsIn(j,Railldz->getTab(),RAILLDZ)!=-1)
        {
            alla[j]->setType(2);                                //Typ zwrotnica dolna
            alla[j]->setWTL();
            VLay[z] = new QVBoxLayout(alla[j]);
            VLay[z]->setSpacing(0);
            VLay[z]->setContentsMargins(0,0,0,0);
            tmpCol = ZwKol->get();
            tmpCol->setStyleSheet(YELLOW);  //Domyslne nastawienia STRAIGHT wiec koniecznosc wyswietlania gornej czesci
            VLay[z]->addWidget(tmpCol);
            tmpCol = ZwKol->get();
            VLay[z]->addWidget(tmpCol);
            z++;
        }
        //--ZWROTNICA GORNA (PRAWA)
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
            tmpCol->setStyleSheet(YELLOW);
            PVLay[Pz]->addWidget(tmpCol);
            Pz++;
        }
        //--ZWROTNICA DOLNA (PRAWA)
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
            tmpCol->setStyleSheet(YELLOW);
            PVLay[Pz]->addWidget(tmpCol);
            tmpCol = PZwKol->get();
            PVLay[Pz]->addWidget(tmpCol);
            Pz++;
        }
        //---------------Semafory-----------
        //--SEMAFORY WEJSCIA-WYJSCIA
        else if(IsIn(j,SemStos->getTab(),SEM)!=-1)
        {
            int spqr = SemStos->Get();
            VSemaf[s]=new QVBoxLayout(alla[spqr]);
            VSemaf[s]->setContentsMargins(0,0,0,0);
            sella[s] = new Semafor(0);

            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/WWSemafor.png");
            mypix=mypix.scaled(40,25);
            sella[s]->setPixmap(mypix);

            VSemaf[s]->addWidget(sella[s]);

            s++;
        }
        //--SEMAFORY PERONOW
        else if(IsIn(j,OtherSem->getTab(),SEMPER)!=-1)
        {
            int spqr = OtherSem->Get();
            VOSemaf[p]=new QVBoxLayout(alla[spqr]);
            VOSemaf[p]->setContentsMargins(0,0,0,0);
            Osella[p] = new Semafor(0);

            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/WWSemafor.png");
            //mypix=mypix.scaled(40,25);
            Osella[p]->setPixmap(mypix);

            VOSemaf[p]->addWidget(Osella[p]);
            p++;
        }
        //---------------Tory-----------
        //--TORY PROSTE
        else if(IsIn(j,RailroadS->getTab(), RAILROADS) !=-1)
        {
            /*
            if(j==71)
            {
                qDebug("GENERUJE!"); //Wchodzi do warunku lecz nie nastawia pixmapa
            }
            */
            alla[j]->setType(0);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/Tor_prosty.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        //--UKOSNE GORNE (LEWA)
        else if(IsIn(j,Raillg->getTab(),RAILLG) !=-1)
        {
            alla[j]->setType(5);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_gora.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        //--UKOSNE GORNE (PRAWA)
        else if(IsIn(j,Railpg->getTab(),RAILPG) !=-1)
        {
            alla[j]->setType(7);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_gora.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        //--UKOSNE DOLNE (LEWA)
        else if(IsIn(j,Railld->getTab(),RAILLD) !=-1)
        {
            alla[j]->setType(6);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/lewy_dol.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        //--UKOSNE DOLNE (PRAWA)
        else if(IsIn(j,Railpd->getTab(),RAILPD) !=-1)
        {
            alla[j]->setType(8);
            alla[j]->setWTL();
            QPixmap mypix ("B:/Informatyka PWSZ Tarnow/SEMESTR IV/Architektury_Systemow_Komputerowych/LCS_New_v1/prawy_dol.png");
            mypix=mypix.scaled(40,25);
            alla[j]->setPixmap(mypix);
        }
        //-------Dodawanie do grida
        GTory->addWidget(alla[j],j/(LUNGHEZZA),i);

        i++;                                                    //Zmienna iteracyjna konieczna dla Layaout typu grid
        if(i>=LUNGHEZZA)
        {
            i=0;
        }
    }

    //--Nastawianie przyciskow zwrotnic (Gornych Lewych i Dolnych Lewych)
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
        QString ela = "Z"+QString::number((j/LZWROTNICE))+QString::number(i);
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

    //--Nastawianie przyciskow zwrotnic (Gornych PRAWYCH i Dolnych PRAWYCH)
    i=0;
    for(j=0;j<RAILPGZ;j++)
    {
        PZwrotnice[j] = new QPushButton();
        QString ela = "Z"+QString::number((j/LZWROTNICE)+((RAILLDZ+RAILLGZ)/LZWROTNICE)+1)+QString::number(i);
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
        QString ela = "Z"+QString::number(j/(LZWROTNICE)+((RAILLDZ+RAILLGZ)/LZWROTNICE)+1)+QString::number(i);
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
    //--Nastawianie przyciskow semaforow wejscia-wyjscia
    i=0;
    for(j=0;j<SEM;j++)
    {
        Semafory[j] = new QPushButton();
        if(j<(SEM/2))
        {
            QString ela = "SWW"+QString::number(j/(LSEMAFORY))+QString::number(i);
            Semafory[j]->setText(ela);
            LLSemafory->addWidget(Semafory[j]);
        }
        else
        {
            QString ela = "SWW"+QString::number((j/LSEMAFORY)-1)+QString::number(i);
            Semafory[j]->setText(ela);
            PLSemafory->addWidget(Semafory[j]);
        }
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
    //--Nastawianie przyciskow semaforow PERONOW
    for(j=0;j<SEMPER;j++)
    {
        OSemafory[j] = new QPushButton();
        QString ela = "SP"+QString::number(j/(LSEMAFORY))+QString::number(i);
        //OSemafory[j]->setObjectName(ela);
        OSemafory[j]->setText(ela);
        if(j%2==0) { LLSemafory->addWidget(OSemafory[j]); }
        else if(j%2!=0) { PLSemafory->addWidget(OSemafory[j]); }
        connect(OSemafory[j], SIGNAL(clicked()), OSmapper, SLOT(map()));      //polaczenie signalu zwrotnicy do signalmapper
        //int temp = OtherGen->GetThat(j);
        //sella[temp]->setText(ela);                                                 //Przypisywanie do toru o koordach, nazwe elementu
        //sella[temp]->setAlignment(Qt::AlignBottom);
        OSmapper->setMapping(OSemafory[j], j);                             //nastawianie parametru wedlug ktorego signalmapper rozpoznaje wcisniety przycisk (koordy na ktorych moze sie znajdowac pociag)
        i++;
        if(i>=LSEMAFORY)
        {
            i=0;
        }
    }
    //--Nastawienie przyciskow generowania pociagow (Lewa)
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
    //--Nastawienie przyciskow generowania pociagow (Prawa)
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
    QString tmpKol;
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

        if(kolor=='r'){ tmpKol=RED; }
        else if(kolor=='g'){ tmpKol=GREEN; }
        else if(kolor=='e'){ tmpKol=GREY; }
        else if(kolor=='y'){ tmpKol=YELLOW; }
        else if(kolor=='w'){ tmpKol=WHITE; }

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
    QString tmpKol;
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

        if(kolor=='r'){ tmpKol=RED; }
        else if(kolor=='g'){ tmpKol=GREEN; }
        else if(kolor=='e'){ tmpKol=GREY; }
        else if(kolor=='y'){ tmpKol=YELLOW; }
        else if(kolor=='w'){ tmpKol=WHITE; }

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
    QString stilo = YELLOW;
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
            if(tmp2>ALTEZZA*LUNGHEZZA)
            {
                break;
            }
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
    for(tmp1=n+LUNGHEZZA;tmp1<(ALTEZZA*LUNGHEZZA)-1;tmp1=tmp1+LUNGHEZZA)
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
            if(tmp2>ALTEZZA*LUNGHEZZA)
            {
                break;
            }
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
    QString stilo = YELLOW;
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
            if(tmp2<0)
            {
                break;
            }
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
    for(tmp1=n+LUNGHEZZA;tmp1<(ALTEZZA*LUNGHEZZA)-1;tmp1=tmp1+LUNGHEZZA)
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
            if(tmp2<0)
            {
                break;
            }
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
                stile = BLUE;
            }
            kids.at(x)->setStyleSheet(stile);
            kids.at(y)->setStyleSheet(GREY);
            kids.clear();
            return;
        }
        if(alla[n]->getITrain()!=0)
        {
            alla[n]->setStyleSheet(BLUE);
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
    QCoreApplication::processEvents();
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
            Ukosna=0;
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
            if(canIgo==NULLO || canIgo==STRAIGHT || Ukosna!=0) //dla blokow ukosnych, ide zgodnie z wtl ale jak null do w prawo
            {
                Ukosna=0;
                n++;
            }
            else
            {
                Ukosna++;
                n=n-LUNGHEZZA;
            }
            return n;
        }
        else if(bloktype==7) //blok ukosny gora od prawej strony
        {
            canIgo = alla[n+LUNGHEZZA]->getWTL();
            if(canIgo==NULLO || canIgo==STRAIGHT || Ukosna!=0)
            {
                Ukosna=0;
                n++;
            }
            else
            {
                Ukosna++;
                n=n+LUNGHEZZA;
            }
            return n;
        }
        else if (tmpWTL==UP)
        {
            if(bloktype==3)
            {
                Ukosna=0;
                n++;
                return n;
            }
            Ukosna++;
            n=n-LUNGHEZZA;
            return n;
        }
        else if(tmpWTL==DOWN)
        {
            if(bloktype==4)
            {
                Ukosna=0;
                n++;
                return n;
            }
            Ukosna++;
            n=n+LUNGHEZZA;
            return n;
        }
    }
    else
    {
        Ukosna=0;
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
            Ukosna=0;
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
            if(canIgo==NULLO || canIgo==STRAIGHT || Ukosna!=0) //dla blokow ukosnych, ide zgodnie z wtl ale jak null do w prawo
            {
                Ukosna=0;
                n--;
            }
            else
            {
                Ukosna++;
                n=n+LUNGHEZZA;
            }
            return n;
        }
        else if(bloktype==5) //blok ukosny gora od lewej strony
        {
            canIgo = alla[n+LUNGHEZZA]->getWTL();
            if(canIgo==NULLO || canIgo==STRAIGHT || Ukosna!=0)
            {
                Ukosna=0;
                n--;
            }
            else
            {
                Ukosna++;
                n=n-LUNGHEZZA;
            }
            return n;
        }
        else if (tmpWTL==UP)
        {
            if(bloktype==1)
            {
                Ukosna=0;
                n--;
                return n;
            }
            Ukosna++;
            n=n-LUNGHEZZA;
            return n;
        }
        else if(tmpWTL==DOWN)
        {
            if(bloktype==2)
            {
                Ukosna=0;
                n--;
                return n;
            }
            Ukosna++;
            n=n+LUNGHEZZA;
            return n;
        }
    }
    else
    {
        Ukosna=0;
        return -2;
    }
}

int Widget::WhatTrainThere(int n)
{
    int i;
    int temp;
    for(i=0;i<CIUF;i++)
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
        clean(n,GREEN);
    }
    else
    {
        clean(n,GREY);
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
    if(zwnum==-1)
    {
        zwnum = ZwDw->getpos(n);
        if(zwnum==-1)
        {
            qDebug("Zwrotnica nie istnieje!");
            return;
        }
        zwnum=zwnum+RAILPGZ;
    }
    //int nrCiuf;
    QList<int>* gridTrain;
    bool check=Zwrotnice[zwnum]->isChecked();
    //Zwrotnice[zwnum]->setDisabled(true);
    if(check==true)
    {
        Zwrotnice[zwnum]->setDown(true);
    }
    else
    {
        Zwrotnice[zwnum]->setDown(false);
    }
    //QThread::msleep(500);
    alla[n]->setWTL();
    clean(n,YELLOW);

    if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
    {
        cleanAdjacent(gridTrain->at(0),GREY);
    }
    if((gridTrain=IsTrainOnThere(Perony))->isEmpty()==false)
    {
        cleanAdjacent(gridTrain->at(0),GREY);
        ReversecleanAdjacent(gridTrain->at(0),GREY);
    }
    if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
    {
        ReversecleanAdjacent(gridTrain->at(0),GREY);
    }
    WyznaczTrase();
    //Zwrotnice[zwnum]->setDisabled(false);
}

void Widget::PZwChange(int n)
{
    int zwnum = PZwUp->getpos(n);
    if(zwnum==-1)
    {
        zwnum = PZwDw->getpos(n);
        if(zwnum==-1)
        {
            qDebug("Zwrotnica nie istnieje!");
            return;
        }
        zwnum=zwnum+RAILPGZ;
    }
    //int nrCiuf;
    QList<int>* gridTrain;
    bool check=PZwrotnice[zwnum]->isChecked();
    //PZwrotnice[zwnum]->setDisabled(true);
    if(check==true)
    {
        PZwrotnice[zwnum]->setDown(true);
    }
    else
    {
        PZwrotnice[zwnum]->setDown(false);
    }
    //QThread::msleep(500);
    alla[n]->setWTL();
    clean(n,YELLOW);

    if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
    {
        cleanAdjacent(gridTrain->at(0),GREY);
    }
    if((gridTrain=IsTrainOnThere(Perony))->isEmpty()==false)
    {
        cleanAdjacent(gridTrain->at(0),GREY);
        ReversecleanAdjacent(gridTrain->at(0),GREY);
    }
    if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
    {
        ReversecleanAdjacent(gridTrain->at(0),GREY);
    }
    WyznaczTrase();
    //PZwrotnice[zwnum]->setDisabled(false);
}

void Widget::SemaforChanged(int n)
{
    int num = TrainCan->getpos(n);
    int peron, delciuf;
    QList<int>* gridTrain;
    if(alla[n]->getITrain())
    {
        int trainnr = WhatTrainThere(n);
        if(IsTrainOnThere(Perony)->isEmpty()==false)
        {
            Ciuf[trainnr]->setPredkosc(40); //SET TO 40
            sella[num]->setColor(3);
        }
        else
        {
            Ciuf[trainnr]->setPredkosc(100);
            sella[num]->setColor(4);
        }
        if((Ciuf[trainnr]->getDirection())==1)
        {
            //Podajemy z AKTUALNYM bloczku znajdywania sie pociagu!!
            if(TrasaPociag(n,trainnr,WHITE))
            {

                if((peron=IsIn(Ciuf[trainnr]->getCoords(),End,ALTEZZA))!=-1)
                {
                    delciuf = WhatTrainThere(End[peron]);
                    decrementCiuf(delciuf);
                    clean(End[peron],GREY);
                    ReversecleanAdjacent(Perony[peron],GREY);
                }


            }
        }
        else if((Ciuf[trainnr]->getDirection())==2)
        {
            if(ReverseTrasaPociag(n,trainnr,WHITE))
            {
                //qDebug("Reverse Trasa");
                if((peron=IsIn(Ciuf[trainnr]->getCoords(),Start,ALTEZZA))!=-1)
                {
                    delciuf = WhatTrainThere(End[peron]);
                    decrementCiuf(delciuf);
                    clean(Start[peron],GREY);
                    cleanAdjacent(Start[peron],GREY);
                }

            }
        }

        if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
        {
            cleanAdjacent(gridTrain->at(0),GREY);
        }
        if((gridTrain=IsTrainOnThere(Perony))->isEmpty()==false)
        {
            cleanAdjacent(gridTrain->at(0),GREY);
            ReversecleanAdjacent(gridTrain->at(0),GREY);
        }
        if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
        {
            ReversecleanAdjacent(gridTrain->at(0),GREY);
        }
        WyznaczTrase();

        sella[num]->setColor(0);
    }
    else
    {
        qDebug("Nie ma pociagu");
    }
}

void Widget::Train(int n)
{
    int zwnum = TrainCan->getpos(n);
    int dirCiuf;
    QList<int>* gridTrain;
    bool check=GenTrain[zwnum]->isChecked();
    if(zwnum==-1)
    {
        return;
    }
    //GenTrain[zwnum]->setDisabled(true);
    if(check==true)
    {
        GenTrain[zwnum]->setDown(true);
        if(alla[n]->getITrain()==0)
        {
            if(zwnum<TRAIN/2)
            {
                dirCiuf=1;
            }
            else
            {
                dirCiuf=2;
            }
            incrementCiuf(n,dirCiuf);
            alla[n]->setITrain();
        }

        if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
        {
            cleanAdjacent(gridTrain->at(0),GREY);
        }
        if((gridTrain=IsTrainOnThere(Perony))->isEmpty()==false)
        {
            cleanAdjacent(gridTrain->at(0),GREY);
            ReversecleanAdjacent(gridTrain->at(0),GREY);
        }
        if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
        {
            ReversecleanAdjacent(gridTrain->at(0),GREY);
        }
        WyznaczTrase();
        //GenTrain[zwnum]->setDisabled(false);
    }
    else
    {
        GenTrain[zwnum]->setDown(false);
    }
}

void Widget::ObslugaPeronu(int p)
{
    //TYMCZASOWA GENERACJA POCIAGU DO DEBAGOWANIA//
    //Pociag::increment();
    //alla[n]->setITrain();
    //Ciuf[Pociag::getQuanto()-1]->setDirection(1);
    //Ciuf[Pociag::getQuanto()-1]->setCoords(n);
    //clean(n,"background color: grey");
    //---//
    int n = OtherGen->GetThat(p);
    int delciuf;
    //int zwnum = OtherGen->getpos(n); //rowniez indeks przycisku semafora (mozna sprawdzic czy obsluguje lewa/prawa strone)
    int peron;
    QList<int>* gridTrain;
    if(alla[n]->getITrain())
    {
        int trainnr = WhatTrainThere(n);
        Ciuf[trainnr]->setPredkosc(100);


        if(p%2!=0)
        {
            if((Ciuf[trainnr]->getDirection())==1) //==1 w prawo, ==2 w lewo
            {
                Osella[p]->setColor(4);
                alla[n]->setITrain();
                QThread::msleep(trasaTime(trainnr,n)*1000);
                alla[n+1]->setITrain();
                clean(n,GREY);
                QCoreApplication::processEvents();
                QThread::msleep(TrainTime(trainnr)*1000);
                clean(n+1,GREY);
                QCoreApplication::processEvents();
                QThread::msleep(trasaTime(trainnr,n+1)*1000);

                //Podajemy z NASTEPUJACYM bloczku znajdywania sie pociagu!!
                TrasaPociag(n+1,trainnr,WHITE);

                if((peron=IsIn(Ciuf[trainnr]->getCoords(),End,ALTEZZA))!=-1)
                {
                    delciuf = WhatTrainThere(End[peron]);
                    decrementCiuf(delciuf);
                    alla[End[peron]]->setITrain();
                    clean(End[peron],GREY);
                    ReversecleanAdjacent(End[peron],GREY);
                }
                Osella[p]->setColor(0);

            }
        }
        else if(p%2==0)
        {
            if((Ciuf[trainnr]->getDirection())==2)
            {
                Osella[p]->setColor(4);
                alla[n]->setITrain();
                QThread::msleep(trasaTime(trainnr,n)*1000);
                alla[n-1]->setITrain();
                clean(n,GREY);
                QCoreApplication::processEvents();
                QThread::msleep(TrainTime(trainnr)*1000);
                clean(n-1,GREY);
                QCoreApplication::processEvents();
                QThread::msleep(trasaTime(trainnr,n+1)*1000);
                //qDebug("Reverse Trasa");
                //Podajemy z NASTEPUJACYM bloczku znajdywania sie pociagu!!
                ReverseTrasaPociag(n-1,trainnr,WHITE);

                if((peron=IsIn(Ciuf[trainnr]->getCoords(),Start,ALTEZZA))!=-1)
                {
                    delciuf = WhatTrainThere(Start[peron]);
                    decrementCiuf(delciuf);
                    alla[Start[peron]]->setITrain();
                    clean(Start[peron],GREY);
                    cleanAdjacent(Start[peron],GREY);
                }
                Osella[p]->setColor(0);
            }
        }

        if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
        {
            cleanAdjacent(gridTrain->at(0),GREY);
        }
        if((gridTrain=IsTrainOnThere(Perony))->isEmpty()==false)
        {
            cleanAdjacent(gridTrain->at(0),GREY);
            ReversecleanAdjacent(gridTrain->at(0),GREY);
        }
        if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
        {
            ReversecleanAdjacent(gridTrain->at(0),GREY);
        }
        WyznaczTrase();
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

void Widget::WyznaczTrase()
{
    int nrCiuf;
    QList<int>* gridTrain;
    if((gridTrain=IsTrainOnThere(Start))->isEmpty()==false)
    {
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
            nrCiuf = WhatTrainThere(gridTrain->at(nn));
            if(nrCiuf!=-1)
            {
                if(Ciuf[nrCiuf]->getDirection()==1)
                {
                    //qDebug("TRASA W PRAWO START"); //wzgledem gridTrain
                    Trasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
                }
            }
        }
    }
    if((gridTrain=IsTrainOnThere(Perony))->isEmpty()==false)
    {
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
            nrCiuf = WhatTrainThere(gridTrain->at(nn));
            if(nrCiuf!=-1)
            {
                if(Ciuf[nrCiuf]->getDirection()==1)
                {
                    //qDebug("TRASA W PRAWO PERON"); //wzgledem gridTrain
                    Trasa(gridTrain->at(nn)+1,'w',alla[gridTrain->at(nn)]->getITrain());
                }
                if(Ciuf[nrCiuf]->getDirection()==2)
                {
                    //qDebug("TRASA W LEWO PERON");
                    ReverseTrasa(gridTrain->at(nn)-1,'w',alla[gridTrain->at(nn)]->getITrain());
                }
            }
        }
    }
    if((gridTrain=IsTrainOnThere(End))->isEmpty()==false)
    {
        for(int nn=0; nn<gridTrain->count(); nn++)
        {
            nrCiuf = WhatTrainThere(gridTrain->at(nn));
            if(nrCiuf!=-1)
            {
                if(Ciuf[nrCiuf]->getDirection()==2)
                {
                    //qDebug("TRASA W LEWO END");
                    ReverseTrasa(gridTrain->at(nn),'w',alla[gridTrain->at(nn)]->getITrain());
                }
            }
        }
    }
}

void Widget::decrementCiuf(int num)
{
    Ciuf[num]->setCoords(0);
    Ciuf[num]->setPredkosc(0);
    Pociag::decrement();
}

void Widget::incrementCiuf(int coord, int dir)
{
    Pociag::increment();
    int i, allapos;
    for(i=0;i<CIUF;i++)
    {
        if(Ciuf[i]->getCoords()==0 && Ciuf[i]->getPredkosc()==0)
        {
            Ciuf[i]->setCoords(coord);
            Ciuf[i]->setDirection(dir);
            return;
        }
    }
    allapos=Ciuf[0]->getCoords();
    alla[allapos]->setITrain();
    clean(allapos,GREY);
    Ciuf[0]->setCoords(coord);
    Ciuf[0]->setDirection(dir);
}
