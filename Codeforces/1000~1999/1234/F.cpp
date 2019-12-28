#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e6 + 61, M = 1 << 20;

int n, ans, dp[M];
char s[N];
int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
		for (int j = i, msk = 0; j <= n; j++) {
			if ((msk >> (s[j] - 97)) & 1) break;
			msk |= 1 << (s[j] - 97);
			dp[msk] = j - i + 1;
		}
	for (int i = 1; i < M; i <<= 1)
		for (int j = 0; j < M; j++)
			if (~j & i) dp[j | i] = std::max(dp[j | i], dp[j]);
	for (int i = 0; i < M; i++) ans = std::max(ans, dp[i] + dp[(M - 1) ^ i]);
	printf("%d", ans);
}