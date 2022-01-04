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

template<typename T>
struct edge {
  int from;
  int to;
  T cost;
  edge(int from, int to, T cost) {
    this->from = from;
    this->to = to;
    this->cost = cost;
  }
};
using VVE = vector<vector<edge<int>>>;

ll max_height(ll vy) {
  return vy*(vy+1)/2LL;
}

ll getx(ll v, ll n) {
  return max(0LL, n*(v*2 - n + 1LL)/2LL);
}

ll gety(ll v, ll n) {
  return n*(v*2 - n + 1LL)/2LL;
}

int sim(ll vx, ll vy, ll ln, ll un, ll lx, ll ux, ll ly, ll uy) {
  int res = 0;
  for (ll n=ln; n<=un; n++) {
    ll px = getx(vx, n), py = gety(vy, n);
    if (px < lx || ux < px) continue;
    if (py < ly || uy < py) continue;
    res = 1;
  }
  return res;
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n; 
  REP(i,n) {
    ll lx, ux, ly, uy;
    cin >> lx >> ux >> ly >> uy; 
    ll res = 0;
    ll vx0 = (ll)((sqrt((double)lx*8) - 1.0)*0.5);
    for (ll vx = vx0; vx<1000; vx++) {
      for (ll vy = -1000; vy <1000; vy++) {
        ll ln = 0, un = vx + 1;
        if (sim(vx,vy,ln,un,lx,ux,ly,uy)) {
          res = max(res, max_height(vy));
        }
      }
    }
    cout << res << endl; 
  }
  return 0;
}
