#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 2e2 + 22;
int a, b, d[N][N], f[N][N];

int main() {
	scanf("%d%d", &a, &b);
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++) scanf("%d", d[i] + j);
	for (int i = 0; i <= 100; i++)
		for (int j = 0; j <= 100; j++)
			for (int x = 1; x <= a; x++)
				for (int y = 1; y <= b; y++)
					f[i][j] = std::max(f[i][j], d[x][y] - i * x - j * y);
	for (int x = 1; x <= a; x++)
		for (int y = 1; y <= b; y++) {
			int tmp = 1e9;
			for (int i = 0; i <= 100; i++)
				for (int j = 0; j <= 100; j++)
					tmp = std::min(tmp, f[i][j] + i * x + j * y);
			if (tmp != d[x][y]) return puts("Impossible"), 0;
		}
	puts("Possible\n202 10401");
	for (int i = 0; i < 100; i++)
		printf("%d %d X\n%d %d Y\n", i + 1, i + 2, i + 103, i + 102);
	for (int i = 0; i <= 100; i++)
		for (int j = 0; j <= 100; j++) printf("%d %d %d\n", i + 1, j + 102, f[i][j]);
	puts("1 102");
}