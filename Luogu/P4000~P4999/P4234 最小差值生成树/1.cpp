#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54, INF = 0x3f3f3f3f;
struct edge {
	int x, y, z;
} e[N];
int n;

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT {
	int ch[N][2], p[N], v[N], r[N], id[N], st[N], top;
	bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	void up(int x) {
		id[x] = x;
		if (id[L(x)] > n && (id[x] <= n || id[L(x)] < id[x])) id[x] = id[L(x)];
		if (id[R(x)] > n && (id[x] <= n || id[R(x)] < id[x])) id[x] = id[R(x)];
	}
	void pd(int x) { if (r[x]) std::swap(L(x), R(x)), r[L(x)] ^= 1, r[R(x)] ^= 1, r[x] = 0; }
	bool c(int x) { return R(p[x]) == x; }
	void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w, p[w] = y, (nr(y) && (ch[z][c(y)] = x)), p[x] = z, ch[x][!k] = y, p[y] = x, up(y), up(x);
	}
	void sp(int x) {
		for (int i = st[top = 1] = x; nr(i); i = p[i]) st[++top] = p[i]; while (top) pd(st[top--]);
		for (int y = p[x]; nr(x); rt(x), y = p[x]) if (nr(y)) rt(c(x) == c(y) ? y : x);
	}
	void ac(int x) { for (int i = 0; x; x = p[i = x]) sp(x), R(x) = i, up(x); }
	void mr(int x) { ac(x), sp(x), r[x] ^= 1; }
	int fr(int x) { for (ac(x), sp(x); L(x);) x = L(x); return x; }
	void spl(int x, int y) { mr(x), ac(y), sp(y); }
	void lk(int x, int y) { mr(x); p[x] = y; }
	void cut(int x, int y) { spl(x, y); L(y) = p[x] = 0; }
} lct;
struct { int p[N]; int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }} dsu;
// clang-format on

int m, ans = INF, lb = 1, cnt, vis[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].z);
	std::sort(e + 1, e + m + 1, [](const edge& x, const edge& y) { return x.z < y.z; });
	for (int i = 1; i <= m; i++) {
		int x = e[i].x, y = e[i].y, z = e[i].z, t;
		if (x == y) continue;
		if (dsu.f(x) == dsu.f(y)) {
			lct.spl(x, y), t = lct.id[y];
			lct.cut(e[t - n].x, t), lct.cut(e[t - n].y, t);
			for (vis[t - n] = 0; !vis[lb];) lb++;
		} else
			dsu.p[dsu.f(x)] = dsu.f(y), cnt++;
		vis[i] = 1, lct.v[i + n] = z, lct.lk(x, i + n), lct.lk(y, i + n);
		if (cnt >= n - 1) ans = std::min(ans, e[i].z - e[lb].z);
	}
	printf("%d", ans);
}