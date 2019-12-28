#include <algorithm>
#include <cstdio>

int n, a[111], a1, a2;
int main() {
	scanf("%d", &n), n /= 2;
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	std::sort(a, a + n);
	for (int i = 0; i < n; i++) a1 += abs(2 * i + 1 - a[i]), a2 += abs(2 * i + 2 - a[i]);
	printf("%d", a1 < a2 ? a1 : a2);
}