/**
 * Stosowanie: Usuwa punkty współliniowe.
 * Czas: O(n \log n)
 */

vector<pt> convex_hull(vector<pt> p) {
  if (ssize(p) <= 1) return p;
  sort(p.begin(), p.end());
  vector<pt> h(ssize(p) + 1);
  int s = 0, t = 0;
  for (int it = 0; it < 2; it++) {
    for (pt a : p) {
      while (t >= s + 2) {
        pt u = h[t - 2], v = h[t - 1];
        if (cross(v - u, a - v) <= 0) t--;
        else break;
      }
      h[t++] = a;
    }
    reverse(p.begin(), p.end());
    s = --t;
  }
  h.resize(t - (t == 2 && h[0] == h[1]));
  return h;
}
