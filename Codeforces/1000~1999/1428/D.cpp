#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

const int N = 1e5 + 51;

std::deque<int> v[4];
std::vector<std::tuple<std::vector<int>, int, int>> vt;
std::vector<std::pair<int, int>> pt;
int n, a[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) {
		if (a[i] == 1) {
			std::vector<int> tmp;
			int t1 = i, t2 = 0;
			if (!v[2].empty()) {
				t2 = v[2].back();
				v[2].pop_back();
			}
			while (!v[3].empty() && v[3].front() < (t2 ? t2 : t1)) {
				tmp.push_back(v[3].front());
				v[3].pop_front();
			}
			vt.push_back(std::make_tuple(tmp, t2, t1));
		} else
			v[a[i]].push_back(i);
	}
	if (v[2].size() || v[3].size()) return puts("-1"), 0;

	int cnt = 1;
	for (auto [x, y, z] : vt) {
		for (int i = 0; i < x.size(); i++) {
			pt.push_back({cnt, x[i]});
			if (i + 1 < x.size()) pt.push_back({cnt, x[i + 1]});
			cnt++;
		}
		if (y) {
			if (!x.empty()) pt.push_back({cnt - 1, y});
			pt.push_back({cnt, y});
		} else if (!x.empty())
			pt.push_back({cnt - 1, z});
		pt.push_back({cnt, z});
		cnt++;
	}
	// if (cnt > n + 1) return puts("-1"), 0;
	// if (pt.size() > 2 * n) return puts("-1"), 0;
	printf("%d\n", (int)pt.size());
	for (auto [vt, y] : pt) printf("%d %d\n", vt, y);
}