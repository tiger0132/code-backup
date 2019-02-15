#include <algorithm>
#include <cstdio>
#include <cstring>

using ll = long long;
const int N = 5e4 + 45;

struct node {
	ll x, y;
	inline bool operator<(const node& rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
} a[N], b[N];

int n, p, l, r, q[N];
ll dp[N];
inline double slope(int x, int y) { return 1. * (dp[x] - dp[y]) / (b[y + 1].y - b[x + 1].y); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].y, &a[i].x);
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		while (p && b[p].y <= a[i].y) p--;
		b[++p] = a[i];
	}
	for (int i = 1; i <= p; i++) {
		while (l < r && slope(q[l + 1], q[l]) < b[i].x) l++;
		dp[i] = dp[q[l]] + b[i].x * b[q[l] + 1].y;
		while (l < r && slope(q[r], q[r - 1]) > slope(i, q[r])) r--;
		q[++r] = i;
	}
	printf("%lld", dp[p]);
}