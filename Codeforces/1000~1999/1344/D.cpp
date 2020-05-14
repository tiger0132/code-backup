#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define int long long
#define mid (l + r) / 2

const int N = 1e5 + 51;

int n, k, cur, a[N];
bool check(int t) {
	cur = 0;
	for (int i = 1; i <= n; i++) {
		double d = (a[i] - t - .25) / 3;
		if (d >= 0) cur += std::min(a[i], (int)(.5 + sqrtl(d)));
	}
	return cur > k;
}

int f(int x, int y) { return -3 * x * x + 3 * x + y - 1; }

int l, r, ans;
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (l = -4e18, r = 4e18; l <= r;)
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	check(l);
	for (int i = 1; i <= n; i++) {
		double d = (a[i] - l - .25) / 3;
		int out;
		if (d >= 0) out = std::min(a[i], (int)(.5 + sqrtl(d)));
		if (cur < k && f(out + 1, a[i]) == r) cur++, out++;
		printf("%lld ", out);
	}
}