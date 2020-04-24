#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52, K = 4e4;

#define L ch][0
#define R ch][1
#define mid (l + r) / 2

double k[N], b[N];
double f(int i, int x) { return k[i] * x + b[i]; }
bool chk(int i, int j, int x) { return f(i, x) < f(j, x); }

int ch[N][2], id[N], cnt;
void build(int& x, int l, int r) {
	if (x = ++cnt, l != r) build(x[L], l, mid), build(x[R], mid + 1, r);
}
void _upd(int x, int l, int r, int y) {
	if (chk(y, x[id], l) && chk(y, x[id], r)) return;
	if (chk(x[id], y, l) && chk(x[id], y, r)) return x[id] = y, void();
	if (chk(x[id], y, mid)) std::swap(x[id], y);
	chk(x[id], y, l) ? _upd(x[L], l, mid, y) : _upd(x[R], mid + 1, r, y);
}
void upd(int x, int l, int r, int ql, int qr, int y) {
	if (ql <= l && r <= qr) return _upd(x, l, r, y);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, y);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y);
}
int qry(int x, int l, int r, int i) {
	if (l == r) return x[id];
	int ret = i <= mid ? qry(x[L], l, mid, i) : qry(x[R], mid + 1, r, i);
	return chk(ret, x[id], i) ? x[id] : ret;
}

int n, op, x, y, z, w, la, rt, lc;
int main() {
	scanf("%d", &n);
	build(rt, 1, K);
	while (n--) {
		scanf("%d", &op);
		if (op) {
			scanf("%d%d%d%d", &x, &y, &z, &w);
			x = (x + la - 1) % 39989 + 1, y = (y + la - 1) % 1000000000 + 1;
			z = (z + la - 1) % 39989 + 1, w = (w + la - 1) % 1000000000 + 1;
			if (x > z) std::swap(x, z), std::swap(y, w);
			lc++;
			if (x == z)
				lc[k] = 0, lc[b] = std::max(y, w);
			else
				lc[k] = 1. * (w - y) / (z - x), lc[b] = y - x * lc[k];
			upd(rt, 1, K, x, z, lc);
		} else {
			scanf("%d", &x);
			x = (x + la - 1) % 39989 + 1;
			printf("%d\n", la = qry(rt, 1, K, x));
		}
	}
}