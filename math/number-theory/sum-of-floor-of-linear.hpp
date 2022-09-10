/**
 * @brief Sum of Floor of Linear(一次関数の床関数の和)
 * @docs docs/sum-of-floor-of-linear.md
 */
template< typename T >
T sum_of_floor_of_linear(const T &n, const T &m, T a, T b) {
  T ret = 0;
  if(a >= m) ret += (n - 1) * n * (a / m) / 2, a %= m;
  if(b >= m) ret += n * (b / m), b %= m;
  T y = (a * n + b) / m;
  if(y == 0) return ret;
  T x = y * m - b;
  ret += (n - (x + a - 1) / a) * y;
  ret += sum_of_floor_of_linear(y, a, m, (a - x % a) % a);
  return ret;
}
