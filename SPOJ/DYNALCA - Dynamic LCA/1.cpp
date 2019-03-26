#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
int ch[N][2], p[N], r[N];
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
}
inline void sp(int x) {
	static int st[N], top = 0;
	st[++top] = x;
	for (int i = x; nr(i); i = p[i]) st[++top] = p[i];
	while (top) pd(st[top--]);
	for (int y; y = p[x], nr(x); rt(x)) if (nr(y)) rt(c(x) == c(y) ? y : x);
}
inline int ac(int x) { int i; for (i = 0; x; x = p[i = x]) sp(x), R(x) = i; return i; }
inline void mr(int x) { ac(x), sp(x), r[x] ^= 1; }
inline void cut(int x) { ac(x), sp(x); L(x) = p[L(x)] = 0; }
inline void lk(int x, int y) { mr(x); p[x] = y; }
inline int lca(int x, int y) { ac(x); return ac(y); }
// clang-format on

int n, m, x, y;
char op[9];
int main() {
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%s%d", op, &x);
		if (op[1] == 'i') {
			scanf("%d", &y);
			lk(x, y);
		} else if (op[1] == 'u') {
			cut(x);
		} else if (op[1] == 'c') {
			scanf("%d", &y);
			printf("%d\n", lca(x, y));
		}
	}
}