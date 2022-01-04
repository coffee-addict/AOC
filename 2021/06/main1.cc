#include <bits/stdc++.h>
using namespace std;

#define FOR(i,s,e) for(int i=(s);(i)<(int)(e);++(i))
#define REP(i,e) FOR(i,0,e)
#define all(o) (o).begin(), (o).end()
#define epb(x) emplace_back((x))
#define psb(x) push_back((x))
#define ppb(x) pop_back((x))
#define mkp(x,y) make_pair((x),(y))
#define mkt(x,y,z) make_tuple((x),(y),(z))
#define nth(x,n) get<(n)>((x))

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
  VI x(n);
  REP(i,n) cin >> x[i];
  REP(c,80) {
//  REP(c,18) {
    int y = 0;
    REP(i,x.size()) {
      x[i]--;
      if (x[i] < 0) {
        x[i] = 6;
        y++;
      }
    }
    REP(i,y) x.epb(8);
//REP(i,x.size()) cout << x[i] << ' ';
//cout << endl; 
  }
  cout << x.size() << endl;
  return 0;
}
