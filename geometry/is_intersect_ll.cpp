#include "line.cpp"
#include "is_parallel.cpp"

namespace geometry {
  bool is_intersect(const Line &l, const Line &m) {
    return !is_parallel(l, m);
  }
}
