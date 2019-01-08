#include <algorithm>
#include <cstdio>

typedef long long ll;
const int N = 1e2+21, M = 32;

int lb[M];
bool insert(int x) {
	for (int i = 31; i >= 0; i--) {
		if (1 & ~(x >> i)) continue;
		if (!lb[i]) return (lb[i] = x), 1;
		x ^= lb[i];
	}
	return 0;
}

int n, a[N];
ll ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a+i);
	std::sort(a+1, a+n+1);
	for (int i = n; i >= 1; i--) {
		ans += a[i] * !insert(a[i]);
	}
	printf("%lld\n", ans);
}