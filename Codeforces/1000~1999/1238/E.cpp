#include <algorithm>
#include <cstdio>
#include <cstring>

const int _ = 1e5 + 51, N = 22, M = 1 << 22;

int n, m, c[N][N], dp[M];
char str[_];
int main() {
	scanf("%d%d%s", &n, &m, str + 1);
	for (int i = 1; i < n; i++)
		if (str[i] != str[i + 1])
			c[str[i] - 'a'][str[i + 1] - 'a']++, c[str[i + 1] - 'a'][str[i] - 'a']++;
	memset(dp, 0x3f, sizeof dp), dp[0] = 0;
	for (int s = 1; s < (1 << m); s++) {
		int cnt = 0;
		for (int i = 0; i < m; i++)
			if ((s >> i) & 1)
				for (int j = 0; j < m; j++)
					if ((~s >> j) & 1) cnt += c[i][j];
		for (int i = 0; i < m; i++)
			if ((s >> i) & 1) {
				int w = cnt;
				for (int j = 0; j < m; j++) w += (s >> j) & 1 ? c[j][i] : -c[i][j];
				dp[s] = std::min(dp[s], dp[s ^ (1 << i)] + w);
			}
	}
	printf("%d", dp[(1 << m) - 1]);
}