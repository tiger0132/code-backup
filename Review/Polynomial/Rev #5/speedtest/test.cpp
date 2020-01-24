#include <algorithm>
#include <cstdio>
#include <cstring>

typedef unsigned u;

u calc0(u n) {
	while (n != (n & -n)) n += n & -n;
	return n;
}
u calc1(u n) {
	u r = 1;
	while (r < n) r <<= 1;
	return r;
}
u calc2(u n) { return 1u << (32 - __builtin_clz(n - 1)); }

int main() {
	for (u i = 1; i < 10; i++)
		// if (calc0(i) != calc1(i) || calc1(i) != calc2(i) || calc0(i) != calc2(i))
		printf("i = %u, (%u %u %u)\n", i, calc0(i), calc1(i), calc2(i));
}