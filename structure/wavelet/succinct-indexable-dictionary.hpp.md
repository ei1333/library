---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
    title: Wavelet Matrix Point Add Rectangle Sum
  - icon: ':heavy_check_mark:'
    path: structure/wavelet/wavelet-matrix.hpp
    title: "Wavelet Matrix(\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-1549-2.test.cpp
    title: test/verify/aoj-1549-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-1549.test.cpp
    title: test/verify/aoj-1549.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2674-2.test.cpp
    title: test/verify/aoj-2674-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2674.test.cpp
    title: test/verify/aoj-2674.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-range-kth-smallest-2.test.cpp
    title: test/verify/yosupo-range-kth-smallest-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-range-kth-smallest.test.cpp
    title: test/verify/yosupo-range-kth-smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-rectangle-sum.test.cpp
    title: test/verify/yosupo-rectangle-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)"
    links: []
  bundledCode: "#line 1 \"structure/wavelet/succinct-indexable-dictionary.hpp\"\n\
    /**\n * @brief Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)\n */\n\
    struct SuccinctIndexableDictionary {\n  size_t length;\n  size_t blocks;\n  vector<\
    \ unsigned > bit, sum;\n\n  SuccinctIndexableDictionary() = default;\n\n  SuccinctIndexableDictionary(size_t\
    \ length) : length(length), blocks((length + 31) >> 5) {\n    bit.assign(blocks,\
    \ 0U);\n    sum.assign(blocks, 0U);\n  }\n\n  void set(int k) {\n    bit[k >>\
    \ 5] |= 1U << (k & 31);\n  }\n\n  void build() {\n    sum[0] = 0U;\n    for(int\
    \ i = 1; i < blocks; i++) {\n      sum[i] = sum[i - 1] + __builtin_popcount(bit[i\
    \ - 1]);\n    }\n  }\n\n  bool operator[](int k) {\n    return (bool((bit[k >>\
    \ 5] >> (k & 31)) & 1));\n  }\n\n  int rank(int k) {\n    return (sum[k >> 5]\
    \ + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));\n  }\n\n  int rank(bool\
    \ val, int k) {\n    return (val ? rank(k) : k - rank(k));\n  }\n};\n"
  code: "/**\n * @brief Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)\n\
    \ */\nstruct SuccinctIndexableDictionary {\n  size_t length;\n  size_t blocks;\n\
    \  vector< unsigned > bit, sum;\n\n  SuccinctIndexableDictionary() = default;\n\
    \n  SuccinctIndexableDictionary(size_t length) : length(length), blocks((length\
    \ + 31) >> 5) {\n    bit.assign(blocks, 0U);\n    sum.assign(blocks, 0U);\n  }\n\
    \n  void set(int k) {\n    bit[k >> 5] |= 1U << (k & 31);\n  }\n\n  void build()\
    \ {\n    sum[0] = 0U;\n    for(int i = 1; i < blocks; i++) {\n      sum[i] = sum[i\
    \ - 1] + __builtin_popcount(bit[i - 1]);\n    }\n  }\n\n  bool operator[](int\
    \ k) {\n    return (bool((bit[k >> 5] >> (k & 31)) & 1));\n  }\n\n  int rank(int\
    \ k) {\n    return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k\
    \ & 31)) - 1)));\n  }\n\n  int rank(bool val, int k) {\n    return (val ? rank(k)\
    \ : k - rank(k));\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/wavelet/succinct-indexable-dictionary.hpp
  requiredBy:
  - structure/wavelet/wavelet-matrix.hpp
  - structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-1549.test.cpp
  - test/verify/yosupo-rectangle-sum.test.cpp
  - test/verify/yosupo-range-kth-smallest-2.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum.test.cpp
  - test/verify/aoj-2674-2.test.cpp
  - test/verify/yosupo-range-kth-smallest.test.cpp
  - test/verify/aoj-1549-2.test.cpp
  - test/verify/aoj-2674.test.cpp
documentation_of: structure/wavelet/succinct-indexable-dictionary.hpp
layout: document
redirect_from:
- /library/structure/wavelet/succinct-indexable-dictionary.hpp
- /library/structure/wavelet/succinct-indexable-dictionary.hpp.html
title: "Succinct Indexable Dictionary(\u5B8C\u5099\u8F9E\u66F8)"
---
