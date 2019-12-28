#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 100005;

int n, m, ans, a[N], b[N], c[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	a[n + 1] = m;
	for (int i = 1; i <= n + 1; i++) {
		b[i] = b[i - 1], c[i] = c[i - 1];
		(i % 2 ? b : c)[i] += a[i] - a[i - 1];
	}
	ans = b[n + 1];
	for (int i = 1; i <= n; i++)
		if (a[i] - a[i - 1] > 1 || a[i + 1] - a[i] > 1)
			ans = std::max(ans, b[i] + c[n + 1] - c[i] + (i % 2 ? -1 : 1));
	printf("%d\n", ans);
}