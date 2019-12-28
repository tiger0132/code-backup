#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 5e4 + 45, K = 5e2 + 25;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int dp[N][K], k;
ll ans;
void dfs(int x, int p) {
	dp[x][0] = 1;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x);
			for (int j = 1; j <= k; j++) ans += 1ll * dp[x][j - 1] * dp[nx][k - j];
			for (int j = 1; j <= k; j++) dp[x][j] += dp[nx][j - 1];
		}
}

int n, x, y;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	printf("%lld", ans);
}