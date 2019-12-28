#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>

const int N = 2e3 + 32, K = 120;

int n, k, x, y, a[N], b[N], f[N], tmp[N];

int rnd(int l, int r) { return rand() % (r - l + 1) + l; }
int main() {
	freopen("1.in", "w", stdout);
	srand((unsigned long long)new char);
	printf("%d %d\n", n = 2e3, k = 2e3);
	for (int i = 1; i <= n; i++) {
		if (i < n) {
			a[i] = rnd(i + 1, n);
			if (a[i] == n) f[i] = 1;
		} else
			do
				a[i] = rnd(1, i - 1);
			while (f[a[i]]);
		std::set<int> s;
		x = rand() % K + 2;
		while (x--) s.insert(rand() % K + 1);
		printf("%d %d ", a[i], s.size());
		for (int i : s) printf("%d ", i);
		puts("");
	}
	for (int i = 1; i <= k; i++) printf("%d%c", b[i] = rand() % K + 1, " \n"[i == k]);
}