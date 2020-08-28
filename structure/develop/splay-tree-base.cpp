/**
 * @brief Splay-Tree-Base(Splay木)
 */
template< typename Node >
struct SplayTreeBase {
public:
  bool is_root(Node *t) const {
    return !t->p || (t->p->l != t && t->p->r != t);
  }

  inline size_t count(Node *t) const { return t ? t->sz : 0; }

  void splay(Node *t) {
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

  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {
    splay(t);
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    return make_tuple(x.first, y.first, y.second);
  }

  virtual void push(Node *t) = 0;

  virtual Node *update(Node *t) = 0;

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

protected:

  Node *merge(Node *l) {
    return l;
  }

  Node *build_node(const vector< Node * > &v) {
    return build_node(0, v.size(), v);
  }

  Node *build_node(int l, int r, const vector< Node * > &v) {
    if(l + 1 >= r) return v[l];
    return merge(build_node(l, (l + r) >> 1, v), build_node((l + r) >> 1, r, v));
  }

  Node *push_front_node(Node *t, Node *z) {
    if(!t) {
      return z;
    } else {
      splay(t);
      Node *cur = get_left(t);
      splay(cur);
      z->p = cur;
      cur->l = z;
      splay(z);
      return z;
    }
  }

  Node *push_back_node(Node *t, Node *z) {
    if(!t) {
      return z;
    } else {
      splay(t);
      Node *cur = get_right(t);
      splay(cur);
      z->p = cur;
      cur->r = z;
      splay(z);
      return z;
    }
  }

  void insert_node(Node *&t, int k, Node *v) {
    splay(t);
    auto x = split(t, k);
    t = merge(merge(x.first, v), x.second);
  }

  void erase_node(Node *&t, int k) {
    splay(t);
    auto x = split(t, k);
    auto y = split(x.second, 1);
    delete y.first;
    t = merge(x.first, y.second);
  }
};
