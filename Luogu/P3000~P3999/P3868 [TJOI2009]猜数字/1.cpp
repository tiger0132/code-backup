#include <algorithm>
#include <cmath>
#include <cstdio>
#define int ll

typedef long long ll;
const int N = 1e2 + 21;

int n, a[N], b[N];
inline ll mul(ll x, ll y, ll p) {  // O(1) 快速乘
	return (__int128)x * y % p;
}
void exgcd(ll a, ll b, ll& x, ll& y) {
	if (b)
		exgcd(b, a % b, y, x), y -= x * (a / b);
	else
		x = 1, y = 0;
}
inline ll CRT() {
	ll ans = 0, m = 1, x, y;
	for (int i = 1; i <= n; i++) m *= b[i];
	for (int i = 1; i <= n; i++) {
		ll t = m / b[i];
		exgcd(t, b[i], x, y), x = (x % b[i] + b[i]) % b[i];
		ans = (ans + mul(a[i], mul(x, t, m), m) + m) % m;
	}
	return (ans + m) % m;
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i <= n; i++) scanf("%lld", b + i), a[i] = (a[i] % b[i] + b[i]) % b[i];
	printf("%lld", CRT());
}