#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52;

int n, m, ans, f[N][2][2], g[N][2][2], a[N];
void chkmax(int &x, int &y, int a, int b) {
	if (a > x || a == x && b < y) x = a, y = b;
}
bool check(int k) {
	f[1][1][1] = a[1] + k, g[1][1][1] = 1;
	f[1][1][0] = f[1][0][1] = -3e9;
	for (int i = 2; i <= n; i++) {
		f[i][1][0] = f[i - 1][0][0] + a[i] + k, g[i][1][0] = g[i - 1][0][0] + 1;
		if (i < n)
			f[i][1][1] = f[i - 1][0][1] + a[i] + k, g[i][1][1] = g[i - 1][0][1] + 1;
		for (int j = 0; j <= 1; j++) {
			if (f[i - 1][0][j] > f[i - 1][1][j] ||
				(f[i - 1][0][j] == f[i - 1][1][j] && g[i - 1][0][j] < g[i - 1][1][j]))
				f[i][0][j] = f[i - 1][0][j], g[i][0][j] = g[i - 1][0][j];
			else
				f[i][0][j] = f[i - 1][1][j], g[i][0][j] = g[i - 1][1][j];
		}
	}
	int x = f[n][0][0], y = g[n][0][0];
	chkmax(x, y, f[n][0][1], g[n][0][1]);
	chkmax(x, y, f[n][1][1], g[n][1][1]);
	chkmax(x, y, f[n][1][0], g[n][1][0]);
	if (y <= m) ans = x - k * m;
	return y <= m;
}
signed main() {
	scanf("%lld%lld", &n, &m);
	if (m > n / 2) return puts("Error!"), 0;
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	int l = -1e4, r = 1e4;
#define mid (l + r) / 2
	while (l <= r)
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	check(r);
	printf("%lld", ans);
}