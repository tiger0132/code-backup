#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e2 + 25;

int n, m, a[N], b[N], dp[N][N], l[N][N], ans;
void prt(int i, int j, int f) {
	if (i > 1) prt(i - 1, l[i][j], j != l[i][j]);
	if (f && j) printf("%d ", b[j]);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	for (int i = 1; i <= n; i++)
		for (int j = 1, mi = 0; j <= m; j++) {
			if (a[i] != b[j])
				dp[i][j] = dp[i - 1][j], l[i][j] = j;
			else
				dp[i][j] = dp[i - 1][mi] + 1, l[i][j] = mi;
			if (b[j] < a[i] && dp[i - 1][j] > dp[i - 1][mi]) mi = j;
		}
	for (int i = 1; i <= m; i++)
		if (dp[n][i] > dp[n][ans]) ans = i;
	printf("%d\n", dp[n][ans]);
	prt(n, ans, 1);
}