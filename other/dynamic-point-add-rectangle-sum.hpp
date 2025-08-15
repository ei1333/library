#include "static-point-add-rectangle-sum.hpp"

template <typename T, typename C>
struct DynamicPointAddRectangleSum {
  using StaticRectangleSumSolver = StaticPointAddRectangleSum<T, C>;

  static_assert(is_integral<T>::value,
                "template parameter T must be integral type");

  struct Point {
    T x, y;
    C w;
  };

  struct Query {
    T l, d, r, u;
  };

  vector<variant<Point, Query> > queries;

  DynamicPointAddRectangleSum() = default;

  DynamicPointAddRectangleSum(int q) { queries.reserve(q); }

  void add_point(T x, T y, C w) { queries.emplace_back(Point{x, y, w}); }

  // tatal weight of [l, r) * [d, u) points
  void add_query(T l, T d, T r, T u) {
    queries.emplace_back(Query{l, d, r, u});
  }

  vector<C> calculate_queries() {
    int q = (int)queries.size();
    vector<int> rev(q);
    int sz = 0;
    for (int i = 0; i < q; i++) {
      if (holds_alternative<Query>(queries[i])) {
        rev[i] = sz++;
      }
    }
    vector<C> ans(sz);
    queue<pair<int, int> > range;
    range.emplace(0, q);
    while (not range.empty()) {
      auto [l, r] = range.front();
      range.pop();
      int m = (l + r) >> 1;
      StaticRectangleSumSolver solver;
      for (int k = l; k < m; k++) {
        if (holds_alternative<Point>(queries[k])) {
          auto& point = get<Point>(queries[k]);
          solver.add_point(point.x, point.y, point.w);
        }
      }
      for (int k = m; k < r; k++) {
        if (holds_alternative<Query>(queries[k])) {
          auto& query = get<Query>(queries[k]);
          solver.add_query(query.l, query.d, query.r, query.u);
        }
      }
      auto sub = solver.calculate_queries();
      for (int k = m, t = 0; k < r; k++) {
        if (holds_alternative<Query>(queries[k])) {
          ans[rev[k]] += sub[t++];
        }
      }
      if (l + 1 < m) range.emplace(l, m);
      if (m + 1 < r) range.emplace(m, r);
    }
    return ans;
  }
};
