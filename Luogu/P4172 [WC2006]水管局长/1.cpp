#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

using ll = long long;
const int N = 5e6 + 65, M = 5e6 + 65, INF = 0x3f3f3f3f;

struct edge {
	int x, y, w, id, f;
} e[M];
struct query {
	int op, x, y, id, ans;
} q[M];

struct dsuQwQ {
	int p[N];
	int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
	void m(int x, int y) { (x = f(x)) != (y = f(y)) && (p[x] = y); }
} dsu;

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
} lct;
int qry(int x, int y) {
	lct.spl(x, y);
	return lct.mx[y];
}

int n;
int id(int x, int y) { return (x - 1) * n + y; }

std::map<ll, int> mp;
int ans[N], m, q_, c;
int main() {
	scanf("%d%d%d", &n, &m, &q_);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
		if (e[i].x > e[i].y) std::swap(e[i].x, e[i].y);
	}
	std::sort(e + 1, e + m + 1, [](const edge& u, const edge& v) { return u.w < v.w; });
	for (int i = 1; i <= m; i++) {
		e[i].id = i;
		mp[id(e[i].x, e[i].y)] = i;
	}
	for (int i = 1; i <= q_; i++) {
		scanf("%d%d%d", &q[i].op, &q[i].x, &q[i].y);
		if (q[i].x > q[i].y) std::swap(q[i].x, q[i].y);
		if (q[i].op == 2) {
			int pos = mp[id(q[i].x, q[i].y)];
			e[pos].f = true;
			q[i].id = e[pos].id;
		}
	}
	std::sort(e + 1, e + m + 1, [](const edge& u, const edge& v) { return u.id < v.id; });
	for (int i = 1; i <= m; i++) {
		lct.v[n + i] = e[i].w;
		if (!e[i].f) {
			int x = dsu.f(e[i].x), y = dsu.f(e[i].y);
			if (x != y) {
				dsu.m(x, y);
				lct.link(e[i].x, n + i), lct.link(e[i].y, n + i);
			}
		}
	}
	for (int i = q_; i >= 1; i--) {
		if (q[i].op == 1) {
			q[i].ans = lct.v[qry(q[i].x, q[i].y)];
		} else {
			int t = qry(q[i].x, q[i].y);
			if (e[q[i].id].w < lct.v[t]) {
				lct.cut(e[t - n].x, t), lct.cut(e[t - n].y, t);
				lct.link(q[i].x, q[i].id + n), lct.link(q[i].y, q[i].id + n);
			}
		}
	}
	for (int i = 1; i <= q_; i++) {
		if (q[i].op == 1) printf("%d\n", q[i].ans);
	}
}