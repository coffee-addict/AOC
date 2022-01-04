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
  int h = 1000, w = 1000;
  VVI b(h, VI(w));
  REP(i,n) {
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1; 
    if (x0 != x1 && y0 != y1) continue;
    if (x0 == x1) {
      if (y0 > y1) swap(y0,y1);
      FOR(i,y0,y1+1) b[i][x0]++;
    } else {
      if (x0 > x1) swap(x0,x1);
      FOR(j,x0,x1+1) b[y0][j]++;
    }
  }
  int res = 0;
  REP(i,h) REP(j,w) if (b[i][j] > 1) res++;
  cout << res << endl; 
  return 0;
}
