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
  ll res = 0;
  REP(i,n) {
    VL dp(9);
    dp[x[i]] = 1LL;
    REP(c,256) {
      VL dp2(9);
      for (int j=8; j>0; j--) dp2[j-1] = dp[j];
      dp2[6] += dp[0];
      dp2[8] = dp[0];
      REP(j,9) dp[j] = dp2[j];
    }
    REP(j,9) res += dp[j];
  }
  cout << res << endl;
  return 0;
}

