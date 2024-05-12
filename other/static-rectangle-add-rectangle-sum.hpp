#include "../structure/others/binary-indexed-tree.hpp"

/**
 * @brief Static Rectangle Add Rectangle Sum
 */
template <typename T, typename C>
struct StaticRectangleAddRectangleSum {
  struct Hikari : array<C, 4> {
    Hikari &operator+=(const Hikari &p) {
      for (int i = 0; i < 4; i++) {
        this->at(i) += p.at(i);
      }
      return *this;
    }
  };

  using BIT = BinaryIndexedTree<Hikari>;

  static_assert(is_integral<T>::value,
                "template parameter T must be integral type");

  struct Rectangle {
    T l, d, r, u;
    C w;
  };

  struct Query {
    T l, d, r, u;
  };

  vector<Rectangle> rectangles;
  vector<Query> queries;

  StaticRectangleAddRectangleSum() = default;

  StaticRectangleAddRectangleSum(int n, int q) {
    rectangles.reserve(n);
    queries.reserve(q);
  }

  void add_rectangle(T l, T d, T r, T u, C w) {
    rectangles.emplace_back(Rectangle{l, d, r, u, w});
  }

  // total weight of [l, r) * [d, u) points
  void add_query(T l, T d, T r, T u) {
    queries.emplace_back(Query{l, d, r, u});
  }

  vector<C> calculate_queries() {
    int n = (int)rectangles.size();
    int q = (int)queries.size();
    vector<C> ans(q);
    if (rectangles.empty() or queries.empty()) {
      return ans;
    }
    vector<T> ys;
    ys.reserve(n + n);
    for (Rectangle &p : rectangles) {
      ys.emplace_back(p.d);
      ys.emplace_back(p.u);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    struct Q {
      T x;
      int d, u;
      bool type;
      int idx;
    };
    vector<Q> rs, qs;
    rs.reserve(n + n);
    qs.reserve(q + q);
    for (int i = 0; i < n; i++) {
      auto &p = rectangles[i];
      int d = lower_bound(ys.begin(), ys.end(), p.d) - ys.begin();
      int u = lower_bound(ys.begin(), ys.end(), p.u) - ys.begin();
      rs.emplace_back(Q{p.l, d, u, false, i});
      rs.emplace_back(Q{p.r, d, u, true, i});
    }
    for (int i = 0; i < q; i++) {
      auto &p = queries[i];
      int d = lower_bound(ys.begin(), ys.end(), p.d) - ys.begin();
      int u = lower_bound(ys.begin(), ys.end(), p.u) - ys.begin();
      qs.emplace_back(Q{p.l, d, u, false, i});
      qs.emplace_back(Q{p.r, d, u, true, i});
    }
    sort(rs.begin(), rs.end(),
         [](const Q &a, const Q &b) { return a.x < b.x; });
    sort(qs.begin(), qs.end(),
         [](const Q &a, const Q &b) { return a.x < b.x; });
    int j = 0;
    BIT bit(ys.size());
    for (auto &query : qs) {
      while (j < n + n and rs[j].x < query.x) {
        auto &p = rectangles[rs[j].idx];
        if (rs[j].type) {
          bit.apply(rs[j].d, {-p.w * p.r * p.d, -p.w, p.w * p.d, p.w * p.r});
          bit.apply(rs[j].u, {p.w * p.r * p.u, p.w, -p.w * p.u, -p.w * p.r});
        } else {
          bit.apply(rs[j].d, {p.w * p.l * p.d, p.w, -p.w * p.d, -p.w * p.l});
          bit.apply(rs[j].u, {-p.w * p.l * p.u, -p.w, p.w * p.u, p.w * p.l});
        }
        ++j;
      }
      auto &p = queries[query.idx];
      auto uret = bit.prod(query.u);
      ans[query.idx] += uret[0];
      ans[query.idx] += uret[1] * query.x * p.u;
      ans[query.idx] += uret[2] * query.x;
      ans[query.idx] += uret[3] * p.u;
      auto dret = bit.prod(query.d);
      ans[query.idx] -= dret[0];
      ans[query.idx] -= dret[1] * query.x * p.d;
      ans[query.idx] -= dret[2] * query.x;
      ans[query.idx] -= dret[3] * p.d;
      if (not query.type) ans[query.idx] *= -1;
    }
    return ans;
  }
};
