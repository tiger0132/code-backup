#include <algorithm>
#include <cstdio>
#include <cstdlib>

const int N = 2e3 + 32;

int n, k, a[N], f[N];

int rnd(int l, int r) { return rand() % (r - l + 1) + l; }
int main() {
	freopen("1.in", "w", stdout);
	srand((unsigned long long)new char);
	printf("%d %d\n", n = 10, k = 20);
	for (int i = 1; i <= n; i++) {
		if (i < n) {
			a[i] = rnd(i + 1, n);
			if (a[i] == n) f[i] = 1;
		} else
			do
				a[i] = rnd(1, i - 1);
			while (f[a[i]]);
		printf("%d ", a[i]);
	}
}