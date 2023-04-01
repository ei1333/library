---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/combinatorics/mod-int.hpp
    title: math/combinatorics/mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: structure/others/sliding-window-aggregation.hpp
    title: structure/others/sliding-window-aggregation.hpp
  - icon: ':question:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"test/verify/yosupo-queue-operate-all-composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
    \ std;\n\nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll\
    \ = (1LL << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
    \ {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed\
    \ << setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
    \ntemplate< typename T1, typename T2 >\nostream &operator<<(ostream &os, const\
    \ pair< T1, T2 >& p) {\n  os << p.first << \" \" << p.second;\n  return os;\n\
    }\n\ntemplate< typename T1, typename T2 >\nistream &operator>>(istream &is, pair<\
    \ T1, T2 > &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename\
    \ T >\nostream &operator<<(ostream &os, const vector< T > &v) {\n  for(int i =\
    \ 0; i < (int) v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \"\
    \ : \"\");\n  }\n  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream\
    \ &is, vector< T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate<\
    \ typename T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b &&\
    \ (a = b, true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1\
    \ &a, T2 b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64\
    \ >\nvector< T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate<\
    \ typename T, typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector<\
    \ decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename\
    \ T, typename V >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T\
    \ &t, const V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename\
    \ enable_if< is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto\
    \ &e : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n\
    \  explicit FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename...\
    \ Args >\n  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-queue-operate-all-composite.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/mod-int.hpp\"\ntemplate< int mod >\nstruct ModInt\
    \ {\n  int x;\n\n  ModInt() : x(0) {}\n\n  ModInt(int64_t y) : x(y >= 0 ? y %\
    \ mod : (mod - (-y) % mod) % mod) {}\n\n  ModInt &operator+=(const ModInt &p)\
    \ {\n    if((x += p.x) >= mod) x -= mod;\n    return *this;\n  }\n\n  ModInt &operator-=(const\
    \ ModInt &p) {\n    if((x += mod - p.x) >= mod) x -= mod;\n    return *this;\n\
    \  }\n\n  ModInt &operator*=(const ModInt &p) {\n    x = (int) (1LL * x * p.x\
    \ % mod);\n    return *this;\n  }\n\n  ModInt &operator/=(const ModInt &p) {\n\
    \    *this *= p.inverse();\n    return *this;\n  }\n\n  ModInt operator-() const\
    \ { return ModInt(-x); }\n\n  ModInt operator+(const ModInt &p) const { return\
    \ ModInt(*this) += p; }\n\n  ModInt operator-(const ModInt &p) const { return\
    \ ModInt(*this) -= p; }\n\n  ModInt operator*(const ModInt &p) const { return\
    \ ModInt(*this) *= p; }\n\n  ModInt operator/(const ModInt &p) const { return\
    \ ModInt(*this) /= p; }\n\n  bool operator==(const ModInt &p) const { return x\
    \ == p.x; }\n\n  bool operator!=(const ModInt &p) const { return x != p.x; }\n\
    \n  ModInt inverse() const {\n    int a = x, b = mod, u = 1, v = 0, t;\n    while(b\
    \ > 0) {\n      t = a / b;\n      swap(a -= t * b, b);\n      swap(u -= t * v,\
    \ v);\n    }\n    return ModInt(u);\n  }\n\n  ModInt pow(int64_t n) const {\n\
    \    ModInt ret(1), mul(x);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n\
    \      mul *= mul;\n      n >>= 1;\n    }\n    return ret;\n  }\n\n  friend ostream\
    \ &operator<<(ostream &os, const ModInt &p) {\n    return os << p.x;\n  }\n\n\
    \  friend istream &operator>>(istream &is, ModInt &a) {\n    int64_t t;\n    is\
    \ >> t;\n    a = ModInt< mod >(t);\n    return (is);\n  }\n\n  static int get_mod()\
    \ { return mod; }\n};\n\nusing modint = ModInt< mod >;\n#line 6 \"test/verify/yosupo-queue-operate-all-composite.test.cpp\"\
    \n\n#line 1 \"structure/others/sliding-window-aggregation.hpp\"\ntemplate< typename\
    \ SemiGroup >\nstruct SlidingWindowAggregation {\n  using F = function< SemiGroup(SemiGroup,\
    \ SemiGroup) >;\n \n  struct Node {\n    SemiGroup val, sum;\n \n    Node(const\
    \ SemiGroup &val, const SemiGroup &sum) : val(val), sum(sum) {}\n  };\n \n  SlidingWindowAggregation(F\
    \ f) : f(f) {}\n \n \n  const F f;\n  stack< Node > front, back;\n \n  bool empty()\
    \ const {\n    return front.empty() && back.empty();\n  }\n \n  size_t size()\
    \ const {\n    return front.size() + back.size();\n  }\n \n  SemiGroup fold_all()\
    \ const {\n    if(front.empty()) {\n      return back.top().sum;\n    } else if(back.empty())\
    \ {\n      return front.top().sum;\n    } else {\n      return f(front.top().sum,\
    \ back.top().sum);\n    }\n  }\n \n  void push(const SemiGroup &x) {\n    if(back.empty())\
    \ {\n      back.emplace(x, x);\n    } else {\n      back.emplace(x, f(back.top().sum,\
    \ x));\n    }\n  }\n \n  void pop() {\n    if(front.empty()) {\n      front.emplace(back.top().val,\
    \ back.top().val);\n      back.pop();\n      while(!back.empty()) {\n        front.emplace(back.top().val,\
    \ f(back.top().val, front.top().sum));\n        back.pop();\n      }\n    }\n\
    \    front.pop();\n  }\n};\n#line 8 \"test/verify/yosupo-queue-operate-all-composite.test.cpp\"\
    \n\nconst int MOD = 998244353;\nusing mint = ModInt< MOD >;\n\nint main() {\n\
    \  int Q;\n  cin >> Q;\n  using pi = pair< mint, mint >;\n  auto f = [](const\
    \ pi &a, const pi &b) -> pi {\n    return {a.first * b.first, a.second * b.first\
    \ + b.second};\n  };\n  SlidingWindowAggregation< pi > swa(f);\n  while(Q--) {\n\
    \    int t;\n    cin >> t;\n    if(t == 0) {\n      mint a, b;\n      cin >> a\
    \ >> b;\n      swa.push(pi(a, b));\n    } else if(t == 1) {\n      swa.pop();\n\
    \    } else {\n      mint x;\n      cin >> x;\n      if(swa.empty()) {\n     \
    \   cout << x << \"\\n\";\n      } else {\n        auto s = swa.fold_all();\n\
    \        cout << s.first * x + s.second << \"\\n\";\n      }\n    }\n  }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/mod-int.hpp\"\
    \n\n#include \"../../structure/others/sliding-window-aggregation.hpp\"\n\nconst\
    \ int MOD = 998244353;\nusing mint = ModInt< MOD >;\n\nint main() {\n  int Q;\n\
    \  cin >> Q;\n  using pi = pair< mint, mint >;\n  auto f = [](const pi &a, const\
    \ pi &b) -> pi {\n    return {a.first * b.first, a.second * b.first + b.second};\n\
    \  };\n  SlidingWindowAggregation< pi > swa(f);\n  while(Q--) {\n    int t;\n\
    \    cin >> t;\n    if(t == 0) {\n      mint a, b;\n      cin >> a >> b;\n   \
    \   swa.push(pi(a, b));\n    } else if(t == 1) {\n      swa.pop();\n    } else\
    \ {\n      mint x;\n      cin >> x;\n      if(swa.empty()) {\n        cout <<\
    \ x << \"\\n\";\n      } else {\n        auto s = swa.fold_all();\n        cout\
    \ << s.first * x + s.second << \"\\n\";\n      }\n    }\n  }\n}\n\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/mod-int.hpp
  - structure/others/sliding-window-aggregation.hpp
  isVerificationFile: true
  path: test/verify/yosupo-queue-operate-all-composite.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-queue-operate-all-composite.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-queue-operate-all-composite.test.cpp
- /verify/test/verify/yosupo-queue-operate-all-composite.test.cpp.html
title: test/verify/yosupo-queue-operate-all-composite.test.cpp
---
