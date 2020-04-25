template< typename Monoid, typename F, size_t FULL = 1000 >
struct PersistentRedBlackTree : RedBlackTree< Monoid, F > {
  using RBT = RedBlackTree< Monoid, F >;
  using RBT::RedBlackTree;
  using Node = typename RBT::Node;

private:
  Node *clone(Node *t) override {
    return &(*RBT::pool.alloc() = *t);
  }

public:
  Node *rebuild(Node *r) {
    auto ret = RBT::dump(r);
    RBT::pool.clear();
    return RBT::build(ret);
  }

  bool almost_full() const {
    return this->pool.ptr < FULL;
  }
};
