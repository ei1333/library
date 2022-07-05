template< class T >
struct OrderedMultiSet : RandomizedBinarySearchTree< T >
{
  using RBST = RandomizedBinarySearchTree< T >;
  using Node = typename RBST::Node;

  OrderedMultiSet(int sz) : RBST(sz, [&](T x, T y) { return x; }, T()) {}

  T kth_element(Node *t, int k)
  {
    if(k < RBST::count(t->l)) return kth_element(t->l, k);
    if(k == RBST::count(t->l)) return t->key;
    return kth_element(t->r, k - RBST::count(t->l) - 1);
  }

  virtual void insert_key(Node *&t, const T &x)
  {
    RBST::insert(t, lower_bound(t, x), x);
  }

  void erase_key(Node *&t, const T &x)
  {
    if(!count(t, x)) return;
    RBST::erase(t, lower_bound(t, x));
  }

  int count(Node *t, const T &x)
  {
    return upper_bound(t, x) - lower_bound(t, x);
  }

  int lower_bound(Node *t, const T &x)
  {
    if(!t) return 0;
    if(x <= t->key) return lower_bound(t->l, x);
    return lower_bound(t->r, x) + RBST::count(t->l) + 1;
  }

  int upper_bound(Node *t, const T &x)
  {
    if(!t) return 0;
    if(x < t->key) return upper_bound(t->l, x);
    return upper_bound(t->r, x) + RBST::count(t->l) + 1;
  }
};
template< class T >
struct OrderedSet : OrderedMultiSet< T >
{
  using SET = OrderedMultiSet< T >;
  using RBST = typename SET::RBST;
  using Node = typename RBST::Node;

  OrderedSet(int sz) : OrderedMultiSet< T >(sz) {}

  void insert_key(Node *&t, const T &x) override
  {
    if(SET::count(t, x)) return;
    RBST::insert(t, SET::lower_bound(t, x), x);
  }
};
