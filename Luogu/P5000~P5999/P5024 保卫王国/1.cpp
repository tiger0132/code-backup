#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 1e5 + 51, INF = 1e12;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}
struct mat {
	int a, b, c, d;
	mat operator*(const mat &r) const {
		return {std::max(a + r.a, b + r.c), std::max(a + r.b, b + r.d), std::max(c + r.a, d + r.c), std::max(c + r.b, d + r.d)};
	}
#define $(a, b) \
	{ a, a, b, -INF }
};

// clang-format off
#define M1(a,b,c) a c // 修复 vscode 语法高亮锅
#define L M1(ch][,],0)
#define R M1(ch][,],1)
int p[N], ch[N][2], g[N][2];
mat ml[N];
void up(int x) {
	x[ml] = $(x[g][0], x[g][1]);
	if (x[L]) x[ml] = x[L][ml] * x[ml];
	if (x[R]) x[ml] = x[ml] * x[R][ml];
}
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	y[ch][k] = w, w[p] = y, (nr(y) && (z[ch][c(y)] = x)), x[p] = z, x[ch][!k] = y, y[p] = x, up(y), up(x);
}
void sp(int x) { for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) == c(y) ? y : x), 0); }
void ac(int x) {
	for (int i = 0; x; x = (i = x)[p]) {
		sp(x);
		if (x[R]) x[g][0] += std::max(x[R][ml].a, x[R][ml].c), x[g][1] += x[R][ml].a;
		if (i) x[g][0] -= std::max(i[ml].a, i[ml].c), x[g][1] -= i[ml].a;
		x[R] = i, up(x);
	}
}
// clang-format on

int v[N];
void dfs(int x, int f) {
	x[g][1] = v[x];
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != f) nx[p] = x, dfs(nx, x), x[g][0] += std::max(nx[g][0], nx[g][1]), x[g][1] += nx[g][0];
	x[ml] = $(x[g][0], x[g][1]);
}
void add(int x, int y) {
	ac(x), sp(x);
	x[g][1] += y, v[x] += y;
	up(x);
}

int n, m, x, y, z, w, ofs, s, ans;
char buf[3];
signed main() {
	scanf("%lld%lld%s", &n, &m, buf);
	for (int i = 1; i <= n; i++) scanf("%lld", v + i), s += v[i];
	for (int i = 1; i < n; i++) scanf("%lld%lld", &x, &y), addedge(x, y);
	dfs(1, 0);
	while (m--) {
		scanf("%lld%lld%lld%lld", &x, &y, &z, &w);
		ofs = (2 - y - w) * -INF;
		add(x, y ? -INF : INF), add(z, w ? -INF : INF);
		sp(1);
		if (llabs(ans = s - std::max(1 [ml].a, 1 [ml].c) - ofs) > INF)
			puts("-1");
		else
			printf("%lld\n", ans);
		add(x, y ? INF : -INF), add(z, w ? INF : -INF);
	}
}