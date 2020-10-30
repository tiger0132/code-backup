// O(n^2)

#include <algorithm>
#include <cstdio>
#include <cstring>

typedef std::pair<int, int> pii;
const int N = 3e3 + 33;

int f[N][N], w[N][N], pt[N][N];
int n, m, a[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
			w[i][j] = w[i][j - 1] + a[j] - a[(i + j) >> 1];
		}
	memset(f, 0x3f, sizeof f), f[0][0] = 0;
	for (int j = 1; j <= m; j++) {
		pt[j][n + 1] = n;
		for (int i = n; i >= 1; i--) {
			pii v = {1e9, 0};
			for (int k = pt[j - 1][i]; k <= pt[j][i + 1]; k++)
				v = std::min(v, {f[j - 1][k] + w[k + 1][i], k});
			f[j][i] = v.first;
			pt[j][i] = v.second;
		}
	}
	printf("%d\n", f[m][n]);
}