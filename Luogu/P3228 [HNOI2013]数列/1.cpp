#include <cstdio>

using ll = long long;
ll n, k, m, p;
ll $(ll x, ll y) {
	ll ret = 1;
	for (; y; y >>= 1, (x = x * x % p))
		if (y & 1) ret = ret * x % p;
	return ret;
}
int main() {
	scanf("%lld%lld%lld%lld", &n, &k, &m, &p), n %= p;
	printf("%lld", ((n * $(m, k - 1) % p - (k - 1) * $(m, k - 2) % p * (m * (m + 1) / 2 % p) % p) % p + p) % p);
}