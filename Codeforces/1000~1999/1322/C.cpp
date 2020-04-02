#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <utility>
#include <vector>
#define x first
#define y second

typedef long long L;
const int N = 5e5 + 55;

template <typename T, int base, int mod>
struct Hash {
	int x;
	void operator+=(const T& rhs) { x = ((L)x * base + rhs) % mod; }
	bool operator<(const Hash<T, base, mod>& rhs) const { return x < rhs.x; }
};

typedef Hash<int, 13, 999999937> h1;
typedef Hash<int, 17, 999991919> h2;
typedef std::pair<h1, h2> hp;

std::vector<int> v[N];
std::map<hp, L> mp;
int n, m, x, y;
L a[N], ans;
hp tmp;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);) {
		for (int i = 1; i <= n; i++) scanf("%lld", a + i);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &x, &y);
			v[y].push_back(x);
		}
		for (int i = 1; i <= n; i++) {
			std::sort(v[i].begin(), v[i].end());
			tmp.x.x = tmp.y.x = 0;
			for (int j : v[i]) tmp.x += j, tmp.y += j;
			if (tmp.x.x || tmp.y.x) mp[tmp] += a[i];
		}
		for (auto& i : mp) ans = std::__gcd(ans, i.second);
		printf("%lld\n", ans);

		for (int i = 1; i <= n; i++) v[i].clear();
		mp.clear();
		ans = 0;
	}
}