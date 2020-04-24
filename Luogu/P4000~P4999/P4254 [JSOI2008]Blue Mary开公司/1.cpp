#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54, K = 5e4;

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
void upd(int x, int l, int r, int y) {
	if (chk(y, x[id], l) && chk(y, x[id], r)) return;
	if (chk(x[id], y, l) && chk(x[id], y, r)) return x[id] = y, void();
	if (chk(x[id], y, mid)) std::swap(x[id], y);
	chk(x[id], y, l) ? upd(x[L], l, mid, y) : upd(x[R], mid + 1, r, y);
}
double qry(int x, int l, int r, int i) {
	if (l == r) return f(x[id], i);
	return std::max(f(x[id], i),
					i <= mid ? qry(x[L], l, mid, i) : qry(x[R], mid + 1, r, i));
}

int n, rt, lc, z, t;
double x, y;
char op[9];
int main() {
	build(rt, 1, K);
	b[0] = -1e9;
	for (scanf("%d", &n); n--;) {
		scanf("%s", op);
		if (*op == 'P') {
			scanf("%lf%lf", &x, &y);
			lc++, b[lc] = x - y, k[lc] = y;
			upd(rt, 1, K, lc);
		} else {
			scanf("%d", &z);
			printf("%d\n", std::max(0, (int)qry(rt, 1, K, z) / 100));
		}
	}
}