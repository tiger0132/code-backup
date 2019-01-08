#include <cstdio>

typedef unsigned long long ull;

const ull X1 = 233230706, X2 = 94153035, X3 = 905847205;
const int P = 1e9+7, M = 65536;

namespace $ {
	ull SA, SB, SC;
	inline void init() { scanf("%llu%llu%llu", &SA, &SB, &SC); }
	inline ull rand() {
		SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
		ull t = SA;
		SA = SB, SB = SC, SC ^= t ^ SA;
		return SC;
	}
}

int t, x21[M+5], x22[M+5], x31[M+5], x32[M+5];

int main() {
	register int n, ans = 0, p, q, i;
	*x21 = *x22 = *x31 = *x32 = 1;
	for (i = 1; i <= M; i++) {
		x21[i] = x21[i-1] * X2 % P;
		x31[i] = x31[i-1] * X3 % P;
	}
	for (i = 1; i <= M; i++) {
		x22[i] = 1ll * x22[i-1] * x21[M] % P;
		x32[i] = 1ll * x32[i-1] * x31[M] % P;
	}
	for (scanf("%d", &t), $::init(); t--; ) {
		n = $::rand() % int(1e9+6);
		p = n & (M-1); q = n >> 16;
		if (n) ans ^= X1 * (((1ll * x21[p] * x22[q]
							- 1ll * x31[p] * x32[q]) % P) + P) % P;
	}
	printf("%d\n", ans);
}