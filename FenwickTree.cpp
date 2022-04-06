#include <bits/stdc++.h>
 
#define MAX 10e15+1
#define MIN -10e15+1
#define MOD 998244353
#define FOR(i, a, b)    for(long long i=a;i<b;i++)
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef pair<double,double> ii;
typedef vector<pll> vpll;
vll v1,v2;
ll N,M,K,Q,T;
vll vl;
vector<vll> vadj;

class FenwickTree{
	
	#define LSOne(S) ((S) & -(S)) 
	
	//funciona de [1, n]
	// funciona c++11, 14, 17
	private:
	  vll ft;                                        // internal FT is an array
	public:
	  FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT
	
	  void build(const vll &f) {
	    int m = (int)f.size()-1;                     // note f[0] is always 0
	    ft.assign(m+1, 0);
	    for (int i = 1; i <= m; ++i) {               // O(m)
	      ft[i] += f[i];                             // add this value
	      if (i+LSOne(i) <= m)                       // i has parent
	        ft[i+LSOne(i)] += ft[i];                 // add to that parent
	    }
	  }
	
	  FenwickTree(const vll &f) { build(f); }        // create FT based on f

	  ll rsq(int j) {                                // returns RSQ(1, j)
	    ll sum = 0;
	    for (; j; j -= LSOne(j))
	      sum += ft[j];
	    return sum;
	  }
	
	 // [i, j] inclusive
	  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion
	
	  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
	  void update(int i, ll v) {
	    for (; i < (int)ft.size(); i += LSOne(i))
	      ft[i] += v;
	  }
};


class RUPQ {                                     // RUPQ variant
	private:
	  FenwickTree ft;                                // internally use PURQ FT
	public:
	  RUPQ(int m) : ft(FenwickTree(m)) {}
	  void range_update(int ui, int uj, ll v) {
	    ft.update(ui, v);                            // [ui, ui+1, .., m] +v
	    ft.update(uj+1, -v);                         // [uj+1, uj+2, .., m] -v
	  }                                              // [ui, ui+1, .., uj] +v
	  ll point_query(int i) { return ft.rsq(i); }    // rsq(i) is sufficient
	};
	
	class RURQ  {                                    // RURQ variant
	private:                                         // needs two helper FTs
	  RUPQ rupq;                                     // one RUPQ and
	  FenwickTree purq;                              // one PURQ
	public:
	  RURQ(int m) : rupq(RUPQ(m)), purq(FenwickTree(m)) {} // initialization
	  void range_update(int ui, int uj, ll v) {
	    rupq.range_update(ui, uj, v);                // [ui, ui+1, .., uj] +v
	    purq.update(ui, v*(ui-1));                   // -(ui-1)*v before ui
	    purq.update(uj+1, -v*uj);                    // +(uj-ui+1)*v after uj
	  }
	  ll rsq(int j) {
	    return rupq.point_query(j)*j -               // optimistic calculation
	           purq.rsq(j);                          // cancelation factor
	  }
	  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // standard
};


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
}
