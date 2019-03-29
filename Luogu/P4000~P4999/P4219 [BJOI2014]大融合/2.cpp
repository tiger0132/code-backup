#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

// clang-format off
struct LCT {
	#define L(x) ch[x][0]
	#define R(x) ch[x][1]
	int ch[N][2], p[N], sz[N], vsz[N], r[N], st[N], top;
	bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	void up(int x) { sz[x] = sz[L(x)] + sz[R(x)] + vsz[x] + 1; }
	void pd(int x) { if (r[x]) std::swap(L(x), R(x)), r[L(x)] ^= 1, r[R(x)] ^= 1, r[x] = 0; }
	bool c(int x) { return R(p[x]) == x; }
	void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w, p[w] = y, (nr(y) && (ch[z][c(y)] = x)), p[x] = z, ch[x][!k] = y, p[y] = x, up(y), up(x);
	}
	void sp(int x) {
		for (int i = st[top = 1] = x; nr(i); i = p[i]) st[++top] = p[i];
		while (top) pd(st[top--]);
		for (int y = p[x]; nr(x); rt(x), y = p[x])
			if (nr(y)) rt(c(x) == c(y) ? y : x);
	}
	void ac(int x) { for (int i = 0; x; x = p[i = x]) sp(x), vsz[x] += sz[R(x)], vsz[x] -= sz[R(x) = i]; }
	void mr(int x) { ac(x), sp(x), r[x] ^= 1; }
	void spl(int x, int y) { mr(x), ac(y), sp(y); }
	void lk(int x, int y) { spl(x, y), p[x] = y, vsz[y] += sz[x], up(y); }
} lct;
// clang-format on

int n, m, x, y;
char op[2];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) lct.sz[i] = 1;
	while (m--) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'A')
			lct.lk(x, y);
		else {
			lct.spl(x, y);
			printf("%lld\n", (lct.vsz[x] + 1ll) * (lct.vsz[y] + 1));
		}
	}
}