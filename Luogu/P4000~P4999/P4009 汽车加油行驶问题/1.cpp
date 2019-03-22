#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e2 + 21, K = 22, dir[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

struct node {
	int lv, x, y;
};

int dis[K][N][N], vis[K][N][N], _[N][N];
int n, k, a, b, c, ans = 0x3f3f3f3f;
std::queue<node> q;
int main() {
	scanf("%d%d%d%d%d", &n, &k, &a, &b, &c);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", _[i] + j);
		}
	}
	memset(dis, 0x3f, sizeof dis);
	q.push((node){k, 1, 1});
	dis[k][1][1] = 0;
	while (!q.empty()) {
		int lv = q.front().lv, x = q.front().x, y = q.front().y;
		vis[lv][x][y] = 0;
		q.pop();
		if (_[x][y] && lv < k) {
			if (dis[k][x][y] > dis[lv][x][y] + a) {
				dis[k][x][y] = dis[lv][x][y] + a;
				if (!vis[k][x][y]) vis[k][x][y] = 1, q.push((node){k, x, y});
			}
		} else {
			if (dis[k][x][y] > dis[lv][x][y] + a + c) {
				dis[k][x][y] = dis[lv][x][y] + a + c;
				if (!vis[k][x][y]) vis[k][x][y] = 1, q.push((node){k, x, y});
			}
			if (lv)
				for (int i = 0; i < 4; i++) {
					int nx = x + dir[i][0], ny = y + dir[i][1];
					if (nx < 1 || ny < 1 || nx > n || ny > n) continue;
					if (dis[lv - 1][nx][ny] > dis[lv][x][y] + (i > 1) * b) {
						dis[lv - 1][nx][ny] = dis[lv][x][y] + (i > 1) * b;
						if (!vis[lv - 1][nx][ny]) vis[lv - 1][nx][ny] = 1, q.push((node){lv - 1, nx, ny});
					}
				}
		}
	}
	for (int i = 0; i <= k; i++) ans = std::min(ans, dis[i][n][n]);
	printf("%d", ans);
}