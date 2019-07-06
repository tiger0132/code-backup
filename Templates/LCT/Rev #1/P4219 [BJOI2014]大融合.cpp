#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

// clang-format off
#define M1(a,b) a
#define L M1(ch][,])0
#define R M1(ch][,])1
int p[N], ch[N][2], r[N], s[N], vs[N], st[N], top;
void up(int x) { x[s] = x[L][s] + x[R][s] + x[vs] + 1; }
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
void pd(int x) { x[r] && (rv(x[L]), rv(x[R]), x[r] = 0); }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[x[ch][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) == c(y) ? y : x), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), vs[x] += s[x[R]], vs[x] -= s[x[R] = i], up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void lnk(int x, int y) { spl(x, y), p[x] = y, vs[y] += s[x], up(y); }
// clang-format on

int n, q, x, y;
char op[2];
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) i[s] = 1;
	while (q--) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'A')
			lnk(x, y);
		else
			spl(x, y), printf("%lld\n", (x[vs] + 1ll) * (y[vs] + 1));
	}
}