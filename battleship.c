#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//functie care intitializeaza modul curses
void initializeazaCurses()
{
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    keypad(stdscr,TRUE);
}
//functie care citeste stringuri dintr-un fisier si le afiseaza ca sa dea impresia unei imagini
void printimage(char *numefisier,int coloana)
{
    int i=0;
    char *sir;
    sir=(char *)malloc(100*sizeof(char));
    FILE *fisier;
    fisier=fopen(numefisier,"r");
    //in cazul in care nu s-a deschis fisierul
    if(fisier==NULL)
    {
        mvprintw(8,20,":P nu s-a deschis imaginea");
        mvprintw(12,20,"Apasa o tasta pt a continua");
        refresh();
        //astept sa se apese o tasta pt a curge mai frumos programul
        getch();
    }
    else
    //daca s-a deschis fisierul
    {
        while(fgets(sir,100,fisier)!=NULL)
        {
            mvprintw(i,coloana,"%s",sir);
            i++;
        }
    }
    //inchid fisierul si eliberez memoria folosita
    fclose(fisier);
    refresh();
    free(sir);
}
//funtie de randomizare a unui grid, in functie de numarul de nave de fiecare tip
void randomizemap(char **A,int n4,int n3,int n2,int n1)
{
    int i,j,k,ok,margini;
    //variabila pt a determina daca sa pun nava orizontal sau vertical
    int horvert;
    //pun navele de dimensiune 4
    while(n4>0)
    {
        //iau o variabila ok si verific daca sunt restrictii
        ok=1;
        //aleg un punct random
        i=rand()%10;
        j=rand()%10;
        //1 daca e orizontal 0 daca e vertical
        horvert=rand()%2;
        if(horvert==1)
        {
            //incerc sa pun in dreapta
            if(j<=6)
            {
                for(k=0;k<4;k++)
                {
                    A[i][j+k]='X';
                }
            }
            //daca nu,pun in stanga
            else
            {
                for(k=0;k<4;k++)
                {
                    A[i][j-k]='X';
                }
            }
        }
        if(horvert==0)
        {
            //incerc sa pun in jos
            if(i<=6)
            {
                for(k=0;k<4;k++)
                {
                    A[i+k][j]='X';
                }
            }
            //daca nu, pun in sus
            else
            {
                for(k=0;k<4;k++)
                {
                    A[i-k][j]='X';
                }
            }
        }
        //daca a pus nava scad numarul de nave de dim 4 care trbuie puse
        n4--;
    }
    //pun navele de dimensiune 3
    while(n3>0)
    {
        //iau variabila ok, daca nu se poate se face ok=0
        ok=1;
        margini=0;
        i=rand()%10;
        j=rand()%10;
        if(i==0||i==9||j==0||j==9)
        {
            margini=1;
        }
        if(margini==0)
        {
            //verific casuta random si casutele din jur
            if(A[i][j]=='X'||A[i-1][j-1]=='X'||A[i-1][j]=='X'||A[i-1][j+1]=='X'||A[i][j-1]=='X')
            {
                //incalca restrictia 
                ok=0;
            }
            if(A[i][j+1]=='X'||A[i+1][j-1]=='X'||A[i+1][j]=='X'||A[i+1][j+1]=='X')
            {
                //incalca restrictia
                ok=0;
            }
            if(ok==1)
            {
                //1 daca e orizontal 0 daca e vertical
                horvert=rand()%2;
                if(horvert==1)
                {
                    //incerc sa le pun spre stanga
                    if(j>=3)
                    {
                        //verific daca sunt probleme de pozitionare la stanga
                        if(A[i-1][j-2]=='X'||A[i][j-2]=='X'||A[i+1][j-2]=='X')
                        {
                            ok=0;
                        }
                        if(A[i-1][j-3]=='X'||A[i][j-3]=='X'||A[i+1][j-3]=='X')
                        {
                            ok=0;
                        }
                        //le pun la stanga
                        if(ok==1)
                        {
                            for(k=0;k<3;k++)
                            {
                                A[i][j-k]='X';
                            }
                            //daca se poate pune nava si scade nr 
                            //de nave de pus de dimensiune 3
                            n3--;
                        }
                    }
                    //incerc sa le pun la dreapta
                    else
                    {
                        //verific daca se poate
                        if(A[i-1][j+2]=='X'||A[i][j+2]=='X'||A[i+1][j+2]=='X')
                        {
                            ok=0;
                        }
                        if(A[i-1][j+3]=='X'||A[i][j+3]=='X'||A[i+1][j+3]=='X')
                        {
                            ok=0;
                        }
                        //le pun la dreapta
                        if(ok==1)
                        {
                            for(k=0;k<3;k++)
                            {
                                A[i][j+k]='X';
                            }
                            n3--;
                        }
                    }
                }
                if(horvert==0)
                {
                    //incerc sa le pun spre sus
                    if(i>=3)
                    {
                        //verific daca sunt probleme de pozitionare in sus
                        if(A[i-2][j-1]=='X'||A[i-2][j]=='X'||A[i-2][j+1]=='X')
                        {
                            ok=0;
                        }
                        if(A[i-3][j-1]=='X'||A[i-3][j]=='X'||A[i-3][j+1]=='X')
                        {
                            ok=0;
                        }
                        //le pun in sus
                        if(ok==1)
                        {
                            for(k=0;k<3;k++)
                            {
                                A[i-k][j]='X';
                            }
                            n3--;
                        }
                    }
                    //incerc sa le pun in jos
                    else
                    {
                        //verific daca se poate
                        if(A[i+2][j-1]=='X'||A[i+2][j]=='X'||A[i+2][j+1]=='X')
                        {
                            ok=0;
                        }
                        if(A[i+3][j-1]=='X'||A[i+3][j]=='X'||A[i+3][j+1]=='X')
                        {
                            ok=0;
                        }
                        //le pun la dreapta
                        if(ok==1)
                        {
                            for(k=0;k<3;k++)
                            {
                                A[i+k][j]='X';
                            }
                            n3--;
                        }
                    }
                }
            }
        }
    }
    //pun navele de dimensiune 2
    while(n2>0)
    {
        ok=1;
        margini=0;
        //verific un punct random
        i=rand()%10;
        j=rand()%10;
        if(i==0||i==9||j==0||j==9)
        {
            margini=1;
        }
        if(margini==0)
        {
            //verific casuta random si casutele din jur
            if(A[i][j]=='X'||A[i-1][j-1]=='X'||A[i-1][j]=='X'||A[i-1][j+1]=='X'||A[i][j-1]=='X')
            {
                ok=0;
            }
            if(A[i][j+1]=='X'||A[i+1][j-1]=='X'||A[i+1][j]=='X'||A[i+1][j+1]=='X')
            {
                ok=0;
            }
            if(ok==1)
            {
                //1 daca e orizontal 0 daca e vertical
                horvert=rand()%2;
                if(horvert==1)
                {
                    //incerc sa le pun spre stanga
                    if(j>=2)
                    {
                        //verific daca sunt probleme de pozitionare la stanga
                        if(A[i-1][j-2]=='X'||A[i][j-2]=='X'||A[i+1][j-2]=='X')
                        {
                            ok=0;
                        }
                        //le pun la stanga
                        if(ok==1)
                        {
                            for(k=0;k<2;k++)
                            {
                                A[i][j-k]='X';
                            }
                            //daca se poate pun nava si scad nr de nave de pus
                            n2--;
                        }
                    }
                    //incerc sa le pun la dreapta
                    else
                    {
                        //verific daca se poate
                        if(A[i-1][j+2]=='X'||A[i][j+2]=='X'||A[i+1][j+2]=='X')
                        {
                            ok=0;
                        }
                        //le pun la dreapta
                        if(ok==1)
                        {
                            for(k=0;k<2;k++)
                            {
                                A[i][j+k]='X';
                            }
                            n2--;
                        }
                    }
                }
                if(horvert==0)
                {
                    //incerc sa le pun spre sus
                    if(i>=2)
                    {
                        //verific daca sunt probleme de pozitionare in sus
                        if(A[i-2][j-1]=='X'||A[i-2][j]=='X'||A[i-2][j+1]=='X')
                        {
                            ok=0;
                        }
                        //le pun in sus
                        if(ok==1)
                        {
                            for(k=0;k<2;k++)
                            {
                                A[i-k][j]='X';
                            }
                            n2--;
                        }
                    }
                    //incerc sa le pun in jos
                    else
                    {
                        //verific daca se poate
                        if(A[i+2][j-1]=='X'||A[i+2][j]=='X'||A[i+2][j+1]=='X')
                        {
                            ok=0;
                        }
                        //le pun la dreapta
                        if(ok==1)
                        {
                            for(k=0;k<2;k++)
                            {
                                A[i+k][j]='X';
                            }
                            n2--;
                        }
                    }
                }
            }
        }
    }
    //pun navele de dimensiune 1
    while(n1>0)
    {
        ok=1;
        margini=0;
        i=rand()%10;
        j=rand()%10;
        if(i==0||i==9||j==0||j==9)
        {
            //verific daca e pe margini pentru a explicita mai bine cazurile
            margini=1;
        }
        if(margini==0)
        {
            //verific casuta random si casutele din jur
            if(A[i][j]=='X'||A[i-1][j-1]=='X'||A[i-1][j]=='X'||A[i-1][j+1]=='X'||A[i][j-1]=='X')
            {
                ok=0;
            }
            if(A[i][j+1]=='X'||A[i+1][j-1]=='X'||A[i+1][j]=='X'||A[i+1][j+1]=='X')
            {
                ok=0;
            }
            if(ok==1)
            {
                A[i][j]='X';
                n1--;
            }
        }
        if(margini==1)
        {
            //iau toate cazurile posibile pt a compara doar ce este 
            //in grid pt a nu da segmentation fault (sa nu ies din grid)
            if(i==0&&j==0)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i+1][j]=='X'||A[i][j+1]=='X'||A[i+1][j+1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
            else if(i==0&&j==9)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i+1][j]=='X'||A[i][j-1]=='X'||A[i+1][j-1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
            else if(i==9&&j==0)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i-1][j]=='X'||A[i][j+1]=='X'||A[i-1][j+1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
            else if(i==9&&j==9)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i-1][j]=='X'||A[i][j-1]=='X'||A[i-1][j-1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
            else if(i==0)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i+1][j]=='X'||A[i][j+1]=='X'||A[i][j-1]=='X'||A[i+1][j-1]=='X'||A[i+1][j+1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
            else if(i==9)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i-1][j]=='X'||A[i][j+1]=='X'||A[i][j-1]=='X'||A[i-1][j-1]=='X'||A[i-1][j+1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
            else if(j==0)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i+1][j]=='X'||A[i][j+1]=='X'||A[i-1][j]=='X'||A[i+1][j+1]=='X'||A[i-1][j+1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
            else if(j==9)
            {
                //verific casuta si cele din jur
                if(A[i][j]=='X'||A[i+1][j]=='X'||A[i][j-1]=='X'||A[i-1][j]=='X'||A[i+1][j-1]=='X'||A[i-1][j-1]=='X')
                {
                    ok=0;
                }
                if(ok==1)
                {
                    A[i][j]='X';
                    n1--;
                }
            }
        }
    }
}
//functie pentru a stabili harta jucatorului
void hartaplayer(int argc, char **argv, char **player,int *sadeschisfisier)
{
    //eliberez fereastra pt a pune meniul de alegere a mapei
    clear();
    char *sir;
    sir=(char *)malloc(12*sizeof(char));
    int input,i,j;
    int alegere=1;
    //deschid fisierul si citesc din el linie cu linie apoi le afisez 
    //in fereastra pt a oferi jucatorului un preview la harta
    FILE *fisier3;
    fisier3=fopen(argv[alegere],"r");
    if(fisier3!=NULL)
    {
        for(i=0;i<10;i++)
        {
            fgets(sir,12,fisier3);
            for(j=0;j<10;j++)
            {
                mvprintw(i,j,"%c",sir[j]);
            }
        }
        fclose(fisier3);
    }
    //imi afiseaza textul si numele fisierului curent (alegerea curenta)
    mvprintw(5,20,"Alegerea curenta");
    mvprintw(7,20,"%s",argv[alegere]);
    mvprintw(10,20,"Apasati sagetile pt a alege harta jucatorului");
    mvprintw(11,20,"Apasati r pt a alege o harta random");
    mvprintw(12,20,"Apasati enter pt a selecta optiunea");
    move(10,11);
    refresh();
    //iau inputul cat timp nu e apasat enter (confirmarea alegerii)
    input=getch();
    while(input!='\n')
    {
        switch(input)
        {
            case KEY_UP:
                if(alegere>1) alegere--;
                break;
            case KEY_DOWN:
                if(alegere<(argc-1)) alegere++;
                break;
            case 'r':
                alegere=0;
                break;
            default:
                break;
        }
        if(alegere!=0)
        {
            //pt a vedea alegerea curenta repet algoritmul de afisare a mapei
            clear();
            FILE *fisier2;
            fisier2=fopen(argv[alegere],"r");
            if(fisier2!=NULL)
            {
                for(i=0;i<10;i++)
                {
                    fgets(sir,12,fisier2);
                    for(j=0;j<10;j++)
                    {
                        mvprintw(i,j,"%c",sir[j]);
                    }
                }
                fclose(fisier2);
            }
            mvprintw(5,20,"Alegerea curenta");
            mvprintw(7,20,"%s",argv[alegere]);
            mvprintw(10,20,"Apasati sagetile pt a alege harta jucatorului");
            mvprintw(11,20,"Apasati r pt a alege o harta random");
            mvprintw(12,20,"Apasati enter pt a selecta optiunea");
            move(10,11);
            refresh();
        }
        if(alegere==0)
        {
            //sau in cazul in care e random se precizeaza alegerea
            clear();
            mvprintw(5,20,"Alegerea curenta");
            mvprintw(7,20,"random");
            mvprintw(10,20,"Apasati sageata jos pt a va intoarce la hartile prestabilite");
            mvprintw(11,20,"Apasati r pt a alege o harta random");
            mvprintw(12,20,"Apasati enter pt a selecta optiunea");
            move(10,11);
            refresh();
        }
        input=getch();
    }
    *sadeschisfisier=0;
    //verifica daca alegerea e random, daca da randomizeaza harta playerului
    if(alegere==0)
    {
        randomizemap(player,1,2,3,4);
    }
    //sau face harta dupa modelul din fisier
    else
    {
        FILE *fisier;
        fisier=fopen(argv[alegere],"r");
        //verifica daca s-a deschis fisierul
        if(fisier==NULL)
        {
            clear();
            mvprintw(10,30,"Fisierul %s nu poate fi deschis",argv[alegere]);
            refresh();
            sleep(3);
            endwin();
            *sadeschisfisier=1;
        }
        //daca s-a deschis face mapa jucatorului
        else
        {
            for(i=0;i<10;i++)
            {
                fgets(sir,12,fisier);
                for(j=0;j<10;j++)
                {
                    player[i][j]=sir[j];
                }
            }
            fclose(fisier);
        }
    }
    free(sir);
}
//functia pentru meniul principal al jocului
//returneaza 0 pt New Game, 1 pt Resume Game si 2 pt Quit
int meniu(int *muzica)
{
    clear();
    int input;
    int alegere=0;
    //imi pune imaginea(titlul jocului)
    //imi afiseaza optiunile
    printimage("image4.txt",15);
    mvprintw(10,30,"New Game *");
    mvprintw(12,30,"Resume Game");
    mvprintw(14,30,"Quit");
    mvprintw(20,0,"Pentru muzica apasati tasta m");
    if((*muzica)==0)
    {
        mvprintw(21,0,"Music OFF");
    }
    if((*muzica)==1)
    {
        mvprintw(21,0,"Music ON");
    }
    move(0,0);
    refresh();
    input=getch();
    //imi verifica inputul
    while(input!='\n')
    {
        switch(input)
        {
            case KEY_UP:
                if(alegere==1||alegere==2) alegere--;
                break;
            case KEY_DOWN:
                if(alegere==0||alegere==1) alegere++;
                break;
            case 'm':
                if((*muzica)==1)
                {
                    (*muzica)=0;
                }
                else
                {
                    (*muzica)=1;   
                }
                break;
            default:
                break;
        }
        //in funtie de alegere afisez optiunea cu o steluta in dreptul ei
        if(alegere==0)
        {
            clear();
            printimage("image4.txt",15);
            mvprintw(10,30,"New Game *");
            mvprintw(12,30,"Resume Game");
            mvprintw(14,30,"Quit");
            mvprintw(20,0,"Pentru muzica apasati tasta m");
            if((*muzica)==0)
            {
                mvprintw(21,0,"Music OFF");
            }
            if((*muzica)==1)
            {
                mvprintw(21,0,"Music ON");
            }
            move(0,0);
            refresh();
        }
        if(alegere==1)
        {
            clear();
            printimage("image4.txt",15);
            mvprintw(10,30,"New Game");
            mvprintw(12,30,"Resume Game *");
            mvprintw(14,30,"Quit");
            mvprintw(20,0,"Pentru muzica apasati tasta m");
            if((*muzica)==0)
            {
                mvprintw(21,0,"Music OFF");
            }
            if((*muzica)==1)
            {
                mvprintw(21,0,"Music ON");
            }
            move(0,0);
            refresh();
        }
        if(alegere==2)
        {
            clear();
            printimage("image4.txt",15);
            mvprintw(10,30,"New Game");
            mvprintw(12,30,"Resume Game");
            mvprintw(14,30,"Quit *");
            mvprintw(20,0,"Pentru muzica apasati tasta m");
            if((*muzica)==0)
            {
                mvprintw(21,0,"Music OFF");
            }
            if((*muzica)==1)
            {
                mvprintw(21,0,"Music ON");
            }
            move(0,0);
            refresh();
        }
        input=getch();
    }
    return alegere;
}
//funtie de alocat dinamic o matrice
void alocdinamicmaps(char ***A)
{
    (*A)=(char **)malloc(10*sizeof(char *));
    int i,j;
    for(i=0;i<10;i++)
    {
        (*A)[i]=(char *)malloc(11*sizeof(char));
    }
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            (*A)[i][j]='.';
        }
    }
}
//functie pentru matricea calculatorului din timpul jocului (computer 2)
//matricea pe care o afisez
void computerinjoc(char ***A)
{
    (*A)=(char **)malloc(10*sizeof(char *));
    int i,j;
    for(i=0;i<10;i++)
    {
        (*A)[i]=(char *)malloc(11*sizeof(char));
    }
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            //imi afiseaza space pt a simula fog of war
            (*A)[i][j]=' ';
        }
    }
}
//funtie care verifica daca jocul s-a terminat
//returneaza 0 daca jocul nu s-a terminat, 1 daca a castigat jucatorul
//2 daca a castigat computerul si 3 daca e remiza
int gameover(char **player,char **computer,char **computer2)
{
    int i,j,playerlife,computerlife;
    playerlife=0;
    computerlife=0;
    //verific daca exista parti de barca intacte 
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(player[i][j]=='X')
            {
                //daca gaseste cel putin un X inseamna ca 
                //jucatorul mai are cel putin o nava 
                playerlife=1;
                break;
            }
        }
    }
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(computer[i][j]=='X')
            {
                computerlife=1;
                break;
            }
        }
    }
    //jocul nu s-a terminat
    if(playerlife==1&&computerlife==1)
    {
        return 0;
    }
    //remiza
    if(playerlife==0&&computerlife==0)
    {
        return 3;
    }
    //a castigat playerul
    if(playerlife==1&&computerlife==0)
    {
        return 1;
    }
    //a castigat computerul
    return 2;
}
//functie care afiseaza hartile si borders
void harti(char **player, char **computer,char **computer2)
{
    clear();
    int i,j;
    //imi afiseaza granitele care sunt caracterele - si |
    for(i=1;i<11;i++)
    {
        mvprintw(i,0,"|");
        mvprintw(i,11,"|");
        mvprintw(0,i,"-");
        mvprintw(11,i,"-");
    }
    for(i=1;i<11;i++)
    {
        mvprintw(i,15,"|");
        mvprintw(i,26,"|");
    }
    for(i=16;i<26;i++)
    {
        mvprintw(0,i,"-");
        mvprintw(11,i,"-");
    }
    //afiseaza caracterele de pe matricele player si computer 2
    for(i=1;i<11;i++)
    {
        for(j=1;j<11;j++)
        {
            mvprintw(i,j,"%c",computer2[i-1][j-1]);
        }
    }
    for(i=1;i<11;i++)
    {
        for(j=1;j<11;j++)
        {
            mvprintw(i,j+15,"%c",player[i-1][j-1]);
        }
    }
    //afisez care matrice a cui este
    mvprintw(12,2,"Computer");
    mvprintw(12,18,"Player");
    refresh();
}
//verifica daca au mai ramas casute libere
//funtie ajutatoare pt destroy in advance
//returneaza 1 daca mai sunt casute libere (care nu au fost incercate) 
//si 0 daca nu
int maisuntcasutelibere(char **A)
{
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(A[i][j]=='X'||A[i][j]=='.')
            {
                return 1;
            }
        }
    }
    return 0;
}
//abilitatea destroy in advance
void destroyinadvance(char **player,char **computer,char **computer2)
{
    int i,j;
    int ok;
    int computerhits=10;
    int playerhits=10;
    while(computerhits>0)
    {
        //verifica daca sunt casute libere pt a nu intra in bucla infinita
        if(maisuntcasutelibere(player)==1)
        {
            ok=0;
            while(ok==0)
            {
                i=rand()%10;
                j=rand()%10;
                //schimba ce a gasit in caracterele corespunzatoare
                if(player[i][j]=='X')
                {
                    ok=1;
                    player[i][j]='D';
                }
                if(player[i][j]=='.')
                {
                    ok=1;
                    player[i][j]='M';
                }
            }
            //daca ok=1 se pune ca lovitura si scade din cate lovituri mai sunt
            computerhits--;
        }
        //daca nu sunt locuri libere scade computerhits pt a iesi din while
        else computerhits--;
    }
    //acelasi lucru cand ataca jucatorul
    while(playerhits>0)
    {
        if(maisuntcasutelibere(computer)==1)
        {
            ok=0;
            while(ok==0)
            {
                i=rand()%10;
                j=rand()%10;
                if(computer[i][j]=='X')
                {
                    ok=1;
                    computer[i][j]='D';
                    computer2[i][j]='D';
                }
                if(computer[i][j]=='.')
                {
                    ok=1;
                    computer[i][j]='M';
                    computer2[i][j]='M';
                }
            }
            playerhits--;
        }
        else playerhits--;
    }
}
//funtie pt a verifica cate nave mai sunt
//ajuta la abilitatea randomizare dar si cu score-ul la finalul jocului
void catenavemaisunt(char **A,int *n4,int *n3,int *n2,int *n1)
{
    int i,j,lungime,ok,k;
    *n4=0;
    *n3=0;
    *n2=0;
    *n1=0;
    //parcurge pe verticala 
    for(j=0;j<10;j++)
    {
        for(i=0;i<10;i++)
        {
            //daca gaseste o bucata de nava se uita sa nu fie in spate sau in 
            //lateral alte bucati de nava cu ajutorul unui contor ok
            if(A[i][j]=='X')
            {
                ok=1;
                if(i>0&&A[i-1][j]=='X')
                {
                    ok=0;
                }
                if(j>0&&(A[i][j-1]=='X'||A[i][j-1]=='D'))
                {
                    ok=0;
                }
                if(j<9&&(A[i][j+1]=='X'||A[i][j+1]=='D'))
                {
                    ok=0;
                }
                k=1;
                //calculeaza lungimea navei pt a tine cont 
                //cate sunt din fiecare fel de nava
                lungime=1;
                if(ok==1)
                {
                    while(i+k<10&&(A[i+k][j]=='X'||A[i+k][j]=='D'))
                    {
                        if(A[i+k][j]=='X')
                        {
                            lungime++;
                        }
                        k++;
                    }
                }
                i+=k-1;
                if(lungime==2)
                {
                    *n2=*n2+1;
                }
                if(lungime==3)
                {
                    *n3=*n3+1;
                }
                if(lungime==4)
                {
                    *n4=*n4+1;
                }
            }
        }
    }
    //acum parcurge matricea orizontal pt a verifica toate modurile de asezare
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(A[i][j]=='X')
            {
                //verifica sa nu fie pe verticala bucati de nava
                ok=1;
                if(j>0&&A[i][j-1]=='X')
                {
                    ok=0;
                }
                if(i>0&&(A[i-1][j]=='X'||A[i-1][j]=='D'))
                {
                    ok=0;
                }
                if(i<9&&(A[i+1][j]=='X'||A[i+1][j]=='D'))
                {
                    ok=0;
                }
                k=1;
                //vede lungimea navei
                lungime=1;
                if(ok==1)
                {
                    while(j+k<10&&(A[i][j+k]=='X'||A[i][j+k]=='D'))
                    {
                        if(A[i][j+k]=='X')
                        {
                            lungime++;
                        }
                        k++;
                    }
                }
                j+=k-1;
                //ia in calcul nava gasita in functie de lungime
                if(lungime==2)
                {
                    *n2=*n2+1;
                }
                if(lungime==3)
                {
                    *n3=*n3+1;
                }
                if(lungime==4)
                {
                    *n4=*n4+1;
                }
            }
        }
    }
    //cauta navele de dimensiune 1
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(A[i][j]=='X')
            {
                ok=1;
                if(i>0&&(A[i-1][j]=='X'||A[i-1][j]=='D'))
                {
                    ok=0;
                }
                if(i<9&&(A[i+1][j]=='X'||A[i+1][j]=='D'))
                {
                    ok=0;
                }
                if(j>0&&(A[i][j-1]=='X'||A[i][j-1]=='D'))
                {
                    ok=0;
                }
                if(j<9&&(A[i][j+1]=='X'||A[i][j+1]=='D'))
                {
                    ok=0;
                }
                if(ok==1)
                {
                    *n1=*n1+1;
                }
            }
        }
    }
}
//functia de randomizare mid game, abilitate care ofera avantaj jucatorului
//funtia in sine verifica cate nave mai sunt, initializeaza iar matricea si 
//pune '.' iar apoi o randomizeaza cu numarul de nave gasite transmise prin
//parametrii
void randomizemidgame(char **player)
{
    int n4,n3,n2,n1,i,j;
    n4=0;
    n3=0;
    n2=0;
    n1=0;
    catenavemaisunt(player,&n4,&n3,&n2,&n1);
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            player[i][j]='.';
        }
    }
    randomizemap(player,n4,n3,n2,n1);
}
//functie facuta pt a oferi jucatorului posibilitatea de a ataca random
void randomshot(char **computer,char **computer2,int *playerhit)
{
    int i,j,ok;
    ok=0;
    //am luat variabila pt a verifica daca atacul este unul valid sau nu
    //daca a atacat intr-un loc care deja a fost ales
    while(ok==0)
    {
        i=rand()%10;
        j=rand()%10;
        if(computer[i][j]=='.'||computer[i][j]=='X')
        {
            ok=1;
        }
        if(ok==1)
        {
            //in functie de ce a gasit, apa sau bucata de nava va pune 
            //caracterul corespunzator
            if(computer[i][j]=='.')
            {
                computer2[i][j]='M';
                computer[i][j]='M';
                mvprintw(i+1,j+1,"M");
                mvprintw(16,0,"                              ");
                mvprintw(16,0,"Ai ratat");
                move(i+1,j+1);
                refresh();
                sleep(1.5);
                *playerhit=0;
            }
            if(computer[i][j]=='X')
            {
                computer2[i][j]='D';
                computer[i][j]='D';
                mvprintw(i+1,j+1,"D");
                mvprintw(16,0,"                              ");
                mvprintw(16,0,"Ai nimerit, mai loveste o data");
                move(i+1,j+1);
                refresh();
                sleep(1.5);
                *playerhit=1;
            }
        }
    }
}
//functia in care este propriu zis jocul, implementarea sa
void joaca(char **player,char **computer,char **computer2,int *quit,int *lasthiti,int *lasthitj,int *lasthithorvert,int *final)
{
    int input,i,j,playerhit,computerhit,k,abilitate;
    //coordonatele sa imi puna la inceput cursorul si de unde pornesc calculele
    i=1;
    j=1;
    //variabile prin care sa verific daca continua fie jucatorul fie computerul
    playerhit=1;
    computerhit=1;
    while(playerhit==1)
    {
        mvprintw(15,0,"                             ");
        mvprintw(15,0,"Este randul tau!");
        move(i,j);
        refresh();
        input=getch();
        //verific daca este folosita vreo abilitate
        abilitate=0;
        while(input!='\n'&&input!='q'&&input!='d'&&input!='r'&&input!='x')
        {
            switch(input)
            {
                case KEY_UP:
                    if(i!=1) i--;
                    break;
                case KEY_DOWN:
                    if(i!=10) i++;
                    break;
                case KEY_RIGHT:
                    if(j!=10) j++;
                    break;
                case KEY_LEFT:
                    if(j!=1) j--;
                    break;
                default:
                    break;
            }
            move(i,j);
            refresh();
            input=getch();
        }
        //verific fiecare caz,quit,randomize,destroy in advance,randomshot 
        if(input=='q')
        {
            input='\n';
            *quit=1;
            playerhit=0;
            computerhit=0;
        }
        if(input=='x')
        {
            input='\n';
            abilitate=1;
            randomshot(computer,computer2,&playerhit);
        }
        if(input=='r')
        {
            input='\n';
            playerhit=0;
            computerhit=0;
            abilitate=1;
            randomizemidgame(player);
            harti(player,computer,computer2);
            mvprintw(16,0,"                              ");
            mvprintw(16,0,"Ai folosit randomizare");
            refresh();
            sleep(1.5);
        }
        if(input=='d')
        {
            input='\n';
            playerhit=0;
            abilitate=1;
            computerhit=0;
            destroyinadvance(player,computer,computer2);
            harti(player,computer,computer2);
            mvprintw(16,0,"                              ");
            mvprintw(16,0,"Ai folosit destroy in advance");
            refresh();
            sleep(1.5);
        }
        //verific pentru normal shot
        if(*quit==0&&abilitate==0)
        {
            if(computer[i-1][j-1]=='.'||computer[i-1][j-1]=='M'||computer[i-1][j-1]=='D')
            {
                playerhit=0;
                if(computer[i-1][j-1]=='.')
                {
                    computer2[i-1][j-1]='M';
                    computer[i-1][j-1]='M';
                    mvprintw(i,j,"M");
                    mvprintw(16,0,"                              ");
                    mvprintw(16,0,"Ai ratat");
                    refresh();
                }
            }
            if(computer[i-1][j-1]=='X')
            {
                computer2[i-1][j-1]='D';
                computer[i-1][j-1]='D';
                mvprintw(i,j,"D");
                mvprintw(16,0,"                              ");
                mvprintw(16,0,"Ai nimerit, mai loveste o data");
                move(i,j);
                refresh();
            }
        }
        //verifica daca jocul a fost terminat sau nu
        if(gameover(player,computer,computer2)!=0)
        {
            input='\n';
            *quit=1;
            playerhit=0;
            computerhit=0;
        }
    }
    //e randul computerului sa atace
    while(computerhit==1)
    {
        mvprintw(15,0,"                             ");
        mvprintw(15,0,"Este randul calculatorului");
        //in cazul in care nu a fost lovita o nava inainte ataca random
        if((*lasthiti)==-1&&(*lasthitj)==-1)
        {
            i=rand()%10;
            j=rand()%10;
            move(i+1,j+16);
            refresh();
            //pune corespunzator in locul in care a atacat
            if(player[i][j]=='.')
            {
                computerhit=0;
                player[i][j]='M';
                mvprintw(i+1,j+16,"M");
                mvprintw(16,0,"                              ");
                mvprintw(16,0,"Missed");
                move(i+1,j+16);
                refresh();
                sleep(2);
            }
            if(player[i][j]=='X')
            {
                player[i][j]='D';
                mvprintw(i+1,j+16,"D");
                mvprintw(16,0,"                              ");
                mvprintw(16,0,"Hit");
                move(i+1,j+16);
                refresh();
                sleep(2);
                //daca a nimerit retine coordonatele pentru 
                //strategia de a cauta in jurul locului nimerit
                (*lasthiti)=i;
                (*lasthitj)=j;
            }
        }
        //daca a fost nimerit un loc
        //am folosit variabila lasthithorver (horizontal/vertical) pentru a nu
        //verifica toate directiile din ultimul loc lovit
        if((*lasthiti)!=-1&&(*lasthitj)!=-1)
        {
            //cauta in susul locului nimerit
            if(computerhit==1&&(*lasthithorvert)!=1)
            {
                k=1;
                //cat timp se poate(exista un 'X') trage in sus
                while((*lasthiti)-k>=0&&(player[(*lasthiti)-k][(*lasthitj)]=='X'||player[(*lasthiti)-k][(*lasthitj)]=='D'))
                {
                    if(player[(*lasthiti)-k][(*lasthitj)]=='X')
                    {
                        player[(*lasthiti)-k][(*lasthitj)]='D';
                        mvprintw((*lasthiti)-k+1,(*lasthitj)+16,"D");
                        mvprintw(16,0,"                              ");
                        mvprintw(16,0,"Hit");
                        move((*lasthiti)-k+1,(*lasthitj)+16);
                        refresh();
                        sleep(2);
                        (*lasthithorvert)=0;
                    }
                    k++;
                }
                computerhit=0;
                //cand a "ratat" verifica daca nu e o ratare falsa, fie 
                //un loc in afara griduli sau un loc deja incercat
                if(((*lasthiti)-k>=0&&(player[(*lasthiti)-k][(*lasthitj)]=='M'||player[(*lasthiti)-k][(*lasthitj)]=='D'))||(*lasthiti)-k==-1)
                {
                    //daca a fost fals ratat computerul trage iar
                    computerhit=1;
                }
                //daca nu a fost fals ratat pune in locul locului atacat 'M'
                //simbolul de atac ratat
                if((*lasthiti)-k>=0&&computerhit==0)
                {
                    player[(*lasthiti)-k][(*lasthitj)]='M';
                    mvprintw((*lasthiti)-k+1,(*lasthitj)+16,"M");
                    mvprintw(16,0,"                              ");
                    mvprintw(16,0,"Missed");
                    move((*lasthiti)-k+1,(*lasthitj)+16);
                    refresh();
                    sleep(2);
                }
            }
            //verifica aceleasi lucrui pentru in dreapta locului lovit
            if(computerhit==1&&(*lasthithorvert)!=0)
            {
                k=1;
                while((*lasthitj)+k<10&&(player[(*lasthiti)][(*lasthitj)+k]=='X'||player[(*lasthiti)][(*lasthitj)+k]=='D'))
                {
                    if(player[(*lasthiti)][(*lasthitj)+k]=='X')
                    {
                        player[(*lasthiti)][(*lasthitj)+k]='D';
                        mvprintw((*lasthiti)+1,(*lasthitj)+k+16,"D");
                        mvprintw(16,0,"                              ");
                        mvprintw(16,0,"Hit");
                        move((*lasthiti)+1,(*lasthitj)+k+16);
                        refresh();
                        sleep(2);
                        (*lasthithorvert)=1;
                    }
                    k++;
                }
                computerhit=0;
                //cand a ratat
                if(((*lasthitj)+k<10&&(player[(*lasthiti)][(*lasthitj)+k]=='M'||player[(*lasthiti)][(*lasthitj)+k]=='D'))||(*lasthitj)+k==10)
                {
                    computerhit=1;
                }
                if((*lasthitj)+k<10&&computerhit==0)
                {
                    player[(*lasthiti)][(*lasthitj)+k]='M';
                    mvprintw((*lasthiti)+1,(*lasthitj)+k+16,"M");
                    mvprintw(16,0,"                              ");
                    mvprintw(16,0,"Missed");
                    move((*lasthiti)+1,(*lasthitj)+k+16);
                    refresh();
                    sleep(2);
                }
            }
            //acelasi lucru in josul ultimului loc lovit
            if(computerhit==1&&(*lasthithorvert)!=1)
            {
                k=1;
                while((*lasthiti)+k<10&&(player[(*lasthiti)+k][(*lasthitj)]=='X'||player[(*lasthiti)+k][(*lasthitj)]=='D'))
                {
                    if(player[(*lasthiti)+k][(*lasthitj)]=='X')
                    {
                        player[(*lasthiti)+k][(*lasthitj)]='D';
                        mvprintw((*lasthiti)+k+1,(*lasthitj)+16,"D");
                        mvprintw(16,0,"                              ");
                        mvprintw(16,0,"Hit");
                        move((*lasthiti)+k+1,(*lasthitj)+16);
                        refresh();
                        sleep(2);
                        (*lasthithorvert)=0;
                    }
                    k++;
                }
                computerhit=0;
                //cand a ratat
                if(((*lasthiti)+k<10&&(player[(*lasthiti)+k][(*lasthitj)]=='M'||player[(*lasthiti)+k][(*lasthitj)]=='D'))||(*lasthiti)+k==10)
                {
                    computerhit=1;
                }
                if((*lasthiti)+k<10&&computerhit==0)
                {
                    player[(*lasthiti)+k][(*lasthitj)]='M';
                    mvprintw((*lasthiti)+k+1,(*lasthitj)+16,"M");
                    mvprintw(16,0,"                              ");
                    mvprintw(16,0,"Missed");
                    move((*lasthiti)+k+1,(*lasthitj)+16);
                    refresh();
                    sleep(2);
                }
                //daca nava a fost identificata ca fiind pe verticala asta e 
                //ultima verificare pe care o face computerul
                if((*lasthithorvert)==0)
                {
                    (*final)=1;
                }
            }
            //acelasi algoritm in stanga ultimului loc lovit
            if(computerhit==1&&(*lasthithorvert)!=0)
            {
                k=1;
                while((*lasthitj)-k>=0&&(player[(*lasthiti)][(*lasthitj)-k]=='X'||player[(*lasthiti)][(*lasthitj)-k]=='D'))
                {
                    if(player[(*lasthiti)][(*lasthitj)-k]=='X')
                    {
                        player[(*lasthiti)][(*lasthitj)-k]='D';
                        mvprintw((*lasthiti)+1,(*lasthitj)-k+16,"D");
                        mvprintw(16,0,"                              ");
                        mvprintw(16,0,"Hit");
                        move((*lasthiti)+1,(*lasthitj)-k+16);
                        refresh();
                        sleep(2);
                        (*lasthithorvert)=1;
                    }
                    k++;
                }
                (*final)=1;
                computerhit=0;
                //daca a ratat
                if(((*lasthitj)-k>=0&&(player[(*lasthiti)][(*lasthitj)-k]=='M'||player[(*lasthiti)][(*lasthitj)-k]=='D'))||(*lasthitj)-k==-1)
                {
                    computerhit=1;
                }
                if((*lasthitj)-k>=0&&computerhit==0)
                {
                    player[(*lasthiti)][(*lasthitj)-k]='M';
                    mvprintw((*lasthiti)+1,(*lasthitj)-k+16,"M");
                    mvprintw(16,0,"                              ");
                    mvprintw(16,0,"Missed");
                    move((*lasthiti)+1,(*lasthitj)-k+16);
                    refresh();
                    sleep(2);
                }
            }
            //daca a terminat de verificat pune variabilele de last hit astfel
            //incat sa traga random urmatoarea data
            if((*final)==1)
            {
                (*lasthiti)=-1;
                (*lasthitj)=-1;
                (*lasthithorvert)=-1;
                (*final)=0;
            }
        }
    }
}
//tin cont de argumente pentru functia de harta a jucatorului
//functia main returneaza 1 daca au fost erori la deschiderea unor fisiere sau
//daca nu s-au dat argumente si 0 daca totul s-a iesit din program fara erori
int main(int argc, char **argv)
{
    //declar matricile folosite pe care le voi aloca dinamic
    char **player,**computer,**computer2;
    //iau diferite variabile pe care fie le trimit cu pointeri la functii spre
    //a le modifica, fie pentru a face trcerea dintr-o parte a meniului la alta
    int alegere,game,i,sadeschisfisier,quit,lasthiti,lasthitj,lasthithorvert,final,n4,n3,n2,n1,dezalocamatrice,muzica;
    //variabila pt a stii daca trebuie eliberata memoria la finalul jocului
    muzica=0;
    dezalocamatrice=0;
    final=0;
    game=0;
    //1 daca e orizontal 0 daca e vertical
    lasthithorvert=-1;
    lasthiti=-1;
    lasthitj=-1;
    //se intitializeaza modul curses
    initializeazaCurses();
    //in cazul in care nu s-au dat argumente
    if(argc==1)
    {
        clear();
        mvprintw(10,20,"Nu s-au dat argumente!");
        refresh();
        sleep(3);
        endwin();
        return 1;
    }
    //initializez pt a folosi functia rand
    srand(time(NULL));
    //folosesc prima data meniul
    alegere=meniu(&muzica);
    //daca alegerea e 2 atunci este optiunea quit si nu e nevoie sa intre in
    //jocul propriu zis
    while(alegere!=2)
    {
        //daca se da new game
        if(alegere==0)
        {
            //se genereaza matricile apoi in fctia harti se printeaza hartile
            game=1;
            dezalocamatrice=1;
            quit=0;
            alocdinamicmaps(&player);
            alocdinamicmaps(&computer);
            computerinjoc(&computer2);
            hartaplayer(argc,argv,player,&sadeschisfisier);
            //daca e eroare la deschiderea fisierului iese din joc, returneaza1
            if(sadeschisfisier==1)
            {
                return 1;
            }
            randomizemap(computer,1,2,3,4);
            harti(player,computer,computer2);
            //cat timp jocul de e gata se apeleaza funtia de joc dupa care se
            //actualizeaza hartile
            while(gameover(player,computer,computer2)==0&&quit==0)
            {
                joaca(player,computer,computer2,&quit,&lasthiti,&lasthitj,&lasthithorvert,&final);
                harti(player,computer,computer2);
            }
            //daca a castigat playerul
            if(gameover(player,computer,computer2)==1)
            {
                clear();
                mvprintw(6,30,"Ai castigat! :)");
                catenavemaisunt(computer,&n4,&n3,&n2,&n1);
                mvprintw(9,10,"Ai doborat %d nave",(10-n4-n3-n2-n1));
                catenavemaisunt(player,&n4,&n3,&n2,&n1);
                mvprintw(9,40,"Computerul a doborat %d nave",(10-n4-n3-n2-n1));
                mvprintw(12,22,"Apasa o tasta pt a continua");
                refresh();
                getch();
                clear();
                //se afiseaza o imagine sugestiva castigului
                printimage("image1.txt",0);
                getch();
                clear();
                if(muzica==1)
                {
                    system("rhythmbox win.mp3");
                }
            }
            //daca a castigat computerul
            if(gameover(player,computer,computer2)==2)
            {
                clear();
                mvprintw(6,30,"Ai pierdut :(");
                catenavemaisunt(computer,&n4,&n3,&n2,&n1);
                mvprintw(9,10,"Ai doborat %d nave",(10-n4-n3-n2-n1));
                catenavemaisunt(player,&n4,&n3,&n2,&n1);
                mvprintw(9,40,"Computerul a doborat %d nave",(10-n4-n3-n2-n1));
                mvprintw(12,22,"Apasa o tasta pt a continua");
                refresh();
                getch();
                clear();
                //se afiseaza o imagine corespunzatoare
                printimage("image2.txt",0);
                getch();
                clear();
                if(muzica==1)
                {
                    system("rhythmbox lose.mp3");
                }
            }
            //daca e remiza
            if(gameover(player,computer,computer2)==3)
            {
                clear();
                mvprintw(6,30,"Remiza :/");
                catenavemaisunt(computer,&n4,&n3,&n2,&n1);
                mvprintw(9,10,"Ai doborat %d nave",(10-n4-n3-n2-n1));
                catenavemaisunt(player,&n4,&n3,&n2,&n1);
                mvprintw(9,40,"Computerul a doborat %d nave",(10-n4-n3-n2-n1));
                mvprintw(12,22,"Apasa o tasta pt a continua");
                refresh();
                getch();
                clear();
                //se afiseaza o imagine sugestiva
                printimage("image3.txt",0);
                getch();
                clear();
                if(muzica==1)
                {
                    system("rhythmbox remiza.mp3");
                }
            }
            alegere=meniu(&muzica);
        }
        //in cazul in care se reia jocul, Resume Game
        if(alegere==1)
        {
            quit=0;
            //se verifica daca un joc a fost inceput
            if(game==1)
            {
                if(gameover(player,computer,computer2)!=0)
                {
                    game=0;
                }
            }
            //daca nu, afisez acest lucru
            if(game==0)
            {
                clear();
                mvprintw(10,20,"Un joc nou nu a fost inceput!");
                refresh();
                sleep(3);
                alegere=meniu(&muzica);
            }
            //daca da, reiau din punctul anterior facand aceleasi lucruri ca
            //atunci cand este alegerea=0, alegerea precedenta (apelurile
            //functiilor de joc si de afisare a celor 2 matrice)
            if(game==1)
            {
                harti(player,computer,computer2);
                while(gameover(player,computer,computer2)==0&&quit==0)
                {
                    joaca(player,computer,computer2,&quit,&lasthiti,&lasthitj,&lasthithorvert,&final);
                    harti(player,computer,computer2);
                }
                if(gameover(player,computer,computer2)==1)
                {
                    clear();
                    mvprintw(6,30,"Ai castigat! :)");
                    catenavemaisunt(computer,&n4,&n3,&n2,&n1);
                    mvprintw(9,10,"Ai doborat %d nave",(10-n4-n3-n2-n1));
                    catenavemaisunt(player,&n4,&n3,&n2,&n1);
                    mvprintw(9,40,"Computerul a doborat %d nave",(10-n4-n3-n2-n1));
                    mvprintw(12,22,"Apasa o tasta pt a continua");
                    refresh();
                    getch();
                    clear();
                    printimage("image1.txt",0);
                    getch();
                    clear();
                    if(muzica==1)
                    {
                        system("rhythmbox win.mp3");
                    }
                }
                if(gameover(player,computer,computer2)==2)
                {
                    clear();
                    mvprintw(6,30,"Ai pierdut :(");
                    catenavemaisunt(computer,&n4,&n3,&n2,&n1);
                    mvprintw(9,10,"Ai doborat %d nave",(10-n4-n3-n2-n1));
                    catenavemaisunt(player,&n4,&n3,&n2,&n1);
                    mvprintw(9,40,"Computerul a doborat %d nave",(10-n4-n3-n2-n1));
                    mvprintw(12,22,"Apasa o tasta pt a continua");
                    refresh();
                    getch();
                    clear();
                    printimage("image2.txt",0);
                    getch();
                    clear();
                    if(muzica==1)
                    {
                        system("rhythmbox lose.mp3");
                    }
                }
                if(gameover(player,computer,computer2)==3)
                {
                    clear();
                    mvprintw(6,30,"Remiza :/");
                    catenavemaisunt(computer,&n4,&n3,&n2,&n1);
                    mvprintw(9,10,"Ai doborat %d nave",(10-n4-n3-n2-n1));
                    catenavemaisunt(player,&n4,&n3,&n2,&n1);
                    mvprintw(9,40,"Computerul a doborat %d nave",(10-n4-n3-n2-n1));
                    mvprintw(12,22,"Apasa o tasta pt a continua");
                    refresh();
                    getch();
                    clear();
                    printimage("image3.txt",0);
                    getch();
                    clear();
                    if(muzica==1)
                    {
                        system("rhythmbox remiza.mp3");
                    }
                }
            alegere=meniu(&muzica);
            }
        }
    }
    //daca se ajunge aici, a fost selectata optiunea quit
    //verific daca s-a intrat in New Game, adica daca s-au alocat dinamic
    //matricile iar daca da, le eliberez
    if(dezalocamatrice==1)
    {
        for(i=0;i<10;i++)
        {
            free(player[i]);
            free(computer[i]);
            free(computer2[i]);
        }
        free(player);
        free(computer);
        free(computer2);
    }
    //inchid modul cursez si ies din program dar nu inainte sa ascult o opera
    //de arta a epocii moderne
    if(muzica==1)
    {
        system("rhythmbox music.mp3");
    }
    clear();
    endwin();
    return 0;
}