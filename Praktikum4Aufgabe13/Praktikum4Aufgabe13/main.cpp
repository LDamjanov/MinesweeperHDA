#include <iostream>
#include <cstdio>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "kopf.h"

using namespace std;

void SpielfeldErstellen(int);
void Minenzaehlen(int);
void SpielfeldVerloren(int);
void SpfeldAnzeigen(int);
bool Entdecken(int,int,int);
void Feld_0(int,int,int);
void Aktualisieren(int);
bool gewinnenBool(int);
bool Markieren(int,int,int);

int schritte = 0;


int matrix[15][15];
char spielfeld[15][15];
char SpielfeldAnzeigen[15][15];



void Menu()
{
    int auswahl;
    do
    {

        cout << "\nWilkommen bei Minesweeper\n" << endl;
        cout <<"(1) Anleitung\n(2) Spielen\n(3) Highscores\n(4) Beenden\n\n";
        cin >> auswahl;
                switch (auswahl)
                {
                case 1:
                    cout<<"REGELN:"<<endl;
                    cout<<"1. Die Groesse des Spielfeldes muss ein Wert zwischen 6 und 15 sein."<<endl;
                    cout<<"2. Du darfst keine Bombe treffen."<<endl;
                    cout<<"3. Spaß haben."<<endl;
                    cout<<endl;
                    break;
                case 2:{

                    int feld = 0;
                    srand(time(NULL));

                    cout<<"     ------------- Minesweeper -------------"<<endl;
                    cout<<endl;
                    cout<<endl;

                    cout<<"--> Geben Sie die Groesse des Spielfelds an: ";
                    cin>>feld;
                    cout<<endl;

                    while (feld < 6 || feld > 15){
                    cout<<"Fehler! Geben Sie eine Zahl zwischen 6 und 15 ein."<<endl;
                    cout<<"--> Geben Sie die Groesse des Spielfelds an: ";
                    cin>>feld;
                    }

                    SpielfeldErstellen(feld);
                    Minenzaehlen(feld);
                    SpfeldAnzeigen(feld);
                    cout<<endl;
                    cout<<"Lass uns anfangen!"<<endl;
                    cout<<"--> Geben Sie die Koordinaten der Felder ein, die Sie auswaehlen moechten: "<<endl;
                    int reihe=0;
                    int spalte =0;
                    char charReihe;

                    cout<<"--> Geben Sie die Reihe an: ";
                    cin>>charReihe;
                    charReihe=toupper(charReihe);
                    reihe = charReihe - 64;
                    reihe=reihe-1;
                    cout<<"--> Geben Sie die Spalte an: ";
                    cin>>spalte;
                    spalte=spalte-1;
                    cout<<endl;

                    while(reihe<0 || reihe>feld-1 || spalte<0 || spalte>feld-1){
                    cout<<endl;
                    cout<<"Fehler: Koordinate außerhalb des Spielfelds "<<endl;
                    cout<<"--> Geben Sie die Reihe an: ";
                    cin>>charReihe;
                    charReihe=toupper(charReihe);
                    reihe = charReihe - 64;
                    reihe=reihe-1;
                    cout<<"--> Geben Sie die Spalte an: ";
                    cin>>spalte;
                    spalte=spalte-1;
                    cout<<endl;
                    }
                    bool EntdeckenBool=true;
                    bool Gewinnen=false;
                    cout<<"--> Falls sie Markieren wollen, schreiben sie: MARK "<<endl;
                    string mark;
                    cin >> mark;
                    if(mark == "MARK")
                    {
                        Markieren(feld,reihe,spalte);
                    }
                    else
                    {
                        EntdeckenBool=Entdecken(feld,reihe,spalte);
                    }
                    // EntdeckenBool=Entdecken(feld,reihe,spalte);
                    while (EntdeckenBool==true){
                        cout<<endl;
                        cout<<"--> Geben Sie die Reihe an: ";
                        cin>>charReihe;
                        charReihe=toupper(charReihe);
                        reihe = charReihe - 64;
                        reihe=reihe-1;
                        cout<<"--> Geben Sie die Spalte an: ";
                        cin>>spalte;
                        cout<<endl;
                        spalte=spalte-1;
                        cout<<"--> Falls sie Markieren wollen, schreiben sie: MARK. "<<endl;
                        cout<<"--> Falls sie Entdecken wollen, schreiben sie egal was anderes. "<<endl;
                        string mark;
                        cin >> mark;
                        if(mark == "MARK")
                        {
                            Markieren(feld,reihe,spalte);
                        }
                        else
                        {
                            EntdeckenBool=Entdecken(feld,reihe,spalte);
                        }
                        //EntdeckenBool=Entdecken(feld,reihe,spalte);
                        Gewinnen=gewinnenBool(feld);
                        if (Gewinnen==true){
                            cout<<endl;
                            cout<<"HERZLICHEN GLÜCKWUNSCH!! ... SIE HABEN DAS SPIEL GEWONNEN"<<endl;
                            EntdeckenBool=false;
                            cout<<endl;
                        }
                        /*
                        std::ifstream input("highscores.txt");
                        int highscore;
                        input >> highscore;
                        std::ofstream output("highscores.txt");
                        if(schritte > highscore)
                        {
                            output << schritte;
                        }
                        else
                        {
                            output << highscore;
                        }
                        cout << endl;
                        cout << "Dein Score: " << schritte << endl;
                        cout << "Bisheriger Highscore: " << highscore << endl;*/

                    }

                    break;}
                case 3:
                    cout << "Highscores:\n" << endl;
                    cout << "Top 10: " << endl;
                    Highscoreanzeigen();

                    break;
                case 4:
                    exit(0);
                    break;
                }

    } while (auswahl !=4);
}

