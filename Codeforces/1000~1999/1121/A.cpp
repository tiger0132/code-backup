#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21;

int n, m, q, x, ans, a[N], b[N], mx[N];

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) {
		scanf("%d", b + i);
		mx[b[i]] = std::max(mx[b[i]], a[i]);
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d", &x);
		if (a[x] < mx[b[x]]) ans++;
	}
	printf("%d", ans);
}