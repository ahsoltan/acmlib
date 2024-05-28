/**
 * Opis: Znajduje punkt przecięcia prostych.
 * W obliczeniach użyty jest iloczyn trzech współrzędnych.
 */
#pragma once

#include "Point.h"

P line_inter(P s1, P t1, P s2, P t2) {
  D d = cross(t1 - s1, t2 - s2);
  assert(sgn(d) != 0); // parallel
  D p = cross(t1 - s2, t2 - s2), q = cross(t2 - s2, s1 - s2);
  return (s1 * p + t1 * q) / d;
}
