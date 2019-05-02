#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e7 + 71;
int t, n, m, p[N], cnt, mu[N], g[N];
long long ans;
bool f[N];
int main() {
	f[1] = true, mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1, g[i] = 1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j]) {
				g[i * p[j]] = -g[i] + mu[i];
				mu[i * p[j]] = -mu[i];
			} else {
				g[i * p[j]] = mu[i];
				mu[i * p[j]] = 0;
				break;
			}
		}
		g[i] += g[i - 1];
	}
	for (scanf("%d", &t); t--;) {
		ans = 0;
		scanf("%d%d", &n, &m);
		if (n > m) std::swap(n, m);
		for (int l = 1, r; l <= n; l = r + 1) {
			r = std::min(n / (n / l), m / (m / l));
			ans += 1ll * (g[r] - g[l - 1]) * (n / l) * (m / l);
		}
		printf("%lld\n", ans);
	}
}