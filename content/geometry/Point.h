#pragma once

struct pt {
  ll x, y;
  pt operator+(pt o) const { return {x + o.x, y + o.y}; }
  pt operator-(pt o) const { return {x - o.x, y - o.y}; }
  pt operator*(ll a) const { return {x * a, y * a}; }
  pt operator/(ll a) const { return {x / a, y / a}; }
  auto operator<=>(const pt&) const = default;
  friend ll cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
  friend ll dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
  friend ll norm(pt a) { return a.x * a.x + a.y * a.y; }
  friend int half(pt a) {
    if (a.y < 0) return -1;
    if (a.y == 0 && a.x >= 0) return 0;
    return 1;
  }
  friend auto& operator<<(auto& o, pt a) {
    return o << '(' << a.x << ", " << a.y << ')';
  }
};
