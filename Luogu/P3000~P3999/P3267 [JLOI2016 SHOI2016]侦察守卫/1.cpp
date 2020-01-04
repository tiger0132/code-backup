#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55, K = 55, ofs = 22;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int k, dp[N][K], tmp[K], w[N], v[N];
void dfs(int x, int p) {
	dp[x][k + ofs] = x[w];
	dp[x][ofs] = x[v] ? x[w] : 0;
	dp[x][-1 + ofs] = 0;
	for (int i = k; i >= -k; i--)
		dp[x][i + ofs] = std::min(dp[x][i + ofs], dp[x][i + 1 + ofs]);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
#define PROC() \
	for (int j = k; j >= -k; j--) tmp[j + ofs] = std::min(tmp[j + ofs], tmp[j + ofs + 1]);
			dfs(nx, x);
			memset(tmp, 0x3f, sizeof tmp);
			tmp[k + ofs] = dp[x][k + ofs] + dp[nx][-k + ofs];
			PROC();
			for (int j = 0; j <= k; j++)
				tmp[j + ofs] = std::min({tmp[j + ofs], dp[x][j + ofs] + dp[nx][-j + ofs],
										 dp[x][-j - 1 + ofs] + dp[nx][j + 1 + ofs]});
			PROC();
			for (int j = -k; j < 0; j++)
				tmp[j + ofs] =
					std::min(tmp[j + ofs], dp[x][j + ofs] + dp[nx][j + 1 + ofs]);
			PROC();
			for (int j = k; j >= -k; j--) dp[x][j + ofs] = tmp[j + ofs];
		}
}

int n, x, y;
int main() {
	memset(dp, 0x3f, sizeof dp);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	for (scanf("%d", &x); x--;) scanf("%d", &y), y[v] = 1;
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	printf("%d\n", dp[1][ofs]);
}