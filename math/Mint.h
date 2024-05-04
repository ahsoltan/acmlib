#define NORM(x) x >= MOD ? x - MOD : x
const int MOD = 998244353;
struct mint {
  int x;
  mint(ll y = 0) : x((y %= MOD) < 0 ? y + MOD : y) {}
  mint operator+(mint o) const { return NORM(x + o.x); }
  mint operator-(mint o) const { return NORM(x + MOD - o.x); }
  mint operator*(mint o) const { return 1ll * x * o.x % MOD; }
  mint operator/(mint o) const { return *this * o.inv(); }
  auto operator<=>(const mint&) const = default;
  mint pow(ll n) const {
    mint a = x, b = 1;
    while (n > 0) {
      if (n % 2 == 1) b = b * a;
      a = a * a;
      n /= 2;
    }
    return b;
  }
  mint inv() const {
    return pow(MOD - 2);
  }
};
