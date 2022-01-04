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
  VI d(n);
  REP(i,n) cin >> d[i];
  int s0 = d[0]+d[1]+d[2];
  int res = 0;
  FOR(i,1,n) {
    if (i+2 == n) break;
    int s1 = d[i]+d[i+1]+d[i+2];
    if (s0 < s1) res++;
    s0 = s1;
  }
  cout << res << endl; 
  return 0;
}
