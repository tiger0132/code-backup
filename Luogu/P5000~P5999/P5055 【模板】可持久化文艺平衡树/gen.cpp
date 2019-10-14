#include <algorithm>
#include <cstdio>
#include <cstring>

const int K = 1e6, N = 1e4;
int rnd(int l, int r) { return rand() % (r - l + 1) + l; }

int n, sz[N + 1000];
int main() {
	srand((unsigned long long)new char);
	freopen("1.in", "w", stdout);
	n = N;
	printf("%d\n", n);
	for (int i = 1, v; i <= n; i++) {
		printf("%d ", v = rnd(0, i - 1));
		sz[i] = sz[v];
		if (!sz[i])
			printf("1 0 %d", rnd(-K, K)), sz[i]++;
		else {
			int op = rnd(1, 4);
			printf("%d ", op);
			if (op == 1) printf("%d %d", rnd(0, sz[i]), rnd(-K, K)), sz[i]++;
			if (op == 2) printf("%d", rnd(1, sz[i])), sz[i]--;
			if (op > 2) {
				int l = rnd(1, sz[i]), r = rnd(1, sz[i]);
				if (l > r) std::swap(l, r);
				printf("%d %d", l, r);
			}
		}
		puts("");
	}
}