#include "../structure/others/binary-indexed-tree.hpp"

template <typename T, typename C>
struct StaticRectangleAddPointGet {
 private:
  using BIT = BinaryIndexedTree<C>;

  static_assert(is_integral<T>::value,
                "template parameter T must be integral type");

  struct Rectangle {
    T l, d, r, u;
    C w;
  };

  struct Query {
    T x, y;
  };

  vector<Rectangle> rectangles;
  vector<Query> queries;

 public:
  StaticRectangleAddPointGet() = default;

  explicit StaticRectangleAddPointGet(int n, int q) {
    rectangles.reserve(n);
    queries.reserve(q);
  }

  void add_rectangle(T l, T d, T r, T u, C w) {
    rectangles.emplace_back(Rectangle{l, d, r, u, w});
  }

  void add_query(T x, T y) { queries.emplace_back(Query{x, y}); }

  vector<C> calculate_queries() const {
    int n = (int)rectangles.size();
    int q = (int)queries.size();
    vector<C> ans(q);
    if (rectangles.empty() or queries.empty()) {
      return ans;
    }

    vector<T> ys;
    ys.reserve(q);
    for (int i = 0; i < q; i++) {
      ys.emplace_back(queries[i].y);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    struct R {
      T x;
      int d, u;
      bool type;
      C w;
    };
    vector<R> rs;
    rs.reserve(n + n);
    for (int i = 0; i < n; i++) {
      auto &rect = rectangles[i];
      int d = lower_bound(ys.begin(), ys.end(), rect.d) - ys.begin();
      int u = lower_bound(ys.begin(), ys.end(), rect.u) - ys.begin();
      rs.emplace_back(R{rect.l, d, u, false, rect.w});
      rs.emplace_back(R{rect.r, d, u, true, rect.w});
    }
    sort(rs.begin(), rs.end(),
         [](const R &a, const R &b) { return a.x < b.x; });

    vector<int> qs(q);
    iota(qs.begin(), qs.end(), 0);
    sort(qs.begin(), qs.end(),
         [&](int a, int b) { return queries[a].x < queries[b].x; });

    int j = 0;
    BIT bit(ys.size());
    for (auto &i : qs) {
      while (j < n + n and rs[j].x <= queries[i].x) {
        if (rs[j].type) {
          bit.apply(rs[j].d, -rs[j].w);
          bit.apply(rs[j].u, +rs[j].w);
        } else {
          bit.apply(rs[j].d, rs[j].w);
          bit.apply(rs[j].u, -rs[j].w);
        }
        ++j;
      }
      int y = lower_bound(ys.begin(), ys.end(), queries[i].y) - ys.begin();
      ans[i] = bit.prod(y + 1);
    }
    return ans;
  }
};
