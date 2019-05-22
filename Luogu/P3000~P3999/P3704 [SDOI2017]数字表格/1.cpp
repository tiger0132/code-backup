#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e6 + 61, P = 1e9 + 7;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (ll)x * x % P)
		if (y & 1) r = (ll)r * x % P;
	return r;
}

int t, n, m, p[N], mu[N], fib[N], rf[N], pmul[N], cnt, ans;
bool f[N];
int main() {
	f[1] = true, mu[1] = fib[1] = rf[1] = pmul[0] = pmul[1] = 1;
	for (int i = 2; i < N; i++) {
		fib[i] = (fib[i - 1] + fib[i - 2]) % P;
		rf[i] = pw(fib[i], P - 2);
		pmul[i] = 1;
	}
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				mu[i * p[j]] = -mu[i];
			else {
				mu[i * p[j]] = 0;
				break;
			}
		}
	}
	for (int i = 1; i < N; i++) {
		if (mu[i])
			for (int j = i; j < N; j += i) pmul[j] = (ll)pmul[j] * (mu[i] == 1 ? fib[j / i] : rf[j / i]) % P;
		pmul[i] = (ll)pmul[i - 1] * pmul[i] % P;
	}
	for (scanf("%d", &t); t--;) {
		ans = 1;
		scanf("%d%d", &n, &m);
		if (n > m) std::swap(n, m);
		for (int l = 1, r; l <= n; l = r + 1) {
			r = std::min(n / (n / l), m / (m / l));
			int tmp = (ll)pmul[r] * pw(pmul[l - 1], P - 2) % P;
			ans = (ll)ans * pw(tmp, ll(n / l) * (m / l) % (P - 1)) % P;
		}
		printf("%d\n", ans);
	}
}