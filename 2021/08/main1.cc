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

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int d = 10;
  int n; cin >> n; 
  int res = 0;
  REP(i,n) {
    int m = 4;
    string s;
    REP(j,d) cin >> s; 
//    set<string> x;
    REP(j,m) {
      cin >> s; 
//      if (s.size() == 2) x.insert(s);
//      if (s.size() == 3) x.insert(s);
//      if (s.size() == 4) x.insert(s);
//      if (s.size() == 7) x.insert(s);
      if (s.size() == 2) res++;
      if (s.size() == 3) res++;
      if (s.size() == 4) res++;
      if (s.size() == 7) res++;
    }
//cout << "i = " << i << ", x.size = " << x.size() << endl;
//    res += (int)x.size();
  }
  cout << res << endl; 
  return 0;
}
