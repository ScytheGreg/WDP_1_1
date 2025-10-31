#include "zbior_ary.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>



int main() {

  zbior_ary A = ciag_arytmetyczny(-INT_MAX, INT_MAX , INT_MAX);

  printf("Moc: %u\n", moc(A));

  zbior_ary B = A;

  for(int i = -INT_MAX + 5; i < INT_MAX  - 5; ++i){
    ciag_ary a = {i, i};
    ciag_ary* t_ciag = (ciag_ary*) malloc (sizeof(ciag_ary));
    t_ciag[0] = a;
    sumowalne_ciagi s = {
      INT_MAX,
      t_ciag,
      1
    };
    przypisz_sumowalne(s, &B);
    printf("Dodajemy: %d\n", i);
  }

  //wypisz_zbior(roznica(A, B));




  return 0;
}