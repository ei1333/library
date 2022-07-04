#pragma once
#include "line.cpp"

namespace geometry {
  struct Segment : Line {
    Segment() = default;

    using Line::Line;
  };

  using Segments = vector< Segment >;
}
