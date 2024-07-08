#pragma once

template <typename T>
struct Point {
  T x, y;

  Point() : x(0), y(0) {}
  Point(T x, T y) : x(x), y(y) {}
};

// あとはまかせた！
