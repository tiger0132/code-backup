#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53;

int n, m, a[N], x, sum;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), sum += a[i];
	std::sort(a + 1, a + n + 1);
	for (scanf("%d", &m); m--;) {
		scanf("%d", &x);
		printf("%d\n", sum - a[n - x + 1]);
	}
}