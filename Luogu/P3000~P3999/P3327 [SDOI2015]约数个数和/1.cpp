#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 5e4 + 45;
int n, m, t, p[N], mu[N], d[N], d0[N], cnt;
long long ans;
bool f[N];
int main() {
	f[1] = true, mu[1] = d[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1, d[i] = 2, d0[i] = 1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				mu[i * p[j]] = -mu[i], d[i * p[j]] = 2 * d[i], d0[i * p[j]] = 1;
			else {
				mu[i * p[j]] = 0, d[i * p[j]] = d[i] / (d0[i] + 1) * (d0[i] + 2), d0[i * p[j]] = d0[i] + 1;
				break;
			}
		}
	}
	for (int i = 1; i < N; i++) mu[i] += mu[i - 1], d[i] += d[i - 1];
	for (scanf("%d", &t); t--;) {
		scanf("%d%d", &n, &m);
		if (n > m) std::swap(n, m);
		ans = 0;
		for (int l = 1, r; l <= n; l = r + 1) {
			r = std::min(n / (n / l), m / (m / l));
			ans += 1ll * (mu[r] - mu[l - 1]) * d[n / l] * d[m / l];
		}
		printf("%lld\n", ans);
	}
}