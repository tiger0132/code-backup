#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, K = 2e2 + 22, ofs = 1e2 + 11;
struct edge {
	int to, next;
} e[N << 1];
int head[N], deg[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt, x[deg]++;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt, y[deg]++;
}

int w[N], dp[N][K], tmp[K], dep[N];
void dfs(int x, int p, int d) {
	x[dep] = d;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x, d + 1);
			x[dep] = std::max(x[dep], nx[dep]);
		}
	dp[x][x[w] + ofs] = 1;
	dp[x][-1 + ofs] = 0;
	for (int j = 100; j >= -100; j--)
		dp[x][j + ofs] = std::min(dp[x][j + ofs], dp[x][j + ofs + 1]);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
#define PROC()                        \
	for (int j = 100; j >= -100; j--) \
		tmp[j + ofs] = std::min(tmp[j + ofs], tmp[j + ofs + 1]);
			memset(tmp, 0x3f, sizeof tmp);
			tmp[w[x] + ofs] = dp[x][x[w] + ofs] + dp[nx][-x[w] + ofs];
			PROC();
			for (int j = 0; j <= 100; j++)
				tmp[j + ofs] = std::min({tmp[j + ofs], dp[x][j + ofs] + dp[nx][-j + ofs],
										 dp[nx][j + 1 + ofs] + dp[x][-j - 1 + ofs]});
			PROC();
			for (int j = -100; j < 0; j++)
				tmp[j + ofs] =
					std::min({tmp[j + ofs], dp[x][j + ofs] + dp[nx][j + 1 + ofs]});
			PROC();
			for (int j = 100; j >= -100; j--) dp[x][j + ofs] = tmp[j + ofs];
		}
}

int n, x, y;
int main() {
	for (; ~scanf("%d", &n);) {
		memset(head, 0, sizeof head), cnt = 0;
		memset(dp, 0x3f, sizeof dp);
		for (int i = 1; i <= n; i++) scanf("%d", w + i);
		for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
		dfs(1, 0, 1);
		printf("%d\n", dp[1][ofs]);
	}
}