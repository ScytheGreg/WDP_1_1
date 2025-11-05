#include <stdbool.h>
#include <assert.h>
#include "zbior_ary.h"
#include <limits.h>
#include <stdio.h>

int main() {

  zbior_ary A = ciag_arytmetyczny(INT_MIN + 1, 1, INT_MAX);
  zbior_ary B = ciag_arytmetyczny(INT_MIN + 4, 1, INT_MAX - 4);

  zbior_ary S = suma(A, B);
  zbior_ary R = roznica(A, B);
  zbior_ary I = iloczyn(A, B);

  printf("Moc A: %u\n", moc(A));
  printf("Moc B: %u\n", moc(B));
  printf("Moc S: %u\n", moc(S));
  printf("Moc R: %u\n", moc(R));
  printf("Moc I: %u\n", moc(I));

}
