#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, a[N], t[N], c[N], ans = 1e9;
int calc(int p, int f) {
	int tp = 0;
	for (; !t[p]; p = a[p]) t[p] = ++tp, c[p] = f;
	return c[p] != f ? 1e9 : tp - t[p] + 1;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
		if (!t[i]) ans = std::min(ans, calc(i, i));
	printf("%d", ans);
}