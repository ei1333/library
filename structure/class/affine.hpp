template <typename T>
struct Affine {
  T a, b;  // ax+b
  Affine() : a(1), b(0) {}
  Affine(T a, T b) : a(a), b(b) {}
  T eval(T x) const { return a * x + b; }
  static constexpr Affine op(const Affine& l, const Affine& r) {
    return {l.a * r.a, l.b * r.a + r.b};
  }
  constexpr bool operator==(const Affine& p) const {
    return a == p.a and b == p.b;
  }
  constexpr bool operator!=(const Affine& p) const {
    return a != p.a or b != p.b;
  }
};
