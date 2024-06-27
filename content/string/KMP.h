/**
 * Opis: `p[k]` -- nadjłuższy ścisły sufiks `s[0, k]` który jest prefiksem `s`.
 * Czas: O(n)
 */
#pragma once

vi kmp(const string& s) {
  vi p(sz(s));
  rep(i, 1, sz(s)) {
    int g = p[i - 1];
    while (g && s[i] != s[g]) g = p[g - 1];
    p[i] = g + (s[i] == s[g]);
  }
  return p;
}
