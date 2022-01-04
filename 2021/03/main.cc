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
  VI c(1000);
  vector<string> v(n);
  int d = 0;
  REP(i,n) {
    cin >> v[i];
    if (i == 0) d = (int)v[i].size();
    REP(j,d) c[j] += (int)(v[i][j] - '0');
  }
  ll g = 0, e = 0;
  REP(i,d) {
    g <<= 1; e <<= 1;
    int m = n/2;
    if (n&1) m++;
    if (c[i] >= m) g++;
    else e++;
  }
  cout << g << endl;
  cout << e << endl;
  cout << g*e << endl;
  return 0;
}
