#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long
#define S 1
#define T 2
#define X(x) x + 1000
#define Y(x) x + 2000
#define LX(x) 3000 + x
#define LY(x) 4000 + x

const int N = 5e3 + 35, M = 4e6 + 64, INF = 0x3f3f3f3f3f3f3f3f;
const char _[] = "UDLR";
struct edge {
	int to, next, w;
	int c;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z, int w) {
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
void ek(int s, int t, int& n, int& m) {
	std::queue<int> q;
	static int dis[N], fl[N], pre[N], vis[N];
	for (n = m = 0; (memset(dis, 0x3f, sizeof dis), fl[s] = INF, dis[s] = 0), 1; n += fl[t], m += fl[t] * dis[t]) {
		for (q.push(s); !q.empty(); q.pop())
			for (int x = q.front(), i = head[x], nx = vis[x] = 0; i; i = e[i].next)
				if (dis[nx = e[i].to] > dis[x] + e[i].c && e[i].w)
					dis[nx] = dis[x] + e[i].c, pre[nx] = i, fl[nx] = std::min(fl[x], e[i].w),
					(vis[nx] || (q.push(nx), vis[nx] = 1));
		if (dis[t] == INF) return;
		for (int i = pre[t]; i; i = pre[e[i ^ 1].to]) e[i].w -= fl[t], e[i ^ 1].w += fl[t];
	}
}

int n, m, op[N], a[N], b[N], x[N], y[N], z[N];
int check(int k) {
	static int U[N], D[N], L[N], R[N];
	for (int i = 1; i <= k; i++) L[i] = D[i] = 0, R[i] = U[i] = 100;
	for (int i = 1; i <= m; i++) {
		if (op[i] == 0) U[k - b[i]] = a[i] - 1;
		if (op[i] == 1) D[b[i] + 1] = a[i] + 1;
		if (op[i] == 2) L[b[i] + 1] = a[i] + 1;
		if (op[i] == 3) R[k - b[i]] = a[i] - 1;
	}
	for (int i = 2; i <= k; i++) L[i] = std::max(L[i], L[i - 1]), D[i] = std::max(D[i], D[i - 1]);
	for (int i = k - 1; i >= 1; i--) R[i] = std::min(R[i], R[i + 1]), U[i] = std::min(U[i], U[i + 1]);
	memset(head, 0, sizeof head), cnt = 1;
	for (int i = 1; i <= n; i++) addedge(X(x[i]), Y(y[i]), 1, -z[i]);
	for (int i = 1; i <= k; i++) {
		if (L[i] > R[i] || D[i] > U[i]) return 0;
		addedge(S, LX(i), 1, 0), addedge(LY(i), T, 1, 0);
		for (int j = L[i]; j <= R[i]; j++) addedge(LX(i), X(j), 1, 0);
		for (int j = D[i]; j <= U[i]; j++) addedge(Y(j), LY(i), 1, 0);
	}
	int n, m;
	ek(S, T, n, m);
	return n == k ? -m : 0;
}

int phead[N], pcnt;
char c[2];
int ans;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld%lld", x + i, y + i, z + i);
	scanf("%lld", &m);
	for (int i = 1; i <= m; i++) scanf("%s%lld%lld", c, a + i, b + i), op[i] = strchr(_, *c) - _;
	for (int i = 1; i <= n; i++) ans = std::max(ans, check(i));
	printf("%lld", ans);
}