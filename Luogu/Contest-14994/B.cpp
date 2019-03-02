#include <cstdio>

const int N = 1e3 + 31, P = 19260817;

int n, m, q, c[N][N];
int main() {
	for (int i = 0; i <= 1000; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
		}
	}
	for (int i = 0; i <= 1000; i++) c[i][0] = 0;
	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= 1000; j++) {
			c[i][j] = ((1ll * c[i][j] + c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1]) % P + P) % P;
		}
	}
	for (scanf("%d", &q); q--;) {
		scanf("%d%d", &n, &m);
		if (n <= 0 || m <= 0)
			puts("0");
		else
			printf("%d\n", c[m][n]);
	}
}