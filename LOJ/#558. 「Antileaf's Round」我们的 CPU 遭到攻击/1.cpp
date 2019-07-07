#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 5e5 + 55;

inline int read() {  // Orz Itst
	int a = 0;
	bool f = 0;
	char c = getchar();
	while (c != EOF && !isdigit(c)) {
		if (c == '-') f = 1;
		c = getchar();
	}
	while (c != EOF && isdigit(c)) {
		a = (a << 3) + (a << 1) + (c ^ '0');
		c = getchar();
	}
	return f ? -a : a;
}

// clang-format off
#define M1(a,b)a
#define L ch]M1([,])0
#define R ch]M1([,])1
int p[N], ch[N][2], col[N], cnt[N], vc[N], r[N], st[N], top, pt;
ll s[N], s_[N], d[N], v[N], vs[N];
inline void up(int x) {
	x[cnt] = x[L][cnt] + x[R][cnt] + x[vc] + x[col];
	x[d] = x[L][d] + x[R][d] + x[v];
	x[s] = x[L][s] + x[R][s] + x[vs] + (x[R][cnt] + x[vc] + x[col]) * (x[v] + x[L][d]);
	x[s_] = x[R][s_] + x[L][s_] + x[vs] + (x[L][cnt] + x[vc] + x[col]) * (x[v] + x[R][d]);
}
inline bool c(int x) { return x[p][R] == x; }
inline bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
inline void rv(int x) { std::swap(x[L], x[R]), std::swap(x[s], x[s_]), x[r] ^= 1; }
inline void pd(int x) { x[r] && (rv(x[L]), rv(x[R]), x[r] = 0); }
inline void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[x[ch][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
inline void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) == c(y) ? y : x), 0);
}
inline void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[vc] += x[R][cnt] - i[cnt], x[vs] += x[R][s] - i[s], x[R] = i, up(x); }
inline void mr(int x) { ac(x), sp(x), rv(x); }
inline void spl(int x, int y) { mr(x), ac(y), sp(y); }
inline void lnk(int x, int y) { spl(x, y), p[x] = y, vs[y] += s[x], vc[y] += cnt[x], up(y); }
inline void cut(int x, int y) { spl(x, y); y[L] = x[p] = 0, up(x); }
inline void lnk(int x, int y, int z) { pt++, pt[v] = pt[d] = z, lnk(x, pt), lnk(pt, y); }
// clang-format on

int n, m, k, x, y, z;
char op[2];
signed main() {
	for (scanf("%d%d%d", &n, &m, &k), pt = n; m--;) {
		scanf("%d%d%d", &x, &y, &z);
		lnk(x, y, z);
	}
	while (k--) {
		scanf("%s%d", op, &x);
		if (*op == 'F') mr(x), x[col] ^= 1, up(x);
		if (*op == 'Q') mr(x), printf("%lld\n", x[s]);
		if (*op == 'C') {
			scanf("%d", &y);
			spl(x, y);
			if ((z = y[L]) && z[R]) z = z[R];
			z || ((z = y[R]) && z[L] && (z = z[L]));
			cut(x, z), cut(y, z);
		}
		if (*op == 'L') scanf("%d%d", &y, &z), lnk(x, y, z);
	}
}