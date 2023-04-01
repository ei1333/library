---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-queue-operate-all-composite.test.cpp
    title: test/verify/yosupo-queue-operate-all-composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"structure/others/sliding-window-aggregation.hpp\"\ntemplate<\
    \ typename SemiGroup >\nstruct SlidingWindowAggregation {\n  using F = function<\
    \ SemiGroup(SemiGroup, SemiGroup) >;\n \n  struct Node {\n    SemiGroup val, sum;\n\
    \ \n    Node(const SemiGroup &val, const SemiGroup &sum) : val(val), sum(sum)\
    \ {}\n  };\n \n  SlidingWindowAggregation(F f) : f(f) {}\n \n \n  const F f;\n\
    \  stack< Node > front, back;\n \n  bool empty() const {\n    return front.empty()\
    \ && back.empty();\n  }\n \n  size_t size() const {\n    return front.size() +\
    \ back.size();\n  }\n \n  SemiGroup fold_all() const {\n    if(front.empty())\
    \ {\n      return back.top().sum;\n    } else if(back.empty()) {\n      return\
    \ front.top().sum;\n    } else {\n      return f(front.top().sum, back.top().sum);\n\
    \    }\n  }\n \n  void push(const SemiGroup &x) {\n    if(back.empty()) {\n  \
    \    back.emplace(x, x);\n    } else {\n      back.emplace(x, f(back.top().sum,\
    \ x));\n    }\n  }\n \n  void pop() {\n    if(front.empty()) {\n      front.emplace(back.top().val,\
    \ back.top().val);\n      back.pop();\n      while(!back.empty()) {\n        front.emplace(back.top().val,\
    \ f(back.top().val, front.top().sum));\n        back.pop();\n      }\n    }\n\
    \    front.pop();\n  }\n};\n"
  code: "template< typename SemiGroup >\nstruct SlidingWindowAggregation {\n  using\
    \ F = function< SemiGroup(SemiGroup, SemiGroup) >;\n \n  struct Node {\n    SemiGroup\
    \ val, sum;\n \n    Node(const SemiGroup &val, const SemiGroup &sum) : val(val),\
    \ sum(sum) {}\n  };\n \n  SlidingWindowAggregation(F f) : f(f) {}\n \n \n  const\
    \ F f;\n  stack< Node > front, back;\n \n  bool empty() const {\n    return front.empty()\
    \ && back.empty();\n  }\n \n  size_t size() const {\n    return front.size() +\
    \ back.size();\n  }\n \n  SemiGroup fold_all() const {\n    if(front.empty())\
    \ {\n      return back.top().sum;\n    } else if(back.empty()) {\n      return\
    \ front.top().sum;\n    } else {\n      return f(front.top().sum, back.top().sum);\n\
    \    }\n  }\n \n  void push(const SemiGroup &x) {\n    if(back.empty()) {\n  \
    \    back.emplace(x, x);\n    } else {\n      back.emplace(x, f(back.top().sum,\
    \ x));\n    }\n  }\n \n  void pop() {\n    if(front.empty()) {\n      front.emplace(back.top().val,\
    \ back.top().val);\n      back.pop();\n      while(!back.empty()) {\n        front.emplace(back.top().val,\
    \ f(back.top().val, front.top().sum));\n        back.pop();\n      }\n    }\n\
    \    front.pop();\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/others/sliding-window-aggregation.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-queue-operate-all-composite.test.cpp
documentation_of: structure/others/sliding-window-aggregation.hpp
layout: document
redirect_from:
- /library/structure/others/sliding-window-aggregation.hpp
- /library/structure/others/sliding-window-aggregation.hpp.html
title: structure/others/sliding-window-aggregation.hpp
---
