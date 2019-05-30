#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <unordered_map>

typedef long long ll;
const int N = 2e6 + 62, P = 1e9 + 7, INF = 0x3f3f3f3f;

std::unordered_map<ll, ll> mp;
ll mu[N];
ll S_mu(ll n) {
	if (n < N) return mu[n];
	if (mp[n]) return mp[n];
	ll ret = 1;
	for (ll l = 2, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ret -= (r - l + 1) * S_mu(n / l);
	}
	return mp[n] = ret;
}
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int p[N], cnt, t, n, k, L, R, ans;
bool f[N];
int main() {
	f[1] = true, mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				mu[i * p[j]] = P - mu[i];
			else {
				mu[i * p[j]] = 0;
				break;
			}
		}
	}
	for (int i = 1; i < N; i++) mu[i] += mu[i - 1];
	scanf("%d%d%d%d", &n, &k, &L, &R), L = (L - 1) / k, R /= k;
	for (int l = 1, r; l <= R; l = r + 1) {
		r = std::min(L / l ? L / (L / l) : INF, R / (R / l));
		ans = (ans + (S_mu(r) - S_mu(l - 1)) * pw(R / l - L / l, n) % P) % P;
	}
	printf("%d", (ans + (L == 1) + P) % P);
}