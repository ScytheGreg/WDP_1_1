#include "zbior_ary.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


//Zmienna globalna (bez niej nie da się zrobić zadania)

Q_struct Q;

// Funkcja daje w wyniku zbior reprezentujacy ciag arytmetyczny o elemencie poczatkowym a, końcowym b i roznicy q>0, tj. {a,a+q,...,b}.
// Mozesz zalozyc, ze we wszystkich zapytaniach w danym tescie wartosc q bedzie taka sama.
// Mozesz zalozyc, ze ta funkcja zostanie wywolana jako pierwsza.
zbior_ary ciag_arytmetyczny(int a, int q, int b){

    Q.wartosc = q; // Przypisujemy wartość q dla całego zadania (ta funkcja zostaje wywołana na samym początku)

    // Najpierw tworzymy najmniejszą jednostkę - ciąg arytmetyczny
    ciag_ary pewien_ciag ={ 
        .first = a,
        .last = b
     };

     ciag_ary* t_ciag = (ciag_ary*) malloc (sizeof(ciag_ary)); // Tablica zawierająca ten ciąg.
     t_ciag[0] = pewien_ciag;

     // Ten ciąg jest  również częścią klasy abstrakcji ciągów o tej samej reszcie z dzielenia przez q.
     sumowalne_ciagi pewien_sumowalny_ciag ={
        .reszta = a % Q.wartosc,
        .t_ciag = t_ciag,
        .rozmiar = 1
     };

     sumowalne_ciagi* t_sum = (sumowalne_ciagi*) malloc (sizeof(sumowalne_ciagi)); // Tablica zawierająca tę klasę abstrakcji
     t_sum[0] = pewien_sumowalny_ciag;

     //Ostatecznie tworzymy zbiór klas abstrakcji.
    zbior_ary pewien_zbior = {
        .t_sum = t_sum,
        .rozmiar = 1,
    };
    return pewien_zbior;
}

// Daje w wyniku zbior zlozony z samego elementu a, tj. {a}.
zbior_ary singleton(int a){
    return ciag_arytmetyczny(a, Q.wartosc, a);
}

zbior_ary zbior_pusty(unsigned pamiec){
    sumowalne_ciagi* t_sum = (sumowalne_ciagi*) malloc (pamiec * sizeof(sumowalne_ciagi));
    zbior_ary pusty={
        .t_sum = t_sum,
        .rozmiar = 0,
    };
    return pusty;
}

sumowalne_ciagi pusty_sumowalny(unsigned pamiec, int reszta){
    ciag_ary* t_ciag = (ciag_ary*) malloc (pamiec * sizeof(ciag_ary));
    sumowalne_ciagi pusty ={
        .reszta = reszta,
        .t_ciag = t_ciag,
        .rozmiar = 0
    };
    return pusty;
}

void wypisz_ciag(ciag_ary pewien_ciag){
    for(int a = pewien_ciag.first ; a <= pewien_ciag.last ; a += Q.wartosc){
        printf("%d ", a);
    }
}

void wypisz_sumowalny_ciag(sumowalne_ciagi sum_ciagi){
    for(unsigned i = 0 ; i < sum_ciagi.rozmiar ; ++i){
        ciag_ary pewien_ciag = sum_ciagi.t_ciag[i];
        wypisz_ciag(pewien_ciag);
        printf(" ");
    }
}

void wypisz_zbior(zbior_ary A){
    for(unsigned i = 0 ; i < A.rozmiar ; ++i){
        sumowalne_ciagi pewien_sumowalny_ciag = A.t_sum[i];
        wypisz_sumowalny_ciag(pewien_sumowalny_ciag);
        printf("\n");
    }
    printf("\n");
}


void przypisz_ciag(ciag_ary a, sumowalne_ciagi* suma){
    suma -> rozmiar ++;
    unsigned ost_elem = suma -> rozmiar - 1; // Wskaźnik na ostatni element w wyniku (ten, który teraz zapisujemy
    suma -> t_ciag[ost_elem] = a;
}

