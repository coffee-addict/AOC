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
using TIII = tuple<int,int,int>;

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

// return A*B
VVI prod_2mats(VVI A, VVI B) {
  VVI res(3, VI(3));
  REP(i,3) REP(j,3) {
    REP(k,3) res[i][j] += A[i][k]*B[k][j];
  }
  return res;
}

VVVI get_invrotmats() {
  FILE *fp = fopen("rotmats_inv.dat","r");
  VVVI res(24);
  REP(i,24) {
    VVI v(3, VI(3));
    REP(j,3) {
      REP(k,3) {
        int x;
        fscanf(fp, "%d ", &x);
        v[j][k] = x;
      }
    }
    res[i] = v;
  }
  fclose(fp);
  return res;
}

VVVI gen_rotmats() {
  VVI A = {
    {1, 0, 0},
    {0, 0, -1},
    {0, 1, 0},
  };
  VVI B = {
    {0, 0, 1},
    {0, 1, 0},
    {-1, 0, 0}
  };
  VVVI res;
  REP(p,4) REP(q,4) REP(r,4) REP(s,4) {
    VVI X(3, VI(3));
    REP(i,3) X[i][i] = 1;
    REP(t,s) X = prod_2mats(B, X);
    REP(t,r) X = prod_2mats(A, X);
    REP(t,q) X = prod_2mats(B, X);
    REP(t,p) X = prod_2mats(A, X);
    res.epb(X);
  }
  sort(all(res));
  res.erase(unique(all(res)), res.end());
  return res;
}

// v: 3x1, 0 <= roti < 24
VI rotv(VI v, VVVI &rmats, int roti) {
  VI res(3);
  REP(i,3) REP(j,3) res[i] += rmats[roti][i][j]*v[j];
  return res;
}

const int INF = 1000000000;

