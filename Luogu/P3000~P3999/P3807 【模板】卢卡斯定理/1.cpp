#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e5;

int P;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int fac[N + 5], ifac[N + 5];
int c(int n, int m) {
	if (n < m) return 0;
	return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;
}
int lucas(int x, int y) {
	if (x < y) return 0;
	if (x < P) return c(x, y);
	return 1ll * lucas(x / P, y / P) * c(x % P, y % P) % P;
}

int n, m;
int main() {
	fac[0] = 1;
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &m, &P);) {
		for (int i = 1; i < P; i++) fac[i] = 1ll * fac[i - 1] * i % P;
		ifac[P - 1] = pw(fac[P - 1], P - 2);
		for (int i = P - 1; i >= 1; i--) ifac[i - 1] = 1ll * ifac[i] * i % P;
		if (n < m) std::swap(n, m);
		printf("%d\n", lucas(n + m, n));
	}
}