//~ Tested on
//~ http://www.spoj.com/problems/FASTFLOW/
//~ http://www.spoj.com/problems/MAFBOI08/

#include <bits/stdc++.h>
#define INF 1000000000000000000
#define MAXN 5005
#define SOURCE 1
#define SINK N
#define lint long long
using namespace std;
int TC, N, M, x, y, z;

queue<int> q;
vector<int> edge[MAXN];
lint lvl[MAXN], rem[MAXN][MAXN];

bool bfs() {
	fill_n(lvl, MAXN, INF);
	lvl[SOURCE] = 0;
	q.push(SOURCE);
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		if (lvl[now]+1 > lvl[SINK]) continue;
		for (auto i: edge[now]) {
			if (lvl[now]+1 < lvl[i] && rem[now][i]) {
				lvl[i] = lvl[now]+1;
				q.push(i);
			}
		}
	}
	return lvl[SINK] != INF;
}

lint dfs(int now, lint cur_flow) {
	if (now == SINK) return cur_flow;
	lint used_flow = 0;
	for (auto i: edge[now]) {
		if (lvl[i] == lvl[now]+1 && rem[now][i]) {
			lint next_flow = dfs(i, min(rem[now][i], cur_flow-used_flow));
			used_flow += next_flow;
			rem[now][i] -= next_flow;
			rem[i][now] += next_flow;
			if (used_flow == cur_flow) return used_flow;
		}
	}
	return used_flow;
}

int main() {
	#ifdef FAIRUZI10
	freopen("/home/fairuzi/Documents/CP/input.in", "r", stdin);
	#endif
	
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &x, &y, &z);
		if (x == y) continue;
		if (rem[x][y] == 0) {
			edge[x].push_back(y);
			edge[y].push_back(x);
		}
		rem[x][y] += z;
		rem[y][x] += z;
	}
	
	lint ans = 0;
	while (bfs()) {
		ans += dfs(SOURCE, INF);
	}
	printf("%lld\n", ans);
	
	return 0;
}
