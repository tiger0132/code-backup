#include <algorithm>
#include <cstdio>
#include <cstring>
#define $(x, y) (((x) >> (y)) & 1)

const int N = 22, M = 1 << 12;

int n, x[N], y[N], z[N], dp[M];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d%d", x + i, y + i, z + i), x[i]--, y[i]--, z[i]--;
	memset(dp, 0x3f, sizeof dp), dp[0] = 0;
	for (int s = 1; s < (1 << n); s++) {
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if ($(s, i)) cnt += 3 - $(s, x[i]) - $(s, y[i]) - $(s, z[i]);
		for (int i = 0; i < n; i++)
			if ($(s, i)) {
				int w = cnt - 3 + 2 * ($(s, x[i]) + $(s, y[i]) + $(s, z[i]));
				dp[s] = std::min(dp[s], dp[s & ~(1 << i)] + w);
			}
	}
	printf("%d", dp[(1 << n) - 1]);
}