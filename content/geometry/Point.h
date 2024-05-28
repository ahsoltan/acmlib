/**
 * Opis: Podstawowy szablon do geometrii.
 * Do wszystkich porównań należy używać `sgn`.
 */
#pragma once

using D = ll;
const D EPS = D(1e-9);
int sgn(D x) { return (x > EPS) - (x < -EPS); }
struct P {
  D x, y;
  P operator+(P o) const { return {x + o.x, y + o.y}; }
  P operator-(P o) const { return {x - o.x, y - o.y}; }
  P operator*(D a) const { return {x * a, y * a}; }
  P operator/(D a) const { return {x / a, y / a}; }
  auto operator<=>(const P&) const = default;
};
D cross(P a, P b) { return a.x * b.y - a.y * b.x; }
D dot(P a, P b) { return a.x * b.x + a.y * b.y; }
D norm(P a) { return a.x * a.x + a.y * a.y; }
auto& operator<<(auto& o, P a) {
  return o << '(' << a.x << ", " << a.y << ')';
}
