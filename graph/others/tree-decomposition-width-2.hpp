#pragma once

/**
 * @brief Tree Decomposition Width 2(木幅2の木分解)
 * @see https://ei1333.hateblo.jp/entry/2020/02/12/150319
 * 
 */
struct DecompNode {
  vector< int > bag, child;

  DecompNode() = default;
};

struct TreeDecompositionWidth2 {

  vector< vector< int > > g;

  explicit TreeDecompositionWidth2(int V) : g(V) {}

  void add_edge(int a, int b) {
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }

  vector< DecompNode > build() {
    const int N = (int) g.size();

    vector< int > used(N, -1), deg(N);
    queue< int > que;
    for(int i = 0; i < N; i++) {
      deg[i] = (int) g[i].size();
      if(deg[i] <= 2) que.emplace(i);
    }

    vector< set< int > > exists(N);
    for(int i = 0; i < N; i++) {
      for(auto &j : g[i]) {
        if(i < j) exists[i].emplace(j);
      }
    }

    vector< DecompNode > ret;
    ret.emplace_back();
    while(!que.empty()) {
      int idx = que.front();
      que.pop();
      if(deg[idx] > 2 || used[idx] != -1) continue;

      DecompNode r;
      r.bag.emplace_back(idx);
      int u = -1, v = -1;
      for(auto &to : g[idx]) {
        if(used[to] == -1) {
          (u == -1 ? u : v) = to;
          r.bag.emplace_back(to);
        } else if(used[to] >= 0) {
          r.child.emplace_back(used[to]);
          used[to] = -2;
        }
      }

      if(u == -1) {

      } else if(v == -1) {
        --deg[u];
      } else {
        if(u > v) swap(u, v);
        if(!exists[u].count(v)) {
          g[u].emplace_back(v);
          g[v].emplace_back(u);
          exists[u].emplace(v);
        } else {
          --deg[u];
          --deg[v];
        }
      }

      for(auto &to : g[idx]) {
        if(deg[to] <= 2) que.emplace(to);
      }

      used[idx] = (int) ret.size();
      deg[idx] = 0;
      ret.emplace_back(r);
    }
    for(int i = 0; i < N; i++) {
      if(deg[i] > 0) return {};
    }
    ret.front() = ret.back();
    ret.pop_back();
    return ret;
  }
};


void to_nice(vector< DecompNode > &g, int root = 0) {

  for(auto &p : g) {
    sort(p.bag.begin(), p.bag.end());
  }

  stack< int > st;
  st.emplace(root);

  while(!st.empty()) {
    int idx = st.top();
    st.pop();

    // join
    while(g[idx].child.size() > 2) {
      DecompNode r;
      r.child.resize(2);
      r.child[0] = g[idx].child.back();
      g[idx].child.pop_back();
      r.child[1] = g[idx].child.back();
      g[idx].child.pop_back();
      r.bag = g[idx].bag;
      g[idx].child.emplace_back((int) g.size());
      g.emplace_back(r);
    }

    if(g[idx].child.size() == 2) {
      for(auto &ch : g[idx].child) {
        if(g[ch].bag != g[idx].bag) {
          DecompNode r;
          r.child = {ch};
          r.bag = g[idx].bag;
          ch = (int) g.size();
          g.emplace_back(r);
        }
      }
    }

    // introduce / forget
    if(g[idx].child.size() == 1) {
      int &ch = g[idx].child[0];

      vector< int > latte, malta;
      set_difference(g[idx].bag.begin(), g[idx].bag.end(),
                     g[ch].bag.begin(), g[ch].bag.end(),
                     back_inserter(latte));
      set_difference(g[ch].bag.begin(), g[ch].bag.end(),
                     g[idx].bag.begin(), g[idx].bag.end(),
                     back_inserter(malta));
      if(latte.size() + malta.size() > 1) {
        DecompNode r;
        r.child = {ch};
        r.bag = g[idx].bag;
        if(!latte.empty()) {
          r.bag.erase(find(r.bag.begin(), r.bag.end(), latte.back()));
        } else {
          r.bag.emplace_back(malta.back());
        }
        ch = (int) g.size();
        g.emplace_back(r);
      }
    }

    // leaf
    if(g[idx].child.empty()) {
      if(g[idx].bag.size() > 1) {
        DecompNode r;
        r.bag = g[idx].bag;
        r.bag.pop_back();
        g[idx].child.emplace_back((int) g.size());
        g.emplace_back(r);
      }
    }

    for(auto &ch : g[idx].child) {
      st.emplace(ch);
    }
  }
}
