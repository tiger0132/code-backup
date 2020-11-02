#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

int p, q;
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld", &p, &q);) {
		int ans = 0;
		if (p % q != 0) {
			printf("%lld\n", p);
			continue;
		}
		for (int i = 2; i * i <= q; i++)
			if (q % i == 0) {
				int lans = p;
				while (lans % i == 0 && lans % q == 0) lans /= i;
				ans = std::max(ans, lans);
				while (q % i == 0) q /= i;
			}
		if (q > 1) {
			while (p % q == 0) p /= q;
			ans = std::max(ans, p);
		}
		printf("%lld\n", ans);
	}
}