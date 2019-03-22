#include <cctype>
#include <cstdio>

typedef long long ll;

#define int long long

int p(ll x, int y, int z) {
	int ret = 1;
	for (; y; (x *= x) %= z, y >>= 1) if (y & 1) (ret *= x) %= z;
	return ret;
}

int n, m, k, t, phi;
char ch;
bool f;

signed main() {
	scanf("%lld%lld", &n, &m);
	phi = t = m;
	for (int i = 2; i*i <= m; i++) {
		if (t % i) continue;
		phi = phi / i * (i-1);
		while (!(t % i)) t /= i;
	}
	if (t > 1) phi = phi / t * (t-1);
	while (!isdigit(ch = getchar()));
	do {
		k = k * 10 + ch - 48;
		if (k >= phi) k %= phi, f = 1;
	} while (isdigit(ch = getchar()));
	k += f * phi;
	printf("%lld", p(n, k, m));
}