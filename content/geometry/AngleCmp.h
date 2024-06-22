/**
 * Opis: Sortuje punkty rosnąco po kącie z przedziału $(-\pi, \pi]$.
 * Punkt $(0, 0)$ ma kąt $0$.
 */
#pragma once

#include "Point.h"

template<class P>
bool angle_cmp(P a, P b) {
  auto half = [](P p) { return sgn(p.y) ?: -sgn(p.x); };
  int A = half(a), B = half(b);
  return A == B ? sgn(cross(a, b)) > 0 : A < B;
}
