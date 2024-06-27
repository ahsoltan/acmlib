/**
 * Opis: Dzieli przedział $[1, \infty)$ na przedziały równości dzielenia.
 * Czas: O(\sqrt{n})
 */
#pragma once

vector<ll> same_floor(ll n) {
  vector<ll> v;
  for (ll i = 1; i <= n; i = n / (n / i) + 1) v.push_back(i);
  return v.push_back(n + 1), v;
}
vector<ll> same_ceil(ll n) {
  vector<ll> v;
  for (ll i = 1, j; i < n; i = (n + j - 2) / (j - 1)) {
    j = (n + i - 1) / i;
    v.push_back(i);
  }
  return v.push_back(n), v;
}
