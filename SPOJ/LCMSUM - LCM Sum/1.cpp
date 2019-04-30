#include <algorithm>
#include <cstdio>

typedef long long ll;
const int N = 1e6 + 61;
int t, n, p[N], cnt, phi[N];
ll ans[N];
bool f[N];

int main() {
	phi[1] = 1;
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
	}
	for (int i = 1; i < N; i++) {
		for (int j = 1; i * j < N; j++) {
			ans[i * j] += i == 1 ? 1 : 1ll * i * phi[i] / 2;
		}
	}
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n);
		printf("%lld\n", n * ans[n]);
	}
}