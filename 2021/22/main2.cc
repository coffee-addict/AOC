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
using VVVI = vector<VVI>;
using VL = vector<ll>;
using VVL = vector<VL>;
using VD = vector<double>;
using VLD = vector<long double>;

template<typename T>
vector<T> compress(vector<T> x) {
  vector<T> v = x;
  sort(all(v));
  v.erase(unique(all(v)), v.end());
  vector<T> res(x.size());
  REP(i,x.size()) res[i] = lower_bound(all(v), x[i]) - v.begin();
  return res;
}

VI compress_int(VI x) {
  return compress<int>(x);
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int nc; cin >> nc; 
  while (nc--) {
    int n; cin >> n; 
    VI x(n*2), y(n*2), z(n*2);
    VI sw(n);
    REP(i,n) {
      string s; cin >> s; 
      if (s == "on") sw[i] = 1;
      int lx, ly, lz, ux, uy, uz;
      cin >> lx >> ux >> ly >> uy >> lz >> uz; 
      ux++; uy++; uz++;
      x[i] = lx; x[n+i] = ux;
      y[i] = ly; y[n+i] = uy;
      z[i] = lz; z[n+i] = uz;
    }
    VI xc, yc, zc;
    xc = compress_int(x); yc = compress_int(y); zc = compress_int(z);
    int mx = 0, my = 0, mz = 0;
    REP(i,n*2) {
      mx = max(mx, xc[i]);
      my = max(my, yc[i]);
      mz = max(mz, zc[i]);
    }
    mx++; my++; mz++;
    VI c2ox(mx), c2oy(my), c2oz(mz);
    REP(i,n) {
      c2ox[xc[i]] = x[i]; c2ox[xc[n+i]] = x[n+i];
      c2oy[yc[i]] = y[i]; c2oy[yc[n+i]] = y[n+i];
      c2oz[zc[i]] = z[i]; c2oz[zc[n+i]] = z[n+i];
    }
    VVVI c(mx-1, VVI(my-1, VI(mz-1)));
    REP(i,n) {
      int t = sw[i] ? 1 : 0;
      FOR(j,xc[i],xc[n+i]) FOR(k,yc[i],yc[n+i]) FOR(l,zc[i],zc[n+i]) c[j][k][l] = t;
    }
    ll res = 0;
    REP(i,mx-1) REP(j,my-1) REP(k,mz-1) {
      if (c[i][j][k] == 0) continue;
      ll dx = c2ox[i+1] - c2ox[i];
      ll dy = c2oy[j+1] - c2oy[j];
      ll dz = c2oz[k+1] - c2oz[k];
      res += dx*dy*dz;
    }
    cout << res << endl; 
  }
  return 0;
}
