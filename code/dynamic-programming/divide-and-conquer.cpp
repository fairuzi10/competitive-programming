//~ TESTED ON
//~ http://www.spoj.com/problems/NKLEAVES/

#include <bits/stdc++.h>
#define INF 1000000000000000000
#define MAXN 100005
#define lint long long
using namespace std;
int N, K;

lint arr[MAXN], ps[MAXN], ps2[MAXN], dp[15][MAXN];

lint jumlah(int l, int r) {
	return (ps[r]-ps[l-1])-(ps2[r]-ps2[l-1])*l;
}

void hitung(int l, int r, int optL, int optR, int rem) {
	int m = (l+r)>>1;
	lint &ret = dp[rem][m];
	ret = INF;
	
	int opt = -1;
	for (int i = min(optR, m); i >= optL; i--) {
		if (ret > dp[rem-1][i-1]+jumlah(i, m)) {
			ret = dp[rem-1][i-1]+jumlah(i, m);
			opt = i;
		}
	}
	if (l < m) hitung(l, m-1, optL, opt, rem);
	if (m < r) hitung(m+1, r, opt, optR, rem);
} 

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) scanf("%lld", &arr[i]);
	for (int i = 1; i <= N; i++) {
		ps[i] = ps[i-1] + arr[i]*i;
		ps2[i] = ps2[i-1] + arr[i];
	}
	
	dp[0][0] = 0;
	for (int i = 1; i <= N; i++) dp[0][i] = INF;
	for (int i = 1; i <= K; i++) {
		hitung(1, N, 1, N, i);
	}
	printf("%lld\n", dp[K][N]);
	
	return 0;
}

