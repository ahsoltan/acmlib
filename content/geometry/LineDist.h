/**
 * Opis: Najkrótsza odległość między punktem i prostą/odcinkiem.
 */
#pragma once

#include "Point.h"

auto line_dist(auto p, auto a, auto b) {
  return abs(cross(p, a, b)) / abs(b - a);
}
auto seg_dist(auto p, auto a, auto b) {
  if (sgn(dot(a, p, b)) <= 0) return abs(p - a);
  if (sgn(dot(b, p, a)) <= 0) return abs(p - b);
  return line_dist(p, a, b);
}
