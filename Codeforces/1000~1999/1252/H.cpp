#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#define x first
#define y second

typedef std::pair<int, int> pii;
typedef long long ll;
const int N = 1e5 + 51;

int n, x, y, mx;
pii a[N];
ll ans;

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &x, &y), a[i] = {std::min(x, y), std::max(x, y)};
	std::sort(a + 1, a + n + 1);
	ans = 1ll * a[n].x * a[n].y, mx = a[n].y;
	for (int i = n - 1; i >= 1; i--) {
		ans = std::max({ans, 1ll * a[i].x * a[i].y, 2ll * a[i].x * std::min(mx, a[i].y)});
		mx = std::max(mx, a[i].y);
	}
	printf("%lld.%lld", ans / 2, ans % 2 * 5);
}