/**
 * Opis: Znajduje $x$ i $y$ takie, że $ax + by = \gcd(a, b)$.
 * Czas: O(\log(\min(a, b)))
 */
ll gcd(ll a, ll b, ll& x, ll& y) {
  if (!b) return x = 1, y = 0, a;
  ll g = gcd(b, a % b, y, x);
  return y -= x * (a / b), g;
}
