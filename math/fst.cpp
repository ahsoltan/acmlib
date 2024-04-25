/**
 * Stosowanie: $n$ musi być potęgą dwójki.
 * Czas: O(n \log n)
 */

void fst(vector<mint>& a, bool inv) {
  int n = ssize(a);
  for (int i = 1; i < n; i *= 2) {
    for (int j = 0; j < n; j += 2 * i) {
      for (int k = 0; k < i; k++) {
        mint u = a[j + k], v = a[j + k + i];
        a[j + k] = u + v, a[j + k + i] = u - v; // XOR
        // a[j + k] = inv ? u - v : u + v; // AND
        // a[j + k + i] = inv ? v - u : u + v; // OR
      }
    }
  }
  // XOR
  if (inv) {
    mint d = mint(n).inv();
    for (int i = 0; i < n; i++) a[i] *= d;
  }
}
vector<mint> conv(vector<mint> a, vector<mint> b) {
  int n = ssize(a);
  fst(a, false);
  fst(b, false);
  for (int i = 0; i < n; i++) a[i] *= b[i];
  fst(a, true);
  return a;
}
