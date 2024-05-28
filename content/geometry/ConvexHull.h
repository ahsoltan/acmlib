/**
 * Opis: Znajduje otoczkę wypukłą w kierunku CCW.
 * Usuwa punkty współliniowe.
 * Czas: O(n \log n)
 */
#pragma once

#include "Point.h"

vector<P> convex_hull(vector<P> p) {
  if (ssize(p) <= 1) return p;
  sort(p.begin(), p.end());
  vector<P> h(ssize(p) + 1);
  int s = 0, t = 0;
  for (int it = 0; it < 2; it++) {
    for (P a : p) {
      while (t >= s + 2) {
        P u = h[t - 2], v = h[t - 1];
        if (sgn(cross(v - u, a - v)) <= 0) t--;
        else break;
      }
      h[t++] = a;
    }
    reverse(p.begin(), p.end());
    s = --t;
  }
  h.resize(t - (t == 2 && h[0] == h[1]));
  return h;
}
