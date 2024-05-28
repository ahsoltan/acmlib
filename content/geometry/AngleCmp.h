/**
 * Opis: Sortuje punkty w kolejności CCW, zaczynając od $y < 0$.
 * Punkt $(0, 0)$ należy do linii $x \geq 0$, $y = 0$.
 */
#pragma once

#include "Point.h"

int half(P a) {
  if (sgn(a.y) < 0) return -1;
  if (sgn(a.y) == 0 && sgn(a.x) >= 0) return 0;
  return 1;
}
bool angle_cmp(P a, P b) {
  if (half(a) != half(b)) return half(a) < half(b);
  return sgn(cross(a, b)) > 0;
}
