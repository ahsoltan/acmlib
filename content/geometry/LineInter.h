/**
 * Opis: Punkt przecięcia prostych/odcinków.
 */
#pragma once

#include "Point.h"
#include "LineDist.h"

pair<int, P> line_inter(P a, P b, P c, P d) {
  auto u = cross(b - a, d - c);
  if (sgn(u) == 0) // parallel
    return {-(!sgn(cross(a, b, c))), {}};
  auto p = cross(c, b, d), q = cross(c, d, a);
  return {1, (a * p + b * q) / u};
}
vector<P> seg_inter(P a, P b, P c, P d) {
  auto oa = cross(c, d, a), ob = cross(c, d, b),
       oc = cross(a, b, c), od = cross(a, b, d);
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) // strict
    return {(a * ob - b * oa) / (ob - oa)};
  set<P> s;
  if (!sgn(seg_dist(a, c, d))) s.insert(a);
  if (!sgn(seg_dist(b, c, d))) s.insert(b);
  if (!sgn(seg_dist(c, a, b))) s.insert(c);
  if (!sgn(seg_dist(d, a, b))) s.insert(d);
  return {all(s)};
}
