#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <unordered_map>

typedef long long ll;
const int N = 2e6 + 62;

std::unordered_map<int, int> mp;
ll mu[N];
ll S_mu(ll n) {
	if (n < N) return mu[n];
	if (mp[n]) return mp[n];
	ll ret = 1;
	for (ll l = 2, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ret -= S_mu(n / l) * (r - l + 1);
	}
	return mp[n] = ret;
}
ll S_phi(ll n) {
	ll ret = 0;
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ret += (S_mu(r) - S_mu(l - 1)) * (n / l) * (n / l);
	}
	return (ret + 1) / 2;
}

int p[N], cnt, t, n;
bool f[N];
int main() {
	f[1] = true, mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				mu[i * p[j]] = -mu[i];
			else {
				mu[i * p[j]] = 0;
				break;
			}
		}
	}
	for (int i = 1; i < N; i++) mu[i] += mu[i - 1];
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n);
		printf("%lld %lld\n", S_phi(n), S_mu(n));
	}
}