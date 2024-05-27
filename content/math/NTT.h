/**
 * Opis: Mnoży dwa wielomiany modulo liczba NTT-pierwsza. 
 * Czas: O((n + m)\log (n + m))
 */
#pragma once

#include "ModInt.h"

template<typename T>
void ntt(vector<T>& a, bool inv) {
  int n = ssize(a);
  vector<T> b(n);
  for (int i = n / 2; i > 0; i /= 2, swap(a, b)) {
    T w = T(T::ROOT).pow((T::MOD - 1) / n * i), m = 1;
    for (int j = 0; j < n; j += 2 * i, m *= w) {
      for (int k = 0; k < i; k++) {
        T u = a[j + k], v = a[j + k + i] * m;
        b[j / 2 + k] = u + v;
        b[j / 2 + k + n / 2] = u - v;
      }
    }
  }
  if (inv) {
    reverse(a.begin() + 1, a.end());
    T ni = T(n).inv();
    for (int i = 0; i < n; i++) a[i] *= ni;
  }
}
template<typename T>
vector<T> conv(vector<T> a, vector<T> b) {
  int s = ssize(a) + ssize(b) - 1;
  int n = 1 << (__lg(2 * s - 1));
  a.resize(n); b.resize(n);
  ntt(a, false); ntt(b, false);
  for (int i = 0; i < n; i++) a[i] *= b[i];
  ntt(a, true);
  a.resize(s);
  return a;
}
