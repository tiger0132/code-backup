#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>

const int N = 3e5 + 53;

struct SAM {
	int link[N], len[N], nc, sc, last;
	std::map<int, int> tr[N];
	std::set<int> s[N];
	SAM() { nc = last = 1; }
	void ins(int c) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = p[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc, cl[len] = p[len] + 1, cl[link] = q[link], cl[tr] = q[tr];
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		cur[s].insert(sc), last = cur;
	}

	std::vector<int> g[N];
	int ans;
	void merge(std::set<int> &x, std::set<int> &y) {
		if (x.size() < y.size()) x.swap(y);
		for (int i : y) x.insert(i);
		y.clear();
	}
	void dfs(int x) {
		for (int nx : x[g]) dfs(nx), merge(x[s], nx[s]);
		if ((int)x[s].size() == sc) ans = std::max(ans, x[len]);
	}
	void solve() {
		for (int i = 2; i <= nc; i++) i[link][g].push_back(i);
		dfs(1);
		printf("%d", ans + 1);
	}
} sam;

int n, m, ans, a[N];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &m);
		for (int j = 0; j < m; j++) scanf("%d", a + j);
		for (int j = 1; j < m; j++) sam.ins(a[j] - a[j - 1]);
		sam.last = 1, sam.sc++;
	}
	sam.solve();
}