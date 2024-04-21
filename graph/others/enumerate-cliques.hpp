/**
 * @brief Enumerate Cliques(クリーク全列挙)
 * @see https://www.slideshare.net/wata_orz/ss-12131479
 * 
 */
template< typename Matrix >
vector< vector< int > > enumerate_cliques(Matrix &g) {

  int N = (int) g.size(), M = 0;
  vector< int > deg(N);
  vector< vector< int > > edge(N, vector< int >(N));
  for(int i = 0; i < N; i++) {
    for(auto p : g[i]) deg[i] += p;
    M += deg[i];
  }
  int lim = (int) sqrt(M);

  vector< vector< int > > cliques;

  auto add_clique = [&](const vector< int > &rem, bool last) {
    vector< int > neighbor((int) rem.size() - last);
    for(int i = 0; i < (int) neighbor.size(); i++) {
      for(int j = 0; j < (int) neighbor.size(); j++) {
        if(i != j && !g[rem[i]][rem[j]]) neighbor[i] |= 1 << j;
      }
    }
    for(int i = 1 - last; i < (1 << neighbor.size()); i++) {
      bool ok = true;
      for(int j = 0; j < (int) neighbor.size(); j++) {
        if((i >> j) & 1) {
          if(i & neighbor[j]) {
            ok = false;
            break;
          }
        }
      }
      if(ok) {
        vector< int > clique;
        if(last) clique.emplace_back(rem.back());
        for(int j = 0; j < (int) neighbor.size(); j++) {
          if((i >> j) & 1) clique.emplace_back(rem[j]);
        }
        cliques.emplace_back(clique);
      }
    }
  };

  vector< int > used(N);
  queue< int > que;
  for(int i = 0; i < N; i++) {
    if(deg[i] < lim) {
      used[i] = true;
      que.emplace(i);
    }
  }
  while(!que.empty()) {
    int idx = que.front();
    que.pop();
    vector< int > rem;
    for(int k = 0; k < N; k++) {
      if(g[idx][k]) rem.emplace_back(k);
    }
    rem.emplace_back(idx);
    add_clique(rem, true);
    used[idx] = true;
    for(int k = 0; k < N; k++) {
      if(g[idx][k]) {
        g[idx][k] = false;
        g[k][idx] = false;
        --deg[k];
        if(!used[k] && deg[k] < lim) {
          used[k] = true;
          que.emplace(k);
        }
      }
    }
  }
  vector< int > rem;
  for(int i = 0; i < N; i++) {
    if(!used[i]) rem.emplace_back(i);
  }
  add_clique(rem, false);
  return cliques;
}
