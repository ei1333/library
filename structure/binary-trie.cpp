template< typename T, int MAX_LOG >
struct BinaryTrie {
  BinaryTrie *nxt[2];
  T lazy;
  int exist;
  bool fill;
  vector< int > accept;

  BinaryTrie() : exist(0), lazy(0), nxt{nullptr, nullptr} {}

  void add(const T &bit, int bit_index, int id) {
    propagate(bit_index);
    if(bit_index == -1) {
      ++exist;
      accept.push_back(id);
    } else {
      auto &to = nxt[(bit >> bit_index) & 1];
      if(!to) to = new BinaryTrie();
      to->add(bit, bit_index - 1, id);
      ++exist;
    }
  }

  void add(const T &bit, int id) {
    add(bit, MAX_LOG, id);
  }

  void add(const T &bit) {
    add(bit, exist);
  }

  void del(const T &bit, int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) {
      exist--;
    } else {
      nxt[(bit >> bit_index) & 1]->del(bit, bit_index - 1);
      exist--;
    }
  }

  void del(const T &bit) {
    del(bit, MAX_LOG);
  }


  pair< T, BinaryTrie * > max_element(int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) return {0, this};
    if(nxt[1] && nxt[1]->size()) {
      auto ret = nxt[1]->max_element(bit_index - 1);
      ret.first |= T(1) << bit_index;
      return ret;
    } else {
      return nxt[0]->max_element(bit_index - 1);
    }
  }

  pair< T, BinaryTrie * > min_element(int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) return {0, this};
    if(nxt[0] && nxt[0]->size()) {
      return nxt[0]->min_element(bit_index - 1);
    } else {
      auto ret = nxt[1]->min_element(bit_index - 1);
      ret.first |= T(1) << bit_index;
      return ret;
    }
  }

  T mex_query(int bit_index) { // distinct-values
    propagate(bit_index);
    if(bit_index == -1 || !nxt[0]) return 0;
    if(nxt[0]->size() == (T(1) << bit_index)) {
      T ret = T(1) << bit_index;
      if(nxt[1]) ret |= nxt[1]->mex_query(bit_index - 1);
      return ret;
    } else {
      return nxt[0]->mex_query(bit_index - 1);
    }
  }

  int64_t count_less(const T &bit, int bit_index) {
    propagate(bit_index);
    if(bit_index == -1) return 0;
    int64_t ret = 0;
    if((bit >> bit_index) & 1) {
      if(nxt[0]) ret += nxt[0]->size();
      if(nxt[1]) ret += nxt[1]->count_less(bit, bit_index - 1);
    } else {
      if(nxt[0]) ret += nxt[0]->count_less(bit, bit_index - 1);
    }
    return ret;
  }

  pair< T, BinaryTrie * > get_kth(int64_t k, int bit_index) { // 1-indexed
    propagate(bit_index);
    if(bit_index == -1) return {0, this};
    if((nxt[0] ? nxt[0]->size() : 0) < k) {
      auto ret = nxt[1]->get_kth(k - (nxt[0] ? nxt[0]->size() : 0), bit_index - 1);
      ret.first |= T(1) << bit_index;
      return ret;
    } else {
      return nxt[0]->get_kth(k, bit_index - 1);
    }
  }

  pair< T, BinaryTrie * > max_element() {
    assert(exist);
    return max_element(MAX_LOG);
  }

  pair< T, BinaryTrie * > min_element() {
    assert(exist);
    return min_element(MAX_LOG);
  }

  T mex_query() {
    return mex_query(MAX_LOG);
  }

  int size() const {
    return exist;
  }

  void xorpush(const T &bit) {
    lazy ^= bit;
  }

  int64_t count_less(const T &bit) {
    return count_less(bit, MAX_LOG);
  }

  pair< T, BinaryTrie * > get_kth(int64_t k) {
    assert(0 < k && k <= size());
    return get_kth(k, MAX_LOG);
  }

  void propagate(int bit_index) {
    if((lazy >> bit_index) & 1) swap(nxt[0], nxt[1]);
    if(nxt[0]) nxt[0]->lazy ^= lazy;
    if(nxt[1]) nxt[1]->lazy ^= lazy;
    lazy = 0;
  }
};
