#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

int a[22], mp[2555], c, len;
ll dp[22][2555][55];
ll dfs(int x, int rem, int mod, bool lim) {
	if (!x) return !(rem % mod);
	if (!lim && dp[x][rem][mp[mod]] != -1) return dp[x][rem][mp[mod]];
	int rb = lim ? a[x] : 9;
	ll ret = 0;
	for (int i = 0; i <= rb; i++)
		ret += dfs(x - 1, (rem * 10 + i) % 2520,
				   i > 1 ? mod * i / std::__gcd(mod, i) : mod, lim && i == a[x]);
	if (!lim) dp[x][rem][mp[mod]] = ret;
	return ret;
}
ll calc(ll x) {
	for (len = 0; x; x /= 10) a[++len] = x % 10;
	return dfs(len, 0, 1, 1);
}

ll l, r;
int main() {
	memset(dp, -1, sizeof dp);
	for (int i = 1; i <= 2520; i++)
		if (!(2520 % i)) mp[i] = ++c;
	for (scanf("%*d"); ~scanf("%lld%lld", &l, &r);)
		printf("%lld\n", calc(r) - calc(l - 1));
}