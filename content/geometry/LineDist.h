/**
 * Opis: Najkrótsza odległość między punktem i prostą/odcinkiem.
 */
#pragma once

#include "Point.h"

auto line_dist(P p, P a, P b) {
  return abs(cross(p, a, b)) / abs(b - a);
}
auto seg_dist(P p, P a, P b) {
  if (sgn(dot(a, p, b)) <= 0) return abs(p - a);
  if (sgn(dot(b, p, a)) <= 0) return abs(p - b);
  return line_dist(p, a, b);
}
