#pragma once
#include "line.hpp"

namespace geometry {
  struct Segment : Line {
    Segment() = default;

    using Line::Line;
  };

  using Segments = vector< Segment >;
}
