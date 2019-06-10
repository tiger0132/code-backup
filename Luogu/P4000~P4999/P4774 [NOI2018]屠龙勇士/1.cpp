#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>

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

ll mx;
inline ll excrt(int n, ll *a, ll *b, ll *p) {  // $ax\equiv b\pmod p$
	ll m = 1, ans = 0, x, y;
	for (int i = 1; i <= n; i++) {
		ll t = (b[i] - mul(a[i], ans, p[i]) % p[i] + p[i]) % p[i];
		a[i] = mul(a[i], m, p[i]);
		exgcd(a[i], p[i], x, y), x = (x % p[i] + p[i]) % p[i];
		ll gcd = std::__gcd(a[i], p[i]);
		if (t % gcd) return -1;
		x = mul(x, t / gcd, p[i] / gcd);
		ans += x * m;
		m *= p[i] / gcd;
		ans = (ans % m + m) % m;
	}
	if (ans < mx) ans += ((mx - ans - 1) / m + 1) * m;
	return ans;
}

ll a[N], b[N], p[N], tmp[N], x;
std::multiset<ll> s;
int t, n, m;
int main() {
	for (scanf("%d", &t); t--; s.clear(), mx = 0) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%lld", b + i);
		for (int i = 1; i <= n; i++) scanf("%lld", p + i);
		for (int i = 1; i <= n; i++) scanf("%lld", tmp + i);
		for (int i = 1; i <= m; i++) scanf("%d", &x), s.insert(x);
		for (int i = 1; i <= n; i++) {
			auto it = s.upper_bound(b[i]);
			if (it != s.begin()) it--;
			a[i] = *it, s.erase(it), s.insert(tmp[i]);
			mx = std::max(mx, (b[i] - 1) / a[i] + 1);
		}
		printf("%lld\n", excrt(n, a, b, p));
	}
}