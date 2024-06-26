/**
 * Opis: Rozkłada słowo na nierosnący ciąg podsłów mniejszych
 * od swoich wszystkich nietrywialnych sufiksów.
 * Czas: O(n)
 */
#pragma once

vi duval(const string& s) {
  int n = sz(s); vi f;
  for (int i = 0; i < n;) {
    int j = i + 1, k = i;
    for (; j < n && s[k] <= s[j]; ++j) {
      if (s[k] < s[j]) k = i;
      else ++k;
    }
    for (; i <= k; i += j - k) f.push_back(i);
  }
  return f.push_back(n), f;
}
