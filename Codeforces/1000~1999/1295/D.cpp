#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

int n, m, ans;
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld", &n, &m);) {
		m /= std::__gcd(n, m), ans = m;
		for (int i = 2; i * i <= m; i++)
			if (m % i == 0)
				for (ans = ans / i * (i - 1); m % i == 0;) m /= i;
		if (m > 1) ans = ans / m * (m - 1);
		printf("%lld\n", ans);
	}
}