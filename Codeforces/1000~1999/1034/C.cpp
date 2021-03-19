#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long

const int N = 1e6 + 61, P = 1e9 + 7;

int n, sz[N], p[N], f[N], g[N], c[N], S, ans;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", sz + i);
	for (int i = 2; i <= n; i++) scanf("%lld", p + i);
	for (int i = n; i >= 2; i--) i[p][sz] += i[sz];
	S = sz[1];
	for (int i = 1; i <= n; i++) {
		int t = S / std::__gcd(S, sz[i]);
		if (t <= n) c[t]++;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i) f[j] += c[i];
	g[1] = 1;
	for (int i = 1; i <= n; i++)
		if (S % i == 0 && f[i] == i) {
			ans += g[i];
			for (int j = 2 * i; j <= n; j += i) g[j] += g[i];
		}
	printf("%lld\n", ans % P);
}