typedef struct punkt{
    int wartosc;
    bool czy_A;
    bool poczatek;
} punkt;

void wypisz_punkt(punkt A){
    printf("Punkt:%d, %d, %d\n", A.wartosc, A.czy_A, A.poczatek);
}

void przepisz_punkt(sumowalne_ciagi A, punkt** tab_A, bool czy_A){ //Działa
    for(unsigned i = 0 ; i < A.rozmiar ; ++i){
        punkt poczatek = {A.t_ciag[i].first, czy_A, true};
        (*tab_A)[2 * i] = poczatek;
        wypisz_punkt(poczatek);
        punkt koniec = {A.t_ciag[i].last, czy_A, false};
        (*tab_A)[2 * i + 1] = koniec;
        wypisz_punkt(koniec);
    }
}

void dodaj_punkt(punkt** tab, unsigned* ind, int* wsk_A, punkt wartosc){
    (*tab)[*ind] = wartosc;
    (*wsk_A)++;
    (*ind)++;
}

void posortuj(sumowalne_ciagi A, sumowalne_ciagi B, punkt** tab){
    // Ta funkcja sortuje punkty z A i B do tablicy.

    unsigned ind_tab = 0;

    //Przepisujemy A i B do tablic punktów
    punkt* tab_A = (punkt*) malloc (A.rozmiar * 2 * sizeof(punkt));//Działa
    przepisz_punkt(A, &tab_A, true);
    punkt* tab_B = (punkt*) malloc (B.rozmiar * 2 * sizeof(punkt));
    przepisz_punkt(B, &tab_B, false);
    
    int wsk_A = -1;
    int wsk_B = -1;
    while(wsk_A < (int) A.rozmiar * 2 || wsk_B < (int) B.rozmiar * 2){
        if(wsk_A >= (int) A.rozmiar * 2)
            dodaj_punkt(&(*tab), &ind_tab, &wsk_B, tab_B[wsk_B]);
        
        else if(wsk_B >= (int) B.rozmiar * 2){
            dodaj_punkt(&(*tab), &ind_tab, &wsk_A, tab_A[wsk_A]);
        }
        
        else if(tab_A[wsk_A + 1].wartosc > tab_B[wsk_B + 1].wartosc)
            dodaj_punkt(&(*tab), &ind_tab, &wsk_B, tab_B[wsk_B]);
        
        else
            dodaj_punkt(&(*tab), &ind_tab, &wsk_A, tab_A[wsk_A]);
    }
    printf("Akuku posortuj\n");
    free(tab_A);
    free(tab_B);
}

void dodaj_sumowalne(sumowalne_ciagi A, zbior_ary* wynik){
    // Ta funkcja dodaje do wyniku jeden sumowalny ciąg

    printf("dodaj_sumowalne działa!\n");

    wynik->rozmiar ++; // Te strzałeczki chyba są dobrze ????
    unsigned ost_elem = wynik->rozmiar - 1; // Wskaźnik na ostatni element w wyniku (ten, który teraz zapisujemy)
    wynik->t_sum[ost_elem] = A;

}

