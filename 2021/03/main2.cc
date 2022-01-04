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
  vector<string> vo = v, vc = v;
  REP(i,d) {
    if (vo.size() == 1) break;
    int k = 0;
    REP(j,vo.size()) k += (int)(vo[j][i]-'0');
    int m = vo.size()/2;
    if (vo.size()&1) m++;
    char x = m <= k ? '1' : '0';
    vector<string> vo2;
    REP(j,vo.size()) if (vo[j][i] == x) vo2.epb(vo[j]);
    vo = vo2;
  }
  REP(i,d) {
    if (vc.size() == 1) break;
    int k = 0;
    REP(j,vc.size()) k += (int)(vc[j][i]-'0');
    int m = vc.size()/2;
    if (vc.size()&1) m++;
    char x = k < m ? '1' : '0';
    vector<string> vc2;
    REP(j,vc.size()) if (vc[j][i] == x) vc2.epb(vc[j]);
    vc = vc2;
  }
  ll lo = 0, lc = 0;
  REP(i,d) {
    lo <<= 1;
    lo += (ll)(vo[0][i]-'0');
    lc <<= 1;
    lc += (ll)(vc[0][i]-'0');
  }
  cout << lo << endl;
  cout << lc << endl;
  cout << lo*lc << endl;
  return 0;
}
