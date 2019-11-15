#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef long long ll;
const int N = 1e5 + 51, M = 1e6 + 61;

struct {
	ll a[M];
	void add(int i, int x) {
		for (i++; i < M; i += i & -i) a[i] += x;
	}
	ll qry(int i) {
		ll r = 0;
		for (i++; i; i -= i & -i) r += a[i];
		return r;
	}
} A, B;

__gnu_pbds::tree<ll, __gnu_pbds::null_type, std::less<ll>, __gnu_pbds::rb_tree_tag,
				 __gnu_pbds::tree_order_statistics_node_update>
	s;
int n, k, a[N], mi, val;
ll ans, sum;
ll pack(int i) { return 1ll * a[i] * N + i; }
int main() {
	scanf("%d%d", &n, &k), ans = 1e18;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		s.insert(pack(i));
		sum += a[i];
		A.add(a[i], a[i]), B.add(a[i], 1);
		if (i >= k) {
			int v = *s.find_by_order((k - 1) / 2) / N;
			ll p = B.qry(v - 1), q = A.qry(v - 1);
			ll cur = p * v - q + (sum - q) - (k - p) * v;
			if (cur < ans) ans = cur, mi = i, val = v;
			s.erase(pack(i - k + 1));
			sum -= a[i - k + 1];
			A.add(a[i - k + 1], -a[i - k + 1]), B.add(a[i - k + 1], -1);
		}
	}
	for (int i = mi - k + 1; i <= mi; i++) a[i] = val;
	printf("%lld\n", ans);
	for (int i = 1; i <= n; i++) printf("%d\n", a[i]);
}