/**
 * @brief Splay-Tree-Base(Splay木)
 */
template< typename Node >
struct SplayTreeBase {
public:
  using NP = Node *;

  bool is_root(const NP &t) const { return !t->p || (t->p->l != t && t->p->r != t); }

  inline size_t count(const NP &t) const { return t ? t->sz : 0; }

  void splay(NP t) {
    push(t);
    while(!is_root(t)) {
      auto *q = t->p;
      if(!is_root(t)) {
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

  NP erase(NP t) {
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

  NP splay_front(NP t) {
    splay(t);
    while(t->l) t = t->l;
    splay(t);
    return t;
  }

  NP splay_back(NP t) {
    splay(t);
    while(t->r) t = t->r;
    splay(t);
    return t;
  }

  pair< NP, NP > split(NP t, int k) {
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

  template< typename... Args >
  NP merge(NP p, Args... args) {
    return merge(p, merge(args...));
  }

  NP merge(NP l, NP r) {
    if(!l && !r) return nullptr;
    if(!l) return splay(r), r;
    if(!r) return splay(l), l;
    splay(l), splay(r);
    l = splay_back(l);
    l->r = r;
    r->p = l;
    update(l);
    return l;
  }

  tuple< NP, NP, NP > split3(NP t, int a, int b) {
    splay(t);
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    return make_tuple(x.first, y.first, y.second);
  }

  virtual void push(NP t) = 0;

  virtual Node *update(NP t) = 0;

private:

  void rotr(NP t) {
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

  void rotl(NP t) {
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

  NP build(int l, int r, const vector< NP > &v) {
    if(l + 1 >= r) return v[l];
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

protected:

  NP build_node(const vector< NP > &v) {
    return build(0, v.size(), v);
  }

  NP insert_node(NP t, int k, NP v) {
    splay(t);
    auto x = split(t, k);
    return merge(x.first, v, x.second);
  }

  NP erase_node(NP t, int k) {
    splay(t);
    auto x = split(t, k);
    auto y = split(x.second, 1);
    delete y.first;
    return merge(x.first, y.second);
  }
};
