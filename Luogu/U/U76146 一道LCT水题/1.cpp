// Orz NaCly_Fish

#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e6 + 61;

// clang-format off
#define L ch][0
#define R ch][1
int p[N], ch[N][2], r[N], v1[N], v2[N], s1[N], s2[N], st[N], rec[N], top, top2;
void up(int x) { x[s1] = x[L][s1] + x[v1] + x[R][s1], x[s2] = x[L][s2] + x[v2] + x[R][s2]; }
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

int n, q, op, x, y, sc, lans;
int main() {
	scanf("%d", &n), sc = n;
	for (int i = 1; i <= n; i++) i[v1] = i[s1] = 1;
	for (scanf("%d", &q); q--;) {
		scanf("%d%d%d", &op, &x, &y), x ^= lans, y ^= lans;
		if (op == 1)
			if (f(x) ^ f(y))
				sc++, sc[v2] = sc[s2] = 1, lnk(x, sc), lnk(sc, y), $(x, y);
			else {
				spl(x, y), top2 = 0, dfs(y), sc++;
				for (int i = 1; i < top2; i++) cut(rec[i], rec[i + 1]);
				for (int i = 1; i <= top2; i++) lnk(rec[i], sc);
			}
		else if (op == 2)
			if (f(x) ^ f(y))
				puts("-1");
			else
				spl(x, y), printf("%d\n", lans = y[s2]);
		else if (f(x) ^ f(y))
			puts("-1");
		else
			spl(x, y), printf("%d\n", lans = y[s1]);
	}
}