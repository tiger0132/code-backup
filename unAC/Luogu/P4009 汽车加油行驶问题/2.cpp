#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 3e5 + 53, M = 1e6 + 61, K = 1e2 + 21, dir[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) { e[++cnt] = (edge){y, head[x], z}, head[x] = cnt; }

int n, k, a, b, c;
inline int id(int lv, int x, int y) { return (lv * n + x - 1) * n + y; }
int dis[N], vis[N], _[K][K], mn;
std::queue<int> q;
int main() {
	scanf("%d%d%d%d%d", &n, &k, &a, &b, &c);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", _[i] + j);
		}
	}
	for (int lv = k; lv >= 0; lv--) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (_[i][j] && lv < k)
					addedge(id(lv, i, j), id(k, i, j), a);
				else
					addedge(id(lv, i, j), id(k, i, j), a + c);
				for (int p = 0; p < 4; p++) {
					int nx = i + dir[p][0], ny = j + dir[p][1];
					if (std::min(nx, ny) < 1 || std::max(nx, ny) > n) continue;
					if (lv) addedge(id(lv, i, j), id(lv - 1, nx, ny), (p > 1) * b);
				}
			}
		}
	}
	memset(dis, 0x3f, sizeof dis);
	dis[id(k, 1, 1)] = 0;
	q.push(id(k, 1, 1));
	while (!q.empty()) {
		int pos = q.front();
		vis[pos] = 0;
		q.pop();
		for (int i = head[pos]; i; i = e[i].next) {
			int nx = e[i].to;
			if (dis[nx] > dis[pos] + e[i].w) {
				dis[nx] = dis[pos] + e[i].w;
				if (!vis[nx]) {
					vis[nx] = 1;
					q.push(nx);
				}
			}
		}
	}
	mn = 0x3f3f3f3f;
	for (int i = 0; i <= k; i++) {
		mn = std::min(mn, dis[id(i, n, n)]);
	}
	printf("%d", mn);
}