#include <algorithm>
#include <cstdio>
#define C (n + m - 1)
#define X(x, y) ((x) + (y)*C)
#define Y(x, y) ((x) + n - 1 + (y)*C)

const int N = 4e5 + 52, P = 1e9;

int p[N], vis[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

int n, m, k, x, y, z, ans = 1;
int main() {
	scanf("%d%d%d", &n, &m, &k), n++, m++;
	for (int i = 1; i <= k; i++) {
		scanf("%d%d%d", &x, &y, &z), x++, y++;
		int v = ~x & ~y & 1;
		u(X(x, 0), Y(y, v ^ z));
		u(X(x, 1), Y(y, !v ^ z));
	}
	for (int i = 2; i <= C; i++)
		if (f(i) == f(i + C)) return puts("0"), 0;
	f(X(2, 0))[vis] = f(X(2, 1))[vis] = 1;
	for (int i = 2; i <= C; i++)
		if (!f(i)[vis] && f(i) == i) {
			f(i)[vis] = f(i + C)[vis] = 1;
			ans = ans * 2 % P;
		}
	printf("%d\n", ans);
}