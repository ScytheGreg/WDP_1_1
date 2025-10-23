#ifndef _ZBIOR_ARY_H_
#define _ZBIOR_ARY_H_

#include <stdbool.h>

typedef struct Q_struct{ // Różnica ciągu arytmetycznego, stała dla całego zadania.
  int wartosc;
} Q_struct;

typedef struct ciag_ary {
  int first; // Pierszy element ciągu
  int last; // Osatni element ciągu.
} ciag_ary;

typedef struct sumowalne_ciagi {

  int reszta; // Reszta z dzielenia przez q;
  ciag_ary* t_ciag;
  unsigned rozmiar; // Rozmiar tablicy t_ciag (rozłączne ciągi arytmetyczne  o różnicy q z tą samą resztą z dzielenia przez q)

} sumowalne_ciagi;

typedef struct zbior_ary {
  /* do uzupelnienia */
  sumowalne_ciagi* t_sum; // Tablica parami rozłącznych ciągów, która ma możliwie najmniej elementów.
  unsigned rozmiar; // Rozmiar tablicy t_sum (ilość różnych reszt z dzilenia przez q w zbiorze)

} zbior_ary;

void wypisz_zbior(zbior_ary A);



/* Najlepiej nie modyfikowac nic ponizej. */

// Funkcja daje w wyniku zbior reprezentujacy ciag arytmetyczny o elemencie poczatkowym a, końcowym b i roznicy q>0, tj. {a,a+q,...,b}.
// Mozesz zalozyc, ze we wszystkich zapytaniach w danym tescie wartosc q bedzie taka sama.
// Mozesz zalozyc, ze ta funkcja zostanie wywolana jako pierwsza.
zbior_ary ciag_arytmetyczny(int a, int q, int b);

// Daje w wyniku zbior zlozony z samego elementu a, tj. {a}.
zbior_ary singleton(int a);

// Daje w wyniku zbior reprezentujacy teoriomnogosciowa sume zbiorow A i B.
zbior_ary suma(zbior_ary A, zbior_ary B);

// Daje w wyniku zbior reprezentujacy czesc wspolna zbiorow A i B.
zbior_ary iloczyn(zbior_ary A, zbior_ary B);

// Daje w wyniku zbior A \ B.
zbior_ary roznica(zbior_ary A, zbior_ary B);

// Daje w wyniku true wtw. gdy liczba b nalezy do zbioru A.
bool nalezy(zbior_ary A, int b);

// Wynikiem funkcji jest liczba elementow w zbiorze A.
unsigned moc(zbior_ary A);

// Wynikiem funkcji jest Ary_q(A), czyli minimalna liczba parami rozlacznych ciagow arytmetycznych o roznicy q, ktorych suma jest zbior A.
unsigned ary(zbior_ary A);

#endif
