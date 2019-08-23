#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e3 + 35, M = 1e6, K = 1e3, P = 998244353;

int p[M + 61], sd[M + 61][3], _gcd[K + 31][K + 31], cnt;
bool f[M + 61];

void assign(int *a, int x, int y, int z) { a[0] = x, a[1] = y, a[2] = z; }
int gcd(int x, int y) {
	int ans = 1;
	for (int i = 0; i < 3; i++) {
		int v = sd[x][i], d = 1;
		if (v <= K)
			d = _gcd[v][y % v];
		else if (!(y % v))
			d = v;
		ans *= d, y /= d;
	}
	return ans;
}

int n, a[N], b[N];
int main() {
	f[1] = sd[1][0] = sd[1][1] = sd[1][2] = 1;
	for (int i = 2; i <= M; i++) {
		if (!f[i]) sd[i][0] = sd[i][1] = 1, sd[i][2] = i, p[++cnt] = i;
		for (int j = 1; j <= cnt && i * p[j] <= M; j++) {
			f[i * p[j]] = 1;
			int cm = sd[i][0] * p[j];
			if (cm < sd[i][1])
				assign(sd[i * p[j]], cm, sd[i][1], sd[i][2]);
			else if (cm < sd[i][2])
				assign(sd[i * p[j]], sd[i][1], cm, sd[i][2]);
			else
				assign(sd[i * p[j]], sd[i][1], sd[i][2], cm);
			if (!(i % p[j])) break;
		}
	}
	for (int i = 0; i <= K; i++) _gcd[i][0] = _gcd[0][i] = i;
	for (int i = 1; i <= K; i++)
		for (int j = 1; j <= i; j++) _gcd[i][j] = _gcd[j][i] = _gcd[i - j][j];
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	for (int i = 1; i <= n; i++) {
		int ans = 0;
		for (int j = 1, k = i; j <= n; j++, k = 1ll * k * i % P)
			ans = (ans + 1ll * k * gcd(a[i], b[j])) % P;
		printf("%d\n", ans);
	}
}