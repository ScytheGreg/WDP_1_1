#include "zbior_ary.h"

int main() {
  // A = {2, 7, 12}
  zbior_ary A = ciag_arytmetyczny(2, 5, 32);
  wypisz_zbior(A);

  zbior_ary B = ciag_arytmetyczny(42, 5, 82);
  wypisz_zbior(B);

  zbior_ary(C) = ciag_arytmetyczny(17,5, 22);
  wypisz_zbior(C);

  zbior_ary D = ciag_arytmetyczny(32, 5, 47);
  wypisz_zbior(D);

  wypisz_zbior(roznica(suma(A, B), suma(D, C)));
}