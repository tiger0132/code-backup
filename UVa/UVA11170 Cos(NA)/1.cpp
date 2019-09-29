#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
typedef __int128_t lll;
const int N = 1e2;

ll P = 1145141919810111101;
ll pw(ll x, ll y) {
	ll r = 1;
	for (; y; y >>= 1, x = (lll)x * x % P)
		if (y & 1) r = (lll)r * x % P;
	return r;
}

ll fac[N + 5], ifac[N + 5];
ll c(int n, int m) { return (lll)fac[n] * ifac[m] % P * ifac[n - m] % P; }
ll f(int k, int n) {
	if (!k) return pw(2, n - 1);
	if (!n) return 1;
	return (lll)(n + 2 * k) * c(n + k - 1, k - 1) % P * pw(2, (n + P - 2) % (P - 1)) % P *
		   pw(k, P - 2) % P;
}
void print(int n) {
	for (int b = n, a = 0; b >= 0; b -= 2, a++) {
		ll v = f(a, b);
		if (v != 1 || !b) printf("%lld", v);
		if (!b) break;
		printf(b == 1 ? "Cos" : "Cos^%d", b);
		printf(b > 1 ? "(A)%c" : "(A)", "-+"[a % 2]);
	}
	puts("");
}

int n;
int main() {
	fac[0] = ifac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = (lll)fac[i - 1] * i % P;
	ifac[N] = pw(fac[N], P - 2);
	for (int i = N - 1; i >= 1; i--) ifac[i] = (lll)ifac[i + 1] * (i + 1) % P;
	while (scanf("%d", &n), n) print(n);
}