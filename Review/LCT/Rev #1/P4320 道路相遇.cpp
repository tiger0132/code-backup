#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e6 + 61;

// clang-format off
#define L ch][0
#define R ch][1
int p[N], ch[N][2], r[N], v[N], s[N], st[N], rec[N], top, top2;
void up(int x) { x[s] = x[L][s] + x[v] + x[R][s]; }
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
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void cut(int x, int y) { spl(x, y), x[p] = y[L] = 0, up(x), up(y); }
void lnk(int x, int y) { mr(x), x[p] = y, up(y); }
void dfs(int x) { pd(x); if (x[L]) dfs(x[L]); rec[++top2] = x; if (x[R]) dfs(x[R]); }
int _[N];int f(int x){return _[x]?_[x]=f(_[x]):x;}void $(int x,int y){(x=f(x))^(y=f(y))&&(_[x]=y);}
// clang-format on

int n, m, q, x, y, sc;
int main() {
	scanf("%d%d", &n, &m), sc = n;
	for (int i = 1; i <= n; i++) i[v] = i[s] = 1;
	while (m--) {
		scanf("%d%d", &x, &y);
		if (f(x) ^ f(y))
			lnk(x, y), $(x, y);
		else {
			spl(x, y), top2 = 0, dfs(y), sc++;
			for (int i = 1; i < top2; i++) cut(rec[i], rec[i + 1]);
			for (int i = 1; i <= top2; i++) lnk(rec[i], sc);
		}
	}
	for (scanf("%d", &q); q--;) {
		scanf("%d%d", &x, &y);
		spl(x, y);
		printf("%d\n", y[s]);
	}
}