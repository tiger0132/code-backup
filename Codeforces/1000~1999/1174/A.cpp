#include <algorithm>
#include <cstdio>
const int N = 5e3 + 35;
int n, a[N], x, y;
int main() {
	scanf("%d", &n), n *= 2;
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n / 2; i++) x += a[i];
	for (int i = n / 2 + 1; i <= n; i++) y += a[i];
	if (x == y) return puts("-1"), 0;
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
}