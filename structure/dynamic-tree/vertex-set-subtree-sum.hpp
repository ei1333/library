#include "top-tree.hpp"

template <typename T>
struct VertexSetSubtreeSum {
  struct Point {
    T sum;
  };
  struct Path {
    T sum;
  };
  struct Info {
    T v;
  };

  static Path vertex(const Info& u) { return {u.v}; }
  static Path add_vertex(const Point& d, const Info& u) {
    return {d.sum + u.v};
  }
  static Point add_edge(const Path& d) { return {d.sum}; }
  static Point rake(const Point& l, const Point& r) { return {l.sum + r.sum}; }
  static Path compress(const Path& p, const Path& c) { return {p.sum + c.sum}; }
};
