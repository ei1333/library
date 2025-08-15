#include "../structure/segment-tree/lazy-segment-tree.hpp"

template <typename T>
struct AreaOfUnionOfRectangles {
 private:
  struct Rectangle {
    T l, d, r, u;
  };
  vector<Rectangle> rectangles;

 public:
  AreaOfUnionOfRectangles() = default;
  explicit AreaOfUnionOfRectangles(int n) : rectangles{} {
    rectangles.reserve(n);
  }
  void add_rectangle(T l, T d, T r, T u) {
    assert(l < r and d < u);
    rectangles.emplace_back(Rectangle{l, d, r, u});
  }

  template <typename T2>
  T2 calc() const {
    int n = (int)rectangles.size();
    if (n == 0) return 0;

    vector<T> ys;
    vector<tuple<T, int, int>> xs;
    ys.reserve(n + n);
    xs.reserve(n + n);
    for (int i = 0; i < n; i++) {
      auto& rect = rectangles[i];
      ys.emplace_back(rect.d);
      ys.emplace_back(rect.u);
      xs.emplace_back(rect.l, i, +1);
      xs.emplace_back(rect.r, i, -1);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(xs.begin(), xs.end());
    vector<int> to_d(n), to_u(n);
    for (int i = 0; i < n; i++) {
      auto& rect = rectangles[i];
      to_d[i] = lower_bound(ys.begin(), ys.end(), rect.d) - ys.begin();
      to_u[i] = lower_bound(ys.begin(), ys.end(), rect.u) - ys.begin();
    }
    using pi = pair<int, T>;
    auto f = [](const pi& a, const pi& b) -> pi {
      if (a.first < b.first) return a;
      if (b.first < a.first) return b;
      return {a.first, a.second + b.second};
    };
    auto e = [&]() -> pi { return {n + 1, 0}; };
    auto g = [](const pi& a, int b) -> pi { return {a.first + b, a.second}; };
    auto h = [](int a, int b) -> int { return a + b; };
    auto id = []() { return 0; };
    vector<pi> vs(ys.size() - 1);
    for (int i = 0; i + 1 < ys.size(); i++) {
      vs[i] = {0, ys[i + 1] - ys[i]};
    }
    LazySegmentTree seg(LambdaActedMonoid(f, e, g, h, id), vs);
    T2 ret = 0;
    T total = ys.back() - ys.front();
    for (int i = 0; i + 1 < n + n; i++) {
      auto& [k, j, d] = xs[i];
      seg.apply(to_d[j], to_u[j], d);
      auto [v, cnt] = seg.all_prod();
      T2 dy = total - (v == 0 ? cnt : 0);
      T2 dx = get<0>(xs[i + 1]) - k;
      ret += dy * dx;
    }
    return ret;
  }
};
