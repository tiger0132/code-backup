#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e2 + 22, M = 350;

int n, f[N][M + 10], t[N];
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", t + i);
		std::sort(t + 1, t + n + 1);
		memset(f, 0x3f, sizeof f), f[0][0] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 0; j <= M; j++)
				for (int k = j + 1; k <= M; k++)
					f[i][k] = std::min(f[i][k], f[i - 1][j] + abs(k - t[i]));
		int ans = 1e9;
		for (int i = 0; i <= M; i++) ans = std::min(ans, f[n][i]);
		printf("%d\n", ans);
	}
}