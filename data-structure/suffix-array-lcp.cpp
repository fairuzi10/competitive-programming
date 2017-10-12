//~ TESTED ON
//~ http://www.spoj.com/problems/ADASTRNG/

#include <bits/stdc++.h>
#define MAXN 300005
#define lint long long
using namespace std;
int N;

char str[MAXN];
int lcp[MAXN], cnt[MAXN], ra[MAXN], tra[MAXN], sa[MAXN], tsa[MAXN];
lint ans[30];

void radix(int step) {
	int maxi = max(300, N);
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < N; i++) cnt[sa[i]+step < N? ra[sa[i]+step]: 0]++;
	for (int i = 0; i < maxi; i++) cnt[i] += cnt[i-1];
	for (int i = N-1; i >= 0; i--) tsa[--cnt[sa[i]+step < N? ra[sa[i]+step]: 0]] = sa[i];
	for (int i = 0; i < N; i++) sa[i] = tsa[i];
}

void compute_sa() {
	for (int i = 0; i < N; i++) ra[i] = str[i];
	for (int i = 0; i < N; i++) sa[i] = i;
	for (int step = 1; step < N; step <<= 1) {
		radix(step);
		radix(0);
		tra[sa[0]] = 0;
		for (int i = 1; i < N; i++)
			tra[sa[i]] = ra[sa[i]] == ra[sa[i-1]] && 
				ra[sa[i]+step] == ra[sa[i-1]+step]? tra[sa[i-1]]: tra[sa[i-1]]+1;
		for (int i = 0; i < N; i++) ra[i] = tra[i];
		if (ra[sa[N-1]] == N-1) break;
}}

void compute_lcp() {
	int cur_lcp = 0;
	for (int i = 0; i < N; i++) {
		if (ra[i] == 0) {
			lcp[i] = 0;
			continue;
		}
		cur_lcp = max(0, cur_lcp-1);
		while (str[i+cur_lcp] == str[sa[ra[i]-1]+cur_lcp]) cur_lcp++;
		lcp[i] = cur_lcp;
	}
}

int main() {
	scanf("%s", str);
	N = strlen(str);
	str[N++] = '$';
	compute_sa();
	compute_lcp();
	
	for (int i = 0; i < N-1; i++) {
		ans[str[i]-'a'] += N-1-i-lcp[i];
	}
	for (int i = 0; i < 26; i++) {
		if (i > 0) printf(" ");
		printf("%lld", ans[i]);
	}
	puts("");
	
	return 0;
}
