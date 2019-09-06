#include <algorithm>
#include <cstdio>
#include <cstring>
#define X(x, y) x = std::max(x, y)
#define Y(x, y) x = std::min(x, y)

// clang-format off
#define L ch][0
#define R ch][1
const int N = 4e5 + 54;
int n, p[N], ch[N][2], r[N], v[N], s[N], mx[N], mn[N], m[N], st[N], top;
void up(int x) {
	x[mx] = std::max(x[L][mx], x[R][mx]), x[mn] = std::min(x[L][mn], x[R][mn]), x[s] = x[L][s] + x[R][s] + x[v];
	if (x > n) X(x[mx], x[v]), Y(x[mn], x[v]);
}
void neg(int x) { x[v] *= -1, x[s] *= -1, x[mx] *= -1, x[mn] *= -1, std::swap(x[mx], x[mn]), x[m] ^= 1; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
void pd(int x) { r[x] && (rv(x[L]), rv(x[R]), x[r] = 0); x[m] && (neg(x[L]), neg(x[R]), x[m] = 0); }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
bool c(int x) { return x[p][R] == x; }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
// clang-format on

struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt, num;
void addedge(int x, int y, int z) {
	e[++cnt] = {y, x[head], z}, x[head] = cnt;
	e[++cnt] = {x, y[head], z}, y[head] = cnt;
}
void dfs(int x, int _p) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != _p)
			num = ((i + 1) / 2) + n, num[p] = x,
			num[v] = num[mn] = num[mx] = num[s] = e[i].w, nx[p] = num, dfs(nx, x);
}

int q, x, y, z;
char op[11];
int main() {
	scanf("%d", &n), 0 [mx] = -1e9, 0 [mn] = 1e9;
	for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x + 1, y + 1, z);
	scanf("%d", &q);
	for (dfs(1, 0); q--;) {
		scanf("%s%d%d", op, &x, &y), x++, y++;
		if (*op == 'C')
			x--, y--, ac(x + n), sp(x + n), (x + n)[v] = y, up(x + n);
		else if (*op == 'N')
			spl(x, y), neg(y);
		else if (*op == 'S')
			spl(x, y), printf("%d\n", y[s]);
		else if (op[1] == 'A')
			spl(x, y), printf("%d\n", y[mx]);
		else
			spl(x, y), printf("%d\n", y[mn]);
	}
}