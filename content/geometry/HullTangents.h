/**
 * Opis: Znajduje punkty styczne różne od $a$.
 * Wielokąt musi być CCW i $n \geq 3$.
 * Punkt $a$ nie może leżeć w ściśłym wnętrzu wielokąta.
 * Czas: O(\log n)
 */
#pragma once

#include "Point.h"

pii tangents(const vector<P>& p, P a) {
  int n = sz(p), t[2];
  rep(it, 0, 2) {
    auto dir = [&](int i) {
      P u = p[i] - a, v = p[(i + 1) % n] - a;
      D c = cross(u, v);
      if (sgn(c) != 0) return sgn(c) < 0;
      if (sgn(dot(u, v)) <= 0) return true;
      return sgn(abs2(u) - abs2(v)) > 0;
    };
    auto idir = [&](int i) { return dir(i) ^ it; };
    if (idir(0) && !idir(n - 1)) { t[it] = 0; continue; }
    int s[2] = {0, n - 1};
    while (s[1] - s[0] > 2) {
      int mid = (s[0] + s[1]) / 2, x = idir(mid);
      if (idir(s[x ^ 1]) == (x ^ 1)) {
        s[x] = mid;
      } else {
        bool b = sgn(cross(p[mid] - a, p[s[1]] - a)) < 0;
        s[b ^ x ^ it ^ 1] = mid;
      }
    }
    t[it] = s[0] + 1 + (idir(s[0] + 1) == 0);
  }
  return {t[0], t[1]};
}
