//~ TESTED ON
//~ http://codeforces.com/gym/101470 B. Circle of digits
//~ http://www.spoj.com/problems/BEADS/

#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;
int N, K;

string str;
int rentang;
int cnt[MAXN], sa[MAXN], tsa[MAXN], ra[MAXN], tra[MAXN];
vector<int> urutan;

void radix(int k) {
	memset(cnt, 0, sizeof(cnt));
	int maxi = max(300, N);
	for (int i = 0; i < N; i++) cnt[ra[min(sa[i]+k, sa[i]+rentang-k)%N]]++;
	for (int i = 1; i < maxi; i++) cnt[i] += cnt[i-1];
	for (int i = N-1; i >= 0; i--) tsa[--cnt[ra[min(sa[i]+k, sa[i]+rentang-k)%N]]] = sa[i];
	for (int i = 0; i < N; i++) sa[i] = tsa[i];
}

void compute_sa() {
	for (int i = 0; i < N; i++) ra[i] = str[i];
	for (int i = 0; i < N; i++) sa[i] = i;
	for (int k = 1; k < rentang; k <<= 1) {
		radix(k);
		radix(0);
		tra[sa[0]] = 0;
		for (int i = 1; i < N; i++)
			tra[sa[i]] = ra[sa[i]] == ra[sa[i-1]] && 
				ra[min(sa[i]+k, sa[i]+rentang-k)%N] == ra[min(sa[i-1]+k, sa[i-1]+rentang-k)%N] ? 
				tra[sa[i-1]]: tra[sa[i-1]]+1;
		for (int i = 0; i < N; i++) ra[i] = tra[i];
		if (ra[sa[N-1]] == N-1) break;
}}

bool is_valid(int m) {
	for (int j = 0; j < rentang; j++) {
		int now = j;
		for (int i = 0; i < K; i++) {
			if (ra[now%N] <= ra[urutan[m]]) now += rentang;
			else now += rentang-1;
		}
		if (now-j >= N) return 1;
	}
	return 0;
}

int main() {
	cin >> N >> K;
	cin >> str;
	
	rentang = (N+K-1)/K;
	compute_sa();
	for (int i = 0; i < N; i++) {
		urutan.push_back(sa[i]);
	}
	int l = 0, r = N;
	while (l < r) {
		int m = (l+r)/2;
		if (is_valid(m)) r = m;
		else l = m+1;
	}
	
	for (int i = 0; i < rentang; i++) {
		cout << str[(i+urutan[r])%N];
	}
	cout << endl;
	
	return 0;
}