VI get_path(int n, int s, VVI &con) {
  VI p(n);
  queue<VI> q;
  VI v0 = {s};
  q.push(v0);
  p[s] = 1;
  while (q.size()) {
    VI v = q.front();
    q.pop();
    int m = v.size();
    int x = v[m-1];
    p[x] = 1;
    if (x == 0) return v;
    REP(i,n) {
      if (i == x) continue;
      if (p[i]) continue;
      if (con[x][i] == 0) continue;
      VI w = v;
      w.epb(i);
      q.push(w);
    }
  }
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n; 
  VVVI cds(n);
  REP(i,n) {
    int m; cin >> m;
    cds[i].resize(m);
    REP(k,m) {
      int x, y, z; cin >> x >> y >> z; 
      cds[i][k].epb(x);
      cds[i][k].epb(y);
      cds[i][k].epb(z);
    }
  }

  VVVI rmats = gen_rotmats();
  VVVI rmats_inv = get_invrotmats();

  VVI con(n, VI(n));
  VVVI rotids(n, VVI(n));
  VVI ids_dup_bcn(n);
  vector<vector<TIII>> dxyz(n, vector<TIII>(n, mkt(INF,INF,INF)));
  REP(i,n) {
    REP(j,n) {
      if (i == j) continue;
      int found = 0;
//      REP(ri0,24) REP(ri1,24) {
      FOR(ri0,23,24) REP(ri1,24) {
        if (found) break;
        VVI rcd0(cds[i].size());
        REP(k,cds[i].size()) rcd0[k] = rotv(cds[i][k], rmats, ri0);
        VVI rcd1(cds[j].size());
        REP(k,cds[j].size()) rcd1[k] = rotv(cds[j][k], rmats, ri1);
        int m0 = rcd0.size(); int m1 = rcd1.size();
        map<TIII,int> mp;
        REP(k,m0) REP(l,m1) {
          int dx = rcd0[k][0] - rcd1[l][0];
          int dy = rcd0[k][1] - rcd1[l][1];
          int dz = rcd0[k][2] - rcd1[l][2];
          TIII t = mkt(dx,dy,dz);
          if (mp.find(t) == mp.end())
            mp[t] = 1;
          else
            mp[t]++;
        }
        for (const auto& kv: mp) {
          if (kv.second < 12) continue; 
          con[i][j] = con[j][i] = 1;
          int rx, ry, rz; tie(rx,ry,rz) = kv.first;
          dxyz[i][j] = mkt(rx,ry,rz);
          found = 1;
          REP(k,m0) REP(l,m1) {
            int dx = rcd0[k][0] - rcd1[l][0];
            int dy = rcd0[k][1] - rcd1[l][1];
            int dz = rcd0[k][2] - rcd1[l][2];
            if (rx == dx && ry == dy && rz == dz) {
              ids_dup_bcn[i].epb(k);
              ids_dup_bcn[j].epb(l);
            }
          }
          rotids[i][j].epb(ri1);
          rotids[i][j].epb(ri0); // need to take inverse
          break;
          if (found) break;
        }
      }
    }
  }

//cout << "relative positions:\n";
//REP(i,n) REP(j,n) {
//  if (i == j) continue;
//  if (con[i][j] == 0) continue;
//  int rx, ry, rz; tie(rx,ry,rz) = dxyz[i][j];
//  cout << j << "-th location relative to " << i << "-th scanner: " 
//  << rx << ", " << ry << ", " << rz << endl;
//}

  // make ids_dup_bcn' unique
  REP(i,n) {
    if (ids_dup_bcn[i].empty()) continue;
    sort(all(ids_dup_bcn[i]));
    ids_dup_bcn[i].erase(unique(all(ids_dup_bcn[i])), ids_dup_bcn[i].end());
  }

  // get paths to 0 from each ith
  VVI p20(n);
  FOR(i,1,n) {
    p20[i] = get_path(n, i, con);
cout << "path from " << i << "th to 0: ";
REP(j,p20[i].size()) cout << p20[i][j] << ' ';
cout << endl; 
cout << "rotation matrix ids: ";
REP(j,p20[i].size()-1) {
  int f = p20[i][j], t = p20[i][j+1];
  cout << rotids[t][f][0] << ", " << rotids[t][f][1] << ' ';
}
cout << endl; 
  }

  // compute relative positions to 0th scanner
  VVI dxyz20(n);
  set<TIII> res;
  REP(i,cds[0].size()) {
    int x = cds[0][i][0];
    int y = cds[0][i][1];
    int z = cds[0][i][2];
    res.insert(mkt(x,y,z));
  }
  dxyz20[0] = {0, 0, 0};
  FOR(i,1,n) {
    VI cumd(3);
    VVI cds0 = cds[i];
    REP(j,p20[i].size()-1) {
      int f = p20[i][j], t = p20[i][j+1];
      // forward rotation
      int rotid0 = rotids[t][f][0];
      REP(k,cds0.size()) cds0[k] = rotv(cds0[k], rmats, rotid0);

      int dx0, dy0, dz0; tie(dx0,dy0,dz0)= dxyz[t][f];
      VI vd0 = {dx0, dy0, dz0};

      // inverse rotation
      int rotid0_inv = rotids[t][f][1];
      REP(k,cds0.size()) REP(l,3) cds0[k][l] += vd0[l];
      REP(k,cds0.size()) cds0[k] = rotv(cds0[k], rmats_inv, rotid0_inv);

      // adjust cumulative (dx,dy,dz) to the current coordinates
      cumd = rotv(cumd, rmats, rotid0);
      REP(k,3) cumd[k] += vd0[k];
      cumd = rotv(cumd, rmats_inv, rotid0_inv);
    }
    dxyz20[i] = cumd;
//    REP(j,cds0.size()) res.epb(mkt(cds0[j][0],cds0[j][1],cds0[j][2]));
    REP(j,cds0.size()) res.insert(mkt(cds0[j][0],cds0[j][1],cds0[j][2]));
  }
  cout << endl; 

  cout << "Scanners' locations relative to 0th:\n";
  REP(i,n) {
    int dx, dy, dz;
    dx = dxyz20[i][0]; dy = dxyz20[i][1]; dz = dxyz20[i][2];
    cout << i << "th (dx,dy,dz) = " << dx << ", " << dy << ", " << dz << endl;
  }

// // check indecies of rotation matrices
//  REP(i,n) {
//    REP(j,n) {
//      if (i == j) continue;
//      if (rotids[i][j].empty()) continue;
//      cout << "i, j = " << i << ", " << j << ": ";
//      cout << "rot = " << rotids[i][j][0] << ", ";
//      cout << "inv rot = " << rotids[i][j][1] << endl;
//    }
//  }

cout << "# of unique beacons = " << res.size() << endl;

  return 0;
}
