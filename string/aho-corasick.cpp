template< int char_size, int margin >
struct AhoCorasick : Trie< char_size, margin > {
  using TRIE = Trie< char_size, margin >;
  static const int FAIL = char_size;
  vector< int > correct;

  AhoCorasick() : TRIE() {}

  void build(bool heavy = true) {
    correct.resize(TRIE::nodes.size());
    for(int i = 0; i < TRIE::nodes.size(); i++) {
      correct[i] = (int) TRIE::nodes[i].accept.size();
    }

    queue< int > que;
    for(int i = 0; i <= char_size; i++) {
      if(~TRIE::nodes[0].nxt[i]) {
        TRIE::nodes[TRIE::nodes[0].nxt[i]].nxt[FAIL] = 0;
        que.emplace(TRIE::nodes[0].nxt[i]);
      } else {
        TRIE::nodes[0].nxt[i] = 0;
      }
    }
    while(!que.empty()) {
      TrieNode< char_size > &now = TRIE::nodes[que.front()];
      correct[que.front()] += correct[now.nxt[FAIL]];
      que.pop();
      for(int i = 0; i < char_size; i++) {
        if(now.nxt[i] == -1) continue;
        int fail = now.nxt[FAIL];
        while(TRIE::nodes[fail].nxt[i] == -1) fail = TRIE::nodes[fail].nxt[FAIL];
        TRIE::nodes[now.nxt[i]].nxt[FAIL] = TRIE::nodes[fail].nxt[i];
        if(heavy) {
          auto &u = TRIE::nodes[now.nxt[i]].accept;
          auto &v = TRIE::nodes[TRIE::nodes[fail].nxt[i]].accept;
          vector< int > accept;
          set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
          u = accept;
        }
        que.emplace(now.nxt[i]);
      }

    }
  }

  int match(const string &str, vector< int > &result, int now = 0) {
    result.assign(TRIE::size(), 0);
    int count = 0;
    for(auto &c : str) {
      while(TRIE::nodes[now].nxt[c - margin] == -1) now = TRIE::nodes[now].nxt[FAIL];
      now = TRIE::nodes[now].nxt[c - margin];
      count += correct[now];
      for(auto &v : TRIE::nodes[now].accept) ++result[v];
    }
    return (count);
  }

  int move(const char &c, int &now) {
    int count = 0;
    while(TRIE::nodes[now].nxt[c - margin] == -1) now = TRIE::nodes[now].nxt[FAIL];
    now = TRIE::nodes[now].nxt[c - margin];
    count += correct[now];
    return (count);
  }
};
