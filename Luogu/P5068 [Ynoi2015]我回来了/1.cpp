#include <utility>
#include <vector>
#include <bitset>
#include <cstdio>
#include <queue>

const int N = 1e3+31, M = 1e5+51;

typedef std::pair<int, int> pii;

std::vector<int> gph[N];
void addedge(int x, int y) {
	gph[x].push_back(y);
	gph[y].push_back(x);
}

std::bitset<N> p[N][N], ans;
int n, m, q, k, x, y;
std::queue<pii> bfs;
int mdis[N];
int vis[N];

int main() {
	for (scanf("%d%d%d", &n, &m, &q); m--; ) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	for (int i = 1; i <= n; i++) {
		int last = 0;
		bfs.push(pii(i, 0));
		vis[i] = i;
		while (!bfs.empty()) {
			int pos = bfs.front().first;
			int dis = bfs.front().second;
			bfs.pop();
			if (dis > last) {
				p[i][dis] = p[i][last];
				last = dis;
			}
			p[i][dis][pos] = 1;
			// printf("%d -- %d (%d)\n", i, pos, dis);
			for (int j = 0; j < gph[pos].size(); j++) {
				int nx = gph[pos][j];
				if (vis[nx] == i) continue;
				vis[nx] = i;
				bfs.push(pii(nx, dis+1));
			}
		}
		mdis[i] = last;
	}
	while (q--) {
		ans.reset();
		for (scanf("%d", &k); k--; ) {
			scanf("%d%d", &x, &y);
			y = std::min(y, mdis[x]);
			ans |= p[x][y];
		}
		printf("%lu\n", ans.count());
	}
}