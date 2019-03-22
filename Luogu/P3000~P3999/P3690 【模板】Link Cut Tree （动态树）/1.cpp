#include <algorithm>
#include <cstdio>
#include <cstring>

#define L(x) ch[x][0]
#define R(x) ch[x][1]

const int N = 3e5 + 53;

// clang-format off
int ch[N][2], v[N], p[N], r[N], _[N];
inline void up(int x) { v[x] = v[L(x)] ^ v[R(x)] ^ _[x]; }
inline bool c(int x) { return R(p[x]) == x; }
inline bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
inline void pd(int x) {
	if (!r[x]) return;
	std::swap(L(x), R(x));
	r[L(x)] ^= 1, r[R(x)] ^= 1; r[x] = 0;
}
inline void rt(int x) {
	int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
	ch[y][k] = w, p[w] = y;
	if (nr(y)) ch[z][c(y)] = x; p[x] = z;
	ch[x][!k] = y, p[y] = x;
	up(y), up(x);
}
inline void sp(int x) {
	static int st[N], top = 0;
	st[++top] = x;
	for (int i = x; nr(i); i = p[i]) st[++top] = p[i];
	while (top) pd(st[top--]);
	for (int y; y = p[x], nr(x); rt(x)) if (nr(y)) rt(c(x) == c(y) ? y : x);
}
inline void ac(int x) { for (int i = 0; x; x = p[i = x]) sp(x), R(x) = i, up(x); }
inline void mr(int x) { ac(x), sp(x), r[x] ^= 1; }
inline int fr(int x) { ac(x), sp(x); while (L(x)) x = L(x); return x; }
inline void spl(int x, int y) { mr(x), ac(y), sp(y); }
inline void cut(int x, int y) { spl(x, y); if (L(y) == x) L(y) = p[x] = 0; }
inline void lk(int x, int y) { mr(x); if (fr(y) != x) p[x] = y; }
// clang-format on

int n, m, op, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", _ + i), v[i] = _[i];
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		switch (op) {
			case 0:
				spl(x, y);
				printf("%d\n", v[y]);
				break;
			case 1:
				lk(x, y);
				break;
			case 2:
				cut(x, y);
				break;
			case 3:
				sp(x);
				_[x] = y;
				up(x);
				break;
		}
	}
}