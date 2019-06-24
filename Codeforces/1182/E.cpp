#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 11, P = 1e9 + 7, PP = 1e9 + 6;

void mul(int n, int a[N][N], int b[N][N], int c[N][N]) {
	static int tmp[N][N];
	memset(tmp, 0, sizeof tmp);
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j < n; j++) tmp[i][j] = (tmp[i][j] + 1ll * a[i][k] * b[k][j]) % PP;
	memcpy(c, tmp, sizeof tmp);
}
void pw(int n, int x[N][N], ll y, int z[N][N]) {
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

int A[N][N] = {{1, 1, 1}, {1}, {0, 1}};
int a[N][N] = {{0, 0, 1}, {0, 1}, {1}};
int B[N][N] = {{1, 1, 1, 2, -4}, {1}, {0, 1}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 1}};
int b[N][N] = {{}, {}, {}, {3}, {1}};

int f1, f2, f3, c;
ll n;
int main() {
	scanf("%lld%d%d%d%d", &n, &f1, &f2, &f3, &c);
	pw(3, A, n - 3, A), pw(5, B, n - 3, B);
	mul(3, A, a, a), mul(5, B, b, b);
	printf("%d", 1ll * pw(f1, a[0][0]) * pw(f2, a[0][1]) % P * pw(f3, a[0][2]) % P * pw(c, b[0][0]) % P);
}