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

const int N = 1000;
int dx[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int n; cin >> n; 
  string s;
  REP(i,n) {
    string x;
    cin >> x; 
    s += x;
  }
  VI a(s.size());
  REP(i,s.size()) a[i] = s[i]=='#' ? 1 : 0;
  int h, w;
  cin >> h;  
  w = h;
  VVI b(N, VI(N));
  REP(i,h) {
    string x; cin >> x; 
    REP(j,w) {
      int p = x[j]=='#' ? 1 : 0;
      b[i+N/2][j+N/2] = p;
    }
  }
  VVI c(N, VI(N));
  int uit = 50;
  REP(it,uit) {
    REP(i,N) REP(j,N) c[i][j] = 0;
    FOR(i,N/2-2-it,N/2+h+2+it) REP(j,2)
      b[i][N/2-j-1-it] = b[i][N/2+w+j+it] = it&1;
    REP(i,2) FOR(j,N/2-1-it,N/2+w+it)
      b[N/2-1-i-it][j] = b[N/2+h+i+it][j] = it&1;
    FOR(i,N/2-1-it,N/2+h+1+it) FOR(j,N/2-1-it,N/2+w+1+it) {
      int x = 0;
      REP(k,9) {
        x <<= 1;
        int ny = i + dy[k] , nx = j + dx[k];
        x += b[ny][nx];
      }
      if (a[x]) c[i][j] = 1;
    }
    FOR(i,N/2-1-it,N/2+h+1+it) FOR(j,N/2-1-it,N/2+w+1+it) b[i][j] = c[i][j];
  }
  int res = 0;
  FOR(i,N/2-uit,N/2+h+uit) FOR(j,N/2-uit,N/2+w+uit) if (c[i][j]) res++;
  cout << res << endl; 
  return 0;
}

