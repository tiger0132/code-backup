#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const double eps = 1e-6;
const int N = 1e2 + 21;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}
double a[N], b[N], c[N], dp[N][N];
int n, m, sz[N];
void dfs(int x, int p) {
	sz[x] = 1, dp[x][0] = 0, dp[x][1] = c[x];
	for (int i = head[x], nx; i; i = e[i].next) {
		if ((nx = e[i].to) == p) continue;
		dfs(nx, x), sz[x] += sz[nx];
		for (int j = std::min(m, sz[x]); j >= 1; j--) {
			for (int k = 0; k < j; k++) {
				dp[x][j] = std::max(dp[x][j], dp[x][j - k] + dp[nx][k]);
			}
		}
	}
}
bool chk(double x) {
	for (int i = 1; i <= n; i++) c[i] = a[i] - x * b[i];
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++) dp[i][j] = -1e8;
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		if (dp[i][m] >= 0) return true;
	return false;
}

double l, r, mid;
int x, y;
int main() {
	scanf("%d%d", &n, &m), m = n - m;
	for (int i = 1; i <= n; i++) scanf("%lf", a + i);
	for (int i = 1; i <= n; i++) scanf("%lf", b + i);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	for (l = 0, r = 1e6; r - l > eps;) mid = (l + r) / 2, (chk(mid) ? l : r) = mid;
	printf("%.1f", l);
}