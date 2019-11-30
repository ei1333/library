int main() {
  int N, Q;
  cin >> N >> Q;
  struct submax {
    int64 lsum, rsum, ans, all;
  } e{-infll, -infll, -infll, 0};
  auto f = [](const submax &a, const submax &b) {
    submax c;
    c.ans = max({a.ans, b.ans, a.rsum + b.lsum});
    c.all = a.all + b.all;
    c.lsum = max(a.lsum, a.all + b.lsum);
    c.rsum = max(b.rsum, b.all + a.rsum);
    return c;
  };
  auto g = [](submax a, int64 b, int p) {
    a.ans = max(b, b * p);
    a.all = b * p;
    a.lsum = a.ans;
    a.rsum = a.ans;
    return a;
  };
  auto h = [](int64 a, int64 b) {
    return b;
  };
  auto s = [](submax a) {
    swap(a.lsum, a.rsum);
    return a;
  };
  using LCT = LinkCutTree< submax, int64 >;
  LCT lct(f, g, h, s, e, infll);
  vector< LCT::Node * > nodes;
  for(int i = 0; i < N; i++) {
    int x;
    cin >> x;
    nodes.emplace_back(lct.make_node(i, g(e, x, 1)));
  }
  for(int i = 1; i < N; i++) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    lct.evert(nodes[y]); //忘れずに
    lct.link(nodes[y], nodes[x]);
  }
  while(Q--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    --b, --c;
    lct.evert(nodes[b]);
    lct.expose(nodes[c]);
    if(a == 1) {
      lct.set_propagate(nodes[c], d);
    } else {
      cout << nodes[c]->sum.ans << "\n";
    }
  }
}


