const int MOD = 998'244'353;
int add(int a, int b) {
  return a + b >= MOD ? a + b - MOD : a + b;
}
int sub(int a, int b) {
  return add(a, MOD - b);
}
int mul(int a, int b) {
  return 1ll * a * b % MOD;
}
int powi(int a, int b) {
  int c = 1;
  while (b > 0) {
    if (b % 2 == 1) c = mul(c, a);
    a = mul(a, a);
    b /= 2;
  }
  return c;
}
