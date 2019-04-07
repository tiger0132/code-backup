// clang-format off
#include <cstring>
#include <cstdio>
#include <algorithm>

const int N = 3e5 + 53;

#define L(x) ch[x][0]
#define R(x) ch[x][1]
int ch[N][2], p[N], r[N], xv[N], _[N], st[N], top;
void up(int x) { xv[x] = xv[L(x)] ^ xv[R(x)] ^ _[x]; }
bool c(int x) { return R(p[x]) == x; }
bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
void pd(int x) { if (r[x]) std::swap(L(x), R(x)), r[L(x)] ^= 1, r[R(x)] ^= 1, r[x] = 0; }
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
int fr(int x) { for (ac(x), sp(x); L(x);) x = L(x); return sp(x), x; }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void cut(int x, int y) { mr(x); if (fr(y) == x && p[y] == x && !L(y)) p[y] = R(x) = 0; }
void lk(int x, int y) { mr(x); if (fr(y) != x) p[x] = y; }

int n, m, op, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", _ + i);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		switch (op) {
			case 0: spl(x, y); printf("%d\n", xv[y]); break;
			case 1: lk(x, y); break;
			case 2: cut(x, y); break;
			case 3: sp(x), _[x] = y, up(x); break;
		}
	}
}