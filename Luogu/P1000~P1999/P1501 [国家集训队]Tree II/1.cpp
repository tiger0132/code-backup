#include <algorithm>
#include <cstdio>
#include <cstring>
#define int unsigned
#define L(x) ch[x][0]
#define R(x) ch[x][1]

const int N = 1e5 + 51, P = 51061;
// 毒瘤，慎入
struct LCT {
	int ch[N][2], p[N], sz[N], v[N], s[N], r[N], a[N], m[N], st[N];
	bool c(int x) { return R(p[x]) == x; }
	void up(int x) { s[x] = (s[L(x)] + s[R(x)] + v[x]) % P, sz[x] = sz[L(x)] + sz[R(x)] + 1; }
	void add(int x, int y) { s[x] = (s[x] + y * sz[x]) % P, v[x] = (v[x] + y) % P, a[x] = (a[x] + y) % P; }
	void mul(int x, int y) {
		s[x] = (s[x] * y) % P, v[x] = (v[x] * y) % P, a[x] = (a[x] * y) % P, m[x] = (m[x] * y) % P;
	}
	void pd(int x) {
		if (r[x]) std::swap(L(x), R(x)), r[L(x)] ^= 1, r[R(x)] ^= 1;
		mul(L(x), m[x]), mul(R(x), m[x]), add(L(x), a[x]), add(R(x), a[x]), a[x] = r[x] = 0, m[x] = 1;
	}
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

int n, m, x, y, z, w;
char buf[2];
signed main() {
	scanf("%u%u", &n, &m);
	for (int i = 1; i <= n; i++) lct.v[i] = lct.m[i] = lct.sz[i] = lct.s[i] = 1;
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), lct.link(x, y);
	while (m--) {
		scanf("%s%u%u", buf, &x, &y);
		switch (*buf) {
			case '+':
				scanf("%u", &z);
				lct.spl(x, y);
				lct.add(y, z);
				break;
			case '-':
				scanf("%u%u", &z, &w);
				lct.cut(x, y);
				lct.link(z, w);
				break;
			case '*':
				scanf("%u", &z);
				lct.spl(x, y);
				lct.mul(y, z);
				break;
			case '/':
				lct.spl(x, y);
				printf("%u\n", lct.s[y]);
				break;
		}
	}
}