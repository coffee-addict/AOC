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

const int INF = 1000000000;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int h, w; cin >> h >> w; 
  VVI b(h, VI(w));
  REP(i,h) {
    string s; cin >> s;
    REP(j,w) b[i][j] = (int)(s[j]-'0');
  }
  VVI d(h, VI(w));
  REP(i,h) REP(j,w) d[i][j] = INF;
  queue<tuple<int,int,int>> q;
  q.push(mkt(0,0,0));
  while (q.size()) {
    int r, y, x;
    tie(r,y,x) = q.front(); q.pop();
    REP(i,4) {
      int ny = y + dy[i], nx = x + dx[i];
      if (ny < 0 || h <= ny) continue;
      if (nx < 0 || w <= nx) continue;
      if (d[ny][nx] <= r + b[ny][nx]) continue;
      d[ny][nx] = r + b[ny][nx];
      q.push(mkt(d[ny][nx],ny,nx));
    }
  }
  cout << d[h-1][w-1] << endl;
  return 0;
}