int main ()
{
    Menu();
}

void SpielfeldErstellen(int feld){
    int reihen = 0;
    int spalten = 0;
    reihen=feld;
    spalten=feld;
    double k;
    k = (12 + rand()%(9)); //Anzahl an Minen wird hier randomisiert
    double Anteil;
    Anteil = (feld*feld)*(k/100);

    int anzahlMinen;
    anzahlMinen = Anteil;
    cout<<endl;
    cout<<"Anzahl der Minen im Spielfeld: "<<anzahlMinen<<endl;
    cout<<endl;

  for(int i=0; i<reihen; i++)
  {

  for(int j=0; j<spalten; j++)
  {
       matrix[i][j] = 7;
  }

 }

    for (int i=0; i<anzahlMinen; i++){ //Position der Minen wird hier randomisiert
    int posSpalten = rand()%(spalten);
    int posReihen = rand()%(reihen);
      if (matrix[posSpalten][posReihen]==7){
         matrix[posSpalten][posReihen]=9;
  }
  else{
            i--;
  }
   }
}

void Minenzaehlen(int feld){
    int reihen = 0;
    int spalten = 0;
    int cont = 0;
    reihen=feld;
    spalten=feld;

    //--------------------------------------------Die Ecken zählen-------------------------------------------------
    for(int i=0; i<reihen; i++) {
     for(int j=0; j<spalten; j++) {
        if ((i==0 && j==0)&& (matrix[i][j]!=9)){ //Zählen, wenn die Mine sich in der Ecke oben links befindet
            if (matrix[i][j+1] == 9){
            cont++;}
            if (matrix[i+1][j+1]==9){
            cont++;}
            if (matrix[i+1][j]==9){
            cont++;}

            matrix[i][j]=cont;
            cont=0;
        }
        else if ((i==0 && j==feld-1)&& (matrix[i][j]!=9)){ //Zählen wenn die Mine sich in der Ecke oben rechts befindet
            if (matrix[i][j-1] == 9){
            cont++;}
            if (matrix[i+1][j-1]==9){
            cont++;}
            if (matrix[i+1][j]==9){
            cont++;}

            matrix[i][j]=cont;
            cont=0;
        }
        else if ((i==feld-1 && j==0)&& (matrix[i][j]!=9)){ //Zählen, wenn die Mine sich in der Ecke unten links befindet
            if (matrix[i-1][j] == 9){
            cont++;}
            if (matrix[i-1][j+1]==9){
            cont++;}
            if (matrix[i][j+1]==9){
            cont++;}

            matrix[i][j]=cont;
            cont=0;
        }
        else if ((i==feld-1 && j==feld-1)&& (matrix[i][j]!=9)){ //Zählen, wenn die Mine sich in der Ecke unten rechts befindet
            if (matrix[i-1][j] == 9){
            cont++;}
            if (matrix[i-1][j-1]==9){
            cont++;}
            if (matrix[i][j-1]==9){
            cont++;}

            matrix[i][j]=cont;
            cont=0;
        }
        //Zählen in die Felder die keine Ecken sind.

        else if (i==0 && (matrix[i][j]!=9)){ //Zählen in Feld mitte oben
            if (matrix[i][j+1] == 9){
            cont++;}
            if (matrix[i+1][j+1]==9){
            cont++;}
            if (matrix[i+1][j]==9){
            cont++;}
            if (matrix[i][j-1] == 9){
            cont++;}
            if (matrix[i+1][j-1]==9){
            cont++;}
            matrix[i][j]=cont;
            cont=0;
        }
        else if (i==feld-1 && (matrix[i][j]!=9)){ //Zählen in Feld mitte unten
            if (matrix[i-1][j] == 9){
            cont++;}
            if (matrix[i-1][j+1]==9){
            cont++;}
            if (matrix[i][j+1]==9){
            cont++;}
            if (matrix[i-1][j-1]==9){
            cont++;}
            if (matrix[i][j-1]==9){
            cont++;}

            matrix[i][j]=cont;
            cont=0;
        }

        else if (j==0 && (matrix[i][j]!=9)){ //Zählen in Feld mitte links
            if (matrix[i-1][j] == 9){
            cont++;}
            if (matrix[i-1][j+1]==9){
            cont++;}
            if (matrix[i][j+1]==9){
            cont++;}
            if (matrix[i+1][j+1]==9){
            cont++;}
            if (matrix[i+1][j]==9){
            cont++;}

            matrix[i][j]=cont;
            cont=0;
        }

        else if (j==feld-1 && (matrix[i][j]!=9)){ //Zählen in Feld mitte rechts
            if (matrix[i-1][j] == 9){
            cont++;}
            if (matrix[i-1][j-1]==9){
            cont++;}
            if (matrix[i][j-1]==9){
            cont++;}
            if (matrix[i+1][j-1]==9){
            cont++;}
            if (matrix[i+1][j]==9){
            cont++;}

            matrix[i][j]=cont;
            cont=0;
        }
        else{//Zählen, wenn es sich um die Kästchen in der Mitte handelt.
            if (matrix[i][j]!=9){
                if (matrix[i-1][j] == 9){
                cont++;}
                if (matrix[i-1][j-1]==9){
                cont++;}
                if (matrix[i][j-1]==9){
                cont++;}
                if (matrix[i+1][j-1]==9){
                cont++;}
                if (matrix[i+1][j]==9){
                cont++;}
                if (matrix[i-1][j+1]==9){
                cont++;}
                if (matrix[i][j+1]==9){
                cont++;}
                if (matrix[i+1][j+1]==9){
                cont++;}
                matrix[i][j]=cont;
                cont=0;
            }
        }
        }
    }
    for(int i=0; i<reihen; i++) {
      for(int j=0; j<spalten; j++) {
        if (matrix[i][j]==9){
            spielfeld[i][j]='*';
          }
          else{
            spielfeld[i][j]=char(matrix[i][j]+48);
          }
      }
     }
}

