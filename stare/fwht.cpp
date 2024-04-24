void fwht(vector<mint>& a) {
  int n = ssize(a);
  for (int i = 1; i < n; i *= 2) {
    for (int j = 0; j < n; j += 2 * i) {
      for (int k = 0; k < i; k++) {
        mint u = a[j + k], v = a[j + k + i];
        a[j + k] = u + v;
        a[j + k + i] = u - v;
      }
    }
  }
}

vector<mint> conv(vector<mint> a, vector<mint> b) {
  int n = ssize(a);
  fwht(a);
  fwht(b);
  for (int i = 0; i < n; i++) {
    a[i] *= b[i];
  }
  mint inv = mint(n).inv();
  fwht(a);
  for (int i = 0; i < n; i++) {
    a[i] *= inv;
  }
  return a;
}
