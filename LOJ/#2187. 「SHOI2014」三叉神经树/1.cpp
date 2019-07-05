#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62;

// clang-format off
#define M1(a,b,c) a c
#define L M1(ch][,],0)
#define R M1(ch][,],1)
int p[N], ch[N][2], s[N], v[N], sz[N], d1[N], d2[N], t[N], st[N], top;
void up(int x) {
	(x[d1] = x[R][d1]) || (x[d1] = x * (x[s] != 1)) || (x[d1] = x[L][d1]);
	(x[d2] = x[R][d2]) || (x[d2] = x * (x[s] != 2)) || (x[d2] = x[L][d2]);
}
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void ad(int x, int k) { x[s] ^= 3, std::swap(d1[x], d2[x]), x[t] += k; }
void pd(int x) { x[t] && (ad(x[L], x[t]), ad(x[R], x[t]), x[t] = 0); }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	y[ch][k] = w, w[p] = y, (nr(y) && (z[ch][c(y)] = x)), x[p] = z, x[ch][!k] = y, y[p] = x, up(y), up(x);
}
void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) == c(y) ? y : x), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
// clang-format on

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int ans;
void solve(int x, int c) {
	int y = x[p];
	ac(y), sp(y);
	int z = y[c ? d2 : d1], ofs = c ? -1 : 1;
	if (z)
		sp(z), ad(z[R], ofs), up(z[R]), z[s] += ofs, up(z);
	else
		ad(y, ofs), ans ^= 1, up(y);
}

int n;
void dfs(int x) {
	if (x > n) return;
	for (int i = x[head]; i; i = e[i].next) dfs(e[i].to), x[s] += e[i].to[v];
	x[v] = x[s] / 2;
}

int m, x, y, z;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &x, &y, &z), x[p] = y[p] = z[p] = i, addedge(i, x), addedge(i, y), addedge(i, z);
	for (int i = n + 1; i <= 3 * n + 1; i++) scanf("%d", v + i);
	dfs(1), ans = 1 [v];
	for (scanf("%d", &m); m--;) {
		scanf("%d", &x);
		solve(x, x[v]), x[v] ^= 1;
		printf("%d\n", ans);
	}
}