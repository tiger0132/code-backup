#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e2 + 25, M = 5e3 + 35;

int p[N], q[N], v[N], id[N];
int n, m, f[M];
int main() {
	while (~scanf("%d%d", &n, &m)) {
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d", p + i, q + i, v + i);
			id[i] = i;
		}
		std::sort(id + 1, id + n + 1,
				  [](int x, int y) { return p[x] - q[x] < p[y] - q[y]; });
		for (int _i = 1; _i <= n; _i++) {
#define i id[_i]
			for (int j = q[i] - p[i]; j <= m - p[i]; j++) {
				f[j] = std::max(f[j], f[j + p[i]] + v[i]);
			}
		}
		printf("%d\n", *std::max_element(f, f + m + 1));
	}
}