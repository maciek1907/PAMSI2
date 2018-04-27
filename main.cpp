#include <iostream>
#include <time.h>
#include <windows.h>

#define ILOSC_ELEMENTOW 1000000 // Ilosc elementow w jednej tablicy
#define ILOSC_TABLIC 100 // Ilosc tablic, po "ILOSC_ELEMENTOW" w kazdej tablicy

using namespace std;

/* Zmienne globalne */

int tablica_glowna[ILOSC_ELEMENTOW];
int tablica_temp[ILOSC_ELEMENTOW]; // Tablica pomocnicza dla sortowania przez scalanie

/* ***************  */

void scal(int poczatek, int srodek, int koniec)
{
    int i, j, k;

    for (i = poczatek; i <= koniec; i++)
    {
        tablica_temp[i] = tablica_glowna[i];
    }

    i = k = poczatek;
    j = srodek+1;

    while ( i <= srodek && j <= koniec)
    {
        if (tablica_temp[i] < tablica_temp[j])
        {
            tablica_glowna[k++] = tablica_temp[i++];
        }
        else
        {
            tablica_glowna[k++] = tablica_temp[j++];
        }
    }

    while (i <= srodek)
    {
        tablica_glowna[k++] = tablica_temp[i++];
    }
}

void sortowanie_scalanie(int poczatek, int koniec)
{
    if ( poczatek < koniec )
    {
        long long int srodek = (poczatek+koniec)/2;

        sortowanie_scalanie(poczatek, srodek);
        sortowanie_scalanie(srodek+1, koniec);
        scal(poczatek, srodek, koniec);
    }
}

void sortowanie_szybkie(int tablica[], int poczatek, int koniec)
{
    int i = poczatek;
    int j = koniec;
    int srodek = tablica[(poczatek+koniec)/2];

    do
    {
        while ( tablica[i] < srodek)
        {
            i++;
        }
        while ( tablica[j] > srodek)
        {
            j--;
        }

        if (i <= j)
        {
            swap(tablica[i], tablica[j]);

            i++;
            j--;
        }
    }
    while ( i <= j);

    if (poczatek < j)
    {
        sortowanie_szybkie(tablica, poczatek, j);
    }

    if (koniec > i)
    {
        sortowanie_szybkie(tablica, i, koniec);
    }
}

void sortowanie_kopcowanie(int tablica[], int ilosc)
{
    int i, j;

    for (int k = 2; k <= ilosc; k++)
    {
        i = k;
        j = i / 2;

        while( (tablica[i] > tablica[j] ) && (j > 0) )
        {
            swap(tablica[i], tablica[j]);
            i = j;
            j = i / 2;
        }
    }

    int n;

    for (int k = ilosc; k > 1; k-- )
    {
        swap (tablica[1], tablica[k]);

        i = 1;
        j = 2;

        while(j < k)
        {
            if( (j + 1 < k) && (tablica[j] < tablica[j + 1]) )
            {
                n = j + 1;
            }
            else
            {
                n = j;
            }

            if ( tablica[n] <= tablica[i] )
            {
                break;
            }

            swap (tablica[n], tablica[n]);
            i = n;
            j = i + i;
        }
    }
}

void generuj_losowo()
{
    /* Inicjalizajca generatora liczb losowych */

    srand(time(NULL));

    for (int i = 0; i < ILOSC_ELEMENTOW; ++i)
    {
        int wartosc = (rand()%100)+1;

        tablica_glowna[i] = wartosc;
    }

}

