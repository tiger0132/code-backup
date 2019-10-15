#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5, Q = 3e5, K = 1e9 + 6;
int rnd(int l, int r) { return rand() % (r - l + 1) + l; }

int n, q;

int main() {
	freopen("1.in", "w", stdout);
	srand((unsigned long long)new char);
	n = N, q = Q;
	printf("%d %d\n", n, q);
	for (int i = 1; i <= n; i++) printf("%d%c", rnd(0, K), " \n"[i == n]);
	while (q--) {
	mmp:
		int op = rnd(4, 6), x = rnd(1, n), y = rnd(1, n);
		if (x > y) std::swap(x, y);
		if (op == 1 || op == 6)
			printf("%d %d %d\n", op, x, y);
		else if (op == 2 || op == 3) {
			int z = rnd(0, K);
			printf("%d %d %d %d\n", op, x, y, z);
		} else {
			int z = rnd(1, n), w = z + y - x + 1;
			if (w > n || x <= w || z <= y) goto mmp;
			printf("%d %d %d %d %d\n", op, x, y, z, w);
		}
	}
}