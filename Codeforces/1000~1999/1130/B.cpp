#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n, x, f[N], a[N], b[N];
long long ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= 2 * n; i++) {
		scanf("%d", &x);
		if (f[x]) {
			b[x] = i;
		} else {
			a[x] = i;
			f[x] = 1;
		}
	}
	a[0] = b[0] = 1;
	for (int i = 1; i <= n; i++) {
		ans += abs(a[i] - a[i - 1]) + abs(b[i] - b[i - 1]);
	}
	printf("%lld", ans);
}