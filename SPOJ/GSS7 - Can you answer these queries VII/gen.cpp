#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 1e5, M = 1e5, K = 1e4;

int rnd(int L, int R) { return rand() % (R - L + 1) + L; }
int n, m, op, x, y, z, a[N];
int main() {
	freopen("1.in", "w", stdout);
	srand((unsigned long long)new char);
	printf("%d\n", n = N);
	for (int i = 1; i <= n; i++) printf("%d%c", a[i] = rnd(-K, K), " \n"[i == n]);
	for (int i = 2; i <= n; i++) printf("%d %d\n", i, rnd(1, i - 1));
	printf("%d\n", m = M);
	while (m--) {
		printf("%d %d %d", op = rnd(1, 2), x = rnd(1, n), y = rnd(1, n));
		printf(op == 1 ? "\n" : " %d\n", z = rnd(-K, K));
	}
}