void SpielfeldVerloren(int feld){ //Spielfeld wenn man verliert.
    for(int i=0; i<feld; i++) {
    for(int j=0; j<feld; j++) {
   cout<<spielfeld[i][j]<<" ";
  }
  cout<<endl;
 }

    cout<<"\nUeberstandene Schritte " << schritte <<endl;
    cout<<"Spiel Verloren, gib deine Name ein: " <<endl;
    string name;
    cin >> name;

    addscore(name,schritte);
    Highscoreanzeigen();
    schritte=0; //Bei Ende des Spiels "Schritte" wieder auf 0 setzen.

    return;
}

void SpfeldAnzeigen(int feld){
    int reihen=feld;
    int spalten=feld;

    for(int i=0; i<reihen; i++) {
      for(int j=0; j<spalten; j++) {
       SpielfeldAnzeigen[i][j]='#';
       cout<<SpielfeldAnzeigen[i][j]<<" ";
      }
      cout<<endl;
     }


}

bool Entdecken(int feld,int reihe,int spalte){
    int reihen=feld;
    int spalten=feld;

    while(reihen<0 || reihe>feld-1 || spalte<0 || spalte>feld-1){
        cout<<"Fehler! Koordinate außerhalb des Spielfeldes. "<<endl;
        cout<<"--> Geben Sie die Reihe an: ";
        cin>>reihe;
        reihe=reihe-1;
        cout<<"--> Geben Sie die Spalte an: ";
        cin>>spalte;
        spalte=spalte-1;
        cout<<endl;
    }

    if (spielfeld[reihe][spalte]=='0'){ //Aufdecken wenn Feld 0 Minen um sich hat.
        Feld_0(feld,reihe,spalte);
        Aktualisieren(feld);
        return true;
     }
    else if(spielfeld[reihe][spalte]!='*'){ // Aufdecken wenn keine Mine
        SpielfeldAnzeigen[reihe][spalte] =spielfeld[reihe][spalte] ;
        Aktualisieren(feld);
        return true;
    }
    else if(spielfeld[reihe][spalte]=='*'){ //Aufdecken wenn Mine (Spiel verloren)
        cout<<"Sie haben eine Mine getroffen. Das Spiel ist verloren."<<endl;
        cout<<endl;
        SpielfeldVerloren(feld);
        return false;
    }
}

