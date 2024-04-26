/**
 * Stosowanie: Wielokąt musi być CCW i $n \geq 3$. Zwraca najbliższe punkty styczne różne od $a$.
 * Czas: O(\log n)
 */

pair<pt, pt> tangents(const vector<pt>& p, pt a) {
  int n = ssize(p);
  pt t[2];
  for (int it = 0; it < 2; it++) {
    auto dir = [&](int i) {
      pt u = p[i] - a;
      pt v = p[i < n - 1 ? i + 1 : 0] - a;
      ld c = cross(u, v);
      if (abs(c) > EPS) return c < 0;
      if (dot(u, v) > EPS) return norm(u) > norm(v);
      return true;
    };
    auto dirx = [&](int i) { return dir(i) ^ it; };
    if (dirx(0) == 1 && dirx(n - 1) == 0) {
      t[it] = p[0];
      continue;
    }
    int s[2] = {0, n - 1};
    while (s[1] - s[0] > 2) {
      int mid = (s[0] + s[1]) / 2;
      int x = dirx(mid);
      if (dirx(s[x ^ 1]) == (x ^ 1)) {
        s[x] = mid;
      } else {
        ((cross(p[mid] - a, p[s[1]] - a) < -EPS) ^ it
             ? s[x]
             : s[x ^ 1]) = mid;
      }
    }
    t[it] = dirx(s[0] + 1) == 0 ? p[s[0] + 2] : p[s[0] + 1];
  }
  return {t[0], t[1]};
}
