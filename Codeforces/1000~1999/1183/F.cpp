#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;
int n, ans, a[N], f, x;

int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		std::sort(a + 1, a + n + 1);
		ans = a[n], f = 0, x = -1;
		for (int i = 1; i <= n; i++) {
			if (a[i] * 2 == a[n]) f |= 1;
			if (a[i] * 3 == a[n]) f |= 2;
			if (a[i] * 5 == a[n]) f |= 4;
		}
		if (f == 7) ans = std::max(ans, a[n] / 2 + a[n] / 3 + a[n] / 5);
		for (int i = n; i >= 1; i--)
			if (a[n] % a[i] && x % a[i]) {
				if (~x)
					ans = std::max(ans, a[n] + x + a[i]);
				else
					x = a[i], ans = std::max(ans, a[n] + x);
			}
		printf("%d\n", ans);
	}
}