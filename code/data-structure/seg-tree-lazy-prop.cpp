//~ TESTED ON
//~ http://www.spoj.com/problems/POSTERS/

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;

int st[4*MAXN], lz[4*MAXN], N;

void prop(int p, int l, int r) {
	// drop the lazy to its child
	// it doesn't require l and r in this case but you need it in some cases
	if (lz[p]) {
		st[p<<1] = st[p<<1|1] = lz[p];
		lz[p<<1] = lz[p<<1|1] = lz[p];
		lz[p] = 0;
	}
}

void update(int tl, int tr, int c, int p = 1, int l = 0, int r = N-1) {
	if (tl <= l && r <= tr) {
		// if this range is inside the target range
		st[p] = c;
		lz[p] = c;
	} else if (tl <= r && l <= tr) {
		// if some segment is inside the target range
		prop(p, l, r);
		int m = (l+r)/2;
		update(tl, tr, c, p<<1, l, m);
		update(tl, tr, c, p<<1|1, m+1, r);
	}
	// if no segment is inside the target range, do nothing
}

int query(int t, int p = 1, int l = 0, int r = N-1) {
	if (l == r && r == t) return st[p];
	else {
		// in this case, there would be no 'range outside the target'
		prop(p, l, r);
		int m = (l+r)/2;
		if (t <= m) return query(t, p<<1, l, m);
		else return query(t, p<<1|1, m+1, r);
	}
}

int main() {
	return 0;
}
