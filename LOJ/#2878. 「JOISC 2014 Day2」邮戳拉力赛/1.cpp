#include <algorithm>
#include <cstdio>
#include <cstring>
#define cmin(x, y) x = std::min(x, y)

const int N = 3e3 + 33;

int l0[N], l1[N], l2[N], l3[N];
int n, T, f[N][N];
int main() {
	scanf("%d%d", &n, &T);
	for (int i = 1; i <= n; i++) scanf("%d%d%d%d", l0 + i, l1 + i, l2 + i, l3 + i);
	memset(f, 0x3f, sizeof f), f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j) {
				cmin(f[i][j], f[i - 1][j] + 2 * j * T + l2[i] + l3[i]);
				cmin(f[i][j], f[i - 1][j - 1] + 2 * (j - 1) * T + l1[i] + l2[i]);
			}
			cmin(f[i][j], f[i - 1][j] + 2 * j * T + l0[i] + l1[i]);
			cmin(f[i][j], f[i - 1][j + 1] + 2 * (j + 1) * T + l0[i] + l3[i]);
		}
		for (int j = 1; j <= n; j++) cmin(f[i][j], f[i][j - 1] + l1[i] + l2[i]);
		for (int j = i; j >= 0; j--) cmin(f[i][j], f[i][j + 1] + l0[i] + l3[i]);
	}
	printf("%d", f[n][0] + (n + 1) * T);
}