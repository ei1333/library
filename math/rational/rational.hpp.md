---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-1236.test.cpp
    title: test/verify/yukicoder-1236.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Rational (\u6709\u7406\u6570\u578B)"
    links: []
  bundledCode: "#line 1 \"math/rational/rational.hpp\"\n/**\n * @brief Rational (\u6709\
    \u7406\u6570\u578B)\n */\ntemplate< typename T >\nstruct Rational {\nprivate:\n\
    \  T num, den;\n\n  static T gcd(T a, T b) {\n    if(a < 0) a = -a;\n    if(b\
    \ < 0) b = -b;\n    return std::__gcd(a, b);\n  }\n\n  void normalize() {\n  \
    \  if(num == 0) {\n      den = 1;\n    } else {\n      T g = gcd(num, den);\n\
    \      num /= g;\n      den /= g;\n      if(den < 0) {\n        num = -num;\n\
    \        den = -den;\n      }\n    }\n  }\n\npublic:\n\n  Rational() : num(0),\
    \ den(1) {}\n\n  explicit Rational(const T &n) : num(n), den(1) {}\n\n  explicit\
    \ Rational(const T &n, const T &d) : num(n), den(d) {\n    normalize();\n  }\n\
    \n  Rational &operator=(const T &n) { return assign(n, 1); }\n\n  Rational &assign(const\
    \ T &n, const T &d) {\n    num = n;\n    den = d;\n    normalize();\n    return\
    \ *this;\n  }\n\n  T numerator() const { return num; }\n\n  T denominator() const\
    \ { return den; }\n\n  Rational &operator+=(const Rational &r) {\n    T r_num\
    \ = r.num, r_den = r.den;\n    T g = gcd(den, r_den);\n    den /= g;\n    num\
    \ = num * (r_den / g) + r_num * den;\n    g = gcd(num, g);\n    num /= g;\n  \
    \  den *= r_den / g;\n    return *this;\n  }\n\n  Rational &operator-=(const Rational\
    \ &r) {\n    T r_num = r.num, r_den = r.den;\n    T g = gcd(den, r_den);\n   \
    \ den /= g;\n    num = num * (r_den / g) - r_num * den;\n    g = gcd(num, g);\n\
    \    num /= g;\n    den *= r_den / g;\n    return *this;\n  }\n\n  Rational &operator*=(const\
    \ Rational &r) {\n    T r_num = r.num, r_den = r.den;\n    T g1 = gcd(num, r_den);\n\
    \    T g2 = gcd(den, r_num);\n    num = (num / g1) * (r_num / g2);\n    den =\
    \ (den / g2) * (r_den / g1);\n    return *this;\n  }\n\n  Rational &operator/=(const\
    \ Rational &r) {\n    T r_num = r.num, r_den = r.den;\n    T g1 = gcd(num, r_num);\n\
    \    T g2 = gcd(den, r_den);\n    num = (num / g1) * (r_den / g2);\n    den =\
    \ (den / g2) * (r_num / g1);\n    if(den < 0) {\n      num = -num;\n      den\
    \ = -den;\n    }\n    return *this;\n  }\n\n  Rational &operator+=(const T &i)\
    \ { return (*this) += Rational{i}; }\n\n  Rational &operator-=(const T &i) { return\
    \ (*this) -= Rational{i}; }\n\n  Rational &operator*=(const T &i) { return (*this)\
    \ *= Rational{i}; }\n\n  Rational &operator/=(const T &i) { return (*this) /=\
    \ Rational{i}; }\n\n  Rational operator+(const Rational &r) const { return Rational(*this)\
    \ += r; }\n\n  Rational operator-(const Rational &r) const { return Rational(*this)\
    \ -= r; }\n\n  Rational operator*(const Rational &r) const { return Rational(*this)\
    \ *= r; }\n\n  Rational operator/(const Rational &r) const { return Rational(*this)\
    \ /= r; }\n\n  Rational operator+(const T &i) const { return Rational(*this) +=\
    \ i; }\n\n  Rational operator-(const T &i) const { return Rational(*this) -= i;\
    \ }\n\n  Rational operator*(const T &i) const { return Rational(*this) *= i; }\n\
    \n  Rational operator/(const T &i) const { return Rational(*this) /= i; }\n\n\
    \  Rational operator-() const { return Rational{-num, den}; }\n\n  Rational &operator++()\
    \ {\n    num += den;\n    return *this;\n  }\n\n  Rational &operator--() {\n \
    \   num -= den;\n    return *this;\n  }\n\n#define define_cmp(op) \\\n  bool operator\
    \ op (const Rational& r) const { return num * r.den op r.num * den; }\n\n  define_cmp(==)\n\
    \n  define_cmp(!=)\n\n  define_cmp(<)\n\n  define_cmp(>)\n\n  define_cmp(<=)\n\
    \n  define_cmp(>=)\n\n#undef define_cmp\n\n  template< typename Real = double\
    \ >\n  Real to_double() const {\n    return static_cast < Real >(numerator())\
    \ / denominator();\n  }\n\n  Rational abs() const {\n    return Rational{num <\
    \ 0 ? -num : num, den};\n  }\n\n  friend ostream &operator<<(ostream &os, const\
    \ Rational &r) {\n    return os << r.numerator() << \"/\" << r.denominator();\n\
    \  }\n};\n"
  code: "/**\n * @brief Rational (\u6709\u7406\u6570\u578B)\n */\ntemplate< typename\
    \ T >\nstruct Rational {\nprivate:\n  T num, den;\n\n  static T gcd(T a, T b)\
    \ {\n    if(a < 0) a = -a;\n    if(b < 0) b = -b;\n    return std::__gcd(a, b);\n\
    \  }\n\n  void normalize() {\n    if(num == 0) {\n      den = 1;\n    } else {\n\
    \      T g = gcd(num, den);\n      num /= g;\n      den /= g;\n      if(den <\
    \ 0) {\n        num = -num;\n        den = -den;\n      }\n    }\n  }\n\npublic:\n\
    \n  Rational() : num(0), den(1) {}\n\n  explicit Rational(const T &n) : num(n),\
    \ den(1) {}\n\n  explicit Rational(const T &n, const T &d) : num(n), den(d) {\n\
    \    normalize();\n  }\n\n  Rational &operator=(const T &n) { return assign(n,\
    \ 1); }\n\n  Rational &assign(const T &n, const T &d) {\n    num = n;\n    den\
    \ = d;\n    normalize();\n    return *this;\n  }\n\n  T numerator() const { return\
    \ num; }\n\n  T denominator() const { return den; }\n\n  Rational &operator+=(const\
    \ Rational &r) {\n    T r_num = r.num, r_den = r.den;\n    T g = gcd(den, r_den);\n\
    \    den /= g;\n    num = num * (r_den / g) + r_num * den;\n    g = gcd(num, g);\n\
    \    num /= g;\n    den *= r_den / g;\n    return *this;\n  }\n\n  Rational &operator-=(const\
    \ Rational &r) {\n    T r_num = r.num, r_den = r.den;\n    T g = gcd(den, r_den);\n\
    \    den /= g;\n    num = num * (r_den / g) - r_num * den;\n    g = gcd(num, g);\n\
    \    num /= g;\n    den *= r_den / g;\n    return *this;\n  }\n\n  Rational &operator*=(const\
    \ Rational &r) {\n    T r_num = r.num, r_den = r.den;\n    T g1 = gcd(num, r_den);\n\
    \    T g2 = gcd(den, r_num);\n    num = (num / g1) * (r_num / g2);\n    den =\
    \ (den / g2) * (r_den / g1);\n    return *this;\n  }\n\n  Rational &operator/=(const\
    \ Rational &r) {\n    T r_num = r.num, r_den = r.den;\n    T g1 = gcd(num, r_num);\n\
    \    T g2 = gcd(den, r_den);\n    num = (num / g1) * (r_den / g2);\n    den =\
    \ (den / g2) * (r_num / g1);\n    if(den < 0) {\n      num = -num;\n      den\
    \ = -den;\n    }\n    return *this;\n  }\n\n  Rational &operator+=(const T &i)\
    \ { return (*this) += Rational{i}; }\n\n  Rational &operator-=(const T &i) { return\
    \ (*this) -= Rational{i}; }\n\n  Rational &operator*=(const T &i) { return (*this)\
    \ *= Rational{i}; }\n\n  Rational &operator/=(const T &i) { return (*this) /=\
    \ Rational{i}; }\n\n  Rational operator+(const Rational &r) const { return Rational(*this)\
    \ += r; }\n\n  Rational operator-(const Rational &r) const { return Rational(*this)\
    \ -= r; }\n\n  Rational operator*(const Rational &r) const { return Rational(*this)\
    \ *= r; }\n\n  Rational operator/(const Rational &r) const { return Rational(*this)\
    \ /= r; }\n\n  Rational operator+(const T &i) const { return Rational(*this) +=\
    \ i; }\n\n  Rational operator-(const T &i) const { return Rational(*this) -= i;\
    \ }\n\n  Rational operator*(const T &i) const { return Rational(*this) *= i; }\n\
    \n  Rational operator/(const T &i) const { return Rational(*this) /= i; }\n\n\
    \  Rational operator-() const { return Rational{-num, den}; }\n\n  Rational &operator++()\
    \ {\n    num += den;\n    return *this;\n  }\n\n  Rational &operator--() {\n \
    \   num -= den;\n    return *this;\n  }\n\n#define define_cmp(op) \\\n  bool operator\
    \ op (const Rational& r) const { return num * r.den op r.num * den; }\n\n  define_cmp(==)\n\
    \n  define_cmp(!=)\n\n  define_cmp(<)\n\n  define_cmp(>)\n\n  define_cmp(<=)\n\
    \n  define_cmp(>=)\n\n#undef define_cmp\n\n  template< typename Real = double\
    \ >\n  Real to_double() const {\n    return static_cast < Real >(numerator())\
    \ / denominator();\n  }\n\n  Rational abs() const {\n    return Rational{num <\
    \ 0 ? -num : num, den};\n  }\n\n  friend ostream &operator<<(ostream &os, const\
    \ Rational &r) {\n    return os << r.numerator() << \"/\" << r.denominator();\n\
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/rational/rational.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-1236.test.cpp
documentation_of: math/rational/rational.hpp
layout: document
redirect_from:
- /library/math/rational/rational.hpp
- /library/math/rational/rational.hpp.html
title: "Rational (\u6709\u7406\u6570\u578B)"
---
