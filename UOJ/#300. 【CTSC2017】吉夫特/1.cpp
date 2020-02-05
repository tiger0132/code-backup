#include <algorithm>
#include <cstdio>
#include <cstring>

const int K = 233333, P = 1e9 + 7;

int a[K], id[K + 5], dp[K + 5], n, ans;
inline void $(int& x) { x += x >> 31 & P; }
int main() {
	scanf("%d", &n), ans = P - n;
	for (int i = 1; ~scanf("%d", a + i); i++) id[a[i]] = i, dp[a[i]] = 1;
	for (int i = 1; i <= n; $(ans += dp[a[i++]] - P))
		for (int j = a[i]; j; j = (j - 1) & a[i])
			if (id[j] > i) $(dp[j] += dp[a[i]] - P);
	printf("%d", ans);
}