#include <algorithm>
#include <cstdio>
#include <cstring>
#define cmax(x, y) x = std::max(x, y)

typedef long long ll;
const int N = 5e2 + 25;

int n, k, a, b, c;
ll dp[N][N], s;
signed main() {
	memset(dp, 0xc0, sizeof dp);
	dp[0][0] = 0;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		for (int x = 0; x < k; x++) {
			int y = (s + k - x) % k;
			for (int p = 0; p <= std::min(a, k - 1); p++) {
				int q = (a + b + k - p) % k;
				if (q > b) continue;
				cmax(dp[i + 1][(x + p) % k],
					 dp[i][x] + (x + p) / k + (y + q) / k + (a + b - p - q) / k);
			}
		}
		s += a + b;
	}
	printf("%lld", *std::max_element(dp[n], dp[n] + k));
}