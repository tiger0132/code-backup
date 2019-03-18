#include <algorithm>
#include <cstdio>
#include <cstring>
#ifndef ONLINE_JUDGE
#define debugf(...) printf(__VA_ARGS__)
#else
#define debugf(...) 0
#endif

const int N = 2e5 + 52, M = 2e5 + 52, INF = 0x3f3f3f3f;
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT {
	int ch[N][2], p[N], r[N], v[N], mx[N], st[N];
	bool c(int x) { return R(p[x]) == x; }
	void up(int x) {
		mx[x] = x;
		if (v[mx[L(x)]] > v[mx[x]]) mx[x] = mx[L(x)];
		if (v[mx[R(x)]] > v[mx[x]]) mx[x] = mx[R(x)];
	}
	void pd(int x) { r[x] && (std::swap(L(x), R(x)), r[L(x)] ^= 1, r[R(x)] ^= 1, r[x] = 0); }
	bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w, p[w] = y;
		if (nr(y)) ch[z][c(y)] = x;
		p[x] = z, ch[x][!k] = y, p[y] = x;
		up(y), up(x);
	}
	void sp(int x) {
		static int top = 0;
		st[++top] = x;
		for (int i = x; nr(i); i = p[i]) st[++top] = p[i];
		while (top) pd(st[top--]);
		for (int y = p[x]; nr(x); rt(x), y = p[x])
			if (nr(y)) rt(c(x) == c(y) ? y : x);
	}
	void ac(int x) {
		for (int i = 0; x; x = p[i = x]) sp(x), R(x) = i, up(x);
	}
	void mr(int x) { ac(x), sp(x), r[x] ^= 1; }
	int fr(int x) {
		for (ac(x), sp(x); L(x);) x = L(x);
		return x;
	}
	void spl(int x, int y) { mr(x), ac(y), sp(y); }
	void cut(int x, int y) {
		if (spl(x, y), L(y) == x) p[x] = L(y) = 0;
	}
	void link(int x, int y) {
		if (mr(x), fr(y) != x) p[x] = y;
	}
	int query(int x, int y) { return spl(x, y), mx[y]; }
} lct;

struct {
	int p[N];
	int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
	void m(int x, int y) { (x = f(x)) != (y = f(y)) && (p[x] = y); }
} dsu;

struct edge {
	int x, y, a, b;
} e[M];

int n, m, ans = INF;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d%d", &e[i].x, &e[i].y, &e[i].a, &e[i].b);
	}
	std::sort(e + 1, e + m + 1, [](const edge& x, const edge& y) { return x.b < y.b; });
	for (int i = 1; i <= m; i++) lct.v[i + n] = e[i].a;
	for (int i = 1; i <= m; i++) {
		int x = e[i].x, y = e[i].y, z = e[i].a, f = 1;
		debugf("%d %d: ", x, y);
		if (dsu.f(x) == dsu.f(y)) {
			int w = lct.query(x, y);
			debugf("(same)%d", w);
			if (lct.v[w] > z)
				debugf("(cut)"), lct.cut(e[w - n].x, w), lct.cut(e[w - n].y, w);
			else
				f = 0;
		} else
			debugf("(nope)"), dsu.m(x, y);
		if (f) {
			debugf("(flag)"), lct.link(x, i + n), lct.link(y, i + n);
		}
		if (lct.fr(1) == lct.fr(n)) {
			debugf("(connected) %d %d", e[i].b, lct.query(1, n)), ans = std::min(ans, e[i].b + lct.v[lct.query(1, n)]);
		}
		debugf("\n");
	}
	printf("%d", ans == INF ? -1 : ans);
}