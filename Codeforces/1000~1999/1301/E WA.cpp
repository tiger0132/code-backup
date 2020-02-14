#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e2 + 25;

int R[2][N][N], G[2][N][N], Y[2][N][N], B[2][N][N], sz[N][N];
char a[N][N];
int n, m, q;
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = j; k >= 1; k--, R[0][i][j]++)  // ←
				if (a[i][k] != 'R') break;
			for (int k = i; k >= 1; k--, R[1][i][j]++)  // ↑
				if (a[k][j] != 'R') break;

			for (int k = j; k <= m; k++, G[0][i][j]++)  // →
				if (a[i][k] != 'G') break;
			for (int k = i; k >= 1; k--, G[1][i][j]++)  // ↑
				if (a[k][j] != 'G') break;

			for (int k = j; k >= 1; k--, Y[0][i][j]++)  // ←
				if (a[i][k] != 'Y') break;
			for (int k = i; k <= n; k++, Y[1][i][j]++)  // ↓
				if (a[k][j] != 'Y') break;

			for (int k = j; k <= m; k++, B[0][i][j]++)  // →
				if (a[i][k] != 'B') break;
			for (int k = i; k <= n; k++, B[1][i][j]++)  // ↓
				if (a[k][j] != 'B') break;
		}
	}
	for (int i = 1; i <= n; i++) {
		}
}