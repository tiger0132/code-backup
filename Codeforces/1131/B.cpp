#include <algorithm>
#include <cstdio>
#include <cstring>

int n, x, y, lx, ly, ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
		int u = std::min(x, y), v = std::max(lx, ly);
		if (lx != ly)
			ans += std::max(u - v + 1, 0);
		else
			ans += std::max(0, u - v);
		lx = x, ly = y;
	}
	printf("%d", ans + 1);
}