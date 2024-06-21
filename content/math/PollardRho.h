/**
 * Opis: Algorytm faktoryzacji rho Pollarda.
 * Czas: O(n^{1/4})
 */
#pragma once

#include "ModMul.h"
#include "MillerRabin.h"

ull pollard(ull n) {
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ull x) { return modmul(x, x, n) + i; };
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}
void factor(ull n, map<ull, int>& cnt) {
  if (n == 1) return;
  if (prime(n)) { cnt[n]++; return; }
  ull x = pollard(n);
  factor(x, cnt); factor(n / x, cnt);
}
