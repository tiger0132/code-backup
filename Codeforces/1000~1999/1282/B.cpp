#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, p, k, ans, s0, cur, lans, a[N];
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &p, &k);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		std::sort(a + 1, a + n + 1);
		ans = s0 = 0;
		for (int i = 0; i < k; i++) {
			cur = s0 += a[i];
			if (cur > p) break;
			lans = i;
			for (int j = i + k; j <= n; j += k)
				if (cur + a[j] <= p) cur += a[j], lans += k;
			ans = std::max(ans, lans);
		}
		printf("%d\n", ans);
	}
}