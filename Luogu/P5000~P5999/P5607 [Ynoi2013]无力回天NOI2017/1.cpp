#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, K = 30;
struct LB {
	int p[K];
	LB& ins(int x) {
		for (int i = K - 1; i >= 0; i--)
			if ((x >> i) & 1) {
				if (!p[i]) return p[i] = x, *this;
				x ^= p[i];
			}
		return *this;
	}
	inline LB& clear() {
		memset(p, 0, sizeof p);
		return *this;
	}
	inline int operator[](int i) const { return p[i]; }
	inline int& operator[](int i) { return p[i]; }
	LB operator+(const LB& rhs) {
		LB ret = *this;
		for (int i = 0; i < K; i++)
			if (rhs[i]) ret.ins(rhs[i]);
		return ret;
	}
	int qry(int x) {
		for (int i = K - 1; i >= 0; i--) x = std::max(x, x ^ p[i]);
		return x;
	}
};

int a[N];
struct SGT {
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
	int ch[N][2], t[N], s[N], nc;
	LB v[N];
	SGT() { nc = 1; }
	void up(int x) { x[v] = x[L][v] + x[R][v], x[s] = x[L][s] ^ x[R][s]; }
	void build(int x, int l, int r) {
		if (l == r) return x[v].ins(x[s] = a[l]), void();
		build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r), up(x);
	}
	void upd(int x, int l, int r, int i, int y) {
		if (l == r) return x[v].clear().ins(x[s] ^= y), void();
		if (i <= mid) return upd(x[L], l, mid, i, y), up(x);
		return upd(x[R], mid + 1, r, i, y), up(x);
	}
	LB qry(int x, int l, int r, int ql, int qr, int y) {
		if (ql <= l && r <= qr) return x[v];
		if (qr <= mid) return qry(x[L], l, mid, ql, qr, y);
		if (mid < ql) return qry(x[R], mid + 1, r, ql, qr, y);
		return qry(x[L], l, mid, ql, qr, y) + qry(x[R], mid + 1, r, ql, qr, y);
	}
	int qry2(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return x[s];
		if (qr <= mid) return qry2(x[L], l, mid, ql, qr);
		if (mid < ql) return qry2(x[R], mid + 1, r, ql, qr);
		return qry2(x[L], l, mid, ql, qr) ^ qry2(x[R], mid + 1, r, ql, qr);
	}
} sgt;

int n, m, op, x, y, z;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = n; i >= 1; i--) a[i] ^= a[i - 1];
	sgt.build(1, 1, n);
	while (m--) {
		scanf("%d%d%d%d", &op, &x, &y, &z);
		if (op == 1) {
			sgt.upd(1, 1, n, x, z);
			if (y < n) sgt.upd(1, 1, n, y + 1, z);
		} else if (x == y)
			printf("%d\n", std::max(z, z ^ sgt.qry2(1, 1, n, 1, x)));
		else
			printf("%d\n",
				   sgt.qry(1, 1, n, x + 1, y, z).ins(sgt.qry2(1, 1, n, 1, x)).qry(z));
	}
}