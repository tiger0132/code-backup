#include <algorithm>
#include <cstdio>

const int N = 1e2 + 21;

int n, x, y, a[N][N];
int main() {
	scanf("%d", &n);
	x = 1, y = n / 2 + 1;
	for (int i = 1; i <= n * n; i++) {
		a[x][y] = i;
		if (i % n)
			x = (x + n - 2) % n + 1, y = y % n + 1;
		else
			x = x % n + 1;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) printf("%d%c", a[i][j], " \n"[j == n]);
}