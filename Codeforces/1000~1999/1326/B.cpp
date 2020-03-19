#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52;

int n, a[N], t, mx;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i <= n; i++) {
		printf("%lld%c", t = mx + a[i], " \n"[i == n]);
		mx = std::max(mx, t);
	}
}