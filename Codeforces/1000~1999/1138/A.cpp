#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, m, x, l = -1, ans, a[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		if (x != l) m++, l = x;
		a[m]++;
	}
	for (int i = 1; i < m; i++) {
		ans = std::max(ans, std::min(a[i], a[i + 1]) * 2);
	}
	printf("%d", ans);
}