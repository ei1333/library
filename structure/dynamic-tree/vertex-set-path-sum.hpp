#include "link-cut-tree.hpp"

struct VertexSetPathSum {
  struct Path {
    int64 sum;
  };
  struct Info {
    int64 v;
  };

  static Path vertex(const Info& u) { return {u.v}; }
  static Path compress(const Path& p, const Path& c) { return {p.sum + c.sum}; }
};
