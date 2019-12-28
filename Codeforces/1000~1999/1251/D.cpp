#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = 2e5 + 52;

struct node {
	int l, r;
} a[N];
int n, m, l, r, id[N];
ll s;
bool check(int x) {
	int cnt = 0, k = 0;
	ll ret = 0;
	for (int i = 1; i <= n; i++)
		if (a[i].r < x || x < a[i].l) {
			ret += a[i].l;
			if (a[i].r < x) cnt++;
		} else
			id[++k] = i;
	for (int i = 1; i <= k; i++)
		if (cnt < m - 1)
			cnt++, ret += a[id[i]].l;
		else
			ret += x;
	return ret <= s;
}
int main() {
	for (scanf("%*d"); ~scanf("%d%lld", &n, &s);) {
		m = (n + 1) / 2;
		for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
		std::sort(a + 1, a + n + 1,
				  [](const node& x, const node& y) { return x.r < y.r; });
		r = a[m].r;
		std::sort(a + 1, a + n + 1,
				  [](const node& x, const node& y) { return x.l < y.l; });
		l = a[m].l;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (check(mid))
				l = mid + 1;
			else
				r = mid - 1;
		}
		printf("%d\n", l - 1);
	}
}