/**
 * Stosowanie: $n$ musi być potęgą dwójki.
 * Czas: O(n \log n)
 */

void fst(vector<int>& a, bool inv) {
  int n = ssize(a);
  for (int i = 1; i < n; i *= 2) {
    for (int j = 0; j < n; j += 2 * i) {
      for (int k = 0; k < i; k++) {
        int u = a[j + k], v = a[j + k + i];
        a[j + k] = add(u, v), a[j + k + i] = sub(u, v); // XOR
        // a[j + k] = inv ? sub(u, v) : add(u, v); // AND
        // a[j + k + i] = inv ? sub(v, u) : add(u, v); // OR
      }
    }
  }
  // XOR
  if (inv) {
    int ni = powi(n, MOD - 2);
    for (int i = 0; i < n; i++) a[i] = mul(a[i], ni);
  }
}
vector<int> conv(vector<int> a, vector<int> b) {
  int n = ssize(a);
  fst(a, false); fst(b, false);
  for (int i = 0; i < n; i++) a[i] = mul(a[i], b[i]);
  fst(a, true);
  return a;
}
