using ld = long double;
const ld EPS = ld(1e-9);
struct pt {
  ld x, y;
  pt operator+(pt o) { return {x + o.x, y + o.y}; }
  pt operator-(pt o) { return {x - o.x, y - o.y}; }
  pt operator*(ld a) { return {x * a, y * a}; }
  pt operator/(ld a) { return {x / a, y / a}; }
  friend ld cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
  friend ld dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
  friend ld norm(pt a) { return hypot(a.x, a.y); }
  friend int half(pt a) {
    if (a.y < -EPS) return -1;
    if (abs(a.y) < EPS && a.x > -EPS) return 0;
    return 1;
  }
  friend auto& operator<<(auto& o, pt a) {
    return o << '(' << a.x << ", " << a.y << ')';
  }
};
