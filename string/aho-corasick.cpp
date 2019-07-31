template< int char_size, int margin >
struct AhoCorasick : Trie< char_size + 1, margin > {
  using Trie< char_size + 1, margin >::Trie;

  const int FAIL = char_size;
  vector< int > correct;

  void build(bool heavy = true) {
    correct.resize(this->size());
    for(int i = 0; i < this->size(); i++) {
      correct[i] = (int) this->nodes[i].accept.size();
    }
    queue< int > que;
    for(int i = 0; i <= char_size; i++) {
      if(~this->nodes[0].nxt[i]) {
        this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;
        que.emplace(this->nodes[0].nxt[i]);
      } else {
        this->nodes[0].nxt[i] = 0;
      }
    }
    while(!que.empty()) {
      auto &now = this->nodes[que.front()];
      correct[que.front()] += correct[now.nxt[FAIL]];
      que.pop();
      for(int i = 0; i < char_size; i++) {
        if(now.nxt[i] == -1) continue;
        int fail = now.nxt[FAIL];
        while(this->nodes[fail].nxt[i] == -1) fail = this->nodes[fail].nxt[FAIL];
        this->nodes[now.nxt[i]].nxt[FAIL] = this->nodes[fail].nxt[i];
        if(heavy) {
          auto &u = this->nodes[now.nxt[i]].accept;
          auto &v = this->nodes[this->nodes[fail].nxt[i]].accept;
          vector< int > accept;
          set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
          u = accept;
        }
        que.emplace(now.nxt[i]);
      }

    }
  }

  map< int, int > match(const string &str, int now = 0) {
    map< int, int > result;
    for(auto &c : str) {
      while(this->nodes[now].nxt[c - margin] == -1) now = this->nodes[now].nxt[FAIL];
      now = this->nodes[now].nxt[c - margin];
      for(auto &v : this->nodes[now].accept) result[v] += 1;
    }
    return result;
  }

  pair< int, int > move(const char &c, int now) {
    int sum = 0;
    while(this->nodes[now].nxt[c - margin] == -1) now = this->nodes[now].nxt[FAIL];
    now = this->nodes[now].nxt[c - margin];
    sum += correct[now];
    return {sum, now};
  }
};
