// 严重压行警告，可读性 = 0

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

using ll = long long;
const int N = 5e2 + 25;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}, head[y] = cnt;
}

int n, dis[N][N], fl[N][N], ban[N], vis[N], d2[N];
void spfa(int l, int r) {
	memset(d2, 0x3f, sizeof d2), d2[1] = 0;
	memset(ban, 0, sizeof ban);
	std::queue<int> q;
	for (int i = 1; i <= n; i++)
		for (int j = l; j <= r; j++)
			if (fl[i][j]) ban[i] = 1;
	for (q.push(1); !q.empty(); q.pop())
		for (int x, i = head[x = q.front()], nx = vis[x] = 0; i; i = e[i].next)
			if (!ban[nx = e[i].to] && d2[nx] > d2[x] + e[i].w)
				d2[nx] = d2[x] + e[i].w, vis[nx] || (vis[nx] = 1, q.push(nx), 0);
	dis[l][r] = d2[n];
}

int m, k, d, _, x, y, z;
ll dp[N];
int main() {
	for (scanf("%d%d%d%d", &d, &n, &k, &m); m--;) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	for (scanf("%d", &_); _--;) {
		scanf("%d%d%d", &x, &y, &z);
		std::fill(fl[x] + y, fl[x] + z + 1, 1);
	}
	for (int i = 1; i <= d; i++)
		for (int j = i; j <= d; j++) spfa(i, j);
	dp[0] = -k;
	for (int i = 1; i <= d; i++) {
		dp[i] = 1e18;
		for (int j = 0; j < i; j++) dp[i] = std::min(dp[i], dp[j] + 1ll * dis[j + 1][i] * (i - j) + k);
	}
	printf("%lld", dp[d]);
}