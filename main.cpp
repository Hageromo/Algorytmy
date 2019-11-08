// ALGO2 IN1 20A LAB01
// Jakub Przybysz

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ctime>
#include <algorithm>


using namespace std;

struct Struktura{
    int i;
    char c;
    float f;
};


Struktura** losowanie(int N){

    struct Struktura** tab=(struct Struktura**) malloc(N*sizeof(struct Struktura*)); //alokacja pamięci na tablicę N wskaźników na struktury


    for(int i = 0; i < N; i++){

        tab[i]=(struct Struktura*) malloc(sizeof(struct Struktura)); //alokacja pamięci na pojedynczą strukturę z przypisaniem adresu do i-tej pozycji tablicy tab[]

        int n[N];
        n[i] = (rand() % 10001) - 1000;     //losuje liczby z przedziału od -1000 do 9000
        for (int j=0; j<i; j++){
            if(n[j] == n[i]){               // sprawdza unikalność liczb
                n[i] = (rand() % 10001) - 1000;
                j = -1;
            }
        }
        tab[i] -> i = n[i];
        tab[i] -> c = (char)(rand() % 18) + 66;  // losuje z 18 liter od B do S według tabeli ASCII
        tab[i] -> f = 1000 + i + 1; //kolejny numer struktury
    }

    return tab;
}


void kasowanie(Struktura** tab, int N){             //zwalnianie pamięci, odpowiednio:

    for(int i = 0; i < N; i++){
        free(tab[i]);
    }
    free(tab);
}


void sortowanie(Struktura** tab, int N){
    bool podmien;
    for (int i = 0; i < N - 1; i++)
    {
        podmien = false;
        for (int j = 0; j < N - i - 1; j++)
        {
            if (tab[j] -> i > tab[j+1] -> i)
            {
                swap(tab[j], tab[j+1]);
                podmien = true;
            }
        }
        if (podmien == false)
            break;
    }
}


int zliczanieZnakow(Struktura** tab, int N, char X){
        int znalezionyX = 0;
        for(int i = 0; i < N; i++){
            if (tab[i]->c == X){
                znalezionyX++;
            }
        }

        return znalezionyX;
}


void wypisanie(Struktura** tab){


    for(int i = 0; i < 20; i++){  //Program wypisuje na konsoli listę pierwszych 20-tu posortowanych struktur

        cout << tab[i]->i << '\t';
        cout << tab[i]->c << '\t';
        cout << tab[i]->f << endl;

    }
}


int main() {

    int N;
    char X;

    Struktura** struktura;

    fstream plik;
    plik.open("inlab01.txt", ios::in);
    plik>>N;
    plik>>X;
    plik.close();

    srand(time(NULL));  // resetuje liczby losowe

    //czas start
    clock_t begin, end;
    double time_spent;
    begin = clock();


    struktura = losowanie(N);  // losowanie N elementów

    sortowanie(struktura, N);  // sortowanie

    int iloscZnakow;
    iloscZnakow = zliczanieZnakow(struktura, N, X);  // zliczanie znaków X


    wypisanie(struktura);  // wypisanie

    kasowanie(struktura,N);

    // czas stop
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;



    cout<<"ilosc znalezionych znakow: ";
    cout<<iloscZnakow<<endl;
    cout<<"Czas wykonania kodu: ";
    cout<<time_spent<<endl;

    return 0;
}