template< typename T >
struct BinaryTrieNode {
  using Node = BinaryTrieNode< T >;
 
  BinaryTrieNode< T > *nxt[2];
  int max_index;
 
  BinaryTrieNode() : max_index(-1) {
    nxt[0] = nxt[1] = nullptr;
  }
 
  void update_direct(int id) {
    max_index = max(max_index, id);
  }
 
  void update_child(Node *child, int id) {
    max_index = max(max_index, id);
  }
 
  Node *add(const T &bit, int bit_index, int id, bool need = true) {
    Node *node = need ? new Node(*this) : this;
    if(bit_index == -1) {
      node->update_direct(id);
    } else {
      const int c = (bit >> bit_index) & 1;
      if(node->nxt[c] == nullptr) node->nxt[c] = new Node(), need = false;
      node->nxt[c] = node->nxt[c]->add(bit, bit_index - 1, id, need);
      node->update_child(node->nxt[c], id);
    }
    return node;
  }
 
  inline T min_query(T bit, int bit_index, int bit2, int l) {
    if(bit_index == -1) return bit;
    int c = (bit2 >> bit_index) & 1;
    if(nxt[c] != nullptr && l <= nxt[c]->max_index) {
      return nxt[c]->min_query(bit, bit_index - 1, bit2, l);
    } else {
      return nxt[1 ^ c]->min_query(bit | (1LL << bit_index), bit_index - 1, bit2, l);
    }
  }
};
 
template< typename T, int MAX_LOG >
struct PersistentBinaryTrie {
  using Node = BinaryTrieNode< T >;
  Node *root;
 
  PersistentBinaryTrie(Node *root) : root(root) {}
 
  PersistentBinaryTrie() : root(new Node()) {}
 
  PersistentBinaryTrie add(const T &bit, int id) {
    return PersistentBinaryTrie(root->add(bit, MAX_LOG, id));
  }
 
  T min_query(int bit, int l) {
    return root->min_query(0, MAX_LOG, bit, l);
  }
};
