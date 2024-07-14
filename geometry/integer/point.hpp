#pragma once

template <typename T>
struct Point {
  T x, y;

  Point() : x(0), y(0) {}
  Point(const T &x, const T &y) : x(x), y(y) {}

  Point &operator+=(const Point &p) {
    x += p.x;
    y += p.y;
    return *this;
  }
  Point &operator-=(const Point &p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }
  Point &operator*=(const T &d) {
    x *= d;
    y *= d;
    return *this;
  }

  Point operator-() const { return Point() - *this; }

  Point operator+(const Point &p) const { return Point(*this) += p; }

  Point operator-(const Point &p) const { return Point(*this) -= p; }

  Point operator+(const T &d) const { return Point(*this) *= d; }

  bool operator==(const Point &p) const { return x == p.x and y == p.y; }

  bool operator!=(const Point &p) const { return x != p.x or y != p.y; }

  friend ostream &operator<<(ostream &os, const Point &p) {
    return os << p.x << " " << p.y;
  }

  friend istream &operator>>(istream &is, Point &p) {
    T a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
  }
};

// あとはまかせた！
