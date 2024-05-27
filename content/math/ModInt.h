#pragma once

template<int M, int R>
struct mod {
  static const int MOD = M, ROOT = R;
  int x;
  mod(ll y = 0) : x(y % M) { x += (x < 0) * M; }
  mod operator+=(const mod& o) {
    if ((x += o.x) >= M) x -= M;
    return *this;
  }
  mod operator-=(const mod& o) {
    if ((x -= o.x) < 0) x += M;
    return *this;
  }
  mod operator*=(const mod& o) {
    x = 1ll * x * o.x % M;
    return *this;
  }
  mod operator/=(const mod& o) {
    return (*this) *= o.inv();
  }
  friend mod operator+(mod a, const mod& b) { return a += b; }
  friend mod operator-(mod a, const mod& b) { return a -= b; }
  friend mod operator*(mod a, const mod& b) { return a *= b; }
  friend mod operator/(mod a, const mod& b) { return a /= b; }
  auto operator<=>(const mod&) const = default;
  mod pow(ll n) const {
    mod a = x, b = 1;
    while (n > 0) {
      if (n % 2 == 1) b *= a;
      a *= a;
      n /= 2;
    }
    return b;
  }
  mod inv() const {
    return pow(M - 2);
  }
};
using mint = mod<998244353, 3>;
