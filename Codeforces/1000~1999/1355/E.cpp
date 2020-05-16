#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long
#define mid (l + r) / 2

const int N = 1e5 + 51;

int n, A, R, M, h[N];
int chk(int k) {
	int lo = 0, hi = 0, p1, p2;
	for (int i = 1; i <= n; i++) {
		if (h[i] < k) lo += k - h[i];
		if (h[i] > k) hi += h[i] - k;
	}
	p1 = lo * A + hi * R;
	if (lo < hi)
		p2 = lo * M + (hi - lo) * R;
	else
		p2 = hi * M + (lo - hi) * A;
	return std::min(p1, p2);
}

int l, r, ans = 1e18;
signed main() {
	scanf("%lld%lld%lld%lld", &n, &A, &R, &M);
	for (int i = 1; i <= n; i++) scanf("%lld", h + i), r = std::max(r, h[i]);
	while (r - l > 10)
		if (chk(mid) < chk(mid + 1))
			r = mid + 1;
		else
			l = mid;
	for (int i = l; i <= r; i++) ans = std::min(ans, chk(i));
	printf("%lld", ans);
}