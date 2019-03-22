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
#define F(x) for (int j = (x); j; j -= lowbit(j))

using ll = long long;
const int N = 1e5 + 51;
extern int newNode();
extern struct node pool[];
struct node {
	int lc, rc, v;
	void update(int l, int r, int x, int o) {
		int mid = (l + r) >> 1;
		if (v += o, l == r) return;
		if (x <= mid) {
			if (!lc) lc = newNode();
			pool[lc].update(l, mid, x, o);
		} else {
			if (!rc) rc = newNode();
			pool[rc].update(mid + 1, r, x, o);
		}
	}
} pool[N * 100];
int rt[N];
inline int newNode() {
	static int ptr = 1;
	return ptr++;
}

int L[N], R[N];
int n, cl, cr;
inline int lowbit(int x) { return x & -x; }
int query_(int x, bool f, int l = 1, int r = n) {
	if (l == r) return 0;
	int sum = 0, mid = (l + r) >> 1;
	for (int i = 1; i <= cr; i++) sum += pool[f ? pool[R[i]].lc : pool[R[i]].rc].v;
	for (int i = 1; i <= cl; i++) sum -= pool[f ? pool[L[i]].lc : pool[L[i]].rc].v;
	if (x <= mid) {
		for (int i = 1; i <= cl; i++) L[i] = pool[L[i]].lc;
		for (int i = 1; i <= cr; i++) R[i] = pool[R[i]].lc;
		return !f * sum + query_(x, f, l, mid);
	} else {
		for (int i = 1; i <= cl; i++) L[i] = pool[L[i]].rc;
		for (int i = 1; i <= cr; i++) R[i] = pool[R[i]].rc;
		return f * sum + query_(x, f, mid + 1, r);
	}
}
void add(int x, int y, int o) {
	for (int i = x; i <= n; i += lowbit(i)) pool[rt[i]].update(1, n, y, o);
}
int query(int l, int r, int x, int f) {
	cl = cr = 0;
	F(l - 1) L[++cl] = rt[j];
	F(r) R[++cr] = rt[j];
	return query_(x, f);
}

int m, x, p[N];
ll ans;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) rt[i] = newNode();
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		p[x] = i;
		cr = 0;
		ans += query(1, i - 1, x, 0);
		add(i, x, 1);
	}
	printf("%lld\n", ans);
	while (--m) {
		scanf("%d", &x);
		ans -= query(1, p[x] - 1, x, 0);
		ans -= query(p[x] + 1, n, x, 1);
		printf("%lld\n", ans);
		add(p[x], x, -1);
	}
}