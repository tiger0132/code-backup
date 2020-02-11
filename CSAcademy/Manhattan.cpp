#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2e5 + 52, P = 666013;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int fac[N], ifac[N];
int C(int n, int m) {
	if (m > n) return 0;
	return 1ll * n[fac] * m[ifac] % P * (n - m)[ifac] % P;
}

int x1, y1, x2, y2, x3, y3, x4, y4;
ll ans;
int main() {
	0 [fac] = 0 [ifac] = 1;
	for (int i = 1; i < N; i++) i[fac] = 1ll * (i - 1)[fac] * i % P;
	(N - 1)[ifac] = pw((N - 1)[fac], P - 2);
	for (int i = N - 1 - 1; i >= 1; i--) i[ifac] = (i + 1)[ifac] * (i + 1ll) % P;

	scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);

	if ((y1 <= y3 && y3 <= y2) || (y1 <= y4 && y4 <= y2) || (y3 <= y1 && y1 <= y4) ||
		(y3 <= y2 && y2 <= y4))
		std::swap(x1, y1), std::swap(x2, y2), std::swap(x3, y3), std::swap(x4, y4);
	if (y1 > y3)
		std::swap(x1, x3), std::swap(x2, x4), std::swap(y1, y3), std::swap(y2, y4);

	for (int k = x3 - x2; k <= x4 - x1; k++) {
		ll fk = std::min(x2 + k, x4) - std::max(x1 + k, x3) + 1;
		int p = abs(k) + 2;
		ans += fk * (C(y4 - y1 + p, p) - C(y3 - y1 - 1 + p, p) - C(y4 - y2 - 1 + p, p) +
					 C(y3 - y2 - 2 + p, p));
	}
	printf("%lld", (ans % P + P) % P);
}