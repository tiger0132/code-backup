#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54;

#define L ch][0
#define R ch][1
int p[N], ch[N][2], v[N], s[N], la[N], ra[N], gss[N], sz[N], nc, root;
void init(int x, int y) {
	x[la] = x[ra] = std::max(0, x[v] = x[s] = x[gss] = y), x[sz] = 1;
}
void up(int x) {
	x[sz] = x[L][sz] + x[R][sz] + 1, x[s] = x[L][s] + x[R][s] + x[v];
	x[la] = std::max(x[L][la], x[L][s] + x[v] + x[R][la]);
	x[ra] = std::max(x[L][ra] + x[v] + x[R][s], x[R][ra]);
	x[gss] = std::max(std::max(x[L][gss], x[R][gss]), x[L][ra] + x[v] + x[R][la]);
}
bool c(int x) { return x[p][R] == x; }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = ch[x][!k];
	ch[z][c(y)] = x, p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x, int g = 0) {
	for (int y = x[p]; y != g; rt(x), y = x[p])
		y[p] == g || (rt(c(x) == c(y) ? y : x), 0);
	g || (root = x);
}
int kth(int x, int k) {
	if (x[L] && k <= x[L][sz]) return kth(x[L], k);
	return k == x[L][sz] + 1 ? x : kth(x[R], k - x[L][sz] - 1);
}
int spl(int ql, int qr) {
	int l = kth(root, ql), r = kth(root, qr + 2);
	return sp(l), sp(r, l), r;
}
int build(int ql, int qr, int *a) {
	if (ql > qr) return 0;
	int mid = (ql + qr) / 2, x = ++nc;
	init(x, a[mid]);
	if (ql == qr) return x;
	if (x[L] = build(ql, mid - 1, a)) x[L][p] = x;
	if (x[R] = build(mid + 1, qr, a)) x[R][p] = x;
	return up(x), x;
}

int n, m, a[N], x, y, u;
char op[2];
int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n + 1; i++) scanf("%d", a + i);
	0 [a] = 1 [a] = (n += 2)[a] = 0 [gss] = -1e5;
	root = build(1, n, a);
	for (scanf("%d", &m); m--;) {
		scanf("%s%d", op, &x);
		if (*op == 'D')
			u = spl(x, x), u[L] = 0, up(u), up(root);
		else {
			scanf("%d", &y);
			if (*op == 'Q') u = spl(x, y), printf("%d\n", u[L][gss]);
			if (*op == 'R') u = spl(x, x), init(u[L], y), up(u), up(root);
			if (*op == 'I')
				u = spl(x, x - 1), init(u[L] = ++nc, y), nc[p] = u, up(u), up(root), n++;
		}
	}
}