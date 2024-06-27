/**
 * Opis: `f[k]` -- nadjłuższy prefiks `s[k, n)` który jest prefiksem `s`.
 * Czas: O(n)
 */
#pragma once

vi z(const string& s) {
  int n = sz(s), l = -1, r = -1;
  vi f(n); f[0] = n;
  rep(i, 1, sz(s)) {
    if (i < r) f[i] = min(r - i, f[i - l]);
    while (i + f[i] < n && s[i + f[i]] == s[f[i]]) f[i]++;
    if (i + f[i] > r) l = i, r = i + f[i];
  }
  return f;
}
