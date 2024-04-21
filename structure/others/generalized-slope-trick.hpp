/**
 * @brief Generalized-Slope-Trick
 * 
 * @see https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8
 */
template< typename T >
struct LazySplayTree {
public:

  struct Node {
    Node *l, *r, *p;
    T key, sum;
    size_t sz;
    T add;

    bool is_root() const {
      return !p || (p->l != this && p->r != this);
    }

    Node(const T &key, const T &add) :
        key(key), sum(key), sz(1), add(add), l(nullptr), r(nullptr), p(nullptr) {}
  };

  LazySplayTree() = default;

  inline size_t count(const Node *t) { return t ? t->sz : 0; }

  Node *alloc(const T &key, const T &add = T()) {
    return new Node(key, add);
  }

  void splay(Node *t) {
    push(t);
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        push(r), push(q), push(t);
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }

  Node *erase(Node *t) {
    splay(t);
    Node *x = t->l, *y = t->r;
    delete t;
    if(!x) {
      t = y;
      if(t) t->p = nullptr;
    } else if(!y) {
      t = x;
      t->p = nullptr;
    } else {
      x->p = nullptr;
      t = get_right(x);
      splay(t);
      t->r = y;
      y->p = t;
    }
    return t;
  }

  Node *get_left(Node *t) const {
    while(t->l) t = t->l;
    return t;
  }

  Node *get_right(Node *t) const {
    while(t->r) t = t->r;
    return t;
  }

  void set_propagate(Node *t, const T &add) {
    splay(t);
    propagate(t, add);
    push(t);
  }

  pair< Node *, Node * > split(Node *t, int k) {
    if(!t) return {nullptr, nullptr};
    push(t);
    if(k <= count(t->l)) {
      auto x = split(t->l, k);
      t->l = x.second;
      t->p = nullptr;
      if(x.second) x.second->p = t;
      return {x.first, update(t)};
    } else {
      auto x = split(t->r, k - count(t->l) - 1);
      t->r = x.first;
      t->p = nullptr;
      if(x.first) x.first->p = t;
      return {update(t), x.second};
    }
  }

  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {
    splay(t);
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    return make_tuple(x.first, y.first, y.second);
  }

  pair< Node *, Node * > split_lower_bound(Node *t, const T &key) {
    if(!t) return {nullptr, nullptr};
    push(t);
    if(key <= t->key) {
      auto x = split_lower_bound(t->l, key);
      t->l = x.second;
      t->p = nullptr;
      if(x.second) x.second->p = t;
      return {x.first, update(t)};
    } else {
      auto x = split_lower_bound(t->r, key);
      t->r = x.first;
      t->p = nullptr;
      if(x.first) x.first->p = t;
      return {update(t), x.second};
    }
  }

  Node *merge_wuh(Node *t1, Node *t2) {
    if(!t1 and !t2) return nullptr;
    if(!t1) return splay(t2), t2;
    if(!t2) return splay(t1), t1;
    splay(t1), splay(t2);
    if(count(t1) < count(t2)) swap(t1, t2);
    auto[t2l, v, t2r] = split3(t2, count(t2) / 2, count(t2) / 2 + 1);
    auto[t1l, t1r] = split_lower_bound(t1, v->key);
    return merge(merge_wuh(t1l, t2l), v, merge_wuh(t1r, t2r));
  }

  template< typename ... Args >
  Node *merge(Node *l, Args ...rest) {
    Node *r = merge(rest...);
    if(!l && !r) return nullptr;
    if(!l) return splay(r), r;
    if(!r) return splay(l), l;
    splay(l), splay(r);
    l = get_right(l);
    splay(l);
    l->r = r;
    r->p = l;
    update(l);
    return l;
  }

  Node *insert_lower_bound(Node *t, const T &v) {
    if(t) {
      splay(t);
      auto x = split_lower_bound(t, v);
      return merge(merge(x.first, alloc(v)), x.second);
    } else {
      return alloc(v);
    }
  }

