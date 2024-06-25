/**
 * Czas: O((n + m) \log (n + m))
 */
#pragma once

#include "ModInt.h"

template<class T>
void ntt(vector<T>& a, bool inv) {
  int n = sz(a); vector<T> b(n);
  for (int i = n / 2; i; i /= 2, swap(a, b)) {
    T w = T(T::ROOT).pow((T::MOD - 1) / n * i), m = 1;
    for (int j = 0; j < n; j += 2 * i, m *= w) rep(k, 0, i) {
      T u = a[j + k], v = a[j + k + i] * m;
      b[j / 2 + k] = u + v, b[j / 2 + k + n / 2] = u - v;
    }
  }
  if (inv) {
    reverse(1 + all(a));
    T z = T(n).inv(); rep(i, 0, n) a[i] *= z;
  }
}
template<class T>
vector<T> conv(vector<T> a, vector<T> b) {
  int s = sz(a) + sz(b) - 1, n = 1 << __lg(2 * s - 1);
  a.resize(n); ntt(a, 0); b.resize(n); ntt(b, 0);
  rep(i, 0, n) a[i] *= b[i];
  ntt(a, 1); a.resize(s);
  return a;
}
