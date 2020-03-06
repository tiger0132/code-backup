#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e7 + 71, P = 998244353, div2 = (P + 1) / 2;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}
inline void $(int& x) { x += x >> 31 & P; }

int fac[N], ifac[N];
inline int C(int n, int m) { return 1ll * n[fac] * m[ifac] % P * (n - m)[ifac] % P; }

int n, ans, cur;
int main() {
	scanf("%d", &n);
	0 [fac] = 0 [ifac] = 1;
	for (int i = 1; i <= n; i++) i[fac] = 1ll * (i - 1)[fac] * i % P;
	n[ifac] = pw(n[fac], P - 2);
	for (int i = n - 1; i; i--) i[ifac] = (i + 1)[ifac] * (i + 1ll) % P;
	ans = pw(3, n), cur = pw(2, n / 2);
	for (int i = n / 2 + 1; i <= n; i++) {
		$(ans -= 1ll * cur * C(n, i) % P);
		cur = 1ll * cur * div2 % P;
	}
	printf("%d", ans);
}