  Node *update(Node *t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum += t->l->sum;
    if(t->r) t->sz += t->r->sz, t->sum += t->r->sum;
    return t;
  }

  void propagate(Node *t, const T &x) {
    t->add += x;
    t->sum += count(t) * x;
    t->key += x;
  }

  void push(Node *t) {
    if(t->add) {
      if(t->l) propagate(t->l, t->add);
      if(t->r) propagate(t->r, t->add);
      t->add = 0;
    }
  }

private:
  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  Node *merge(Node *l) {
    return l;
  }
};

template< typename T >
struct GeneralizedSlopeTrick {

  const T INF = numeric_limits< T >::max() / 3;

  T min_f;
  LazySplayTree< T > st;
  typename LazySplayTree< T >::Node *L, *R;
private:
  void push_R(const T &a) {
    R = st.insert_lower_bound(R, a);
  }

  T top_R() {
    if(R) {
      st.splay(R = st.get_left(R));
      return R->key;
    } else {
      return INF;
    }
  }

  T pop_R() {
    T val = top_R();
    if(R) R = st.erase(R);
    return val;
  }

  void push_L(const T &a) {
    L = st.insert_lower_bound(L, a);
  }

  T top_L() {
    if(L) {
      st.splay(L = st.get_right(L));
      return L->key;
    } else {
      return -INF;
    }

  }

  T pop_L() {
    T val = top_L();
    if(L) L = st.erase(L);
    return val;
  }

  size_t size() {
    return st.count(L) + st.count(R);
  }

public:
   GeneralizedSlopeTrick() : min_f(0), L(nullptr), R(nullptr) {}

  struct Query {
    T lx, rx, min_f;
  };

  // return min f(x)
  Query query() {
    return (Query) {top_L(), top_R(), min_f};
  }

  // f(x) += a
  void add_all(const T &a) {
    min_f += a;
  }

  // add \_
  // f(x) += max(a - x, 0)
  void add_a_minus_x(const T &a) {
    min_f += max(T(0), a - top_R());
    push_R(a);
    push_L(pop_R());
  }

  // add _/
  // f(x) += max(x - a, 0)
  void add_x_minus_a(const T &a) {
    min_f += max(T(0), top_L() - a);
    push_L(a);
    push_R(pop_L());
  }

  // add \/
  // f(x) += abs(x - a)
  void add_abs(const T &a) {
    add_a_minus_x(a);
    add_x_minus_a(a);
  }

  // \/ -> \_
  // f_{new} (x) = min f(y) (y <= x)
  void clear_right() {
    R = nullptr;
  }

  // \/ -> _/
  // f_{new} (x) = min f(y) (y >= x)
  void clear_left() {
    L = nullptr;
  }

  // \/ -> \_/
  // f_{new} (x) = min f(y) (x-b <= y <= x-a)
  void shift(const T &a, const T &b) {
    assert(a <= b);
    if(L) st.set_propagate(L, a);
    if(R) st.set_propagate(R, b);
  }

  // \/. -> .\/
  // f_{new} (x) = f(x - a)
  void shift(const T &a) {
    shift(a, a);
  }

  // return f(x) L, R を破壊する
  T get(const T &x) {
    T ret = min_f;
    {
      auto[l, r] = st.split_lower_bound(L, x);
      if(r) {
        ret += r->sum;
        ret -= x * (T) st.count(r);
      }
      L = st.merge(l, r);
    }
    {
      auto[l, r] = st.split_lower_bound(R, x);
      if(l) {
        ret += x * (T) st.count(r);
        ret -= l->sum;
      }
      R = st.merge(l, r);
    }
    return ret;
  }

  // f(x) += g(x)
  void merge(GeneralizedSlopeTrick &g) {
    L = st.merge_wuh(L, g.L);
    R = st.merge_wuh(R, g.R);
    min_f += g.min_f;
  }
};
