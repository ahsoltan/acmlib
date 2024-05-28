/**
 * Opis: Znajduje najbliższe punkty styczne różne od $a$.
 * Wielokąt musi być CCW i $n \geq 3$.
 * Punkt $a$ nie może leżeć w ściśłym wnętrzu wielokąta.
 * Czas: O(\log n)
 */
#pragma once

#include "Point.h"

pair<P, P> tangents(const vector<P>& p, P a) {
  int n = ssize(p);
  P t[2];
  for (int it = 0; it < 2; it++) {
    auto dir = [&](int i) {
      P u = p[i] - a;
      P v = p[i < n - 1 ? i + 1 : 0] - a;
      int c = sgn(cross(u, v));
      if (c != 0) return c < 0;
      if (sgn(dot(u, v)) <= 0) return true;
      return sgn(norm(u) - norm(v)) > 0;
    };
    auto dirx = [&](int i) { return dir(i) ^ it; };
    if (dirx(0) == 1 && dirx(n - 1) == 0) {
      t[it] = p[0];
      continue;
    }
    int s[2] = {0, n - 1};
    while (s[1] - s[0] > 2) {
      int mid = (s[0] + s[1]) / 2;
      int x = dirx(mid);
      if (dirx(s[x ^ 1]) == (x ^ 1)) {
        s[x] = mid;
      } else {
        bool b = sgn(cross(p[mid] - a, p[s[1]] - a)) < 0;
        s[b ^ x ^ it ^ 1] = mid;
      }
    }
    t[it] = p[s[0] + 1 + (dirx(s[0] + 1) == 0)];
  }
  return {t[0], t[1]};
}
