#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e4 + 41, M = 1e5 + 51, INF = 0x3f3f3f3f;
const double eps = 1e-5;
struct edge {
	int to, next;
	double w;
} e[M << 1];
int head[N], cnt = 1;
double s[N];
void addedge(int x, int y, double z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt, s[cnt] = z;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}
// clang-format off
int lv[N];
bool bfs(int s, int t) {
    std::queue<int> q; memset(lv, 0, sizeof lv), lv[s] = 1;
    for (q.push(s); !q.empty(); q.pop())
        for (int x = q.front(), i = head[x], nx; i; i = e[i].next)
            if (e[i].w > 0 && !lv[nx = e[i].to]) lv[nx] = lv[x] + 1, q.push(nx);
    return lv[t];
}
double dfs(int s, int t, double f) {
    if (s == t || !f) return f; double r = 0, w;
    for (int i = head[s]; f > 0 && i; i = e[i].next)
        if (e[i].w > 0 && lv[e[i].to] == lv[s] + 1)
            w = dfs(e[i].to, t, std::min(f, e[i].w)), r += w, f -= w, e[i].w -= w, e[i ^ 1].w += w;
    return (f > 0 && (lv[s] = -1)), r;
}
double dinic(int s, int t) { double r = 0; while (bfs(s, t)) r += dfs(s, t, INF); return r; }
void init(double lim) { for (int i = 2; i <= cnt; i++) e[i].w = std::min(s[i], lim); }
// clang-format on

double l, r, mid, mn, mx, tmp;
int n, m, p, x, y, z, ans;
int main() {
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
	init(1e9);
	printf("%.4f\n", mn = dinic(1, n));
	for (l = 0, r = 1e9; r - l > eps;) {
		init(mid = (l + r) / 2), tmp = dinic(1, n);
		(fabs(tmp - mn) < eps ? r : l) = mid;
	}
	init(mid), dinic(1, n);
	for (int i = 1; i <= cnt; i += 2) mx = std::max(mx, e[i].w);
	printf("%.4f", mx * p);
}