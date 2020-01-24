#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>

typedef unsigned long long ul;
typedef unsigned u;

namespace $ {
ul SA, SB, SC;
inline void init() { scanf("%llu%llu%llu", &SA, &SB, &SC); }
inline ul rand() {
	SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
	ul t = SA;
	SA = SB, SB = SC, SC ^= t ^ SA;
	return SC;
}
}  // namespace $

u calc0(u n) {
	while (n != (n & -n)) n += n & -n;
	return n;
}

u calc1(u n) {
	u r = 1;
	while (r < n) r <<= 1;
	return r;
}

u calc2(u n) {
	u l = 31 - __builtin_clz(n | 1);
	return 1 << l;
}

u k, x, ans;
int n;
int main() {
	scanf("%d", &n);
	$::init();
	scanf("%u", &k);
	puts("ze");
	for (int i = 1; i <= n; i++) {
		x = $::rand() % k + 1;
		ans ^= calc0(x);
	}
	printf("calc0: %.6f, %u\n", 1. * clock() / CLOCKS_PER_SEC, ans);
}