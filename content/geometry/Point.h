/**
 * Opis: Podstawowy szablon do geometrii.
 */
#pragma once

using D = long double;
const D EPS = 1e-9l;
int sgn(D x) { return (x > EPS) - (x < -EPS); }
struct P {
  D x, y;
  P operator+(P o) const { return {x + o.x, y + o.y}; }
  P operator-(P o) const { return {x - o.x, y - o.y}; }
  P operator*(D a) const { return {x * a, y * a}; }
  P operator/(D a) const { return {x / a, y / a}; }
  auto operator<=>(P o) const {
    return pair(sgn(x - o.x), sgn(y - o.y)) <=> pair(0, 0); }
  bool operator==(P o) const {
    return !sgn(x - o.x) && !sgn(y - o.y); }
};
D cross(P a, P b) { return a.x * b.y - a.y * b.x; }
D cross(P p, P a, P b) { return cross(a - p, b - p); }
D dot(P a, P b) { return a.x * b.x + a.y * b.y; }
D dot(P p, P a, P b) { return dot(a - p, b - p); }
D abs2(P a) { return a.x * a.x + a.y * a.y; }
D abs(P a) { return sqrt(abs2(a)); }
auto& operator<<(auto& o, P a) {
  return o << "(" << a.x << ", " << a.y << ")"; }
