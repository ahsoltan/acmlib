/**
 * Opis: Rozszerzony algorytm Euklidesa.
 * Czas: O(\log \min(a, b))
 */
#pragma once

ll gcd(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = gcd(b, a % b, y, x);
  return y -= a / b * x, d;
}
