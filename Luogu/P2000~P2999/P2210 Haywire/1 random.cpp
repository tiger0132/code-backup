#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

const int N = 22;

int n, x[N], y[N], z[N];
int p[N], a[N], ans = 1e9;

int calc() {
	int ret = 0;
	for (int i = 1; i <= n; i++) p[a[i]] = i;
	for (int i = 1, j; i <= n; i++)
		j = p[i], ret += abs(j - p[x[i]]) + abs(j - p[y[i]]) + abs(j - p[z[i]]);
	return ret / 2;
}

int main() {
	srand(time(0));
	// freopen("haywire.in", "r", stdin);
	// freopen("haywire.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", x + i, y + i, z + i), a[i] = i;
	std::random_shuffle(a + 1, a + n + 1);
	ans = calc();
	for (int _ = 0; _ < 233; _++) {
		std::random_shuffle(a + 1, a + n + 1);
		ans = std::min(ans, calc());
		for (int __ = 0; __ < 66; __++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j < i; j++) {
					std::swap(a[i], a[j]);
					int tmp = calc();
					ans = std::min(ans, tmp);
					if (tmp > ans) std::swap(a[i], a[j]);
				}
	}
	printf("%d", ans);
}