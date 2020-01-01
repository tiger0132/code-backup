#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51, K = 1e2 + 21, P = 1e9 + 7;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}
void _(int &x, int y) { (x += y) >= P && (x -= P); }

int dp[N][2][2][K], tmp[2][2][K], sz[N], k;
void dfs(int x, int p) {
	x[sz] = 1;
	dp[x][0][0][0] = dp[x][0][1][1] = 1;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x);
			memset(tmp, 0, sizeof tmp);
			for (int u = 0; u <= std::min(x[sz] + nx[sz], k); u++)
				for (int v = std::max(u - x[sz], 0); v <= std::min(nx[sz], u); v++) {
					_(tmp[0][0][u], (ll)dp[x][0][0][u - v] * dp[nx][1][0][v] % P);
					_(tmp[0][1][u],
					  (ll)dp[x][0][1][u - v] * (dp[nx][0][0][v] + dp[nx][1][0][v]) % P);
					_(tmp[1][0][u],
					  ((ll)dp[x][0][0][u - v] * dp[nx][1][1][v] +
					   (ll)dp[x][1][0][u - v] * (dp[nx][1][0][v] + dp[nx][1][1][v])) %
						  P);
					_(tmp[1][1][u],
					  ((ll)dp[x][0][1][u - v] * (dp[nx][0][1][v] + dp[nx][1][1][v]) +
					   (ll)dp[x][1][1][u - v] * ((ll)dp[nx][0][0][v] + dp[nx][0][1][v] +
												 dp[nx][1][0][v] + dp[nx][1][1][v])) %
						  P);
				}
			x[sz] += nx[sz];
			for (int u = 0; u <= std::min(x[sz], k); ++u) {
				dp[x][0][0][u] = tmp[0][0][u];
				dp[x][0][1][u] = tmp[0][1][u];
				dp[x][1][0][u] = tmp[1][0][u];
				dp[x][1][1][u] = tmp[1][1][u];
			}
		}
}

int n, x, y;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	printf("%d", (dp[1][1][0][k] + dp[1][1][1][k]) % P);
}