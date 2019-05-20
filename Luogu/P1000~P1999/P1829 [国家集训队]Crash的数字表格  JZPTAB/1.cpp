#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e7 + 71, P = 20101009;

int p[N], mu[N], cnt;
inline int sum(int n, int m) { return (n * (n + 1ll) / 2) % P * (m * (m + 1ll) / 2 % P) % P; }
inline int calc(int n, int m) {
	int ans = 0;
	if (n > m) std::swap(n, m);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = std::min(n / (n / l), m / (m / l));
		ans = (ans + 1ll * (mu[r] - mu[l - 1] + P) % P * sum(n / l, m / l) % P) % P;
	}
	return ans;
}

int n, m, ans;
bool f[N];
int main() {
	scanf("%d%d", &n, &m);
	if (n > m) std::swap(n, m);
	f[1] = true, mu[1] = 1;
	for (int i = 2; i <= m; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * p[j] <= m; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				mu[i * p[j]] = -mu[i];
			else {
				mu[i * p[j]] = 0;
				break;
			}
		}
	}
	for (int i = 1; i <= m; i++) mu[i] = (mu[i - 1] + 1ll * (mu[i] + P) % P * i % P * i % P) % P;
	for (int l = 1, r; l <= n; l = r + 1) {
		r = std::min(n / (n / l), m / (m / l));
		ans = (ans + (r - l + 1ll) * (l + r) / 2 % P * calc(n / l, m / l) % P + P) % P;
	}
	printf("%d", ans);
}