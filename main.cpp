#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <queue>
#include <algorithm>

using namespace std;

int rozmiar;
int kwadrat = rozmiar*rozmiar;

char instrukcja_3[] = " 1 : 2 : 3 \n"
                      "...........\n"
                      " 4 : 5 : 6 \n"
                      "...........\n"
                      " 7 : 8 : 9 \n"
                      "\n\n\n";

char instrukcja_4[] = " 1 : 2 : 3 : 4 \n"
                      "...............\n"
                      " 5 : 6 : 7 : 8 \n"
                      "...............\n"
                      " 9 : 10: 11: 12\n"
                      "...............\n"
                      " 13: 14: 15: 16\n"
                      "\n\n\n";

char instrukcja_5[] = " 1 : 2 : 3 : 4 : 5 \n"
                      "...................\n"
                      " 6 : 7 : 8 : 9 : 10\n"
                      "...................\n"
                      " 11: 12: 13: 14: 15\n"
                      "...................\n"
                      " 16: 17: 18: 19: 20\n"
                      "...................\n"
                      " 21: 22: 23: 24: 25\n"
                      "\n\n\n";

queue <int> Os;
queue <int> Xs;

void plansza(char t[])
{
     for (int i = 1; i <= kwadrat; i++)
        {
            cout << " " << t[i] << " ";
            if (i % rozmiar)
                cout << ":";
            else if (i != kwadrat)
                cout << "\n\n";
            else cout << endl;
     }
}

bool wygraj(char t[], char z)
{
    if (rozmiar == 3)
    {
     bool a = false;

     for (int i=1; i<=7; i+=3) a |= ((t[i]==z) && (t[i+1]==z) && (t[i+2]==z));
     for (int i=1; i<=3; i++) a |= ((t[i]==z) && (t[i+3]==z) && (t[i+6]==z));
     a |= ((t[1]==z) && (t[5]==z) && (t[9]==z));
     a |= ((t[7]==z) && (t[5]==z) && (t[3]==z));

     if (a) return true;

     return false;
    }

    if (rozmiar == 4)
    {
     bool a = false;

     for (int i=1; i<=13; i+=4) a |= ((t[i]==z) && (t[i+1]==z) && (t[i+2]==z) && (t[i+3]==z));
     for (int i=1; i<=4; i++) a |= ((t[i]==z) && (t[i+4]==z) && (t[i+8]==z) && (t[i+12]==z));
     a |= ((t[1]==z) && (t[6]==z) && (t[11]==z) && (t[16]==z));
     a |= ((t[13]==z) && (t[10]==z) && (t[7]==z) && (t[4]==z));

     if (a) return true;

     return false;
    }

    if (rozmiar == 5)
    {
     bool a = false;

     for (int i=1; i<=21; i+=5) a |= ((t[i]==z) && (t[i+1]==z) && (t[i+2]==z) && (t[i+3]==z) && (t[i+4]==z));
     for (int i=1; i<=5; i++) a |= ((t[i]==z) && (t[i+5]==z) && (t[i+10]==z) && (t[i+15]==z) && (t[i+20]==z));
     a |= ((t[1]==z) && (t[7]==z) && (t[13]==z) && (t[19]==z) && (t[25]==z));
     a |= ((t[21]==z) && (t[17]==z) && (t[13]==z) && (t[9]==z) && (t[5]==z));

     if (a) return true;

     return false;
    }

}

bool remis(char t[])
{
     for (int i=1; i<=kwadrat; i++)
     {
         if (t[i]==' ')
         {
             return false;
         }
     }

     return true;
}

int wolneMiejsca (char t[])
{
    int miejsca = 0;

    for (int i = 1; i <= kwadrat; i++)
    {
       if (t[i]==' ')
       {
           miejsca++;
       }
    }

    return miejsca;
}

int ruchLosowy(char t[])
{
    int pozycja;
    int a = time(NULL);

    srand(a);

    do
    {
        pozycja = rand() % kwadrat + 1;
    }
    while ( (t[pozycja]!=' ') );

    return pozycja;
}

