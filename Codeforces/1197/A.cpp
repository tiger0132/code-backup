#include <algorithm>
#include <cstdio>

const int N = 1e5 + 51;
int t, n, a[N];

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		std::sort(a + 1, a + n + 1);
		printf("%d\n", std::min(n - 2, a[n - 1] - 1));
	}
}