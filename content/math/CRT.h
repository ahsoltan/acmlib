/**
 * Opis: Chińskie twierdzenie o resztach.
 * Czas: O(\log \min(m, n))
 */
#pragma once

#include "GCD.h"

ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = gcd(m, n, x, y);
  assert((a - b) % g == 0); // no solution
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}
