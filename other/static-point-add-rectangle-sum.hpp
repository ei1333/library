#include "../structure/others/binary-indexed-tree.cpp"

/**
 * @brief Static Point Add Rectangle Sum
 */
template< typename T, typename C >
struct StaticPointAddRectangleSum {
  using BIT = BinaryIndexedTree< C >;

  static_assert(is_integral< T >::value, "template parameter T must be integral type");

  struct Point {
    T x, y;
    C w;
  };

  struct Query {
    T l, d, r, u;
  };

  vector< Point > points;
  vector< Query > queries;

  StaticPointAddRectangleSum() = default;

  StaticPointAddRectangleSum(int n, int q) {
    points.reserve(n);
    queries.reserve(q);
  }

  void add_point(T x, T y, C w) {
    points.emplace_back(Point{x, y, w});
  }

  // tatal weight of [l, r) * [d, u) points
  void add_query(T l, T d, T r, T u) {
    queries.emplace_back(Query{l, d, r, u});
  }

  vector< C > calculate_queries() {
    int n = (int) points.size();
    int q = (int) queries.size();
    vector< C > ans(q);
    if(points.empty() or queries.empty()) {
      return ans;
    }
    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
      return a.y < b.y;
    });
    vector< T > ys;
    ys.reserve(n);
    for(Point &p: points) {
      if(ys.empty() or ys.back() != p.y) ys.emplace_back(p.y);
      p.y = (int) ys.size() - 1;
    }
    ys.shrink_to_fit();

    struct Q {
      T x;
      int d, u;
      bool type;
      int idx;
    };
    vector< Q > qs;
    qs.reserve(q + q);
    for(int i = 0; i < q; i++) {
      auto &query = queries[i];
      int d = lower_bound(ys.begin(), ys.end(), query.d) - ys.begin();
      int u = lower_bound(ys.begin(), ys.end(), query.u) - ys.begin();
      qs.emplace_back(Q{query.l, d, u, false, i});
      qs.emplace_back(Q{query.r, d, u, true, i});
    }
    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
      return a.x < b.x;
    });
    sort(qs.begin(), qs.end(), [](const Q &a, const Q &b) {
      return a.x < b.x;
    });
    int j = 0;
    BIT bit(ys.size());
    for(auto &query: qs) {
      while(j < n and points[j].x < query.x) {
        bit.apply(points[j].y, points[j].w);
        ++j;
      }
      if(query.type) ans[query.idx] += bit.prod(query.d, query.u);
      else ans[query.idx] -= bit.prod(query.d, query.u);
    }
    return ans;
  }
};
