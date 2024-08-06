template <typename T>
struct RangeChminChmaxAddRangeSum {
  static constexpr T infty = numeric_limits<T>::max() / 2 - 1;

  struct MinMaxSum {
    T min, max, sum, minc, maxc, min2, max2, cnt;
    bool fail;
  };

  struct AddChminChmax {
    T add, chmin, chmax;

    bool operator!=(const AddChminChmax &a) const {
      return add != a.add or chmin != a.chmin or chmax != a.chmax;
    }
  };

  using S = MinMaxSum;
  using F = AddChminChmax;

  static constexpr S op(const S &a, const S &b) {
    if (a.min > a.max) return b;
    if (b.min > b.max) return a;

    S c;
    c.min = min(a.min, b.min);
    c.max = max(a.max, b.max);
    c.sum = a.sum + b.sum;

    c.minc = 0;
    if (a.min == c.min) c.minc += a.minc;
    if (b.min == c.min) c.minc += b.minc;

    c.maxc = 0;
    if (a.max == c.max) c.maxc += a.maxc;
    if (b.max == c.max) c.maxc += b.maxc;

    c.min2 = c.max;
    if (c.min < a.min && a.min < c.min2) c.min2 = a.min;
    if (c.min < a.min2 && a.min2 < c.min2) c.min2 = a.min2;
    if (c.min < b.min && b.min < c.min2) c.min2 = b.min;
    if (c.min < b.min2 && b.min2 < c.min2) c.min2 = b.min2;

    c.max2 = c.min;
    if (c.max > a.max && a.max > c.max2) c.max2 = a.max;
    if (c.max > a.max2 && a.max2 > c.max2) c.max2 = a.max2;
    if (c.max > b.max && b.max > c.max2) c.max2 = b.max;
    if (c.max > b.max2 && b.max2 > c.max2) c.max2 = b.max2;

    c.cnt = a.cnt + b.cnt;
    c.fail = false;
    return c;
  }

  static constexpr bool fail(const S &a) { return a.fail; }

  static constexpr S e() {
    return {infty, -infty, 0, 0, 0, infty, -infty, 0, false};
  }

  static constexpr S mapping(S x, const F &f) {
    assert(not x.fail);
    if (x.min > x.max) return x;

    x.sum += x.cnt * f.add;
    x.min += f.add, x.max += f.add;
    x.min2 += f.add, x.max2 += f.add;

    if (f.chmin == infty && f.chmax == -infty) return x;

    T before_min = x.min, before_max = x.max;
    x.min = min(x.min, f.chmin), x.min = max(x.min, f.chmax);
    x.max = min(x.max, f.chmin), x.max = max(x.max, f.chmax);

    if (x.min == x.max) {
      x.sum = x.max * x.cnt;
      x.max2 = x.min2 = x.max;
      x.maxc = x.minc = x.cnt;
    } else if (x.max2 <= x.min) {
      x.max2 = x.min, x.min2 = x.max, x.minc = x.cnt - x.maxc,
      x.sum = x.max * x.maxc + x.min * x.minc;
    } else if (x.min2 >= x.max) {
      x.max2 = x.min, x.min2 = x.max, x.maxc = x.cnt - x.minc,
      x.sum = x.max * x.maxc + x.min * x.minc;
    } else if (x.min < x.min2 && x.max > x.max2) {
      x.sum += (x.min - before_min) * x.minc + (x.max - before_max) * x.maxc;
    } else {
      x.fail = true;
    }
    return x;
  }

  static constexpr F composition(F f, const F &g) {
    f.add += g.add, f.chmax += g.add, f.chmin += g.add;
    f.chmin = min(f.chmin, g.chmin);
    f.chmax = min(f.chmax, g.chmin);
    f.chmax = max(f.chmax, g.chmax);
    return f;
  }

  static constexpr F id() { return {0, infty, -infty}; }

  static constexpr S set(T x) { return {x, x, x, 1, 1, x, x, 1, false}; }
  static constexpr F chmin(T x) { return {0, x, -infty}; }
  static constexpr F chmax(T x) { return {0, infty, x}; }
  static constexpr F add(T x) { return {x, infty, -infty}; }
};
