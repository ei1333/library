#include "static-rectangle-add-point-get.hpp"

template <typename T, typename C>
struct DynamicRectangleAddPointGet {
 private:
  using StaticPointGetSolver = StaticRectangleAddPointGet<T, C>;

  static_assert(is_integral<T>::value,
                "template parameter T must be integral type");

  struct Rectangle {
    T l, d, r, u;
    C w;
  };

  struct Query {
    T x, y;
  };

  vector<variant<Rectangle, Query> > queries;

 public:
  DynamicRectangleAddPointGet() = default;

  explicit DynamicRectangleAddPointGet(int q) { queries.reserve(q); }

  void add_rectangle(T l, T d, T r, T u, C w) {
    queries.emplace_back(Rectangle{l, d, r, u, w});
  }

  void add_query(T x, T y) { queries.emplace_back(Query{x, y}); }

  vector<C> calculate_queries() const {
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
      StaticPointGetSolver solver;
      for (int k = l; k < m; k++) {
        if (holds_alternative<Rectangle>(queries[k])) {
          auto &rect = get<Rectangle>(queries[k]);
          solver.add_rectangle(rect.l, rect.d, rect.r, rect.u, rect.w);
        }
      }
      for (int k = m; k < r; k++) {
        if (holds_alternative<Query>(queries[k])) {
          auto &query = get<Query>(queries[k]);
          solver.add_query(query.x, query.y);
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
