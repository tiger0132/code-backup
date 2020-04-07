#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int M = 7e2 + 27, N = 4e5 + 54;

std::vector<std::vector<int> > ans;
std::map<int, int> mp;
std::vector<pii> v;
int n, x, o1, o2;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &x), mp[x]++;
	for (const auto &i : mp) v.push_back({i.second, i.first});
	std::sort(v.begin(), v.end(), std::greater<pii>());
	for (int l = 1; l * l <= n; l++) {
		int c = 0, wid;
		for (const auto &i : v) c += std::min(l, i.first);
		wid = c / l;
		if (wid < l) continue;
		if (l * wid > o1 * o2)
			o1 = l, o2 = wid;
		else
			continue;

		ans.resize(l);
		for (int i = 0; i < l; i++) ans[i].resize(wid);

		c = 0;
		for (auto i : v)
			for (int j = 0; j < std::min(l, i.first); j++) {
				ans[c % l][(c % l + c / l) % wid] = i.second;
				if (++c >= l * wid) goto end;
			}
	end:;
	}
	printf("%d\n%d %d\n", o1 * o2, o1, o2);
	for (auto &i : ans) {
		for (int &j : i) printf("%d ", j);
		puts("");
	}
}