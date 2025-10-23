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

void dodaj_sumowalne(sumowalne_ciagi A, zbior_ary* wynik){
    // Ta funkcja dodaje do wyniku jeden sumowalny ciąg

    wynik->rozmiar ++; // Te strzałeczki chyba są dobrze ????
    unsigned ost_elem = wynik->rozmiar - 1; // Wskaźnik na ostatni element w wyniku (ten, który teraz zapisujemy)
    wynik->t_sum[ost_elem] = A;
}

// sumowalne_ciagi Min(sumowalne_ciagi A, sumowalne_ciagi B){
//     if(A.first <= B.first)
//         return A;
//     return B;
// }

// sumowalne_ciagi Max(sumowalne_ciagi A, sumowalne_ciagi B){
//     if(A.first >= )
// }

ciag_ary stworz_ciag(sumowalne_ciagi A, unsigned* wsk_A, sumowalne_ciagi B, unsigned* wsk_B){

    ciag_z_A = A.t_ciag[*wsk_A];
    ciag_z_B = B.t_ciag[*wsk_B];

    if(ciag_z_A.first > ciag_z_B.first)
        return stworz_ciag(B, wsk_B, A, wsk_A); //  W razie potrzeby zamieniamy miejscami

    ciag_ary ciag; //Tworzymy ciąg, który zwrócimy.

    ciag.first = ciag_z_A.first;

    bool idziemy_po_B = true;
    bool idziemy_po_A = false
    int nastepny = ciag_z_B[*wsk_B].first;
    int granica = ciag_z_A.last + Q.wartosc;

    while(granica >= następny){
        int przyszla_granica = granica;
        while(granica >= nastepny){
            if(idziemy_po_B && *wsk_B < B.rozmiar){
                *wsk_B++;
                nastepny = B.t_ciag[*wsk_B].first;
                przyszla_granica = B.t_ciag[*wsk_B - 1].last;
            }
            else if(idziemy_po_A && *wsk_A < A.rozmiar){
                *wsk_A++;
                nastepny = A.t_ciag[*wsk_A].first;
                przyszla_granica = A.t_ciag[*wsk_A - 1].last;
            }
            else break; //???
        }
        // Teraz granica < następny
        granica = przyszla_granica;

        idziemy_po_A = !idziemy_po_A;
        idziemy_po_B = !idziemy_po_B; // Czy to działa?

        if(idziemy_po_A && *wsk_A < A.rozmiar){
            *wsk_A++;
            nastepny = A.t_ciag[*wsk_A].first;
        }
        else if(idziemy_po_B && *wsk_B < B.rozmiar){
            *wsk_B++;
            nastepny = B.t_ciag[*wsk_B].first;
        }
    }
    ciag.last = granica;
    return ciag;
}

void przypisz_ciag(ciag_ary a, sumowalne_ciagi* suma){
    suma -> rozmiar ++;
    unsigned ost_elem = suma -> rozmiar - 1; // Wskaźnik na ostatni element w wyniku (ten, który teraz zapisujemy
    suma -> t_ciag[ost_elem] = a;
}

sumowalne_ciagi polacz_sumowalne(sumowalne_ciagi A, sumowalne_ciagi B){
    // Ta funkcja łączy dwa sumowalne ciągi w jeden zapisując go w wyniku.

    // Tworzymy tablicę z od razu zaalokowaną pamięcią.
    // Ostateczny Ary_q(wynik) >= max(A.rozmiar, B.rozmiar), więc limit pamięci spełniony.
    sumowalne_ciagi suma  = pusty_sumowalny(A.rozmiar + B.rozmiar, A.reszta);

    unsigned wsk_A = 0;
    unsigned wsk_B = 0;

    while(wsk_A < A.rozmiar && wsk_B < B.rozmiar){
        ciag_ary poloczony_ciag = stworz_ciag(A, &wsk_A, B, &wsk_B);
        przypisz_ciag(poloczony_ciag, &suma);
    }
    while(wsk_A < A.rozmiar){
        przypisz_ciag(A.t_ciag[wsk_A], &suma);
        wsk_A++;
    }
    while(wsk_B < B.rozmiar){
        przypisz_ciag(B.t_ciag[wsk_B], &suma);
        wsk_B++;
    }
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
