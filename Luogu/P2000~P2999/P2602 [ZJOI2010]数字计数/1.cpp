#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

ll l, r, p[22] = {1}, f[22], ans[22], a0[22];
int a[22], len;
void calc(ll x, int op) {
	len = 0;
	for (ll y = x; y; y /= 10) a[++len] = y % 10;
	for (int i = len; i >= 1; i--) {
		ans[0] += op * f[i - 1] * a[i];
		ans[1] += op * p[i - 1];
		ans[a[i]] -= op * p[i - 1];
		a0[a[i]] += op * (x % p[i - 1] + 1);
	}
}
int main() {
	for (int i = 1; i <= 15; i++) p[i] = p[i - 1] * 10, f[i] = i * p[i - 1];
	scanf("%lld%lld", &l, &r);
	calc(l - 1, -1), calc(r, 1);
	printf("%lld ", ans[0] + a0[0]);
	for (int i = 1; i < 10; i++) printf("%lld ", (ans[i] += ans[i - 1]) + a0[i]);
}