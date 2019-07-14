#include <algorithm>
#include <cstdio>
#include <cstring>
#define int unsigned

const int N = 1e5 + 51, P = 51061;

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT {
	int p[N], ch[N][2], r[N], v[N], a[N], m[N], s[N], sz[N], st[N], top;
	void up(int x) { s[x] = (s[L(x)] + s[R(x)] + v[x]) % P, sz[x] = sz[L(x)] + sz[R(x)] + 1; }
	bool c(int x) { return R(p[x]) == x; }
	bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	void rv(int x) { r[x] ^= 1, std::swap(L(x), R(x)); }
	void ad(int x, int y) { s[x] = (s[x] + y * sz[x]) % P, a[x] = (a[x] + y) % P, v[x] = (v[x] + y) % P; }
	void ml(int x, int y) { s[x] = s[x] * y % P, a[x] = a[x] * y % P, m[x] = m[x] * y % P, v[x] = v[x] * y % P; }
	void pd(int x) {
		r[x] && (rv(L(x)), rv(R(x)), r[x] = 0);
		ml(L(x), m[x]), ml(R(x), m[x]), m[x] = 1; ad(L(x), a[x]), ad(R(x), a[x]), a[x] = 0;
	}
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

int n, q, x, y, z, w;
char op[2];
signed main() {
	scanf("%u%u", &n, &q);
	for (int i = 1; i <= n; i++) lct.sz[i] = lct.v[i] = lct.m[i] = lct.s[i] = 1;
	for (int i = 1; i < n; i++) scanf("%u%u", &x, &y), lct.lnk(x, y);
	while (q--) {
		scanf("%s%u%u", op, &x, &y);
		switch (*op) {
			case '+':
				scanf("%u", &z);
				lct.spl(x, y);
				lct.ad(y, z);
				break;
			case '-':
				scanf("%u%u", &z, &w);
				lct.cut(x, y);
				lct.lnk(z, w);
				break;
			case '*':
				scanf("%u", &z);
				lct.spl(x, y);
				lct.ml(y, z);
				break;
			case '/':
				lct.spl(x, y);
				printf("%u\n", lct.s[y]);
				break;
		}
	}
}