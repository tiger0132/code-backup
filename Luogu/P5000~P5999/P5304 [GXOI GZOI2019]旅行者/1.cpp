#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 1e5 + 51, M = 5e5 + 55;

struct node {
	int x, d;
	bool operator<(const node& rhs) const { return d > rhs.d; }
};
struct graph {
	std::vector<pii> g[N];
	int n, dis[N], from[N];

	void operator()(int x, int y, int z) { x[g].push_back({y, z}); }
	void init(int nn) {
		n = nn;
		for (int i = 1; i <= n; i++) i[g].clear();
	}
	void spfa(const std::vector<int>& sv) {
		std::priority_queue<node> pq;
		memset(dis + 1, 0x3f, n * 4);
		for (int i : sv) i[dis] = 0, i[from] = i, pq.push({i, 0});
		while (!pq.empty()) {
			auto [x, d] = pq.top();
			pq.pop();
			if (d != x[dis]) continue;
			for (auto [nx, w] : x[g])
				if (nx[dis] > x[dis] + w)
					nx[from] = x[from], nx[dis] = x[dis] + w, pq.push({nx, nx[dis]});
		}
	}
} g, gr;

int n, m, k, x[M], y[M], z[M], w;
std::vector<int> v;
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &m, &k);) {
		g.init(n), gr.init(n);
		for (int i = 1; i <= m; i++) {
			scanf("%d%d%d", x + i, y + i, z + i);
			g(x[i], y[i], z[i]), gr(y[i], x[i], z[i]);
		}
		v.clear();
		while (k--) scanf("%d", &w), v.push_back(w);
		g.spfa(v), gr.spfa(v);
		int ans = 1e9;
		for (int i = 1; i <= m; i++)
			if (x[i][g.from] != y[i][gr.from])
				ans = std::min(ans, x[i][g.dis] + y[i][gr.dis] + z[i]);
		printf("%d\n", ans);
	}
}