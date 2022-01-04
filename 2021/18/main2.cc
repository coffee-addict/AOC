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

vector<TIII> explode(vector<TIII> vec) {
  vector<TIII> res;
  while (1) {
    int s;
    int found = 0;
    int n = vec.size();
    REP(i,n) {
      int p, lr, v; tie(p,lr,v) = vec[i];
      if (p > 4) {
        found = 1;
        s = i;
        break;
      }
    }
    if (found == 0) return vec;
    res.clear();
    // explode 
    // left
    if (s == 0) {
      // left
      res.epb(mkt(nth(vec[s],0)-1,-1,0));
      // right
      FOR(i,s+2,n) res.epb(vec[i]);
      res[s+1] = mkt(nth(vec[s+2],0), nth(vec[s+2],1), nth(vec[s+2],2)+nth(vec[s+1],2));
    } else if (s+1 == n-1) {
      // left
      REP(i,s) res.epb(vec[i]);
      res[s-1] = mkt(nth(vec[s-1],0),nth(vec[s-1],1),nth(vec[s-1],2)+nth(vec[s],2));
      // right
      res.epb(mkt(nth(vec[s+1],0)-1,1,0));
    } else {
      // left
      REP(i,s) res.epb(vec[i]);
      res[s-1] = mkt(nth(vec[s-1],0),nth(vec[s-1],1),nth(vec[s-1],2)+nth(vec[s],2));
      // middle
      int pl, lrl, vl; tie(pl,lrl,vl) = vec[s-1];
      int p, lr, v; tie(p,lr,v) = vec[s];
      int pr, lrr, vr; tie(pr,lrr,vr) = vec[s+2];
      if (pl + 1 == p && vl == 0 && lrl == -1) // single 0 on the left
        res.epb(mkt(p-1,1,0));
      else if (p == pr + 1 && vr == 0 && lrr == 1) // single 0 on the right
        res.epb(mkt(p-1,-1,0));
      else if (pl < pr) // connected to the right more strongly
        res.epb(mkt(p-1,-1,0));
      else if (pl > pr) // connected to the left more strongly
        res.epb(mkt(p-1,1,0));
      else if (pl == pr) {
        res.epb(mkt(p-1,-1,0));
      } 
      // right
      FOR(i,s+2,n) res.epb(vec[i]);
      res[s+1] = mkt(nth(vec[s+2],0), nth(vec[s+2],1), nth(vec[s+2],2)+nth(vec[s+1],2));
    }
    vec = res;
//cout << "explode:\n";
//for (TIII x : vec) {
//  cout << "[" << nth(x,0) << ", " << nth(x,1) << ", " << nth(x,2) << "], ";
//}
//cout << endl; 
  }
  return res;
}

vector<TIII> split(vector<TIII> vec) {
  vector<TIII> res;
    while (1) {
    int s;
    int found = 0;
    int n = vec.size();
    REP(i,n) {
      int p, lr, v; tie(p,lr,v) = vec[i];
      if (v >= 10) {
        found = 1;
        s = i;
        break;
      }
    }
    if (found == 0) return vec;
    res.clear();
    // split
    // left
    REP(i,s) res.epb(vec[i]);
    int p = nth(vec[s],0) + 1;
    int val = nth(vec[s],2)/2;
    res.epb(mkt(p,-1,val));
    if (nth(vec[s],2)&1) val++;
    res.epb(mkt(p,1,val));
    // right
    FOR(i,s+1,n) res.epb(vec[i]);
//cout << "split:\n";
//for (TIII x : res) {
//  cout << "[" << nth(x,0) << ", " << nth(x,1) << ", " << nth(x,2) << "], ";
//}
//cout << endl; 
    // check explosion
    res = explode(res);
    vec = res;
  }
  return res;
}

vector<TIII> parse(string s) {
  vector<TIII> res;
  int n = (int)s.size();
  int p = 0, v = -1;
  REP(i,n) {
    char t = s[i];
    if (t == '[') {
      p++;
    } else if (t == ',') {
      if (v == -1) continue;
      res.psb(mkt(p,-1,v));
      v = -1;
    } else if (t == ']') {
      p--;
      if (v == -1) continue;
      res.psb(mkt(p+1,1,v));
      v = -1;
    } else {
      if (v == -1) 
        v = (int)(t-'0');
      else 
        v = v*10 + (int)(t-'0');
    }
  }
  return res;
}

int calc_mag(vector<TIII> vec) {
  stack<TIII> st;
  while (vec.size() > 1) {
    vector<TIII> tmp;
    int n = (int)vec.size();
    int max_p = 0;
    REP(i,n) max_p = max(max_p, nth(vec[i],0));
    int rem = 1;
    REP(i,n-1) {
      int pl, lrl, vl; tie(pl,lrl,vl) = vec[i];
      int pr, lrr, vr; tie(pr,lrr,vr) = vec[i+1];
      if (pl == pr && pl == max_p) {
          tmp.epb(mkt(pl-1, 1, vl*3 + vr*2));
        if (i == n-2) {
          rem = 0;
          break;
        }
        i++;
      } else 
        tmp.epb(vec[i]);
    }
    if (rem) tmp.epb(vec[n-1]);
    vec = tmp;
  }
  return nth(vec[0],2);
}

int main() {
  cin.tie(0);
  cout << fixed << setprecision(10);
  ios::sync_with_stdio(false);
  int cases; cin >> cases; 
  while (cases--) {
    int n; cin >> n; 
    vector<string> s(n);
    REP(i,n) cin >> s[i];
    int res = 0;
    REP(i,n) REP(j,n) {
      if (i == j) continue;
      vector<TIII> v =  parse(s[i]);
      vector<TIII> w =  parse(s[j]);
      REP(k,v.size()) v[k] = mkt(nth(v[k],0)+1, nth(v[k],1), nth(v[k],2));
      REP(k,w.size()) v.epb(mkt(nth(w[k],0)+1, nth(w[k],1), nth(w[k],2)));
      v = explode(v);
      v = split(v);
//cout << "i, j = " << i << ", " << j << endl;
//if (i == 0 && j == 9) {
//  for (TIII x : v) {
//    cout << "[" << nth(x,0) << ", " << nth(x,1) << ", " << nth(x,2) << "], ";
//  }
//  cout << endl; 
//}
      res = max(res, calc_mag(v));
    }
    cout << res << endl; 
  }
  return 0;
}

