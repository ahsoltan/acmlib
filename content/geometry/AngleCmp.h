/**
 * Opis: Sortuje punkty rosnąco po kącie z przedziału $(-\pi, \pi]$.
 * Punkt $(0, 0)$ ma kąt $0$.
 */
#pragma once

#include "Point.h"

int half(auto a) { return sgn(a.y) ?: -sgn(a.x); }
bool angle_cmp(auto a, auto b) {
  int A = half(a), B = half(b);
  return A == B ? sgn(cross(a, b)) > 0 : A < B;
}
