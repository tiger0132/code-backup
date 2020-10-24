#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>
#include <utility>
#define int long long

typedef std::pair<int, int> pii;
const int N = 1e5 + 51;

std::priority_queue<pii> pq;
int n, m, a[N], cnt[N];
inline int f(int x, int c) {
	int rem = x % c, ret = 0;
	ret += (x / c) * (x / c) * (c - rem);
	ret += (x / c + 1) * (x / c + 1) * rem;
	return ret;
}

int ans;
signed main() {
	scanf("%lld%lld", &n, &m), m -= n;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a + i);
		ans += a[i] * a[i];
		cnt[i] = 1;
		pq.push({f(a[i], 1) - f(a[i], 2), i});
	}
	while (m--) {
		auto [val, i] = pq.top();
		pq.pop();
		ans -= val, cnt[i]++;
		pq.push({f(a[i], cnt[i]) - f(a[i], cnt[i] + 1), i});
	}
	printf("%lld\n", ans);
}