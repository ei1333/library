/**
 * @brief Persistent-Binary-Trie
 */
template< typename T, int MAX_LOG, typename D = int >
struct PersistentBinaryTrie : BinaryTrie< T, MAX_LOG, D > {
  using BinaryTrie< T, MAX_LOG, D >::BinaryTrie;
  using Node = typename BinaryTrie< T, MAX_LOG, D >::Node;
private:
  Node *clone(Node *t) { return new Node(*t); }
};
