/**
 * Opis: Znajduje długość najdłuższego palindromu w każdym środku.
 * `p[2 * i]` -- środek w $i$, `p[2 * i + 1]` -- środek między $i$ a $i + 1$.
 * Czas: O(n)
 */
#pragma once

vector<int> manacher(const string& s) {
  int n = ssize(s);
  string t(2 * n - 1, '#');
  for (int i = 0; i < n; i++) t[2 * i] = s[i];
  vector<int> p(2 * n - 1);
  for (int i = 0, l = -1, r = -1; i < 2 * n - 1; i++) {
    if (i <= r) p[i] = min(r - i + 1, p[l + r - i]);
    while (p[i] < min(i + 1, 2 * n - 1 - i)) {
      if (t[i - p[i]] != t[i + p[i]]) break;
      p[i]++;
    }
    if (i + p[i] - 1 > r) {
      l = i - p[i] + 1;
      r = i + p[i] - 1;
    }
  }
  for (int i = 0; i < 2 * n - 1; i++) {
    p[i] -= t[i - p[i] + 1] == '#';
  }
  return p;
}
