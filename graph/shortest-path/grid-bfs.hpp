vector< vector< int > > grid_bfs(vector< string > &s, char start, const string &wall = "#") {
  const int vx[] = {0, 1, 0, -1}, vy[] = {1, 0, -1, 0};
  vector< vector< int > > min_cost(s.size(), vector< int >(s[0].size(), -1));
  queue< pair< int, int > > que;
  for(int i = 0; i < s.size(); i++) {
    for(int j = 0; j < s[i].size(); j++) {
      if(s[i][j] == start) {
        que.emplace(i, j);
        min_cost[i][j] = 0;
      }
    }
  }
  while(!que.empty()) {
    auto p = que.front();
    que.pop();
    for(int i = 0; i < 4; i++) {
      int ny = p.first + vy[i], nx = p.second + vx[i];
      if(nx < 0 || ny < 0 || nx >= s[0].size() || ny >= s.size()) continue;
      if(min_cost[ny][nx] != -1) continue;
      if(wall.find(s[ny][nx]) != string::npos) continue;
      min_cost[ny][nx] = min_cost[p.first][p.second] + 1;
      que.emplace(ny, nx);
    }
  }
  return min_cost;
}
