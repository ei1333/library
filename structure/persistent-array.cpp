template< typename T, int LOG >
struct PersistentArray {
  struct Node {
    T data;
    Node *child[1 << LOG] = {};

    Node() {}

    Node(const T &data) : data(data) {}
  };

  Node *root;

  PersistentArray() : root(nullptr) {}

  T get(Node *t, int k) {
    if(k == 0) return t->data;
    return get(t->child[k & ((1 << LOG) - 1)], k >> LOG);
  }

  T get(const int &k) {
    return get(root, k);
  }

  pair< Node *, T * > mutable_get(Node *t, int k) {
    t = t ? new Node(*t) : new Node();
    if(k == 0) return {t, &t->data};
    auto p = mutable_get(t->child[k & ((1 << LOG) - 1)], k >> LOG);
    t->child[k & ((1 << LOG) - 1)] = p.first;
    return {t, p.second};
  }

  T *mutable_get(const int &k) {
    auto ret = mutable_get(root, k);
    root = ret.first;
    return ret.second;
  }

  Node *build(Node *t, const T &data, int k) {
    if(!t) t = new Node();
    if(k == 0) {
      t->data = data;
      return t;
    }
    auto p = build(t->child[k & ((1 << LOG) - 1)], data, k >> LOG);
    t->child[k & ((1 << LOG) - 1)] = p;
    return t;
  }

  void build(const vector< T > &v) {
    root = nullptr;
    for(int i = 0; i < v.size(); i++) {
      root = build(root, v[i], i);
    }
  }
};

