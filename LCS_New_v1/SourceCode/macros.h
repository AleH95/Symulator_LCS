#ifndef MACROS_H
#define MACROS_H

#define LUNGHEZZA 35 //Ilosc torow w poziomie
#define ALTEZZA 10 //Ilosc torow w pionie

#define STRAIGHT "Straight"
#define UP "Up"
#define DOWN "Down"
#define NULLO "Null"

#define LZWROTNICE 4 //Ilosc przyciskow zwrotnic w poziomie
#define AZWROTNICE 5 //Ilosc przyciskow zwrotnic w pionie

#define LSEMAFORY 2 //Ilosc przyciskow semaforow w poziomie
#define ASEMAFORY 2 //Ilosc przyciskow semaforow w pioni

#define PERON 16 //Na ktorej kolumnje sie znajduej Peron (po ilu bloczkach)

#define STARTX 0 //Pozycja pozioma Pojawiania sie pociagu
#define STARTY 2 //Pozycja pionowa Pojawiania sie pociagu

#define FINISHX 4
#define FINISHY 2

#define START (STARTY*LUNGHEZZA)+STARTX //Coords 2,0 = 0*LUNGHEZZA+2
#define FINISH (FINISHY*LUNGHEZZA)+FINISHX

#define TRAIN 4 //Ilosc punktow generujacych pociagi

#define SEM 4 //Ilosc semaforow Wejsciowe + Wyjsciowe
#define SEMPER 14

//--------UWAGA: N+M musi byc rowne AZWROTNICE*LZWROTNICE!!-------
#define UZW 2 //ilosc zwrotnic typu Up
#define DZW 1 //ilosc zwrotnicc typu Down

//Klasa do obslugi Torow typu:
//    0.Tor
//    1.Zwrotnica Gorna
//    2.Zwrotnica Dolna

//<------------
#define RAILROADS 108
#define RAILROADO 46
#define RAILLG 13
#define RAILPG 13
#define RAILLD 10
#define RAILPD 10

#define RAILLGZ 5
#define RAILPGZ 5
#define RAILLDZ 8
#define RAILPDZ 8
//<----------

//----Colors for StyleSheet--------//
#define GREY "QLabel { background-color: grey }"
#define YELLOW "QLabel { background-color: yellow }"
#define BLUE "QLabel { background-color: blue }"
#define WHITE "QLabel { background-color: white }"
#define GREEN "QLabel { background-color: green }"
#define RED "QLabel { background-color: red }"

#endif // MACROS_H
