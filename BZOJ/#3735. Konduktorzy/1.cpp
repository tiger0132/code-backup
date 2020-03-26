#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long
#define x first
#define y second

typedef std::pair<int, int> pii;
const int N = 1e5 + 51;

int n, m, a[N];
bool check(int k) {
	int s = 0;
	for (int i = 1; i <= n; i++) s += k / a[i];
	return s > m;
}

std::priority_queue<pii, std::vector<pii>, std::greater<pii> > pq;
int l, r, ub, s, ans[N];
signed main() {
	scanf("%lld%lld", &m, &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
#define mid (l + r) / 2
	for (r = 1e18; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	ub = r;
	for (int i = 1; i <= n; i++) ub = std::min(ub, std::max(r / a[i] * a[i] - a[i], 0ll));
	for (int i = 1; i <= n; i++) {
		pq.push(pii(ub / a[i] * a[i], i));
		s += ub / a[i];
	}
	for (pii x; s < m;) {
		x = pq.top(), pq.pop();
		x.y[ans] = ++s;
		pq.push(pii(x.x + a[x.y], x.y));
	}
	for (int i = 1; i <= n; i++) printf("%lld ", i[ans]);
}