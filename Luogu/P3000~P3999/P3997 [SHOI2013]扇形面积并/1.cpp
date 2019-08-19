#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <utility>

typedef long long ll;
const int M = 2e6 + 62;

struct multiset {
	__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type,
					 std::less<std::pair<int, int>>, __gnu_pbds::rb_tree_tag,
					 __gnu_pbds::tree_order_statistics_node_update>
		s;
	__gnu_pbds::gp_hash_table<int, int> mp;
	void ins(int x) { s.insert(std::make_pair(x, ++mp[x])); }
	void del(int x) { s.erase(std::make_pair(x, mp[x]--)); }
	size_t size() { return s.size(); }
} s;

std::vector<int> v[M];
int m;

void ad(int x, int l, int r) { v[l + m].push_back(x), v[r + m].push_back(-x); }

int n, k, x, l, r;
ll ans;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &x, &l, &r);
		if (l < r)
			ad(x, l, r);
		else
			ad(x, l, m), ad(x, -m, r);
	}
	for (int i = 0; i <= 2 * m; i++) {
		if (s.size() >= k) {
			int x = s.s.find_by_order(s.size() - k)->first;
			ans += 1ll * x * x;
		}
		for (int j : v[i])
			if (j > 0)
				s.ins(j);
			else
				s.del(-j);
	}
	printf("%lld", ans);
}