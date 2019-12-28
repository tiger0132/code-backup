#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55;

int n, k, d, a[N], dp[N];
int main() {
	scanf("%d%d%d", &n, &k, &d);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	dp[0] = 1;
	int cnt = 0;
	for (int l = 0, r = k; r <= n; r++) {
		if (dp[r - k]) cnt++;
		while (a[r] - a[l + 1] > d && r - l >= k) {
			if (dp[l]) cnt--;
			l++;
		}
		if (cnt && a[r] - a[l + 1] <= d && r - l >= k) dp[r] = 1;
	}
	puts(dp[n] ? "YES" : "NO");
}