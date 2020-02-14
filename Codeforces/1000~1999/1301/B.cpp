#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54;

int n, a[N], mn, mx, x, ans;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		mn = 2e9, mx = -2e9, x = 0;
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		for (int i = 2; i <= n; i++) {
			if (a[i] == -1) {
				if (a[i - 1] != -1) {
					mn = std::min(mn, a[i - 1]);
					mx = std::max(mx, a[i - 1]);
				}
			} else if (a[i - 1] == -1) {
				mn = std::min(mn, a[i]);
				mx = std::max(mx, a[i]);
			} else
				x = std::max(x, abs(a[i] - a[i - 1]));
		}
		if (mn == 2e9) mn = mx = 0;
		// printf("%d %d %d\n", mn, mx, x);
		ans = (mn + mx) / 2;
		printf("%d %d\n", std::max({abs(ans - mn), abs(ans - mx), x}), ans);
	}
}