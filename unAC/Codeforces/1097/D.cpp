#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <map>

typedef long long ll;

namespace PollardRho {
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
		for (; !(t & 1); s++) t >>= 1;
		ll y = p_(x, t, p);
		if (y == 1 || y == p-1) return 1;
		while (s--) {
			(y *= y) %= p;
			if (y == p-1) return 1;
		}
		return 0;
	}
	bool miller(ll x) { // 假装 _[x] 里面都是质数
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
}

const int N = 1e5+51, P = 1e9+7;

std::map<int, int> mp;
ll f[N], g[N];
int m;
void proc(ll x, ll cnt = 1) {
	if (x == 1) return;
	if (PollardRho::miller(x)) {
		if (!mp.count(x)) mp[x] = ++m;
		int i = mp[x];
		f[i] = x;
		g[i] += cnt;
		return;
	}
	ll p = PollardRho::pollard(x), _x = 0;
	while (!(x % p)) {
		x /= p;
		_x++;
	}
	proc(p, cnt * _x); proc(x, cnt);
}

int pr[N], np[N], sd[N], sp[N], d[N];
ll n, h[N], h_[N], p[N];
int k, cnt;
int main() {
	srand(time(0));
	scanf("%lld%d", &n, &k);
	proc(n);
	h[++cnt] = 1;
	for (int i = 1; i <= m; i++) { // m unique prime factors
		int cnt_ = cnt;
		for (int j = 1; j <= cnt_; j++) { // cnt divisors
			ll tmp = f[i];
			for (int k = 1; k <= g[i]; k++, tmp *= f[i]) { // g[i] exponment
				h[++cnt] = h[j] * tmp;
			}
		}
	}
	std::sort(h+1, h+cnt+1);
	memcpy(p, h, sizeof p);
	for (int i = 1; i <= k; i++) {
		h_[1] = 1;
		int cnt$ = 0;
		for (int i = 2; i <= cnt; i++) {
			if (!np[i]) {
				pr[++cnt$] = i;
				h_[i] = i-1;
				sd[i] = sp[i] = i+1;
			}
			for (int j = 1, k; j <= cnt$ && (k = i * pr[j]) < N; j++) {
				np[k] = 1;
				if (i % pr[j]) {
					h_[k] = h_[i] * h_[pr[j]];
				} else {
					h_[k] = h_[i] * pr[j];
					break;
				}
			}
		}
		memcpy(h, h_, sizeof h);
	}
	printf("%lld\n", h[cnt]);
	/*
	13082761331670030
	for (int i = 1; i <= m; i++) {
		printf("%lld^%lld ", f[i], g[i]);
	} puts("");
	for (int i = 1; i <= cnt; i++) {
		printf("%lld ", h[i]);
	}*/
}