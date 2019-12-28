#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e2 + 25, L = 250;

struct edge {
	int to, next;
} e[N << 1];
int head[N], d[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt, x[d]++;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt, y[d]++;
}

int dp[N][2 * N], s[N][2 * N], a[N], k;
void dfs(int x, int p) {
	dp[x][L + k] = a[x];
	if (x[d] == 1)
		for (int j = 0; j < k; j++) dp[x][L + j] = a[x];
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x);
			for (int j = k; j >= -k; j--) s[x][L + j] += dp[nx][L + j];
		}
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dp[x][L + k] += dp[nx][L - k];
			for (int j = k - 1; j >= 0; j--) {
				dp[x][L + j] = std::max(dp[x][L + j],
										dp[nx][L + j + 1] + s[x][L - j] - dp[nx][L - j]);
			}
			for (int j = -1; j >= -k; j--) dp[x][L + j] += dp[nx][L + j + 1];
		}
	printf("%d: ", x);
	for (int j = -k; j <= k; j++) printf("%d%c", dp[x][L + j], " \n"[j == k]);
	// for (int j = k - 1; j >= -k; j--)
	// 	dp[x][L + j] = std::max(dp[x][L + j], dp[x][L + j + 1]);
}

int n, x, y;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	for (int j = k - 1; j >= 0; j--)
		dp[1][L + j] = std::max(dp[1][L + j + 1], dp[1][L + j]);
	printf("%d", dp[1][L]);
}