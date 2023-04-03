---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/heap/leftist-heap.hpp
    title: Leftist-Heap
  - icon: ':heavy_check_mark:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C
  bundledCode: "#line 1 \"test/verify/aoj-alds-1-9-c.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C\"\n\n#line\
    \ 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\
    \nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL\
    \ << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-alds-1-9-c.test.cpp\"\
    \n\n#line 1 \"structure/heap/leftist-heap.hpp\"\n/**\n * @brief Leftist-Heap\n\
    \ */\ntemplate< typename T, bool isMin = true >\nstruct LeftistHeap {\n  struct\
    \ Node {\n    Node *l, *r;\n    int s;\n    T key;\n    int idx;\n\n    explicit\
    \ Node(const T &key, int idx) : key(key), s(1), l(nullptr), r(nullptr), idx(idx)\
    \ {}\n  };\n\n  LeftistHeap() = default;\n\n  virtual Node *clone(Node *t) {\n\
    \    return t;\n  }\n\n  Node *alloc(const T &key, int idx = -1) {\n    return\
    \ new Node(key, idx);\n  }\n\n  Node *meld(Node *a, Node *b) {\n    if(!a || !b)\
    \ return a ? a : b;\n    if((a->key < b->key) ^ isMin) swap(a, b);\n    a = clone(a);\n\
    \    a->r = meld(a->r, b);\n    if(!a->l || a->l->s < a->r->s) swap(a->l, a->r);\n\
    \    a->s = (a->r ? a->r->s : 0) + 1;\n    return a;\n  }\n\n  Node *push(Node\
    \ *t, const T &key, int idx = -1) {\n    return meld(t, alloc(key, idx));\n  }\n\
    \n  Node *pop(Node *t) {\n    assert(t != nullptr);\n    return meld(t->l, t->r);\n\
    \  }\n\n  Node *make_root() {\n    return nullptr;\n  }\n};\n#line 6 \"test/verify/aoj-alds-1-9-c.test.cpp\"\
    \n\nint main() {\n  string s;\n  LeftistHeap< int, false > que;\n  auto root =\
    \ que.make_root();\n  while(cin >> s, s != \"end\") {\n    if(s == \"insert\"\
    ) {\n      int x;\n      cin >> x;\n      root = que.push(root, x);\n    } else\
    \ {\n      cout << root->key << \"\\n\";\n      root = que.pop(root);\n    }\n\
    \  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/heap/leftist-heap.hpp\"\
    \n\nint main() {\n  string s;\n  LeftistHeap< int, false > que;\n  auto root =\
    \ que.make_root();\n  while(cin >> s, s != \"end\") {\n    if(s == \"insert\"\
    ) {\n      int x;\n      cin >> x;\n      root = que.push(root, x);\n    } else\
    \ {\n      cout << root->key << \"\\n\";\n      root = que.pop(root);\n    }\n\
    \  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/heap/leftist-heap.hpp
  isVerificationFile: true
  path: test/verify/aoj-alds-1-9-c.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-alds-1-9-c.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-alds-1-9-c.test.cpp
- /verify/test/verify/aoj-alds-1-9-c.test.cpp.html
title: test/verify/aoj-alds-1-9-c.test.cpp
---
