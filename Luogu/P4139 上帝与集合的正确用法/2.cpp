#include <cstdio>
#define int long long

typedef long long ll;
const int N = 1e7+71;

int p_(ll x, int y, int z) {
	int ret = 1;
	for (; y; (x *= x) %= z, y >>= 1) if (y & 1) (ret *= x) %= z;
	return ret;
}
signed phi[N];
ll solve(int p) {
	if (p == 1) return 0;
	return p_(2, solve(phi[p]) + phi[p], p);
}
int np[N], pr[N], cnt;
int t, p;

signed main() {
	phi[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!np[i]) {
			pr[++cnt] = i;
			phi[i] = i-1;
		}
		for (int j = 1, k; j <= cnt && (k = i * pr[j]) < N; j++) {
			np[k] = 1;
			if (i % pr[j]) {
				phi[k] = phi[i] * phi[pr[j]];
			} else {
				phi[k] = phi[i] * pr[j];
				break;
			}
		}
	}
	for (scanf("%lld", &t); t--; ) {
		scanf("%lld", &p);
		printf("%lld\n", solve(p));
	}
}