int minimax(char t[], char player, unsigned int poziom)
{
    int n;
    int m;
    int miejsca = wolneMiejsca(t);

    if (wygraj (t,player))
        return (player == 'X') ? 1 : -1;
    if (remis(t))
        return 0;

    if (15 < miejsca < 25)
    {
      if (poziom>7)
      {
         if (((player=='O') && (m<n)) || ((player=='X') && (m>n)))
         {
            n=m;
         }

         return n;
       }
    }
    else
    {
         if (poziom > 5)
         {
            if (( (player=='O') && (m < n)) || ((player=='X') && (m>n)) )
            {
               n = m;
            }
            return n;
         }
    }

    player = (player == 'X')
        ? 'O':'X';

    n = (player == 'X')? -kwadrat:kwadrat;

    for (int i=1; i<=kwadrat; i++)
    {
        if (t[i]==' ')
        {
           t[i] = player;
           m = minimax(t, player, poziom++);
           t[i] = ' ';
           if ( ((player=='O') && (m<n)) || ((player=='X') && (m>n)) )
           {
               n = m;
           }
        }
    }

    return n;
}

int komputer(char t[])
{
    int pozycja, m, mmx;
    mmx = -kwadrat;

     cout << "Oczekuj na ruch komputera..." << endl;

    for (int i = 1; i <= kwadrat; i++)
    {
        if (t[i] == ' ')
        {
           t[i] = 'X';
           m = minimax(t, 'X', 0);
           t[i] = ' ';

           if (m > mmx)
           {
                mmx = m;
                pozycja = i;
           }
        }
    }

    return pozycja;
}

void ruch(char t[], char &player, unsigned int licznik)
{
     int pozycja;

     if (player == 'O')
     {
        cout << endl << "=== RUCH GRACZA === --> ";
        cin >> pozycja;

        while ((pozycja < 1) && (pozycja > kwadrat))
        {
              cout << "Zly wybor.";
              cin >> pozycja;
        }

        while (t[pozycja] != ' ')
        {
              cout << "Zly wybor.";
              cin >> pozycja;
        }

        Os.push(pozycja);
     }
     else if (player == 'X')
     {
             if (licznik > 1)
                pozycja = komputer(t);
             else
             {
                  pozycja = ruchLosowy(t);
             }
             cout << "== RUCH KOMPUTERA ===" << pozycja << endl;

             Xs.push(pozycja);
     }

     if ((pozycja >= 1) && (pozycja <= kwadrat) && (t[pozycja]==' '))
     {
        t[pozycja] = player;
     }

     player = (player == 'O') ? 'X' : 'O';
}

int main()
{
    int n = 0;
    char t[26], odp, player;

    cout << "Wybierz rozmiar planszy" << endl << endl;
    cout << "3x3 (Wcisnij 3)" << endl;
    cout << "4x4 (Wcisnij 4)" << endl;
    cout << "5x5 (Wcisnij 5)" << endl << endl;
    cout << "Twoj wybor: ";
    cin >> rozmiar;

    if ( !((rozmiar == 3) || (rozmiar == 4) || (rozmiar == 5)) )
    {
        cout << "Bledna wartosc, ustawiam rozmiar 3x3";
        rozmiar = 3;
        getchar(); getchar();
    }

    system ("cls");

    kwadrat = rozmiar*rozmiar;

    do
    {
       for (int i = 1; i <= kwadrat; i++)
       {
           t[i] = ' ';
       }

       player = 'O';

       while ( !wygraj(t,'X') && !wygraj(t,'O') && !remis(t) )
       {
            if (rozmiar == 3)
                cout << instrukcja_3;
            else if (rozmiar == 4)
                cout << instrukcja_4;
            else if (rozmiar == 5)
                cout << instrukcja_5;

             plansza(t);
             ruch(t, player, n);
             n++;

             system("cls");
       }

       n = 0;

            if (rozmiar == 3)
                cout << instrukcja_3;
            else if (rozmiar == 4)
                cout << instrukcja_4;
            else if (rozmiar == 5)
                cout << instrukcja_5;

       plansza(t);

       if (wygraj(t,'X'))
            cout << endl << "Przegrales!" << endl;
       if (wygraj(t,'O'))
            cout << endl << "Wygrales!" << endl;
       if (remis(t))
            cout << endl << "Remis!" << endl;

       cout << "Grasz dalej? (t / n)";
       cin >> odp;
       cout << endl;

       system("cls");

    } while (odp == 't');

    return 0;
}
