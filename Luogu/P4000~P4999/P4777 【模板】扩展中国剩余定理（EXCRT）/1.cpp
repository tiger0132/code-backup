#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long double ld;
typedef long long ll;
const int N = 1e5 + 51;

inline ll mul(ll x, ll y, ll p) { return (x * y - (ll)((ld)x / p * y) * p + p) % p; }  // 毒瘤!
void exgcd(ll a, ll b, ll &x, ll &y) {
	if (b)
		exgcd(b, a % b, y, x), y -= a / b * x;
	else
		x = 1, y = 0;
}
inline ll excrt(int n, ll *a, ll *b) {
	ll m = b[1], ans = a[1], x, y;
	for (int i = 2; i <= n; i++) {
		exgcd(m, b[i], x, y);  // $x == x0
		ll gcd = std::__gcd(m, b[i]), t = (a[i] - ans % b[i] + b[i]) % b[i];
		if (t % gcd) return -1;
		x = mul(x, t / gcd, b[i] / gcd);  // $x == x
		ans += x * m;
		m *= b[i] / gcd;
		ans = (ans % m + m) % m;
	}
	return ans;
}

ll a[N], b[N];
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", b + i, a + i);
	printf("%lld", excrt(n, a, b));
}