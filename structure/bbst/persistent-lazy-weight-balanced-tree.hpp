/**
 * @brief Persistent-Lazy-Weight-Balanced-Tree(永続遅延伝搬重み平衡木)
 */
template< typename Monoid, typename OperatorMonoid, typename F, typename G, typename H, size_t FULL = 1000 >
struct PersistentLazyWeightBalancedTree : LazyWeightBalancedTree< Monoid, OperatorMonoid, F, G, H > {
  using LWBT = LazyWeightBalancedTree< Monoid, OperatorMonoid, F, G, H >;
  using LWBT::LazyWeightBalancedTree;
  using Node = typename LWBT::Node;

private:
  Node *clone(Node *t) override {
    return &(*LWBT::pool.alloc() = *t);
  }

public:
  Node *rebuild(Node *r) {
    auto ret = LWBT::dump(r);
    LWBT::pool.clear();
    return LWBT::build(ret);
  }

  bool almost_full() const {
    return this->pool.ptr < FULL;
  }
};
