#include "link-cut-tree.hpp"

template <typename T>
struct VertexSetPathSum {
  struct Path {
    T sum;
  };
  struct Info {
    T v;
  };

  static Path vertex(const Info& u) { return {u.v}; }
  static Path compress(const Path& p, const Path& c) { return {p.sum + c.sum}; }
};
