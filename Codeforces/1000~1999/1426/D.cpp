#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#define int long long

typedef std::pair<int, int> pii;
const int N = 2e5 + 52;

std::map<int, int> last;
std::vector<pii> v;
int n, a[N];
signed main() {
	scanf("%lld", &n);
	last[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a + i);
		a[i] += a[i - 1];
		if (last.count(a[i])) v.push_back({4 * (last[a[i]] + 1) + 1, 4 * i - 1});
		last[a[i]] = i;
	}
	std::sort(v.begin(), v.end(), [](pii &x, pii &y) {
		return x.second < y.second || (x.second == y.second && x.first > y.first);
	});

	int mk = -1, ans = 0;
	for (auto i : v) {
		if (mk >= i.first && mk <= i.second) continue;
		ans++;
		mk = i.second;
	}
	printf("%lld\n", ans);
}