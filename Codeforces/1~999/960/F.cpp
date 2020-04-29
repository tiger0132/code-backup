#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 1e5 + 51;

std::map<int, int> mp[N];
int n, x, y, z, ans;
int main() {
	scanf("%d%*d", &n);
	for (int i = 1; i <= n; i++) i[mp].insert({-1, 0});
	while (~scanf("%d%d%d", &x, &y, &z)) {
		int t = (--x[mp].lower_bound(z))->second + 1;
		ans = std::max(ans, t);

		auto it = --y[mp].upper_bound(z);
		if (it->second >= t) continue;

		it = y[mp].lower_bound(z);
		while (it != y[mp].end() && it->second <= t) {
			it = y[mp].erase(it);
		}
		y[mp][z] = std::max(y[mp][z], t);
	}
	printf("%d", ans);
}