#include <algorithm>
#include <cstdio>

typedef long long ll;
const int N = 1e3+31, M = 64;

struct $ {
	ll x; int y;
	bool operator<(const $& rhs) const {
		return y > rhs.y;
	}
} a[N];

ll lb[M];
bool ins(ll x) {
	for (ll i = M-1; ~i; i--) {
		if (1 & ~(x >> i)) continue;
		if (!lb[i]) return (lb[i] = x), 1;
		x ^= lb[i];
	}
	return 0;
}

int n, ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%d", &a[i].x, &a[i].y);
	}
	std::sort(a+1, a+n+1);
	for (int i = 1; i <= n; i++) {
		ans += ins(a[i].x) * a[i].y;
	}
	printf("%d", ans);
}