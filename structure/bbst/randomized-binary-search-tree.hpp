template< typename T >
class RandomizedBinarySearchTree {

  using F = function< T(T, T) >;

private:

  struct Node {
    Node *l, *r;
    size_t cnt;
    T key, sum;

    Node() = default;

    Node(const T &k) : cnt(1), key(k), sum(k), l(nullptr), r(nullptr) {}
  };

  inline int xor128() {
    static int x = 123456789;
    static int y = 362436069;
    static int z = 521288629;
    static int w = 88675123;
    int t;

    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }

  Node *build(int l, int r, const vector< T > &v) {
    if(l + 1 >= r) return alloc(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  void dump(Node *t, typename vector< T >::iterator &it) const {
    if(!t) return;
    dump(t->l, it);
    *it = t->key;
    dump(t->r, ++it);
  }

  inline size_t count(const Node *t) const {
    return t ? t->cnt : 0;
  }

  inline T sum(const Node *t) const {
    return t ? t->sum : e;
  }

  inline Node *update(Node *t) {
    t->cnt = count(t->l) + count(t->r) + 1;
    t->sum = f(f(sum(t->l), t->key), sum(t->r));
    return t;
  }

  vector< Node > pool;
  int ptr;
  const F f;
  const T e;

public:

  RandomizedBinarySearchTree(size_t sz, const F &f, const T &e) : pool(sz), f(f), ptr(0), e(e) {}

  inline Node *alloc(const T &v) {
    return &(pool[ptr++] = Node(v));
  }

  Node *merge(Node *l, Node *r) {
    if(!l || !r) return l ? l : r;
    if(xor128() % (l->cnt + r->cnt) < l->cnt) {
      l->r = merge(l->r, r);
      return update(l);
    } else {
      r->l = merge(l, r->l);
      return update(r);
    }
  }

  template< typename... Args >
  Node *merge(Node *p, Args... args) {
    return merge(p, merge(args...));
  }

  pair< Node *, Node * > split(Node *t, int k) {
    if(!t) return {t, t};
    if(k <= count(t->l)) {
      auto s = split(t->l, k);
      t->l = s.second;
      return {s.first, update(t)};
    } else {
      auto s = split(t->r, k - count(t->l) - 1);
      t->r = s.first;
      return {update(t), s.second};
    }
  }

  Node *build(const vector< T > &v) {
    ptr = 0;
    return build(0, (int) v.size(), v);
  }

  vector< T > dump(Node *t) const {
    vector< T > v(count(t));
    auto it = begin(v);
    dump(t, it);
    return v;
  }

  string to_string(Node *r) {
    auto s = dump(r);
    string ret;
    for(int i = 0; i < s.size(); i++) ret += std::to_string(s[i]) + ", ";
    return ret;
  }

  void insert(Node *&t, int k, const T &v) {
    auto x = split(t, k);
    t = merge(merge(x.first, alloc(v)), x.second);
  }

  void push_front(Node *&t, const T &v) {
    t = merge(alloc(v), t);
  }

  void push_back(Node *&t, const T &v) {
    t = merge(t, alloc(v));
  }

  T pop_front(Node *&t) {
    auto ret = split(t, 1);
    t = ret.second;
    return ret.first->key;
  }

  T pop_back(Node *&t) {
    auto ret = split(t, count(t) - 1);
    t = ret.first;
    return ret.second->key;
  }

  void erase(Node *&t, int k) {
    auto x = split(t, k);
    t = merge(x.first, split(x.second, 1).second);
  }

  T query(Node *&t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, merge(y.first, y.second));
    return ret;
  }

  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    return make_tuple(x.first, y.first, y.second);
  }

  void set_element(Node *&t, int k, const T &x) {
    if(k < count(t->l)) set_element(t->l, k, x);
    else if(k == count(t->l)) t->key = t->sum = x;
    else set_element(t->r, k - count(t->l) - 1, x);
    t = update(t);
  }

  size_t size(Node *t) const {
    return count(t);
  }

  bool empty(Node *t) const {
    return !t;
  }
};

