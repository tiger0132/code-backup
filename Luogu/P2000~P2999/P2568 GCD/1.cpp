#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 1e7 + 71;
long long ans, phi[N];
int n, p[N], cnt;
bool f[N];

int main() {
	f[1] = true, phi[1] = 1;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		if (!f[i]) p[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				phi[i * p[j]] = phi[i] * (p[j] - 1);
			else {
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++) phi[i] += phi[i - 1];
	for (int i = 1; i <= cnt; i++) ans += 2 * phi[n / p[i]] - 1;
	printf("%lld", ans);
}