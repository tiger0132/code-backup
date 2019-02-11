#include <algorithm>
#include <cstdio>

typedef long long ll;
ll n, k, p[200002], c[200002], ans, cnt;

int main() {
	scanf("%lld%lld", &n, &k);
	cnt = 0;
	for (ll i = 2; i * i <= k; ++i)
		if (k % i == 0) {
			p[++cnt] = i;
			c[cnt] = 0;
			while (k % i == 0) {
				++c[cnt];
				k /= i;
			}
		}
	if (k > 1) {
		p[++cnt] = k;
		c[cnt] = 1;
	}
	ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= cnt; ++i) {
		ll t = 0, now = n;
		while (now) t += now /= p[i];
		ans = std::min(ans, t / c[i]);
	}
	printf("%lld\n", ans);
}