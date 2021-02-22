#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

typedef long long L;
const int N = 6e5 + 56;

void exgcd(int a, int b, int& x, int& y) {
	if (!b)
		x = 1, y = 0;
	else
		exgcd(b, a % b, y, x), y -= a / b * x;
}
int inv(int a, int m) {
	int x, y;
	exgcd(a, m, x, y);
	return (x % m + m) % m;
}

struct _ {
	int p, q, v;
	bool operator<(const _& rhs) const {
		return p < rhs.p || (p == rhs.p && (q < rhs.q || (q == rhs.q && v < rhs.v)));
	}
};

int n, m, a, b, f[N];
std::map<_, int> mp[N];
signed main() {
	scanf("%d%d", &n, &m);
	f[1] = 1;
	for (int m0 = 2; m0 <= m; m0++)
		if (m % m0 == 0)
			for (int i = 2;; i++) {
				f[i] = (f[i - 1] + f[i - 2]) % m0;
				if (f[i] == 1 && f[i - 1] == 0) break;
				int p = std::__gcd(f[i - 1], m0), q = std::__gcd(f[i], m0);
				int m1 = m0 / p / q;
				_ frac = {p, q, int((L)(f[i] / q) * inv(f[i - 1] / p, m1) % m1)};
				if (!mp[m0].count(frac)) mp[m0][frac] = i;
			}
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a, &b);
		if (!a) {
			puts("0");
			continue;
		}
		if (!b) {
			puts("1");
			continue;
		}
		int t = std::__gcd(std::__gcd(a, b), m), m0 = m / t, m1;
		a /= t, b /= t;
		int p = std::__gcd(b, m0), q = std::__gcd(a, m0);
		m1 = m0 / p / q;
		_ frac = {p, q, int((m1 - (L)(a / q) * inv(b / p, m1) % m1) % m1)};
		if (mp[m0].count(frac))
			printf("%d\n", mp[m0][frac]);
		else
			puts("-1");
	}
}