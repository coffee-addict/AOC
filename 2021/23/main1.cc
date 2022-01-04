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
using TIII = tuple<int,int,int>;
using VT = vector<TIII>;
using QC = queue<TIII>;
using B = VVI;
using TIB = tuple<int,B>;

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

void print(B b) {
  REP(i,b.size()) {
    REP(j,b[i].size()) {
      int c = b[i][j];
      char o = '.';
      if (c == -1)
        o = '#';
      else if (c == 0)
        o = '.';
      else if (c == 1)
        o = 'A';
      else if (c == 2)
        o = 'B';
      else if (c == 3)
        o = 'C';
      else if (c == 4)
        o = 'D';
      cout << o; 
    }
    cout << endl; 
  }
  cout << endl; 
}

int dy[] = {1, -1};

B update_b(int h, int w, VT v) {
  B b(h, VI(w, -1));
  FOR(j,1,w-2) b[1][j] = 0;
  for (int j=3; j<10; j+=2) {
    FOR(i,2,4) b[i][j] = 0;
  }
  REP(i,v.size()) {
    int c, y, x;
    tie(c,y,x) = v[i];
    b[y][x] = c;
  }
  return b;
}

VT get_qc(B b) {
  VT res;
  REP(i,b.size()) REP(j,b[i].size()) {
    int c = b[i][j];
    if (1 <= c && c <= 4) res.epb(mkt(c,i,j));
  }
  return res;
}

int is_sameb(B b, B nb) {
  REP(i,b.size()) REP(j,b[i].size()) if (b[i][j] != nb[i][j]) return 0;
  return 1;
}

set<TIII> vc2s(B b) {
  set<TIII> res;
  VT cyx = get_qc(b);
  REP(i,cyx.size()) res.insert(cyx[i]);
  return res;
}

vector<TIB> explore_1s(int e, B b, map<set<TIII>,int> &hist) {
  vector<TIB> res;
//  VT vc = get_qc(b);
//  for (TIII cyx : vc) {
set<TIII> sc = vc2s(b);
  for (TIII cyx : sc) {
    int c, y, x;
    tie(c,y,x) = cyx;
    // skip if settled
    int gx = 0;
    if (c == 1) gx = 3;
    else if (c == 2) gx = 5;
    else if (c == 3) gx = 7;
    else if (c == 4) gx = 9;
    if (y == 3 && x == gx) continue; // bottom
    if (y == 2 && x == gx && b[y+1][x] == c) continue; // both settled
    vector<tuple<int,int>> vn;
//if (b[1][6] == 4 && b[2][3] == 2 && b[2][7] == 3) {
//  cout << "found\n" ;
//  set<TIII> st = vc2s(b);
//  cout << "e = " << hist[st]  << endl;
//  print(b);
//  return res;
//}
    REP(i,2) {
      // divide into cases: up/down
      // eliminate invalid states
      if (dy[i] > 0) { // down
        if (y != 1) continue;
        if (x == gx) continue;
        int ok = 1;
        if (x < gx) {
          FOR(j,x+1,gx+1) if (b[y][j] != 0) ok = 0;
        } else if (gx < x) {
          FOR(j,gx,x) if (b[y][j] != 0) ok = 0;
        }
        if (ok == 0) continue;
        int ny = y;
        while (b[ny+dy[i]][gx] == 0) ny += dy[i];
        if (ny == y) continue;
        if (ny == 2 && b[ny+1][gx] != c) continue;
        vn.epb(make_tuple(ny,gx));
      } else if (dy[i] < 0) { // up
        // go up
        if (y < 2) continue;
        int ny = y;
        while (b[ny+dy[i]][x] == 0) ny += dy[i];
        if (ny != 1) continue;
        // turn left/right
        int lx = x, rx = x;
        while (b[ny][lx] == 0) lx--;
        while (b[ny][rx] == 0) rx++;
        VI vlx;
        FOR(j,lx+1,x) {
          if (j == 3) continue;
          if (j == 5) continue;
          if (j == 7) continue;
          if (j == 9) continue;
          vlx.epb(j);
        }
        REP(j,vlx.size()) vn.epb(make_tuple(ny,vlx[j]));
        VI vrx;
        FOR(j,x+1,rx) {
          if (j == 3) continue;
          if (j == 5) continue;
          if (j == 7) continue;
          if (j == 9) continue;
          vrx.epb(j);
        }
        REP(j,vrx.size()) vn.epb(make_tuple(ny,vrx[j]));
      }
    }
    REP(i,vn.size()) {
      int ny, nx;
      tie(ny,nx) = vn[i];
      int ne = (int)abs(ny-y) + (int)abs(nx-x);
      REP(k,c-1) ne *= 10;
      ne += e;
      VVI nb = b;
      nb[y][x] = 0;
      nb[ny][nx] = c;

      set<TIII> ns = vc2s(nb);
      if (hist.find(ns) == hist.end()) {
        hist[ns] = ne;
      } else if (hist[ns] <= ne)
        continue;
      res.epb(make_tuple(ne,nb));
    }
  }
  return res;
}

int is_done(VVI b) {
  int res = 1;
  if (b[2][3] != 1) res = 0;
  if (b[3][3] != 1) res = 0;
  if (b[2][5] != 2) res = 0;
  if (b[3][5] != 2) res = 0;
  if (b[2][7] != 3) res = 0;
  if (b[3][7] != 3) res = 0;
  if (b[2][9] != 4) res = 0;
  if (b[3][9] != 4) res = 0;
  return res;
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int nc; cin >> nc;
  while (nc--) {
    int h, w; cin >> h >> w;
    VVI b0(h, VI(w));
    VT vc;
    REP(i,h) {
      string bb; cin >> bb;
      REP(j,w) {
        if (bb[j] == '#' || bb[j] == '.') continue;
        int c = (int)(bb[j]-'A') + 1;
        vc.epb(mkt(c,i,j));
      }
    }
    b0 = update_b(h, w, vc);
    map<set<TIII>,int> hist;
    priority_queue<TIB, vector<TIB>, greater<TIB>> q;
    q.push(make_tuple(0,b0));
    set<TIII> s0 = vc2s(b0);
    hist[s0] = 0;
    int res = 10000000;
    while (q.size()) {
//REP(xxxx,30) {
      int e;
      VVI b;
      tie(e,b) = q.top();
//print(b);
      q.pop();
      if (is_done(b)) {
        res = min(res, e);
cout << "current best sol = " << res << endl; 
        continue;
      }
      // look for new states
      vector<TIB> vn = explore_1s(e, b, hist);
      REP(i,vn.size()) q.push(vn[i]);
    }
    cout << res << endl; 
  }
  return 0;
}
