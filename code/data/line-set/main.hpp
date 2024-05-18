/**
 * Opis: Znajduje maksimum funkcji liniowych online.
 * Dla doubli `div(a,b) = a/b` oraz `INF = 1/.0`.
 * Czas: O(\log n)
 */
struct line {
  mutable ll a, b, p;
  bool operator<(const line& o) const { return a < o.a; }
  bool operator<(ll x) const { return p < x; }
};
struct line_set : multiset<line, less<>> {
  static const ll INF = LLONG_MAX;
  ll div(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool inter(iterator x, iterator y) {
    if (y == end()) return x->p = INF, false;
    if (x->a == y->a) x->p = x->b > y->b ? INF : -INF;
    else x->p = div(y->b - x->b, x->a - y->a);
    return x->p >= y->p;
  }
  void add(ll a, ll b) {
    auto z = insert({a, b, 0}), y = z++, x = y;
    while (inter(y, z)) z = erase(z);
    if (x != begin() && inter(--x, y)) inter(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) {
      inter(x, erase(y));
    }
  }
  ll get(ll x) {
    line l = *lower_bound(x);
    return l.a * x + l.b;
  }
};
