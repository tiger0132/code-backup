#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 2e3 + 32, M = 5e6 + 65, P = 1e9 + 7;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int fac[M], ifac[M];
int c(int n, int m) { return 1ll * n[fac] * m[ifac] % P * (n - m)[ifac] % P; }

int n, k, dp[N][N];
int main() {
	scanf("%d%d", &n, &k);
	if (k == 1) return puts("1"), 0;
	0 [fac] = 0 [ifac] = 1;
	for (int i = 1; i <= n * k; i++) i[fac] = 1ll * (i - 1)[fac] * i % P;
	(n * k)[ifac] = pw((n * k)[fac], P - 2);
	for (int i = n * k - 1; i >= 1; i--) i[ifac] = 1ll * (i + 1)[ifac] * (i + 1) % P;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i; j++)
			if (i || j)
				dp[i][j] = (dp[i - 1][j] +
							(n - j + 1ll) * c(n * k - i - (j - 1) * (k - 1) - 1, k - 2) %
								P * dp[i][j - 1]) %
						   P;
			else
				dp[0][0] = 1;
	printf("%d", dp[n][n]);
}