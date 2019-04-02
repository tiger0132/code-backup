#include <algorithm>
#include <cstdio>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

const int N = 5e5 + 55;
int newNode(int, int, int);
extern struct node _[];
struct node {
	int lc, rc, v;
	int insert(int l, int r, int x, int o) {
		int mid = (l + r) >> 1;
		if (l == r) return newNode(0, 0, v + o);
		if (x <= mid) return newNode(_[lc].insert(l, mid, x, o), rc, v + o);
		return newNode(lc, _[rc].insert(mid + 1, r, x, o), v + o);
	}
} _[N * 90];
inline int newNode(int lc, int rc, int v) {
	static int ptr = 1;
	_[ptr].lc = lc, _[ptr].rc = rc, _[ptr].v = v;
	return ptr++;
}

static int L[N], R[N], rt[N];
static int n, m, cl, cr, n$, i, j;
inline int lowbit(int x) { return x & -x; }
int query(int x, int l = 1, int r = n$) {
	if (l == r) return l;
	int sum = 0, mid = (l + r) >> 1;
	for (i = 1; i <= cr; i++) sum += _[_[R[i]].lc].v;
	for (i = 1; i <= cl; i++) sum -= _[_[L[i]].lc].v;
	if (x <= sum) {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].lc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].lc;
		return query(x, l, mid);
	} else {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].rc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].rc;
		return query(x - sum, mid + 1, r);
	}
}
inline void add(int x, int y, int o) {
	for (i = x; i <= n; i += lowbit(i)) rt[i] = _[rt[i]].insert(1, n$, y, o);
}

static int src[N], a[N], b[N], c[N], t[N];
static char op[2];
int main() {
	register int i, j;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) scanf("%d", src + i), t[++n$] = src[i];
	for (i = 1; i <= m; i++) {
		scanf("%s%d%d", op, a + i, b + i);
		if (*op == 'Q')
			scanf("%d", c + i);
		else
			t[++n$] = b[i];
	}
	std::sort(t + 1, t + n$ + 1);
	n$ = std::unique(t + 1, t + n$ + 1) - t - 1;
	for (i = 1; i <= n; i++) add(i, src[i] = std::lower_bound(t + 1, t + n$ + 1, src[i]) - t, 1);
	for (i = 1; i <= m; i++) {
		if (c[i]) {
			cl = cr = 0;
			for (j = a[i] - 1; j; j -= lowbit(j)) L[++cl] = rt[j];
			for (j = b[i]; j; j -= lowbit(j)) R[++cr] = rt[j];
			printf("%d\n", t[query(c[i])]);
		} else {
			b[i] = std::lower_bound(t + 1, t + n$ + 1, b[i]) - t;
			add(a[i], src[a[i]], -1);
			add(a[i], src[a[i]] = b[i], 1);
		}
	}
}