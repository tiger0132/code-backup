#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e3 + 32;

int n, a[N], dp[N], x, top;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		top = -1;
		int j = 0;
		for (int i = 1, mx = 0; i <= 2 * n; i++, j++) {
			scanf("%d", &x);
			if (x > mx) mx = x, a[++top] = j, j = 0;
		}
		a[++top] = j;
		memset(dp, 0, sizeof dp);
		dp[0] = 1;
		for (int i = 1; i <= top; i++)
			for (int j = n; j >= a[i]; j--) dp[j] |= dp[j - a[i]];
		puts(dp[n] ? "YES" : "NO");
	}
}