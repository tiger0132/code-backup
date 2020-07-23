#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 1e5 + 51;

std::vector<int> v[N];
struct cmp {
	bool operator()(int x, int y) const { return x[v].size() < y[v].size(); }
};

std::priority_queue<int, std::vector<int>, cmp> pq((cmp()));
int n, x, y, a[N], b[N];
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &x, &y);) {
		y -= x;
		int bad;
		for (int i = 1; i <= n; i++) {
			scanf("%d", a + i), a[i][v].push_back(i);
		}
		for (int i = 1; i <= n + 1; i++) {
			pq.push(i);
			if (i[v].empty()) bad = i;
		}
		for (int i = 1, id; i <= x; i++) {
			id = pq.top(), pq.pop();
			id[v].back()[b] = id;
			id[v].pop_back();
			pq.push(id);
		}

		std::vector<pii> idx;
		int cnt1 = pq.top()[v].size();
		for (int id; !pq.empty();) {
			id = pq.top(), pq.pop();
			for (int j : id[v]) idx.push_back({id, j});
		}

		int siz = idx.size();
		int rem = n - x - y;
		if (y > 2 * (n - x) - 2 * cnt1) {
			puts("NO");
			goto end;
		}
		for (int j = 0; j < siz; j++) idx[j].second[b] = idx[(j + cnt1) % siz].first;

		for (int j = 0; j < siz; j++)
			if (idx[j].second[b] == idx[j].second[a]) idx[j].second[b] = bad, rem--;
		for (int j = 0; rem; j++)
			if (idx[j].second[b] != bad) idx[j].second[b] = bad, rem--;

		puts("YES");
		for (int i = 1; i <= n; i++) printf("%d%c", b[i], " \n"[i == n]), b[i] = 0;
	end:
		for (int i = 1; i <= n + 1; i++) i[v].clear();
	}
}