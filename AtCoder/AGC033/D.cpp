#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 188, K = 17;

int f[K][N][N][N];
char mp[N][N];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
	for (int x = 1; x <= n; x++)
		for (int y1 = m; y1 >= 1; y1--)
			if (mp[x][y1] == mp[x][y1 + 1])
				f[0][x][x][y1] = f[0][x][x][y1 + 1];
			else
				f[0][x][x][y1] = y1;
	for (int x1 = 1; x1 <= n; x1++)
		for (int x2 = x1 + 1; x2 <= n; x2++)
			for (int y1 = 1; y1 <= m; y1++)
				if (mp[x2][y1] == mp[x2 - 1][y1])
					f[0][x1][x2][y1] = std::min(f[0][x1][x2 - 1][y1], f[0][x2][x2][y1]);
				else
					f[0][x1][x2][y1] = 0;
	for (int k = 1; k <= 16; k++)
		for (int x1 = 1; x1 <= n; x1++)
			for (int y1 = 1; y1 <= m; y1++)
				for (int x2 = x1, p = x1; x2 <= n; x2++) {
					while (p < x2 &&
						   std::min(f[k - 1][x1][p][y1], f[k - 1][p + 1][x2][y1]) <=
							   std::min(f[k - 1][x1][p + 1][y1], f[k - 1][p + 2][x2][y1]))
						p++;
					f[k][x1][x2][y1] = std::max({
						f[k - 1][x1][x2][y1],									//
						f[k - 1][x1][x2][f[k - 1][x1][x2][y1] + 1],				//
						std::min(f[k - 1][x1][p][y1], f[k - 1][p + 1][x2][y1])	//
					});
				}
	for (int k = 0; k <= 16; k++)
		if (f[k][1][n][1] == m) return !printf("%d", k);
}