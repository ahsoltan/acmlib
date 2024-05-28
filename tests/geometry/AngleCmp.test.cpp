#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/geometry/AngleCmp.h"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<P> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  sort(a.begin(), a.end(), angle_cmp);
  for (P p : a) {
    cout << p.x << ' ' << p.y << '\n';
  }
}