bool Markieren(int feld, int reihe, int spalte){
    int reihen=feld;
    int spalten=feld;
    int flag_counter = 0;
    cout << "MARKIEREN" << endl;

    while(reihen<0 || reihe>feld-1 || spalte<0 || spalte>feld-1){
        cout<<"Fehler! Koordinate außerhalb des Spielfeldes. "<<endl;
        cout<<"--> Geben Sie die Reihe an: ";
        cin>>reihe;
        reihe=reihe-1;
        cout<<"--> Geben Sie die Spalte an: ";
        cin>>spalte;
        spalte=spalte-1;
        cout<<endl;
    }
    if(SpielfeldAnzeigen[reihe][spalte] != '#'){
       cout<<"Fehler! Das Feld wurde bereits aufgedeckt."<<endl;
       return false;
    }
    if(flag_counter >= 15) {
       cout<<"Fehler! Sie haben die maximale Anzahl an Flags platziert."<<endl;
       return false;
    }
    SpielfeldAnzeigen[reihe][spalte] = 'F';
    flag_counter++;
    Aktualisieren(feld);
    return true;
}

void Aktualisieren(int feld){
    for(int i=0; i<feld; i++) {
      for(int j=0; j<feld; j++) {

            cout<<SpielfeldAnzeigen[i][j]<<" ";
      }
      cout<<endl;
     }
    schritte++; //Zählt schritte hoch
}

