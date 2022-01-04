#include <bits/stdc++.h>
using namespace std;

#define FOR(i,s,e) for(int i=(s);(i)<(int)(e);++(i))
#define REP(i,e) FOR(i,0,e)
#define all(o) (o).begin(), (o).end()

#define epb(x) emplace_back((x))
#define psb(x) push_back((x))
#define ppb(x) pop_back((x))

using ll = long long;
using VI = vector<int>;
using VVI = vector<VI>;
using VL = vector<ll>;
using VVL = vector<VL>;
using VD = vector<double>;
using VLD = vector<long double>;

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n;
  ll p = 0, d = 0, a = 0;
  REP(i,n) {
    string s; cin >> s;
    int x; cin >> x;
    if (s == "forward") {
      p += x;
      d += a*x;
    } else if (s == "down")
      a += x;
    else
      a -= x;
  }
  cout << p << endl;
  cout << d << endl;
  cout << p*d << endl;
  return 0;
}

