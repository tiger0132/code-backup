#include <algorithm>
#include <cstdio>
#include <ctime>

typedef __int128_t duliu;
typedef long long ll;

const ll _[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}, M = 12;
ll p_(ll x, ll y, ll z) {
	ll ret = 1;
	for (; y; (x *= x) %= z, y >>= 1) if (y & 1) (ret *= x) %= z;
	return ret;
}
bool chk(ll p, int x) {
	ll s = 0, t = p-1;
	while (!(t & 1)) {
		t >>= 1;
		s++;
	}
	ll y = p_(x, t, p);
	if (y == 1 || y == p-1) return 1;
	while (s--) {
		(y *= y) %= p;
		if (y == p-1) return 1;
	}
	return 0;
}
bool prime(ll x) { // 假装 _[x] 里面都是质数
	if (x == 1) return 0;
	for (int i = 0; i < M; i++) {
		if (x == _[i]) return 1;
	}
	for (int i = 0; i < M; i++) {
		if (!(x % _[i]) || !chk(x, _[i])) return 0;
	}
	return 1;
}
ll abs(ll x) { return x < 0 ? -x : x; }
ll pollard(ll n) {
	ll a = rand() % (n - 1) + 1, x = 0, y = 0, t = 1;
	ll k = 1, q;
	while ("lxldl") {
		k <<= 1; q = 1; y = x;
		for (int i = 1; i <= k; i++) {
			x = ((duliu)x * x + a) % n;
			q = ((duliu)q * abs(x - y)) % n;
			if (!(i & 127)) {
				t = std::__gcd(q, n);
				if (t > 1) goto end;
			}
		}
		if ((t = std::__gcd(q, n)) > 1) break;
	}
	end:
	if (t == n) {
		do {
			x = ((duliu)x * x + a) % n;
			t = std::__gcd(abs(x - y), n);
		} while (t == 1);
	}
	return t;
}
ll ans;
void proc(ll x) {
	if (x == 1 || x <= ans) return;
	if (prime(x)) { ans = std::max(ans, x); return; }
	ll p = pollard(x);
	while (!(x % p)) x /= p;
	proc(p); proc(x);
}
int n;
ll x;
signed main() {
	srand(time(0));
	for (scanf("%d", &n); n--; ) {
		ans = 0;
		scanf("%lld", &x);
		proc(x);
		printf(ans == x ? "Prime\n" : "%lld\n", ans);
	}
}