void Feld_0(int feld,int reihe,int spalte){
    SpielfeldAnzeigen[reihe][spalte] =spielfeld[reihe][spalte] ;
//----------------------------------------------------Die Ecken zählen---------------------------------------------------------------------
    if (reihe==0 && spalte==0){ //Ecke oben links
        SpielfeldAnzeigen[reihe][spalte+1] =spielfeld[reihe][spalte+1] ;
        SpielfeldAnzeigen[reihe+1][spalte+1]=spielfeld[reihe+1][spalte+1];
        SpielfeldAnzeigen[reihe+1][spalte]=spielfeld[reihe+1][spalte];

    }

    else if (reihe==0 && spalte==feld-1){ //Ecke oben rechts
        SpielfeldAnzeigen[reihe][spalte-1] =spielfeld[reihe][spalte-1] ;
        SpielfeldAnzeigen[reihe+1][spalte-1]=spielfeld[reihe+1][spalte-1];
        SpielfeldAnzeigen[reihe+1][spalte]=spielfeld[reihe+1][spalte];
    }

    else if (reihe==feld-1 && spalte==0){ //Ecke unten links
        SpielfeldAnzeigen[reihe-1][spalte] =spielfeld[reihe-1][spalte] ;
        SpielfeldAnzeigen[reihe-1][spalte+1]=spielfeld[reihe-1][spalte+1];
        SpielfeldAnzeigen[reihe][spalte+1]=spielfeld[reihe][spalte+1];
    }

    else if (reihe==feld-1 && spalte==feld-1){ //Ecke unten rechts
        SpielfeldAnzeigen[reihe-1][spalte] =spielfeld[reihe-1][spalte] ;
        SpielfeldAnzeigen[reihe-1][spalte-1]=spielfeld[reihe-1][spalte-1];
        SpielfeldAnzeigen[reihe][spalte-1]=spielfeld[reihe][spalte-1];
    }

        //----------------------------------------------------Zählen der Felder die keine Ecken sind.---------------------------------------------------------------------
    else if (reihe==0){ //Feld mitte oben
        SpielfeldAnzeigen[reihe][spalte+1] =spielfeld[reihe][spalte+1] ;
        SpielfeldAnzeigen[reihe+1][spalte+1]=spielfeld[reihe+1][spalte+1];
        SpielfeldAnzeigen[reihe+1][spalte]=spielfeld[reihe+1][spalte];
        SpielfeldAnzeigen[reihe][spalte-1]=spielfeld[reihe][spalte-1];
        SpielfeldAnzeigen[reihe+1][spalte-1]=spielfeld[reihe+1][spalte-1];
    }

    else if (reihe==feld-1){ //Feld mitte unten
        SpielfeldAnzeigen[reihe-1][spalte] =spielfeld[reihe-1][spalte] ;
        SpielfeldAnzeigen[reihe-1][spalte+1]=spielfeld[reihe-1][spalte+1];
        SpielfeldAnzeigen[reihe][spalte+1]=spielfeld[reihe][spalte+1];
        SpielfeldAnzeigen[reihe-1][spalte-1]=spielfeld[reihe-1][spalte-1];
        SpielfeldAnzeigen[reihe][spalte-1]=spielfeld[reihe][spalte-1];
    }

    else if (spalte==0 ){ //Feld mitte links
        SpielfeldAnzeigen[reihe-1][spalte] =spielfeld[reihe-1][spalte] ;
        SpielfeldAnzeigen[reihe-1][spalte+1]=spielfeld[reihe-1][spalte+1];
        SpielfeldAnzeigen[reihe][spalte+1]=spielfeld[reihe][spalte+1];
        SpielfeldAnzeigen[reihe+1][spalte+1]=spielfeld[reihe+1][spalte+1];
        SpielfeldAnzeigen[reihe+1][spalte]=spielfeld[reihe+1][spalte];
    }

    else if (spalte==feld-1){ //Feld mitte rechts
        SpielfeldAnzeigen[reihe-1][spalte] =spielfeld[reihe-1][spalte] ;
        SpielfeldAnzeigen[reihe-1][spalte-1]=spielfeld[reihe-1][spalte-1];
        SpielfeldAnzeigen[reihe][spalte-1]=spielfeld[reihe][spalte-1];
        SpielfeldAnzeigen[reihe+1][spalte-1]=spielfeld[reihe+1][spalte-1];
        SpielfeldAnzeigen[reihe+1][spalte]=spielfeld[reihe+1][spalte];
    }

    else{//Feld mitte
        SpielfeldAnzeigen[reihe-1][spalte] =spielfeld[reihe-1][spalte] ;
        SpielfeldAnzeigen[reihe-1][spalte-1]=spielfeld[reihe-1][spalte-1];
        SpielfeldAnzeigen[reihe][spalte-1]=spielfeld[reihe][spalte-1];
        SpielfeldAnzeigen[reihe+1][spalte-1]=spielfeld[reihe+1][spalte-1];
        SpielfeldAnzeigen[reihe+1][spalte]=spielfeld[reihe+1][spalte];
        SpielfeldAnzeigen[reihe-1][spalte+1]=spielfeld[reihe-1][spalte+1];
        SpielfeldAnzeigen[reihe][spalte+1]=spielfeld[reihe][spalte+1];
        SpielfeldAnzeigen[reihe+1][spalte+1]=spielfeld[reihe+1][spalte+1];
    }

}
bool gewinnenBool(int feld){
    int cont=0;
    for(int i=0; i<feld; i++) {
      for(int j=0; j<feld; j++) {
       if ((SpielfeldAnzeigen[i][j]=='#' )&& (spielfeld[i][j]!='*')){
        cont++;
       }
      }
     }
    if(cont==0){
        return true;
    }
    else{
        return false;
    }
}


