/**
 * @brief Slope-Trick
 * @see https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8
 */
template< typename T >
struct SlopeTrick {

  const T INF = numeric_limits< T >::max() / 3;

  T min_f;
  priority_queue< T, vector< T >, greater<> > L, R;


  SlopeTrick() : min_f(0) {
    L.push(INF);
    R.push(INF);
  }

  struct Query {
    T lx, rx, min_f;
  };

  // return min f(x)
  Query query() const {
    return (Query) {-L.top(), R.top(), min_f};
  }

  // f(x) += a
  void add_all(const T &a) {
    min_f += a;
  }

  // f(x) += max(a - x, 0)
  void add_left(const T &a) {
    min_f += max(T(0), a - R.top());
    R.push(a);
    L.push(-R.top());
    R.pop();
  }

  // f(x) += max(x - a, 0)
  void add_right(const T &a) {
    min_f += max(T(0), -L.top() - a);
    L.push(-a);
    R.push(-L.top());
    L.pop();
  }

  // f(x) += abs(x - a)
  void add_abs(const T &a) {
    add_left(a);
    add_right(a);
  }

  // f(x) = min f(y) (y <= x)
  void cumulative_min_left() {
    while(R.size() >= 2) R.pop();
  }

  // f(x) = min f(y) (y >= x)
  void cumulative_min_right() {
    while(L.size() >= 2) L.pop();
  }
};
