#include <algorithm>
#include <cstdio>
#include <cstring>

int n, a[303030];
long long ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n / 2; i++) {
		ans += 1ll * (a[i] + a[n - i + 1]) * (a[i] + a[n - i + 1]);
	}
	printf("%lld", ans);
}