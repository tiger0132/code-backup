#include <algorithm>
#include <cstring>
#include <cassert>
#include <cstdio>

typedef long long ll;
const int N = 1e8+81;

int a[N], b[N], c[N];
int n, m, ans[N], p;

signed main() {
	for (int n = 1; n <= 10; n++) {
		m = 0;
		for (int i = 1; i <= n; i++) {
			a[i] = i;
		}
		do {
			memcpy(b+m+1, a+1, n<<2);
			m += n;
		} while (std::next_permutation(a+1, a+n+1));
		p = n * (n+1) / 2;
		for (int i = 1; i <= m; i++) {
			c[i] = c[i-1] + b[i];
			ans[n] += (i >= n && c[i] - c[i-n] == p);
		}
		ans[n] -= m/n;
		assert(!(ans[n] % n));
		// ans[n] /= n;
		printf("\n%d", ans[n] - ans[n-1]);
	}
}