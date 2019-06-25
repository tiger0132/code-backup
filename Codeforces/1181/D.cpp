#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <tuple>
#include <utility>
#include <vector>
#define int long long

typedef std::pair<int, int> pii;
const int N = 5e5 + 55;

__gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag,
				 __gnu_pbds::tree_order_statistics_node_update>
	s;
int n, m, q, x, it = 1, cur, ls, c[N], out[N];
pii rec[N], qry[N];
signed main() {
	scanf("%I64d%I64d%I64d", &n, &m, &q);
	for (int i = 1; i <= n; c[x]++, i++) scanf("%I64d", &x);
	for (int i = 1; i <= q; i++) scanf("%I64d", &qry[i].first), qry[i].first -= n, qry[i].second = i;
	for (int i = 1; i <= m; i++) rec[i] = {c[i], i};
	std::sort(rec + 1, rec + m + 1);
	std::sort(qry + 1, qry + q + 1);
	rec[m + 1] = {2e12, 0};
	for (int l = 1, r; l <= m; l = r + 1) {
		int x = rec[l].first;
		cur += (x - ls) * s.size(), ls = x;
		for (r = l - 1; rec[r + 1].first == x;) s.insert(rec[++r].second);
		int y = rec[r + 1].first, ub = cur + (y - x) * s.size();
		if (r == m) ub = 2e18;
		for (; it <= q && qry[it].first <= ub; it++)
			out[qry[it].second] = *s.find_by_order((qry[it].first - cur + s.size() - 1) % s.size());
	}
	for (int i = 1; i <= q; i++) printf("%I64d\n", out[i]);
}