#include "zbior_ary.h"
#include <stdio.h>
#include <assert.h>

int main() {
  const int a = 22;
  const int m_a = -23;
  const int q = 5;
  zbior_ary U = ciag_arytmetyczny(m_a, q, a);

  for(int i = m_a - 2 ; i <= a + 2 ; i += 1){
    assert(nalezy(U, i) == (modulo(i) == modulo(a)));
    assert(nalezy(singleton(i), i));
    assert(!nalezy(singleton(i), i + q));
    assert(!nalezy(singleton(i), i - q));
  }

    // A = {2, 7, 12}
  zbior_ary A = ciag_arytmetyczny(2, 5, 12);
  assert(moc(A) == 3);
  assert(ary(A) == 1);
  // B = {4, 9, 14, 19}
  zbior_ary B = ciag_arytmetyczny(4, 5, 19);
  // C = {1}
  zbior_ary C = singleton(1);
  // D = {1, 4, 9, 14, 19}
  zbior_ary D = suma(B, C);
  // E = {1, 2, 4, 7, 9, 12, 14, 19}
  zbior_ary E = suma(D, A);
  assert(moc(E) == 8);
  // F = {14}
  zbior_ary F = singleton(14);
  // G = {1, 2, 4, 7, 9, 12, 19}
  zbior_ary G = roznica(E, F);

  wypisz_zbior(G);
  
  assert(ary(G) == 4);
  assert(nalezy(G, 4));
  assert(!nalezy(G, 5));
  // H = {4, 9, 19};
  zbior_ary H = iloczyn(G, B);
  assert(moc(H) == 3);
  assert(ary(H) == 2);
  // I = {}
  zbior_ary I = iloczyn(H, A);
  assert(moc(I) == 0);

  return 0;
}