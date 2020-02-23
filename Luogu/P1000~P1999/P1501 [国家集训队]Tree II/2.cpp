#include <algorithm>
#include <cstdio>
#include <cstring>
#define int unsigned

const int N = 1e5 + 51, P = 51061;

// clang-format off
#define L ch][0
#define R ch][1
int ch[N][2], p[N], sz[N], v[N], r[N], a[N], m[N], s[N];
void up(int x) { x[s] = (x[L][s] + x[R][s] + x[v]) % P, x[sz] = x[L][sz] + x[R][sz] + 1; }
bool c(int x) { return x[p][R] == x; }
void add(int x, int y) { x[s] = (x[s] + y * x[sz]) % P, x[a] = (x[a] + y) % P, x[v] = (x[v] + y) % P; }
void mul(int x, int y) { x[s] = x[s] * y % P, x[v] = x[v] * y % P, x[m] = x[m] * y % P, x[a] = x[a] * y % P; }
void rv(int x) { x[r] ^= 1, std::swap(x[L], x[R]); }
void pd(int x) {
	if (x[r]) rv(x[L]), rv(x[R]), x[r] = 0;
	mul(x[L], x[m]), mul(x[R], x[m]), add(x[L], x[a]), add(x[R], x[a]), x[a] = 0, x[m] = 1;
}
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (ch[z][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void pa(int x) { if (nr(x)) pa(x[p]); pd(x); }
void sp(int x) { pa(x); for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) == c(y) ? y : x), 0); }
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
int fr(int x) { for (ac(x), sp(x); x[L]; x = x[L]) pd(x); return sp(x), x; }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void cut(int x, int y) { spl(x, y), x[p] = y[L] = 0, up(y); }
void link(int x, int y) { mr(x), x[p] = y; }
// clang-format on

int n, q, x, y, z, w;
char op[2];
signed main() {
	scanf("%u%u", &n, &q);
	for (int i = 1; i <= n; i++) i[m] = i[sz] = i[s] = i[v] = 1;
	for (int i = 1; i < n; i++) scanf("%u%u", &x, &y), link(x, y);
	while (q--) {
		scanf("%s%u%u", op, &x, &y);
		if (*op == '+')
			scanf("%u", &z), spl(x, y), add(y, z);
		else if (*op == '-')
			scanf("%u%u", &z, &w), cut(x, y), link(z, w);
		else if (*op == '*')
			scanf("%u", &z), spl(x, y), mul(y, z);
		else
			spl(x, y), printf("%u\n", y[s]);
	}
}