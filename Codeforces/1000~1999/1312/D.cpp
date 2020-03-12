#include <algorithm>
#include <cstring>
#include <cstdio>

typedef long long L;
const int N = 2e5 + 52, P = 998244353;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

int fac[N], ifac[N];
int C(int n, int m) { return (L)n[fac] * m[ifac] % P * (n - m)[ifac] % P; }

int n, m;
int main() {
	scanf("%d%d", &n, &m);
	if (n == 2 || m == 2) return puts("0"), 0;
	0 [fac] = 1;
	for (int i = 1; i <= m; i++) i[fac] = (L)(i - 1)[fac] * i % P;
	m[ifac] = pw(m[fac], P - 2);
	for (int i = m - 1; i >= 0; i--) i[ifac] = (L)(i + 1)[ifac] * (i + 1) % P;
	printf("%lld", (L)C(m, n - 1) * pw(2, n - 3) % P * (n - 2) % P);
}