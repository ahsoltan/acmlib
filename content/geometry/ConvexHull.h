/**
 * Opis: Otoczka wypukła w kierunku CCW.
 * Czas: O(n \log n)
 */
#pragma once

#include "Point.h"

vector<P> convex_hull(vector<P> pts) {
  if (sz(pts) <= 1) return pts;
  sort(all(pts));
  vector<P> h(sz(pts) + 1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(all(pts)))
    for (P p : pts) {
      while (t >= s + 2 &&
             sgn(cross(h[t - 2], h[t - 1], p)) <= 0) t--;
      h[t++] = p;
    }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}