#include <algorithm>
#include <cstdio>
#include <functional>

const int N = 3e5 + 53;
int n, k, a[N], s;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = n; i >= 2; i--) a[i] -= a[i - 1], s += a[i];
	std::sort(a + 2, a + n + 1, std::greater<int>());
	for (int i = 2; i <= k; i--) s -= a[i];
	printf("%d", s);
}