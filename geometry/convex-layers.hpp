#include "../structure/others/decremental-upper-hull.hpp"

template <typename T, typename T2, typename T3>
vector<int> convex_layers(const vector<pair<T, T> >& ps) {
  int n = (int)ps.size();
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int a, int b) { return ps[a] < ps[b]; });
  vector<pair<T, T> > us(n);
  for (int i = 0; i < n; i++) {
    us[i] = ps[ord[i]];
  }
  DecrementalUpperHull<T, T2, T3> upper_hull(us);
  vector<pair<T, T> > ds(n);
  for (int i = 0; i < n; i++) {
    ds[i] = {-us[n - i - 1].first, -us[n - i - 1].second};
  }
  DecrementalUpperHull<T, T2, T3> lower_hull(ds);
  vector<int> convex_hull, res(n, -1);
  convex_hull.reserve(n);
  for (int layer = 1; not lower_hull.empty(); layer++) {
    for (auto& p : upper_hull.get_hull()) {
      res[ord[p]] = layer;
      convex_hull.emplace_back(p);
    }
    for (auto& p : lower_hull.get_hull()) {
      p = n - p - 1;
      if (res[ord[p]] == -1) {
        res[ord[p]] = layer;
        convex_hull.emplace_back(p);
      }
    }
    for (auto& p : convex_hull) {
      upper_hull.erase(p);
      lower_hull.erase(n - p - 1);
    }
    convex_hull.clear();
  }
  return res;
}
