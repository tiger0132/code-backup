#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 22;
double g[N][N], ans;
int _, n, m, x, y;
int main() {
	for (scanf("%d", &_); _--;) {
		memset(g, 0, sizeof g), ans = 1;
		for (scanf("%d%d", &n, &m), n--; m--;) scanf("%d%d", &x, &y), g[x][y]--, g[y][x]--, g[x][x]++, g[y][y]++;
		for (int i = 1; i <= n; i++) {
			int pos = i;
			for (int j = i + 1; j <= n; j++)
				if (g[pos][i] < g[j][i]) pos = j;
			std::swap(g[i], g[pos]);
			if (fabs(g[i][i]) < 1e-6) continue;
			for (int j = i + 1; j <= n; j++) {
				double tmp = g[j][i] / g[i][i];
				for (int k = i; k <= n + 1; k++) g[j][k] -= tmp * g[i][k];
			}
		}
		for (int i = 1; i <= n; i++) ans *= g[i][i];
		printf("%.f\n", fabs(ans));
	}
}