int main()
{
        cout << "Sortowanie dla " << ILOSC_ELEMENTOW << " elementow tablicy." << endl;

        int time = 0;
        int czasA;
        int czasB;

        float ile_juz_posortowane[] = {0.25, 0.50, 0.75, 0.95, 0.99, 0.997};

        /* ****************************************************

        SORTOWANIE PRZEZ SCALANIE

        **************************************************** */

        /* Przypadek pierwszy - wszystkie wartosci losowe */

        czasA = GetTickCount();

        cout << endl << endl << "SORTOWANIE PRZEZ SCALANIE:" << endl;

        for (int i = 0; i < ILOSC_TABLIC; ++i)
        {
            generuj_losowo();
            sortowanie_scalanie(0, ILOSC_ELEMENTOW);
        }

        czasB = GetTickCount();

        time = czasB - czasA;

        cout << "Czas: " << time << " milisekund" << endl;


        /* Przypadek drugi - dana czesc tablicy posortowana */

        for (int j = 0; j < 6; j++)
        {

            time = 0;

            for (int i = 0; i < ILOSC_TABLIC; ++i)
            {
                generuj_losowo();
                sortowanie_scalanie(0, (ILOSC_ELEMENTOW-1) * ile_juz_posortowane[j] );
                czasA = GetTickCount();
                sortowanie_scalanie(0, ILOSC_ELEMENTOW-1);
                czasB = GetTickCount();

                time = time + (czasB - czasA);
            }

            cout << "Czas: " << time << " milisekund" << endl;

        }


        /* Przypadek trzeci - posortowane w odwrotnej kolejnosci*/

        time = 0;

        for (int i = 0; i < ILOSC_TABLIC; ++i)
        {
            generuj_losowo();
            sortowanie_scalanie(0, ILOSC_ELEMENTOW-1 );

            int temp;

            for (int i = 0; i < ILOSC_ELEMENTOW/2; ++i)
            {
                temp = tablica_glowna[ILOSC_ELEMENTOW-i-1];
                tablica_glowna[ILOSC_ELEMENTOW-i-1] = tablica_glowna[i];
                tablica_glowna[i] = temp;
            }

            czasA = GetTickCount();
            sortowanie_scalanie(0, ILOSC_ELEMENTOW-1);
            czasB = GetTickCount();

            time = time + (czasB - czasA);
        }

        cout << "Czas: " << time << " milisekund" << endl;

        /* ****************************************************

        SORTOWANIE SZYBKIE (QUICKSORT)

        **************************************************** */

        /* Przypadek pierwszy - wszystkie wartosci losowe */

        czasA = GetTickCount();

        cout << endl << endl << "SORTOWANIE SZYBKIE:" << endl;

        for (int i = 0; i < ILOSC_TABLIC; ++i)
        {
            generuj_losowo();
            sortowanie_szybkie(tablica_glowna, 0, ILOSC_ELEMENTOW-1);
        }

        czasB = GetTickCount();

        time = czasB - czasA;

        cout << "Czas: " << time << " milisekund" << endl;


        /* Przypadek drugi - dana czesc tablicy posortowana */

        for (int j = 0; j < 6; j++)
        {

            time = 0;

            for (int i = 0; i < ILOSC_TABLIC; ++i)
            {
                generuj_losowo();
                sortowanie_szybkie(tablica_glowna, 0, (ILOSC_ELEMENTOW-1) * ile_juz_posortowane[j] );
                czasA = GetTickCount();
                sortowanie_szybkie(tablica_glowna, 0, ILOSC_ELEMENTOW-1);
                czasB = GetTickCount();

                time = time + (czasB - czasA);
            }

            cout << "Czas: " << time << " milisekund" << endl;

        }

        /* Przypadek trzeci - posortowane w odwrotnej kolejnosci*/

        time = 0;

        for (int i = 0; i < ILOSC_TABLIC; ++i)
        {
            generuj_losowo();
            sortowanie_szybkie(tablica_glowna, 0, ILOSC_ELEMENTOW-1 );

            int temp;

            for (int i = 0; i < ILOSC_ELEMENTOW/2; ++i)
            {
                temp = tablica_glowna[ILOSC_ELEMENTOW-i-1];
                tablica_glowna[ILOSC_ELEMENTOW-i-1] = tablica_glowna[i];
                tablica_glowna[i] = temp;
            }

            czasA = GetTickCount();
            sortowanie_szybkie(tablica_glowna, 0, ILOSC_ELEMENTOW-1);
            czasB = GetTickCount();

            time = time + (czasB - czasA);
        }

        cout << "Czas: " << time << " milisekund" << endl;

        /* ****************************************************

        SORTOWANIE PRZEZ KOPCOWANIE

        **************************************************** */

        /* Przypadek pierwszy - wszystkie wartosci losowe */

        czasA = GetTickCount();

        cout << endl << endl << "SORTOWANIE PRZEZ KOPCOWANIE:" << endl;

        for (int i = 0; i < ILOSC_TABLIC; ++i)
        {
            generuj_losowo();
            sortowanie_kopcowanie(tablica_glowna, ILOSC_ELEMENTOW-1);
        }

        czasB = GetTickCount();

        time = czasB - czasA;

        cout << "Czas: " << time << " milisekund" << endl;


        /* Przypadek drugi - dana czesc tablicy posortowana */

        for (int j = 0; j < 6; j++)
        {

            time = 0;

            for (int i = 0; i < ILOSC_TABLIC; ++i)
            {
                generuj_losowo();
                sortowanie_kopcowanie(tablica_glowna, (ILOSC_ELEMENTOW)*ile_juz_posortowane[j]);
                czasA = GetTickCount();
                sortowanie_kopcowanie(tablica_glowna, ILOSC_ELEMENTOW);
                czasB = GetTickCount();

                time = time + (czasB - czasA);
            }

            cout << "Czas: " << time << " milisekund" << endl;

        }


        /* Przypadek trzeci - posortowane w odwrotnej kolejnosci*/

        time = 0;

        for (int i = 0; i < ILOSC_TABLIC; ++i)
        {
            generuj_losowo();
            sortowanie_kopcowanie(tablica_glowna, ILOSC_ELEMENTOW);

            int temp;

            for (int i = 0; i < ILOSC_ELEMENTOW/2; ++i)
            {
                temp = tablica_glowna[ILOSC_ELEMENTOW-i-1];
                tablica_glowna[ILOSC_ELEMENTOW-i-1] = tablica_glowna[i];
                tablica_glowna[i] = temp;
            }

            czasA = GetTickCount();
            sortowanie_kopcowanie(tablica_glowna, ILOSC_ELEMENTOW-1);
            czasB = GetTickCount();

            time = time + (czasB - czasA);
        }

        cout << "Czas: " << time << " milisekund" << endl;
    }
