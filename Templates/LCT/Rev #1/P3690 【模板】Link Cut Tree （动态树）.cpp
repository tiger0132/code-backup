#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53;
int _[N];

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT {
	int ch[N][2], p[N], v[N], r[N], st[N], top;
	void up(int x) { v[x] = v[L(x)] ^ v[R(x)] ^ _[x]; }
	bool c(int x) { return R(p[x]) == x; }
	void rv(int x) { r[x] ^= 1, std::swap(L(x), R(x)); }
	void pd(int x) { r[x] && (rv(L(x)), rv(R(x)), r[x] = 0); }
	bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w, p[w] = y, (nr(y) && (ch[z][c(y)] = x)), p[x] = z, ch[x][!k] = y, p[y] = x, up(y), up(x);
	}
	void sp(int x) {
		for (int i = st[top = 1] = x; nr(i); i = p[i]) st[++top] = p[i];
		while (top) pd(st[top--]);
		for (int y = p[x]; nr(x); rt(x), y = p[x]) (nr(y) && (rt(c(x) == c(y) ? y : x), 0));
	}
	void ac(int x) { for (int i = 0; x; x = p[i = x]) sp(x), R(x) = i, up(x); }
	void mr(int x) { ac(x); sp(x); rv(x); }
	int fr(int x) { ac(x); sp(x); while (L(x)) pd(x), x = L(x); sp(x); return x; }
	void spl(int x, int y) { mr(x); ac(y); sp(y); }
	void cut(int x, int y) { mr(x); if (fr(y) == x && p[y] == x && !L(y)) R(x) = p[y] = 0, up(x); }
	void link(int x, int y) { mr(x); if (fr(y) != x) p[x] = y; }
} lct;
// clang-format on

int n, m, op, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", _ + i), lct.v[i] = _[i];
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		switch (op) {
			case 0:
				lct.spl(x, y);
				printf("%d\n", lct.v[y]);
				break;
			case 1:
				lct.link(x, y);
				break;
			case 2:
				lct.cut(x, y);
				break;
			case 3:
				lct.sp(x);
				_[x] = y;
		}
	}
}

/*
HACK:
5 6
1 2 3 4 5
1 1 2
1 2 3
1 3 4
1 4 5
2 1 5
0 1 5
*/