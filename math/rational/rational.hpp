/**
 * @brief Rational (有理数型)
 */
template< typename T >
struct Rational {
private:
  T num, den;

  static T gcd(T a, T b) {
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    return std::__gcd(a, b);
  }

  void normalize() {
    if(num == 0) {
      den = 1;
    } else {
      T g = gcd(num, den);
      num /= g;
      den /= g;
      if(den < 0) {
        num = -num;
        den = -den;
      }
    }
  }

public:

  Rational() : num(0), den(1) {}

  explicit Rational(const T &n) : num(n), den(1) {}

  explicit Rational(const T &n, const T &d) : num(n), den(d) {
    normalize();
  }

  Rational &operator=(const T &n) { return assign(n, 1); }

  Rational &assign(const T &n, const T &d) {
    num = n;
    den = d;
    normalize();
    return *this;
  }

  T numerator() const { return num; }

  T denominator() const { return den; }

  Rational &operator+=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g = gcd(den, r_den);
    den /= g;
    num = num * (r_den / g) + r_num * den;
    g = gcd(num, g);
    num /= g;
    den *= r_den / g;
    return *this;
  }

  Rational &operator-=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g = gcd(den, r_den);
    den /= g;
    num = num * (r_den / g) - r_num * den;
    g = gcd(num, g);
    num /= g;
    den *= r_den / g;
    return *this;
  }

  Rational &operator*=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g1 = gcd(num, r_den);
    T g2 = gcd(den, r_num);
    num = (num / g1) * (r_num / g2);
    den = (den / g2) * (r_den / g1);
    return *this;
  }

  Rational &operator/=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g1 = gcd(num, r_num);
    T g2 = gcd(den, r_den);
    num = (num / g1) * (r_den / g2);
    den = (den / g2) * (r_num / g1);
    if(den < 0) {
      num = -num;
      den = -den;
    }
    return *this;
  }

  Rational &operator+=(const T &i) { return (*this) += Rational{i}; }

  Rational &operator-=(const T &i) { return (*this) -= Rational{i}; }

  Rational &operator*=(const T &i) { return (*this) *= Rational{i}; }

  Rational &operator/=(const T &i) { return (*this) /= Rational{i}; }

  Rational operator+(const Rational &r) const { return Rational(*this) += r; }

  Rational operator-(const Rational &r) const { return Rational(*this) -= r; }

  Rational operator*(const Rational &r) const { return Rational(*this) *= r; }

  Rational operator/(const Rational &r) const { return Rational(*this) /= r; }

  Rational operator+(const T &i) const { return Rational(*this) += i; }

  Rational operator-(const T &i) const { return Rational(*this) -= i; }

  Rational operator*(const T &i) const { return Rational(*this) *= i; }

  Rational operator/(const T &i) const { return Rational(*this) /= i; }

  Rational operator-() const { return Rational{-num, den}; }

  Rational &operator++() {
    num += den;
    return *this;
  }

  Rational &operator--() {
    num -= den;
    return *this;
  }

#define define_cmp(op) \
  bool operator op (const Rational& r) const { return num * r.den op r.num * den; }

  define_cmp(==)

  define_cmp(!=)

  define_cmp(<)

  define_cmp(>)

  define_cmp(<=)

  define_cmp(>=)

#undef define_cmp

  template< typename Real = double >
  Real to_double() const {
    return static_cast < Real >(numerator()) / denominator();
  }

  Rational abs() const {
    return Rational{num < 0 ? -num : num, den};
  }

  friend ostream &operator<<(ostream &os, const Rational &r) {
    return os << r.numerator() << "/" << r.denominator();
  }
};
