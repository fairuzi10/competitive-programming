//~ TESTED ON
//~ http://www.spoj.com/problems/ADAPLNTS/
//~ http://www.spoj.com/problems/MATCHING/

#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define MAXN 805
#define NIL (MAXN-1)
using namespace std;
int N, M;

int arr[MAXN], arr2[MAXN], lvl[MAXN], pairL[MAXN], pairR[MAXN];
queue<int> q;
vector<int> edge[MAXN];

bool bfs() {
	memset(lvl, 63, sizeof(lvl));
	for (int i = 0; i < N; i++) {
		if (pairL[i] == NIL) {
			lvl[i] = 0;
			q.push(i);
		}
	}
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (auto i: edge[now]) {
			if (lvl[pairR[i]] > lvl[now]+1) {
				lvl[pairR[i]] = lvl[now]+1;
				q.push(pairR[i]);
			}
		}
	}
	return lvl[NIL] < INF;
}

bool dfs(int now) {
	if (now == NIL) return 1;
	for (auto i: edge[now]) {
		if (lvl[pairR[i]] == lvl[now]+1) {
			if (dfs(pairR[i])) {
				pairL[now] = i;
				pairR[i] = now;
				return 1;
			} else lvl[pairR[i]] = INF;
		}
	}
	return 0;
}

int bipartite_matching() {
	for (int i = 0; i < N; i++) pairL[i] = NIL;
	for (int i = 0; i < M; i++) pairR[i] = NIL;
	int ret = 0;
	while (bfs()) {
		for (int i = 0; i < N; i++) {
			if (lvl[i] == 0) {
				if (dfs(i)) ret++;
				else lvl[i] = INF;
			}
		}
	}
	return ret;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
	for (int i = 0; i < M; i++) scanf("%d", &arr2[i]);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (__gcd(arr[i], arr2[j]) > 1) edge[i].push_back(j);
		}
	}
	
	int ans = N+M-bipartite_matching();	// maximum independent set
	printf("%d\n", ans);
	
	return 0;
}
