#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long

const int N = 2e5 + 52, dir[][5] = {{3, 0, 1, 2}, {2, 0, 3}, {2, 3, 0}, {2, 1, 3}, {2, 3, 1}, {2, 2, 3}, {2, 3, 2}, {1, 4}};

std::priority_queue<int, std::vector<int>, std::greater<int>> u;
int n, x, y, z, c[N][5], dp[N][10];

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		for (scanf("%lld", &x); x--;) {
			scanf("%lld%lld", &y, &z);
			if (y == 1) {
				u.emplace(z);
				if (u.size() > 3) u.pop();
			} else if (y == 2)
				c[i][3] = std::max(c[i][3], z);
			else
				c[i][4] = std::max(c[i][4], z);
		}
		for (int j = (int)u.size() - 1; j >= 0; j--, u.pop()) c[i][j] = u.top();
	}
	for (int i = 1; i <= n; i++)
		for (int a = 0; a < 10; a++)
			for (int j = 0; j < 8; j++)
				for (int k = 1, l = 0; k <= dir[j][0] && c[i][dir[j][k]]; k++) {
					l += c[i][dir[j][k]] * (a + k == 10 ? 2 : 1);
					dp[i + 1][(a + k) % 10] = std::max(dp[i + 1][(a + k) % 10], dp[i][a] + l);
				}
	printf("%lld", *std::max_element(dp[n + 1], dp[n + 1] + 10));
}