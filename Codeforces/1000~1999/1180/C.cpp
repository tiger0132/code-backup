#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <utility>

typedef std::pair<int, int> pii;
const int N = 1e5 + 51;

int n, m, a[N], mx, mi;
int ladd(int x, int y) { return (x + y - 1) % n + 1; }

std::deque<int> d;
long long x;
pii ans[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		d.push_back(a[i]);
		if (a[i] > mx) mx = a[i], mi = i;
	}
	for (int i = 1, x, y; i < mi; i++) {
		x = d.front(), d.pop_front();
		y = d.front(), d.pop_front();
		ans[i] = {x, y};
		if (x < y) std::swap(x, y);
		d.push_front(x), d.push_back(y);
	}
	for (int i = 1; i <= n; i++) a[i] = d.front(), d.pop_front();
	while (m--) {
		scanf("%lld", &x);
		if (x < mi)
			printf("%d %d\n", ans[x].first, ans[x].second);
		else
			printf("%d %d\n", a[1], a[2 + (x - mi) % (n - 1)]);
	}
}