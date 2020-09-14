#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 77, M = 1e7;

std::vector<int> v;
int n, a, b, g[N][N];
bool vis[N];
int dfs(int x) {
	x[vis] = true;
	v.push_back(x);
	int r = 1;
	for (int nx = 1; nx <= n; nx++)
		if (g[x][nx] == a && !nx[vis]) r += dfs(nx);
	return r;
}

#define id(x, y) ((x)*n + (y)-1)

std::priority_queue<pii> pq;
int m, c1, c2, col[N], dis[M];
int main() {
	scanf("%d%d%d%d", &n, &m, &a, &b), c2 = n;
	for (int i = 1, x, y, z; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		g[x][y] = g[y][x] = z;
	}
	for (int i = 1; i <= n; i++, v.clear())
		if (!vis[i]) {
			int sz = dfs(i);
			if (sz > 3) {
				c1++;
				for (int j : v) j[col] = c1;
			} else {
				c2++;
				for (int j : v) j[col] = c2;
			}
		}

	memset(dis, 0x3f, sizeof dis);
	for (pq.push(pii(0, id(0, 1))), dis[id(0, 1)] = 0; !pq.empty();) {
		int x = pq.top().second, y = -pq.top().first;
		int S = x / n, cur = x % n + 1;
		pq.pop();
		if (x[dis] < y) continue;
		for (int nx = 1; nx <= n; nx++)
			if (g[cur][nx]) {
				if (nx[col] <= c1 && ((S >> (nx[col] - 1)) & 1)) continue;
				if (cur[col] == nx[col] && g[cur][nx] == b) continue;

				int nx_state;
				if (cur[col] <= c1 && nx[col] != cur[col])
					nx_state = id(S | (1 << (cur[col] - 1)), nx);
				else
					nx_state = id(S, nx);

				if (nx_state[dis] > x[dis] + g[cur][nx]) {
					nx_state[dis] = x[dis] + g[cur][nx];
					pq.push(pii(-nx_state[dis], nx_state));
				}
			}
	}
	for (int i = 1; i <= n; i++) {
		int ans = 2e9;
		for (int S = 0; S < (1 << c1); S++) ans = std::min(ans, id(S, i)[dis]);
		printf("%d%c", ans, " \n"[i == n]);
	}
}