sumowalne_ciagi polacz_sumowalne(sumowalne_ciagi A, sumowalne_ciagi B){
    // Ta funkcja łączy dwa sumowalne ciągi w jeden zapisując go w wyniku.
    
    // Tworzymy tablicę z od razu zaalokowaną pamięcią.
    // Ostateczny Ary_q(wynik) >= max(A.rozmiar, B.rozmiar), więc limit pamięci spełniony.
    sumowalne_ciagi suma  = pusty_sumowalny(A.rozmiar + B.rozmiar, A.reszta);

    // Tablica, która będzie przechowywała posortowane początki i końce A i B
    punkt* sort_punkt = (punkt*) malloc (2 * (A.rozmiar + B.rozmiar) * sizeof(punkt));
    posortuj(A, B, &sort_punkt); // O(Ary_q(A) + Ary_q(B)
    printf("Akuku\n");
    int zlicz_pocz = 0;
    int zlicz_kon = 0;
    int first = -1;

    for(unsigned i = 0 ; i < 2 * (A.rozmiar + B.rozmiar) ; ++i){
        //wypisz_punkt(sort_punkt[i]);
        //printf("Pocz: %d, Kon: %d\n", zlicz_pocz, zlicz_kon);
        if(first == -1)
            first = sort_punkt[i].wartosc;

        if(sort_punkt[i].poczatek)
            zlicz_pocz++;
        else
            zlicz_kon++;
        
        if(zlicz_pocz == zlicz_kon){
            ciag_ary nowy_ciag = {first, sort_punkt[i].wartosc};
            przypisz_ciag(nowy_ciag, &suma);
            first = -1;
        }
    }

    free(sort_punkt);
    return suma;
}

// Daje w wyniku zbior reprezentujacy teoriomnogosciowa sume zbiorow A i B.
zbior_ary suma(zbior_ary A, zbior_ary B){

    // Tworzymy tablicę z od razu zaalokowaną pamięcią.
    // Ostateczny Ary_q(wynik) >= max(A.rozmiar, B.rozmiar), więc limit pamięci spełniony.
    zbior_ary wynik = zbior_pusty(A.rozmiar + B.rozmiar); 

    unsigned wsk_A = 0; // Wskaźnik po zbiorze A.
    unsigned wsk_B = 0; // Wskaźnik po zbiorze B.
    while(wsk_A < A.rozmiar && wsk_B < B.rozmiar){

        int reszta_A = A.t_sum[wsk_A].reszta;
        int reszta_B = B.t_sum[wsk_B].reszta;

        if(reszta_A == reszta_B){
            sumowalne_ciagi poloczne_ciagi = polacz_sumowalne(A.t_sum[wsk_A], B.t_sum[wsk_B]);
            dodaj_sumowalne(poloczne_ciagi, &wynik);
            wsk_A++;
            wsk_B++;
        }

        else if(reszta_A < reszta_B){
            dodaj_sumowalne(A.t_sum[wsk_A], &wynik);
            wsk_A++;
        }

        else if(reszta_A > reszta_B){
            dodaj_sumowalne(B.t_sum[wsk_B], &wynik);
            wsk_B++;
        }
    }
    while(wsk_A < A.rozmiar){
        dodaj_sumowalne(A.t_sum[wsk_A], &wynik);
        wsk_A++;
    }
    while(wsk_B < B.rozmiar){
        dodaj_sumowalne(B.t_sum[wsk_B], &wynik);
        wsk_B++;
    }

    return wynik;
}

// // Daje w wyniku zbior reprezentujacy czesc wspolna zbiorow A i B.
// zbior_ary iloczyn(zbior_ary A, zbior_ary B){
//     zbior_ary x = A;
//     assert(B.Ary_q == 0);
//     return x;
// }

// // Daje w wyniku zbior A \ B.
// zbior_ary roznica(zbior_ary A, zbior_ary B){
//     zbior_ary x = A;
//     assert(B.Ary_q == 0);
//     return x;
// }

// // Daje w wyniku true wtw. gdy liczba b nalezy do zbioru A.
// bool nalezy(zbior_ary A, int b){
//     assert(moc(A) == 1);
//     return b == 0;
// }

// // Wynikiem funkcji jest liczba elementow w zbiorze A.
// unsigned moc(zbior_ary A){
//     return ary(A);
// }

// // Wynikiem funkcji jest Ary_q(A), czyli minimalna liczba parami rozlacznych ciagow arytmetycznych o roznicy q, ktorych suma jest zbior A.
// unsigned ary(zbior_ary A){
//     return moc(A);
// }
