#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 6, P = 1e9 + 7;

void mul(int n, int a[N][N], int b[N][N], int c[N][N]) {
	static int tmp[N][N];
	memset(tmp, 0, sizeof tmp);
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j < n; j++)
				tmp[i][j] = (tmp[i][j] + 1ll * a[i][k] * b[k][j]) % P;
	memcpy(c, tmp, sizeof tmp);
}
void pw(int n, int x[N][N], int y, int z[N][N]) {
	static int tmp[N][N];
	memset(tmp, 0, sizeof tmp);
	for (int i = 0; i < n; i++) tmp[i][i] = 1;
	for (; y; y >>= 1, mul(n, x, x, x))
		if (y & 1) mul(n, tmp, x, tmp);
	memcpy(z, tmp, sizeof tmp);
}
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * x * r % P;
	return r;
}

const int tr[N][N] = {{1, 1, 2, 0, 1}, {1}, {0, 0, 1, 1}, {0, 0, 1}, {0, 0, 0, 0, 1}};
const int src[N][N] = {{0}, {0}, {2}, {1}, {-2}};
int a[N][N], b[N][N], n;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		memcpy(a, tr, sizeof a);
		if (n < 2) {
			puts("0");
			continue;
		}
		pw(5, a, n - 2, b);
		memcpy(a, src, sizeof src);
		mul(5, b, a, a);
		printf("%d\n", (a[0][0] + P) % P);
	}
}