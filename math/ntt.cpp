/**
 * Czas: O((n + m) \log (n + m))
 */

void ntt(vector<mint>& a) {
  int n = ssize(a), d = __lg(n);
  vector<mint> w(n);
  mint ww = 1, r = mint(3).pow(119 * (1 << (23 - d)));
  for (int i = 0; i < n / 2; i++) {
    w[i + n / 2] = ww;
    ww *= r;
  }
  for (int i = n / 2 - 1; i > 0; i--) w[i] = w[2 * i];
  vector<int> rev(n);
  for (int i = 0; i < n; i++) {
    rev[i] = (rev[i >> 1] | ((i & 1) << d)) >> 1;
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int i = 1; i < n; i *= 2) {
    for (int j = 0; j < n; j += 2 * i) {
      for (int k = 0; k < i; k++) {
        mint z = w[i + k] * a[j + k + i];
        a[j + k + i] = a[j + k] - z;
        a[j + k] += z;
      }
    }
  }
}
vector<mint> conv(vector<mint> a, vector<mint> b) {
  int n = 1, s = ssize(a) + ssize(b) - 1;
  while (n < s) n *= 2;
  a.resize(n);
  b.resize(n);
  ntt(a);
  ntt(b);
  for (int i = 0; i < n; i++) a[i] *= b[i];
  ntt(a);
  reverse(a.begin() + 1, a.end());
  a.resize(s);
  mint inv = mint(n).inv();
  for (int i = 0; i < s; i++) a[i] *= inv;
  return a;
}
