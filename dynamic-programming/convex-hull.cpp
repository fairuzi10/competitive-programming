//~ TESTED ON
//~ http://www.spoj.com/problems/NKLEAVES/

#include <bits/stdc++.h>
#define INF 1000000000000000000
#define MAXN 100005
#define lint long long
#define sz(x) (int)(x).size()
using namespace std;
struct ii {
	lint a, b;
	bool operator < (ii o) const { return make_tuple(a, b) < make_tuple(o.a, o.b); }
};
int N, K;

lint arr[MAXN], ps[MAXN], ps2[MAXN], dp[15][MAXN];
vector<ii> hull;

bool tiban(ii x, ii y, ii z) {
	double a = double(x.b-y.b)/(x.a-y.a);
	double b = double(y.b-z.b)/(y.a-z.a);
	return a < b;
}

lint nilai(int ptr, lint x) { return hull[ptr].a*x+hull[ptr].b; }

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) scanf("%lld", &arr[i]);
	for (int i = 1; i <= N; i++) {
		ps[i] = ps[i-1] + arr[i]*i;
		ps2[i] = ps2[i-1] + arr[i];
	}
	
	dp[0][0] = 0;
	for (int i = 1; i <= N; i++) dp[0][i] = INF;
	for (int rem = 1; rem <= K; rem++) {
		hull.clear();
		for (int prev = 1; prev <= N; prev++) {
			//~ y = m*x + c
			//~ dp[now] = related_to[prev]*related_to[now] + related_to[prev/no]
			lint m = -prev;
			lint c1 = ps2[prev-1]*prev-ps[prev-1]+dp[rem-1][prev-1];
			while (sz(hull) >= 2 && tiban(hull[sz(hull)-2], hull.back(), {m, c1})) hull.pop_back();
			hull.push_back({m, c1});
		}
		
		int ptr = 0;
		for (int pos = 1; pos <= N; pos++) {
			lint x = ps2[pos];
			lint c2 = ps[pos];
			while (ptr < sz(hull) && nilai(ptr, x) > nilai(ptr+1, x)) ptr++;
			dp[rem][pos] = nilai(ptr, x)+c2;
		}
	}
	printf("%lld\n", dp[K][N]);
	
	return 0;
}

