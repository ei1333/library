int main() {
  int N;
  cin >> N;
  vector< int > h(N);
  cin >> h;
  cout << largest_rectangle(h) << endl;
}
