#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

struct $ {
	int x, y, id;
	bool operator<(const $& rhs) const { return x < rhs.x; }
} a[N];

int n, m, p = 1, l[N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].y), a[i].id = i;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].x);
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) l[a[i].id] = i;
	while (m--) {
		long long ans = 0;
		int x, y;
		scanf("%d%d", &x, &y);
		int t1 = std::min(a[l[x]].y, y);
		ans += 1ll * a[l[x]].x * t1;
		a[l[x]].y -= t1;
		y -= t1;
		while (y && p <= n) {
			int tmp = std::min(a[p].y, y);
			a[p].y -= tmp;
			y -= tmp;
			ans += 1ll * a[p].x * tmp;
			if (!a[p].y) p++;
		}
		if (p > n && y)
			puts("0");
		else
			printf("%lld\n", ans);
	}
}