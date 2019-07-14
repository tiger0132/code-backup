#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT {
	int p[N], ch[N][2], r[N], sz[N], st[N], top;
	void up(int x) { sz[x] = sz[L(x)] + sz[R(x)] + 1; }
	bool c(int x) { return R(p[x]) == x; }
	bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	void rv(int x) { r[x] ^= 1, std::swap(L(x), R(x)); }
	void pd(int x) { r[x] && (rv(L(x)), rv(R(x)), r[x] = 0); }
	void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w, p[w] = y, (nr(y) && (ch[z][c(y)] = x)), p[x] = z, ch[x][!k] = y, p[y] = x, up(y), up(x);
	}
	void sp(int x) {
		for (int i = st[top = 1] = x; nr(i); i = p[i]) st[++top] = p[i];
		while (top) pd(st[top--]);
		for (int y = p[x]; nr(x); rt(x), y = p[x]) nr(y) && (rt(c(x) == c(y) ? y : x), 0);
	}
	void ac(int x) { for (int i = 0; x; x = p[i = x]) sp(x), R(x) = i, up(x); }
	void mr(int x) { ac(x), sp(x), rv(x); }
	int fr(int x) { for (ac(x), sp(x); L(x); x = L(x)) pd(x); return sp(x), x; }
	void spl(int x, int y) { mr(x), ac(y), sp(y); }
	void cut(int x, int y) { spl(x, y), L(y) = p[x] = 0, up(y); }
	void lnk(int x, int y) { mr(x), p[x] = y; }
} lct;
// clang-format on

int n, m, op, x, y, a[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++) lct.sz[i] = 1;
	for (int i = 1; i <= n; i++) scanf("%d", a + i), lct.lnk(i, std::min(n + 1, i + a[i]));
	for (scanf("%d", &m); m--;) {
		scanf("%d%d", &op, &x), x++;
		if (op == 1) {
			lct.spl(x, n + 1);
			printf("%d\n", lct.sz[n + 1] - 1);
		} else {
			scanf("%d", &y);
			lct.cut(x, std::min(n + 1, x + a[x]));
			lct.lnk(x, std::min(n + 1, x + (a[x] = y)));
		}
	}
}