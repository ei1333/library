---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-staticrmq-5.test.cpp
    title: test/verify/yosupo-staticrmq-5.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Linear-RMQ
    links: []
  bundledCode: "#line 1 \"structure/others/linear-rmq.hpp\"\n/**\n * @brief Linear-RMQ\n\
    \ **/\ntemplate< typename Comp >\nstruct LinearRMQ {\n\n  vector< int > small;\n\
    \  vector< vector< int > > large;\n\n  LinearRMQ() = default;\n\n  Comp comp;\n\
    \n  static inline int msb(int c) {\n    return 31 - __builtin_clz(c);\n  }\n\n\
    \  static inline int ctz(int c) {\n    return __builtin_ctz(c);\n  }\n\n  inline\
    \ int get_min(int l, int r) const {\n    return comp(l, r) ? l : r;\n  }\n\n \
    \ explicit LinearRMQ(size_t n, const Comp &comp) : comp(comp) {\n    vector< int\
    \ > st;\n    st.reserve(32);\n    large.emplace_back();\n    large.front().reserve(n\
    \ / 32);\n    small.reserve(n);\n    for(int i = 0; i < n; i++) {\n      while(!st.empty()\
    \ && !comp(st.back(), i)) {\n        st.pop_back();\n      }\n      small.emplace_back(st.empty()\
    \ ? 0 : small[st.back()]);\n      small.back() |= 1 << (i % 32);\n      st.emplace_back(i);\n\
    \      if((i + 1) % 32 == 0) {\n        large.front().emplace_back(st.front());\n\
    \        st.clear();\n      }\n    }\n    for(int i = 1; (i << 1) <= n / 32; i\
    \ <<= 1) {\n      vector< int > v;\n      int csz = n / 32 + 1 - (i << 1);\n \
    \     v.reserve(csz);\n      for(int k = 0; k < csz; k++) {\n        v.emplace_back(get_min(large.back()[k],\
    \ large.back()[k + i]));\n      }\n      large.emplace_back(move(v));\n    }\n\
    \  }\n\n  int fold(int l, int r) const {\n    --r;\n    int left = l / 32 + 1;\n\
    \    int right = r / 32;\n    if(left < right) {\n      auto p = msb(right - left);\n\
    \      return get_min(\n          get_min((left - 1) * 32 + ctz(small[left * 32\
    \ - 1] & ~0 << l % 32), large[p][left]),\n          get_min(large[p][right - (1\
    \ << p)], right * 32 + ctz(small[r])));\n    } else if(left == right) {\n    \
    \  return get_min((left - 1) * 32 + ctz(small[left * 32 - 1] & ~0 << l % 32),\n\
    \                     left * 32 + ctz(small[r]));\n    } else {\n      return\
    \ right * 32 + ctz(small[r] & ~0 << l % 32);\n    }\n  }\n};\n\ntemplate< typename\
    \ Comp >\nLinearRMQ< Comp > get_linear_rmq(int n, const Comp &comp) {\n  return\
    \ LinearRMQ< Comp >(n, comp);\n}\n"
  code: "/**\n * @brief Linear-RMQ\n **/\ntemplate< typename Comp >\nstruct LinearRMQ\
    \ {\n\n  vector< int > small;\n  vector< vector< int > > large;\n\n  LinearRMQ()\
    \ = default;\n\n  Comp comp;\n\n  static inline int msb(int c) {\n    return 31\
    \ - __builtin_clz(c);\n  }\n\n  static inline int ctz(int c) {\n    return __builtin_ctz(c);\n\
    \  }\n\n  inline int get_min(int l, int r) const {\n    return comp(l, r) ? l\
    \ : r;\n  }\n\n  explicit LinearRMQ(size_t n, const Comp &comp) : comp(comp) {\n\
    \    vector< int > st;\n    st.reserve(32);\n    large.emplace_back();\n    large.front().reserve(n\
    \ / 32);\n    small.reserve(n);\n    for(int i = 0; i < n; i++) {\n      while(!st.empty()\
    \ && !comp(st.back(), i)) {\n        st.pop_back();\n      }\n      small.emplace_back(st.empty()\
    \ ? 0 : small[st.back()]);\n      small.back() |= 1 << (i % 32);\n      st.emplace_back(i);\n\
    \      if((i + 1) % 32 == 0) {\n        large.front().emplace_back(st.front());\n\
    \        st.clear();\n      }\n    }\n    for(int i = 1; (i << 1) <= n / 32; i\
    \ <<= 1) {\n      vector< int > v;\n      int csz = n / 32 + 1 - (i << 1);\n \
    \     v.reserve(csz);\n      for(int k = 0; k < csz; k++) {\n        v.emplace_back(get_min(large.back()[k],\
    \ large.back()[k + i]));\n      }\n      large.emplace_back(move(v));\n    }\n\
    \  }\n\n  int fold(int l, int r) const {\n    --r;\n    int left = l / 32 + 1;\n\
    \    int right = r / 32;\n    if(left < right) {\n      auto p = msb(right - left);\n\
    \      return get_min(\n          get_min((left - 1) * 32 + ctz(small[left * 32\
    \ - 1] & ~0 << l % 32), large[p][left]),\n          get_min(large[p][right - (1\
    \ << p)], right * 32 + ctz(small[r])));\n    } else if(left == right) {\n    \
    \  return get_min((left - 1) * 32 + ctz(small[left * 32 - 1] & ~0 << l % 32),\n\
    \                     left * 32 + ctz(small[r]));\n    } else {\n      return\
    \ right * 32 + ctz(small[r] & ~0 << l % 32);\n    }\n  }\n};\n\ntemplate< typename\
    \ Comp >\nLinearRMQ< Comp > get_linear_rmq(int n, const Comp &comp) {\n  return\
    \ LinearRMQ< Comp >(n, comp);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/others/linear-rmq.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-staticrmq-5.test.cpp
documentation_of: structure/others/linear-rmq.hpp
layout: document
redirect_from:
- /library/structure/others/linear-rmq.hpp
- /library/structure/others/linear-rmq.hpp.html
title: Linear-RMQ
---
