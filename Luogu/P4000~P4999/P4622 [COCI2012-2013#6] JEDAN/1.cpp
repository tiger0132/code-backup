#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e4 + 41, P = 1e9 + 7;

int n, a[N], dp[2][N], *f = dp[0], *g = dp[1];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	if (n == 1) return !printf("%d", a[1] <= 0);
	f[0] = 1;
	for (int i = 2; i <= n; i++, std::swap(f, g), memset(g, 0, sizeof *dp))
		if (a[i] != -1)
			g[a[i]] = ((ll)f[a[i] - 1] + f[a[i]] + f[a[i] + 1]) % P;
		else
			for (int j = 0; j <= n / 2; j++) g[j] = ((ll)f[j - 1] + f[j] + f[j + 1]) % P;
	printf("%d", f[0]);
}