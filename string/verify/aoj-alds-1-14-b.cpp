int main() {
  string T, P;

  cin >> T;
  cin >> P;
  RH rh(T), rh2(P);
  for(int i = 0; i + P.size() <= T.size(); i++) {
    if(rh.get(i, i + P.size()) == rh2.get(0, P.size())) {
      cout << i << endl;
    }
  }
}
