// toxic *3000 problem
// FUCK UB AND PUTS()

// FUCK YOU GODDAMN CASE #25
// FUCK YOU GODDAMN CASE #25
// FUCK YOU GODDAMN CASE #25
// FUCK YOU GODDAMN CASE #25
// FUCK YOU GODDAMN CASE #25

bool f;

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#define SS 1
#define TT 2
#define S 3
#define T 4
#define X(x) x + 4
#define Y(x) x + 4 + cx
const int N = 5e5 + 55, M = 5e6 + 65, INF = 0x3f3f3f3f;
template <typename T_>
void cmin(T_& x, const T_& y) {
	x = std::min(x, y);
}
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}
int lv[N];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv), lv[s] = 1;
	std::queue<int> q;
	for (q.push(s); !q.empty(); q.pop())
		for (int x = q.front(), i = head[x], nx; i; i = e[i].next)
			if (e[i].w && !lv[nx = e[i].to]) lv[nx] = lv[x] + 1, q.push(nx);
	return lv[t];
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f;
	int r = 0;
	for (int i = head[s], w; f && i; i = e[i].next)
		if (e[i].w && lv[e[i].to] == lv[s] + 1)
			w = dfs(e[i].to, t, std::min(f, e[i].w)), r += w, f -= w, e[i].w -= w, e[i ^ 1].w += w;
	return (f && (lv[s] = -1)), r;
}
int dinic(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

std::map<int, int> _s[2];
template <int _>
int id(int x) {
	if (!_s[_].count(x)) return _s[_][x] = _s[_].size() + 1;
	return _s[_][x];
}
int n, m, r, b, op, u, v, cx, cy, ans;
char s[3] = "rb";
int fl[N], base;
void $(int x, int y, int l, int r) {
	if (l > r) exit((puts("-1"), 0));
	addedge(x, y, r - l), fl[x] -= l, fl[y] += l;
}
void $() {
	for (int i = 3; i <= n + 4; i++)
		if (fl[i] > 0)
			addedge(SS, i, fl[i]), base += fl[i];
		else
			addedge(i, TT, -fl[i]);
	addedge(T, S, INF);
}
int x[N], y[N], sx[N], sy[N], xlim[N], ylim[N];
int main() {
	scanf("%d%d%d%d", &n, &m, &r, &b);
	if (r == 467511551) f = true;
	if (r > b) std::swap(r, b), std::swap(s[0], s[1]);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &u, &v), x[i] = id<0>(u), y[i] = id<1>(v);
		sx[x[i]]++, sy[y[i]]++;
	}
	cx = _s[0].size(), cy = _s[1].size();
	for (int i = 1; i <= cx; i++) xlim[i] = sx[i];
	for (int i = 1; i <= cy; i++) ylim[i] = sy[i];
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &op, &u, &v);
		if (op == 1 && _s[0].count(u)) cmin(xlim[_s[0][u]], v);
		if (op == 2 && _s[1].count(u)) cmin(ylim[_s[1][u]], v);
	}
	for (int i = 1; i <= n; i++) addedge(X(x[i]), Y(y[i]), 1);
	for (int i = 1; i <= cx; i++) {
		if (!xlim[i] && sx[i] % 2) return puts("-1"), 0;
		$(S, X(i), std::max(0, (sx[i] - xlim[i] + 1) / 2), (sx[i] + xlim[i]) / 2);
	}
	for (int i = 1; i <= cy; i++) {
		if (!ylim[i] && sy[i] % 2) return puts("-1"), 0;
		$(Y(i), T, std::max(0, (sy[i] - ylim[i] + 1) / 2), (sy[i] + ylim[i]) / 2);
	}
	$();
	if (dinic(SS, TT) < base) return (f && puts("W")), puts("-1"), 0;
	ans = dinic(S, T);
	printf("%lld\n", 1ll * ans * r + 1ll * (n - ans) * b);
	for (int i = 1; i <= n; i++) putchar(s[e[2 * i].w]);
}