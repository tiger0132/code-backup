#include <algorithm>
#include <cmath>
#include <cstdio>
#define int long long

const int N = 1e5 + 51;
int n, m, p[N], phi[N], cnt, ans;
bool f[N];

signed main() {
	f[1] = true, phi[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				phi[i * p[j]] = phi[i] * (p[j] - 1);
			else {
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
		}
		phi[i] += phi[i - 1];
	}
	scanf("%lld%lld", &n, &m);
	if (n > m) std::swap(n, m);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = std::min(n / (n / l), m / (m / l));
		ans += (phi[r] - phi[l - 1]) * (n / l) * (m / l);
	}
	printf("%lld", 2 * ans - n * m);
}