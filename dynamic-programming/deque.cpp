//~ TESTED ON
//~ http://www.spoj.com/problems/AE3A/

#include <bits/stdc++.h>
#define INF 1000000000
#define MAXN 2005
using namespace std;
struct ii {
	int a, b;
	bool operator < (ii o) const { return make_tuple(a, b) < make_tuple(o.a, o.b); }
};
int N;

int arr[MAXN], dp[MAXN][MAXN], mid[MAXN][MAXN];
deque<ii> dql[MAXN], dqr[MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
	
	//~ kurang dari mid maka ambil kanan, selain itu ambil kiri
	//~ dql "kalau left belum ke cover dari range sekian, butuh berapa yang minimal?"
	for (int i = 1; i <= N; i++) {
		dp[i][i] = arr[i];
		mid[i][i] = i;
		dql[i].push_back({i, dp[i][i] + arr[i+1]});
		dqr[i].push_front({i, dp[i][i] + arr[i-1]});
	}
	for (int len = 2; len <= N; len++) {
		for (int l = 1; l+len-1 <= N; l++) {
			int r = l+len-1;
			
			for (int i = mid[l][r-1]; i <= N; i++) {
				if (dp[l][i-1] >= dp[i+1][r]) {
					mid[l][r] = i;
					break;
				}
			}
			
			//~ hapus yang tidak valid
			while (!dql[l].empty() && dql[l].front().a < mid[l][r]-1) dql[l].pop_front();
			while (!dqr[r].empty() && dqr[r].back().a > mid[l][r]) dqr[r].pop_back();
			
			dp[l][r] = INF;
			if (!dql[l].empty()) dp[l][r] = min(dp[l][r], dql[l].front().b);
			if (!dqr[r].empty()) dp[l][r] = min(dp[l][r], dqr[r].back().b);
			
			//~ masukkan dengan menggunakan sistem tiban
			while (!dql[l].empty() && dql[l].back().b >= dp[l][r] + arr[r+1]) dql[l].pop_back();
			dql[l].push_back({r, dp[l][r] + arr[r+1]});
			while (!dqr[r].empty() && dqr[r].front().b >= dp[l][r] + arr[l-1]) dqr[r].pop_front();
			dqr[r].push_front({l, dp[l][r] + arr[l-1]});
		}
	}
	printf("%d\n", dp[1][N]);
	
	return 0;
}

