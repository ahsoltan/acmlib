#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "content/geometry/AngleCmp.h"

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<P> a(n);
  for (P& p : a) {
    cin >> p.x >> p.y; 
  }
  sort(a.begin(), a.end(), angle_cmp);
  for (P p : a) {
    cout << p.x << ' ' << p.y << '\n';
  }
}
