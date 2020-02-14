#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

int n, m, c1, c2, x, nn;
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld", &n, &m);) {
		nn = n;
		n -= m, m++;
		x = n / m;
		c2 = n % m;
		c1 = m - c2;
		printf("%lld\n",
			   nn * (nn + 1) / 2 - x * (x + 1) * c1 / 2 - (x + 1) * (x + 2) * c2 / 2);
	}
}