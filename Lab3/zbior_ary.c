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
        .r = a % Q.wartosc,
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

// Daje w wyniku zbior reprezentujacy teoriomnogosciowa sume zbiorow A i B.
zbior_ary suma(zbior_ary A, zbior_ary B){

    // Tworzymy tablicę zaznaczającą, które wspólne reszty z dzilenia przez q są wspólne z A. 
    // Początkowo ustawiamy, że rzadne.
    bool* czy_reszta_uwzgl = (bool*) malloc (B.rozmiar * sizeof(bool));
    for(unsigned i = 0 ; i < B.rozmiar ; ++i){
        czy_reszta_uwzgl[i] = false;
    }


    
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
