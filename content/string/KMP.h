/**
 * Opis: `p[i]` -- najdłuższy ścisły sufiks `s[0:i]` który jest prefiksem `s`.
 * Czas: O(n)
 */
#pragma once

vector<int> kmp(const string& s) {
  int n = ssize(s);
  vector<int> p(n);
  for (int i = 1; i < n; i++) {
    int j = p[i - 1];
    while (j > 0 && s[i] != s[j]) j = p[j - 1];
    p[i] = j + (s[i] == s[j]);
  }
  return p;
}
