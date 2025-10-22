#include <stdbool.h>
#include <assert.h>
#include "zbior_ary.h"

int main() {
  // A = {2, 7, 12}
  zbior_ary A = ciag_arytmetyczny(2, 5, 12);
  wypisz_zbior(A);

  zbior_ary B = singleton(7);
  wypisz_zbior(B);
}
