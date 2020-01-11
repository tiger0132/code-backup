#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e2 + 25, M = 21, K = 1 << M;

int n, m, f[N][M], dp[K], msk;
char s[N];
int main() {
	for (scanf("%*d"); ~scanf("%d%s", &m, s + 1);) {
		if (m > 21) {
			puts("NO");
			continue;
		}
		n = strlen(s + 1), msk = (1 << m) - 1;
		for (int j = 0; j < m; j++)
			for (int i = 0; i <= n + 1; i++) f[i][j] = n + 1;
		for (int i = 1; i <= n; i++) f[i][s[i] - 'a'] = i;
		for (int j = 0; j < m; j++)
			for (int i = n; i >= 0; i--) f[i][j] = std::min(f[i][j], f[i + 1][j]);
		for (int S = 1; S <= msk; S++) {
			dp[S] = 0;
			for (int i = 0; i < m; i++)
				if ((S >> i) & 1) dp[S] = std::max(dp[S], f[dp[S ^ (1 << i)]][i]);
		}
		puts(dp[msk] <= n ? "YES" : "NO");
	}
}