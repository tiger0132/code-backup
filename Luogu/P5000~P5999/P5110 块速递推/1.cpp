#include <cstdio>
#include <cmath>
#define x(i, j, k) x##j##k[i]
#define y(i, j, k) y##j##k[i]
#define mul(C, k, A, i, B, j)\
do {\
	C##00[k] = ((ull)B##00[j] * A##00[i] + (ull)B##10[j] * A##01[i]) % P;\
	C##01[k] = ((ull)B##01[j] * A##00[i] + (ull)B##11[j] * A##01[i]) % P;\
	C##10[k] = ((ull)B##00[j] * A##10[i] + (ull)B##10[j] * A##11[i]) % P;\
	C##11[k] = ((ull)B##01[j] * A##10[i] + (ull)B##11[j] * A##11[i]) % P;\
} while (0) // C[k] = A[i] * B[j]

typedef unsigned long long ull;
const int P = 1e9+7, M = 65536; // ceil(sqrt(1e9+6)) = 31623

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

int x00[M+5], x01[M+5], x10[M+5], x11[M+5];
int y00[M+5], y01[M+5], y10[M+5], y11[M+5];
int z00[1], z01[1], z10[1], z11[1];
int t, n, ans;
int main() {
	register int i, p, q;
	x(0, 0, 0) = x(0, 1, 1) = 1;
	y(0, 0, 0) = y(0, 1, 1) = 1;
	x(1, 0, 0) = 233; x(1, 0, 1) = 666; x(1, 1, 0) = 1;
	for (i = 2; i <= M; i++) mul(x, i, x, i-1, x, 1);
	for (i = 1; i <= M; i++) mul(y, i, y, i-1, x, M);
	for (scanf("%d", &t), $::init(); t--; ) {
		n = $::rand() % int(1e9+6);
		if (!n--) continue;
		p = n & (M-1), q = n >> 16;
		ans ^= ((ull)x00[p] * y00[q] + (ull)x01[p] * y10[q]) % P;
	}
	printf("%d\n", ans);
}