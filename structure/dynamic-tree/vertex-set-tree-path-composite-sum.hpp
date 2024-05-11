#include "link-cut-tree-for-subtree.hpp"

template <typename T>
struct VertexSetTreePathCompositeSum {
  struct Point {
    T s, x;
    static constexpr Point id() { return {0, 0}; }
    Point inv() const { return {-s, -x}; }
  };
  struct Path {
    T a, b, s, x;
  };
  struct Info {
    bool is_vertex;
    T x, y;
  };

  static Path add_vertex(const Point& d, const Info& u) {
    if (u.is_vertex) return {1, 0, d.s + u.x, d.x + 1};
    return {u.x, u.y, d.s * u.x + d.x * u.y, d.x};
  }
  static Point add_edge(const Path& d) { return {d.s, d.x}; }
  static Point rake(const Point& s, const Point& p) {
    return {s.s + p.s, s.x + p.x};
  }
  static Path compress(const Path& p, const Path& c) {
    return {p.a * c.a, p.a * c.b + p.b, p.s + p.a * c.s + p.b * c.x, p.x + c.x};
  }
};
