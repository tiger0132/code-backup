#include <algorithm>
#include <cstdio>
#include <cstring>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

const int N = 3e5 + 53;

// clang-format off
#define M1(a, b) a
#define L ch]M1([,])0
#define R ch]M1([,])1
int p[N], ch[N][2], r[N], s[N], l[N], t[N], mx[N], st[N], top;
void up(int x) {
	x[mx] = x;
	if (x[L][mx][t] < x[mx][t]) x[mx] = x[L][mx];
	if (x[R][mx][t] < x[mx][t]) x[mx] = x[R][mx];
	x[s] = x[L][s] + x[R][s] + x[l];
}
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
void pd(int x) { r[x] && (rv(x[L]), rv(x[R]), r[x] = 0); }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[x[ch][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void cut(int x, int y) { spl(x, y), x[p] = y[L] = 0, up(x), up(y); }
void lnk(int x, int y) { mr(x), x[p] = y, up(y); }
int _[N]; int f(int x) { return _[x] ? _[x] = f(_[x]) : x; }
int $(int x, int y) { (x = f(x)) != (y = f(y)) && (_[x] = y); }
// clang-format on

int n, m, x, y, z, a, b, u[N], v[N];
char op[10];
int main() {
	memset(t, 0x3f, sizeof t);
	for (scanf("%d%d", &n, &m); m--;) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'f') {
			scanf("%d%d%d", &z, &a, &b);
			bool fl = true;
			x += n + 1, y++, z++;
			if (f(y) == f(z)) {
				spl(y, z);
				int k = z[mx];
				if (a > k[t])
					cut(u[k], k), cut(v[k], k);
				else
					fl = false;
			}
			if (fl) u[x] = y, v[x] = z, x[t] = a, x[l] = b, up(x), lnk(y, x), lnk(z, x), $(y, z);
		} else if (*op == 'm') {
			x++, y++;
			if (f(x) == f(y))
				spl(x, y), printf("%d\n", y[s]);
			else
				puts("-1");
		} else
			x += n + 1, mr(x), x[l] = y, up(x);
	}
}