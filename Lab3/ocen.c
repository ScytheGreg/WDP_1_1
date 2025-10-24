#include "zbior_ary.h"

int main() {
  // A = {2, 7, 12}
  zbior_ary A = ciag_arytmetyczny(2, 5, 12);
  wypisz_zbior(A);

  zbior_ary B = ciag_arytmetyczny(22, 5, 32);
  wypisz_zbior(B);

  wypisz_zbior(suma(A, B));
}