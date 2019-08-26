#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55;

bool dp[N];
char s[N];
int n, m;

int main() {
	scanf("%s", s);
	n = strlen(s);
	m = 1 << int(log2(n));
	memset(dp, 1, sizeof dp);
	for (int i = 1; i <= n - m + 1; i++) {
		char c = 'z';
		for (int j = 0; j < m; j++)
			if (dp[j]) c = std::min(c, s[i + j - 1]);
		for (int j = 0; j < m; j++) dp[j] &= s[i + j - 1] == c;
		for (int j = 0; j < m; j++)
			for (int k = 1; k <= j && !dp[j]; k <<= 1)
				if (j & k) dp[j] |= dp[j ^ k];
		putchar(c);
	}
}