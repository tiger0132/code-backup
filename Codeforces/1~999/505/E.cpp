#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#define int long long
#define D(...) void()

const int N = 1e5 + 51;

int n, m, k, p, h[N], a[N];
struct T {
	int x, i, l;
	bool operator>(const T& r) const {
		return (x + l * p) / a[i] > (r.x + r.l * p) / a[r.i];
	}
};

bool check(int x) {
	fprintf(stderr, "mid = %lld\n", x);
	std::priority_queue<T, std::vector<T>, std::greater<T> > pq;
	for (int i = 1; i <= n; i++)
		if (x - a[i] * m < h[i]) pq.push({x, i, 0});
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < k; j++) {
			if (pq.empty()) return D("EMPTY"), true;
			T t = pq.top();
			pq.pop();
			if (t.x / a[t.i] < i) return D("NOPE"), false;
			t.x += p;
			if (t.x - a[t.i] * m < h[t.i]) pq.push(t);
		}
	return pq.empty();
}

int l, r;
signed main() {
	scanf("%lld%lld%lld%lld", &n, &m, &k, &p);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", h + i, a + i);
#define mid (l + r) / 2
	// check(16);
	for (l = 0, r = 1e18; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	printf("%lld", l);
}