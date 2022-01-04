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
  string s; cin >> s; 
  int n; cin >> n; 
  vector<char> a(n), b(n), x(n);
  REP(i,n) {
    string ab; cin >> ab; 
//    a[i] = (int)(ab[0]-'A');
//    b[i] = (int)(ab[1]-'A');
//    char c; cin >> c; 
//    x[i] = (int)(c-'A');
    a[i] = ab[0];
    b[i] = ab[1];
    cin >> x[i];
  }
//  REP(xxx,10) {
  string res = s;
  REP(xxx,10) {
    int m = (int)res.size();
    vector<tuple<int,char>> p;
    REP(i,n) REP(j,m-1) if (res[j]==a[i] && res[j+1]==b[i]) p.epb(make_tuple(j,x[i]));
    sort(all(p));
    int prv = 0;
    string tmp = "";
    REP(i,p.size()) {
      int j;
      char xj;
      tie(j,xj) = p[i];
      tmp += res.substr(prv,j-prv+1);
      tmp += xj;
      prv = j+1;
    }
    tmp += res.substr(prv);
    res = tmp;
//    cout << res << endl;
  }
  VI cnt(26);
  REP(i,res.size()) cnt[(int)(res[i]-'A')]++;
  int min_cnt = (int)res.size(), max_cnt = 0;
  REP(i,26) if (cnt[i]) {
    min_cnt = min(min_cnt, cnt[i]);
    max_cnt = max(max_cnt, cnt[i]);
  }
  cout << max_cnt - min_cnt << endl; 
  return 0;
}
