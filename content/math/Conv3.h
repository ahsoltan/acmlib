/**
 * Opis: NTT z Garnerem.
 * Działa dla $n + m \leq 2^{24}$ i $c_k \leq 5 \cdot 10^{25}$.
 * Czas: O((n + m) \log (n + m))
 */
#pragma once

#include "NTT.h"
#include "ModInt.h"

template<class T>
vector<T> mconv(const auto& x, const auto& y) {
  auto con = [&](const auto& v) {
    vector<T> w(sz(v)); rep(i, 0, sz(v)) w[i] = v[i].x;
    return w; };
  return conv(con(x), con(y));
}
template<class T>
vector<T> conv3(const vector<T>& a, const vector<T>& b) {
  using m0 = mod<754974721, 11>; auto c0 = mconv<m0>(a, b);
  using m1 = mod<167772161, 3>;  auto c1 = mconv<m1>(a, b);
  using m2 = mod<469762049, 3>;  auto c2 = mconv<m2>(a, b);
  int n = sz(c0); vector<T> d(n); m1 r01 = m1(m0::MOD).inv();
  m2 r02 = m2(m0::MOD).inv(), r12 = m2(m1::MOD).inv();
  rep(i, 0, n) {
    int x = c0[i].x, y = ((c1[i] - x) * r01).x,
        z = (((c2[i] - x) * r02 - y) * r12).x;
    d[i] = (T(z) * m1::MOD + y) * m0::MOD + x;
  }
  return d;
}
