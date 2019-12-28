#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e3 + 31;

int n, m, a[N][N], b[N][N], ca[N][N], cb[N][N], na[N], nb[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
			b[j][i] = a[i][j];
		}
	}
	memcpy(ca, a, sizeof a);
	memcpy(cb, b, sizeof b);
	for (int i = 1; i <= n; i++) {
		std::sort(ca[i] + 1, ca[i] + m + 1);
		int tmp = std::unique(ca[i] + 1, ca[i] + m + 1) - ca[i] - 1;
		for (int j = 1; j <= m; j++) {
			a[i][j] = std::lower_bound(ca[i] + 1, ca[i] + tmp + 1, a[i][j]) - ca[i];
		}
		na[i] = tmp;
	}
	for (int i = 1; i <= m; i++) {
		std::sort(cb[i] + 1, cb[i] + n + 1);
		int tmp = std::unique(cb[i] + 1, cb[i] + n + 1) - cb[i] - 1;
		for (int j = 1; j <= n; j++) {
			b[i][j] = std::lower_bound(cb[i] + 1, cb[i] + tmp + 1, b[i][j]) - cb[i];
		}
		nb[i] = tmp;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%d ", std::max(a[i][j], b[j][i]) + std::max(na[i] - a[i][j], nb[j] - b[j][i]));
		}
		puts("");
	}
}