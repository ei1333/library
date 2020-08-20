/**
 * @brief Persistent-Leftist-Heap
 */
template< typename T, bool isMin = true >
struct PersistentLeftistHeap : LeftistHeap< T, isMin > {
  using Node = typename LeftistHeap< T, isMin >::Node;

  Node *clone(Node *t) override {
    return new Node(*t);
  }
};
