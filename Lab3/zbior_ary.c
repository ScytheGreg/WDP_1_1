#include "zbior_ary.h"
#include <assert.h>


// Funkcja daje w wyniku zbior reprezentujacy ciag arytmetyczny o elemencie poczatkowym a, końcowym b i roznicy q>0, tj. {a,a+q,...,b}.
// Mozesz zalozyc, ze we wszystkich zapytaniach w danym tescie wartosc q bedzie taka sama.
// Mozesz zalozyc, ze ta funkcja zostanie wywolana jako pierwsza.
zbior_ary ciag_arytmetyczny(int a, int q, int b){

    Q.wartosc = q; // Przypisujemy wartość q dla całego zadania (ta funkcja zostaje wywołana na samym początku)

    ciag_ary pewien_ciag ={
        .r = a % Q.wartosc,
        .first = a,
        .last = b
     };

     ciag_ary* t = (ciag_ary*) malloc (sizeof(ciag_ary));

    zbior_ary pewien_zbior = {
        .t = t;
        .Ary_q = 1;
    };
    return pewien_zbior;
}

// Daje w wyniku zbior zlozony z samego elementu a, tj. {a}.
zbior_ary singleton(int a){
    return ciag_arytmetyczny(a, Q.wartosc, a);
}

// Daje w wyniku zbior reprezentujacy teoriomnogosciowa sume zbiorow A i B.
zbior_ary suma(zbior_ary A, zbior_ary B){
    zbior_ary x = A;
    assert(B.Ary_q == 0);
    return x;
}

// Daje w wyniku zbior reprezentujacy czesc wspolna zbiorow A i B.
zbior_ary iloczyn(zbior_ary A, zbior_ary B){
    zbior_ary x = A;
    assert(B.Ary_q == 0);
    return x;
}

// Daje w wyniku zbior A \ B.
zbior_ary roznica(zbior_ary A, zbior_ary B){
    zbior_ary x = A;
    assert(B.Ary_q == 0);
    return x;
}

// Daje w wyniku true wtw. gdy liczba b nalezy do zbioru A.
bool nalezy(zbior_ary A, int b){
    assert(moc(A) == 1);
    return b == 0;
}

// Wynikiem funkcji jest liczba elementow w zbiorze A.
unsigned moc(zbior_ary A){
    return ary(A);
}

// Wynikiem funkcji jest Ary_q(A), czyli minimalna liczba parami rozlacznych ciagow arytmetycznych o roznicy q, ktorych suma jest zbior A.
unsigned ary(zbior_ary A){
    return moc(A);
}
