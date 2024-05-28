#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/geometry/ConvexHull.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<P> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i].x >> a[i].y;
    }
    auto b = convex_hull(move(a));
    cout << ssize(b) << '\n';
    for (P p : b) {
      cout << p.x << ' ' << p.y << '\n';
    }
  }
}
