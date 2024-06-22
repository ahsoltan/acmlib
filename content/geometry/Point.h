#pragma once

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct pt {
  T x, y;
  pt operator+(pt o) const { return {x + o.x, y + o.y}; }
  pt operator-(pt o) const { return {x - o.x, y - o.y}; }
  pt operator*(T a) const { return {x * a, y * a}; }
  pt operator/(T a) const { return {x / a, y / a}; }
  friend T cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
  friend T cross(pt p, pt a, pt b) {
    return cross(a - p, b - p); }
  friend T dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
  friend T dot(pt p, pt a, pt b) {
    return dot(a - p, b - p); }
  friend T abs2(pt a) { return a.x * a.x + a.y * a.y; }
  auto operator<=>(const pt&) const = default;
  friend auto& operator<<(auto& o, pt a) {
    return o << '(' << a.x << ", " << a.y << ')'; }
};
using P = pt<ll>;
