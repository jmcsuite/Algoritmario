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

// funciona con c++ 11, 14, 17
/* Segment Tree con range updates y range queries
 * los updates/queries son de [0, N-1]
 * Recordatorio: LazyPropagation lo unico que hace es guardar un valor
 * en el array lazy, que puede llegar a ser utilizado. Sin embargo
 * no se asegura que se use antes de que se acutalize con un nuevo valor
 *
 */
class SegmentTree {
	private:
		
		// override this value
		ll default_value = -1;
		
		int n;
		vll A, st, lazy;
		
		int l(int p){ return p<<1; }
		int r(int p){ return (p<<1) + 1; }
		
		// override this funcion
		ll function_merge(ll a, ll b){
			return 0;
		}
		
		// override this funcion
		ll lazy_function(ll lazy_flag, ll prev_value, ll L, ll R){
			return 0;
		}
		
		ll conquer(ll a, ll b){
			if(a == default_value) return b;
			if(b == default_value) return a;
			return function_merge(a,b);
		}
		
		void build(int p, int L, int R){
			if(L == R){
				st[p] = A[L];
				return;
			}
			int m = (L+R)/2;
			build(l(p), L, m);
			build(r(p), m+1, R);
			st[p] = conquer(st[l(p)], st[r(p)]);
		}
		
		void propagate(int p, int L, int R){
			if(lazy[p] != default_value){
				st[p] = lazy_function(lazy[p], st[p], L, R);
				if(L != R){
					lazy[l(p)] = lazy[r(p)] = lazy[p];
				}else{
					A[L] = st[p];
				}
				lazy[p] = default_value;
			}
		}
		
		ll RMQ(int p, int L, int R, int i, int j){
			propagate(p, L, R);
			if(i > j) return default_value;
			if((L >= i) && (R <= j)) return st[p];
			int m = (L+R)/2;
			return conquer(RMQ(l(p), L, m, i, min(m, j)),
			 RMQ(r(p), m+1, R, max(i, m+1), j));
		}
		
		void update(int p, int L, int R, int i, int j, ll val){
			propagate(p, L, R);
			if(i > j) return;
			if((L >= i) && (R <= j)){
				lazy[p] = val;
				propagate(p, L, R);
			}
			else {
				int m = (L+R)/2;
				update(l(p), L, m, i, min(m,j), val);
				update(r(p), m+1, R, max(i,m+1), j, val);
				st[p] = conquer(RMQ(l(p), L, m, L, m), RMQ(r(p), m+1, R, m+1, R));
			}
		}
	
	public:
		SegmentTree(int sz) : n(sz), A(n+1), st(4*n), lazy(4*n, default_value) {}
		SegmentTree(const vll &initialA) : SegmentTree((int)initialA.size()) {
			A = initialA;
			build(1,0,N-1);
		}
		
		void update(int i, int j, ll val) { update(1,0,n-1, i, j, val);}
		
		ll RMQ(int i, int j) {
			return RMQ(1,0,n-1,i,j);
		}
};




int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
}
