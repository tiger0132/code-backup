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
int t, p;

signed main() {
	phi[1] = 1;
	for (signed i = 2; i < N; i++) if (!phi[i]) {
		for (signed j = i; j < N; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i * (i-1);
		}
	}
	for (scanf("%lld", &t); t--; ) {
		scanf("%lld", &p);
		printf("%lld\n", solve(p));
	}
}