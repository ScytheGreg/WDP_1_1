#include "zbior_ary.h"
#include <stdio.h>

int main() {
  // A = {2, 7, 12}
  zbior_ary A = ciag_arytmetyczny(2, 5, 32);
  wypisz_zbior(A);

  // zbior_ary B = ciag_arytmetyczny(42, 5, 82);
  // wypisz_zbior(B);

  zbior_ary(C) = ciag_arytmetyczny(22 ,5, 52);
  wypisz_zbior(C);

  // zbior_ary D = ciag_arytmetyczny(32, 5, 47);
  // wypisz_zbior(D);

  wypisz_zbior(roznica(A, C));

  //printf("52 należy do B: %d\n", nalezy(B, 52));

}