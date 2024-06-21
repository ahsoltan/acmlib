#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/math/MillerRabin.h"

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int q;
  cin >> q;
  while (q--) {
    ull n;
    cin >> n;
    cout << (prime(n) ? "Yes" : "No") << '\n';
  }
}
